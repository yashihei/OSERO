#include <DxLib.h>
#include "Board.h"
#include "global.h"

Board::Board() {
	turn = BLACK;
	blackCnt = 2;
	whiteCnt = 2;
	for (int i = 0; i < HEIGHT; i++) for (int j = 0; j < HEIGHT; j++) state[i][j] = NONE;
	state[3][3] = state[4][4] = WHITE;
	state[3][4] = state[4][3] = BLACK;
}

void Board::Update() {
	if (GetMouse() == 1) {
		int x, y;
		GetMousePoint(&x, &y);

		int tx = x/SIZE;
		int ty = y/SIZE;

		if (!onBoard(tx, ty)) return;
		put(tx, ty, turn);
		turnChange();
		updateCnt();
		clsDx();
		printfDx("black:%d white:%d", blackCnt, whiteCnt);

		if (onBoard(tx, ty) && state[tx][ty] == NONE) {
			//8•ûŒü’Tõ
			for (int dy = -1; dy < 2; dy++) {
				for (int dx = -1; dx < 2; dx++) {
					if (dy == dx) continue;
					int x = dx, y = dy;
					while(true) {
						if (!onBoard(x, y) || state[x][y] == turn) break;
						//’Tõ‰ÓŠ‚ðŽŸ‚É
						x += dx;
						y += dy;
					}
				}
			}
		}
	}
}

void Board::Draw() {
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			DrawGraph(SIZE * x, SIZE * y, GetHandle("cell"), false);
			if (state[x][y] == BLACK) DrawGraph(SIZE * x, SIZE * y, GetHandle("black"), true);
			else if (state[x][y] == WHITE) DrawGraph(SIZE * x, SIZE * y, GetHandle("white"), true);
		}
	}
}

bool Board::onBoard(int x, int y) {
	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT) return false;
	return true;
}

void Board::turnChange() {
	if (turn == BLACK) turn = WHITE;
	else turn = BLACK;
}

void Board::put(int x, int y, State color) {
	state[x][y] = color;
}

void Board::updateCnt() {
	blackCnt = whiteCnt = 0;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (state[y][x] == WHITE) whiteCnt++;
			else if (state[y][x] == BLACK) blackCnt++;
		}
	}
}
