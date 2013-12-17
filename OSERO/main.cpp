#include <DxLib.h>
#include "Game.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ) {
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetMainWindowText("TitleBar");
	SetDrawScreen(DX_SCREEN_BACK);
	//Game* game = new Game();

	while(ProcessMessage() == 0) {
		//game->Update();
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}

	//delete game;
	DxLib_End();
	return 0;
}
