#include <DxLib.h>
#include <string>
#include "Board.h"
#include "global.h"

Board::Board() {
}

void Board::Init() {
	turn = BLACK;
	gameover = false;
	blackCnt = 2;
	whiteCnt = 2;
	//printState();
	for (int i = 0; i < HEIGHT; i++) for (int j = 0; j < HEIGHT; j++) state[i][j] = NONE;
	int p = WIDTH/2 - 1;
	state[p][p] = state[p+1][p+1] = WHITE;
	state[p][p+1] = state[p+1][p] = BLACK;
	searchTurn();
}

void Board::Update() {
	int x, y;
	GetMousePoint(&x, &y);
	int tx = x/SIZE;
	int ty = y/SIZE;

	if (!onBoard(tx, ty)) return;

	if (GetMouse() == 1) {

		if (gameover) {
			clsDx();
			Init();
			return;
		}

		//put(tx, ty, turn);
		//turnChange();

		//ひっくり返せ!
		auto vec = flipCheck(turn, tx, ty);
		if (!vec.empty()) {
			put(tx, ty, turn);
			for (auto& it: vec) {
				put(it.x, it.y, turn);
			}
			turnChange();
			updateCnt();
			clsDx();
			//printState();
			searchTurn();
			PlaySoundMem(GetHandle("click_se"), DX_PLAYTYPE_BACK);
			if (pos.empty()) {
				//printfDx("\n");
				turnChange();
				searchTurn();
				if (pos.empty()) {
					//ゲームオーバー
					printfDx("ゲーム終了 %sの勝ち\nクリックでリトライ", blackCnt > whiteCnt ? "くろ" : "しろ");
					gameover = true;
				} else {
					printfDx("%sパス", turn == WHITE ? "くろ" : "しろ");
				}
			}
		}
	}

	pos2 = flipCheck(turn, tx, ty);
	if (!pos2.empty()) pos2.push_back(Point(tx, ty));
}

void Board::Draw() {
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			DrawGraph(SIZE * x, SIZE * y, GetHandle("cell"), false);
			if (state[y][x] == BLACK) DrawGraph(SIZE * x, SIZE * y, GetHandle("black"), true);
			else if (state[y][x] == WHITE) DrawGraph(SIZE * x, SIZE * y, GetHandle("white"), true);
		}
	}

	if (!pos.empty()) {
		for (auto& it: pos) {
			DrawGraph(SIZE * it.x, SIZE * it.y, GetHandle("light_cell"), false);
		}
	}

	if (!pos2.empty()) {
		for (auto& it: pos2) {
			int handle;
			if (turn == BLACK) handle = GetHandle("black");
			else handle = GetHandle("white");
			DrawGraph(SIZE * it.x, SIZE * it.y, handle, true);
		}
	}

	//右のステータス
	DrawString(SIZE * WIDTH + 10, 10, "BLACK", GetColor(255,255,255));
}

bool Board::onBoard(int x, int y) {
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return false;
	return true;
}

void Board::turnChange() {
	if (turn == BLACK) turn = WHITE;
	else turn = BLACK;
}

void Board::put(int x, int y, State color) {
	state[y][x] = color;
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

std::vector<Point> Board::flipCheck(State color, int x, int y) {
	std::vector<Point> vec;
	if (state[y][x] == NONE) {
		for (int dy = -1; dy < 2; dy++) {
			for (int dx = -1; dx < 2; dx++) {
				auto vec2 = flipCheck2(color, x, y, dx, dy);
				if (!vec2.empty()) vec.insert(vec.begin(), vec2.begin(), vec2.end());
			}
		}
	}
	return vec;
}

std::vector<Point> Board::flipCheck2(State color, int x, int y, int dx, int dy)
{
	std::vector<Point> vec;
	while(true) {
		x += dx;
		y += dy;

		if (!onBoard(x, y) || state[y][x] == NONE) {
			vec.clear();
			break;
		}
		if (state[y][x] == color) break;
		vec.push_back(Point(x, y));
	}
	return vec;
}

void Board::searchTurn() {
	pos.clear();
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			auto t = flipCheck(turn, x, y);
			if (!t.empty()) pos.push_back(Point(x, y));
		}
	}
}

void Board::printState() {
	std::string s;
	if (turn == BLACK) s = "くろ";
	else s = "しろ";
	printfDx("black:%d white:%d\n%sのターン", blackCnt, whiteCnt, s.c_str());
}
