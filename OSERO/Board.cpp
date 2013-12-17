#include <DxLib.h>
#include "Board.h"
#include "global.h"

Board::Board() {
	turn = 0;
	//memset(state, NONE, WIDTH * HEIGHT);
	for (int i = 0; i < HEIGHT; i++) for (int j = 0; j < HEIGHT; j++) state[i][j] = NONE;
	state[3][3] = state[4][4] = WHITE;
	state[3][4] = state[4][3] = BLACK;
}

void Board::Update() {
	if (GetMouse() == 1) {
		int x, y;
		GetMousePoint(&x, &y);

		int xPos = y/SIZE;
		int yPos = x/SIZE;
		
		//‹²‚ß‚éÎ‚ª‚ ‚ê‚Î

		if (state[xPos][yPos] == NONE && xPos < WIDTH && yPos < HEIGHT) {
			if (turn % 2 == 0) state[xPos][yPos] = WHITE;
			else state[xPos][yPos] = BLACK;
			turn++;
		}
	}
	
	//•`‰æ
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			DrawGraph(SIZE * j, SIZE * i, GetHandle("cell"), false);
			if (state[i][j] == BLACK) DrawGraph(SIZE * j, SIZE * i, GetHandle("black"), true);
			else if (state[i][j] == WHITE) DrawGraph(SIZE * j, SIZE * i, GetHandle("white"), true);
		}
	}
}

void Board::flipCheck() {
}