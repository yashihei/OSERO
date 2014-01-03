#include <DxLib.h>
#include "global.h"
#include "Board.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ) {
	//ChangeWindowMode(TRUE);
	SetGraphMode(Board::SIZE * Board::WIDTH + 150, Board::SIZE * Board::WIDTH, 32);
	SetOutApplicationLogValidFlag(FALSE);
	SetMainWindowText("OSERO");
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	Load("dat/cell.png", "cell");
	Load("dat/light_cell.png", "light_cell");
	//Load("dat/yello_cell.png", "yello_cell");
	Load("dat/white.png", "white");
	Load("dat/black.png", "black");
	Load("dat/on11.wav", "click_se");

	//フォント読み込み
	const char* font_path = "dat/BMmini.TTF";
	AddFontResourceEx(font_path, FR_PRIVATE, NULL);
	ChangeFont("BM mini", DX_CHARSET_DEFAULT);//多分これしか使わない
	SetFontSize(18);

	Board* board = new Board();
	board->Init();

	while (ProcessMessage() == 0) {
		InputUpdate();
		ClearDrawScreen();

		board->Update();
		board->Draw();

		ScreenFlip();
		if (GetKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	delete board;
	RemoveFontResourceEx(font_path, FR_PRIVATE, NULL);

	DxLib_End();
	return 0;
}
