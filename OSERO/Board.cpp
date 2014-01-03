#include <DxLib.h>
#include <string>
#include "Board.h"
#include "global.h"

Board::Board() {
}

void Board::Init() {
	turn = BLACK;
	seq = PLAY;
	blackCnt = 2;
	whiteCnt = 2;
	for (int i = 0; i < HEIGHT; i++) for (int j = 0; j < HEIGHT; j++) state[i][j] = NONE;
	int p = WIDTH/2 - 1;
	state[p][p] = state[p+1][p+1] = WHITE;
	state[p][p+1] = state[p+1][p] = BLACK;
	searchTurn();
}

void Board::Update() {
	GetMousePoint(&posX, &posY);
	int tx = posX/SIZE;
	int ty = posY/SIZE;

	pos2.clear();
	if (!onBoard(tx, ty)) return;

	if (GetMouse() == 1) {

		if (seq == GAMEOVER) {
			Init();
			return;
		}

		//ひっくり返せ!
		auto vec = flipCheck(turn, tx, ty);
		if (!vec.empty()) {
			if (seq == PASS) seq = PLAY;
			put(tx, ty, turn);
			for (auto& it: vec) {
				put(it.x, it.y, turn);
			}
			turnChange();
			updateCnt();
			searchTurn();
			PlaySoundMem(GetHandle("click_se"), DX_PLAYTYPE_BACK);
			if (pos.empty()) {
				turnChange();//パスだから次に進める
				searchTurn();
				if (pos.empty()) {
					seq = GAMEOVER;
					PlaySoundMem(GetHandle("clap_se"), DX_PLAYTYPE_BACK);
				} else {
					seq = PASS;
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
	printState();
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
	if (turn == BLACK) s = "BLACK";
	else s = "WHITE";
	s = "TURN:" + s;
	const int X = SIZE * WIDTH + 10;
	const int WHITE = GetColor(255,255,255);
	int font_size = 18;

	s = "BLACK:" + IntToString(blackCnt);
	DrawString(X, 10, s.c_str(), WHITE);
	s = "WHITE:" + IntToString(whiteCnt);
	DrawString(X, font_size + 10, s.c_str(), WHITE);

	if (seq == GAMEOVER) {
		if (blackCnt > whiteCnt) s = "BLACK";
		else s = "WHITE";
		s += " WIN";
		DrawString(X, font_size* 2 + 10, s.c_str(), WHITE);
	}
	if (seq == PASS) {
		if (turn == State::WHITE) s = "BLACK";
		else s = "WHITE";
		s += " PASS";
		DrawString(X, font_size* 2 + 10, s.c_str(), WHITE);
	}

	int c = WHITE;
	if (posX > X && posY > SIZE*HEIGHT - font_size - 10) {
		c = GetColor(255, 0, 0);
		if (GetMouse() == 1) Init();//ここにこれが入るの泣きたい
	}
	DrawString(X, SIZE*HEIGHT - font_size - 10, "RESTART", c);
}
