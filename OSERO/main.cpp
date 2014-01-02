#include <DxLib.h>
#include "global.h"
#include "Board.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ) {
	//ChangeWindowMode(TRUE);
	SetGraphMode(Board::SIZE * Board::WIDTH, Board::SIZE * Board::WIDTH, 32);
	SetOutApplicationLogValidFlag(FALSE);
	SetMainWindowText("TitleBar");
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	Load("dat/cell.png", "cell");
	Load("dat/light_cell.png", "light_cell");
	Load("dat/white.png", "white");
	Load("dat/black.png", "black");

	Board* board = new Board();

	while (ProcessMessage() == 0) {
		InputUpdate();
		ClearDrawScreen();

		board->Update();
		board->Draw();

		ScreenFlip();
		if (GetKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	delete board;

	DxLib_End();
	return 0;
}
