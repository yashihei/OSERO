#include <DxLib.h>
#include "global.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ) {
	ChangeWindowMode(TRUE);
	SetOutApplicationLogValidFlag(FALSE);
	SetMainWindowText("TitleBar");
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	Load("dat/cell.png", "cell");
	Load("dat/white.png", "white");
	Load("dat/black.png", "black");

	//égÇ§ïœêîÇ±Ç±ÇÁÇ…Ç©Ç¢ÇƒÇ±Å[
	const int HEIGHT = 8;
	const int WIDTH = 8;
	const int SIZE = 30;

	enum {
		NONE,
		BLACK,
		WHITE,
	} state[HEIGHT][WIDTH] = {};//={}Ç≈è]Ç¡ÇøÇ·Ç§C++ÇÃenumÇøÇ·ÇÒâ¬à§Ç¢ÅI

	state[3][3] = state[4][4] = WHITE;
	state[3][4] = state[4][3] = BLACK;

	while(ProcessMessage() == 0) {
		InputUpdate();
		ClearDrawScreen();
		//clsDx();
		
		//ï`âÊ
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				DrawGraph(SIZE * j, SIZE * i, GetHandle("cell"), false);
				if (state[i][j] == BLACK) DrawGraph(SIZE * j, SIZE * i, GetHandle("black"), true);
				else if (state[i][j] == WHITE) DrawGraph(SIZE * j, SIZE * i, GetHandle("white"), true);
			}
		}

		ScreenFlip();
		if (GetKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	DxLib_End();
	return 0;
}
