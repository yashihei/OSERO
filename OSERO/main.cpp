#include <DxLib.h>
#include "Game.h"
#include "global.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ) {
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetMainWindowText("TitleBar");
	SetDrawScreen(DX_SCREEN_BACK);
	Game* game = new Game();

	while(ProcessMessage() == 0) {
		game->Update();
		if (GetKey(KEY_INPUT_ESCAPE) > 0) break;
	}

	delete game;
	DxLib_End();
	return 0;
}
