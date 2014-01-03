#pragma once
#include <vector>
#include <array>

struct Point {
	int x, y;
	Point(int x, int y) { this->x = x, this->y = y; }
};

class Board {
public:
	Board();

	void Init();
	void Update();
	void Draw();

	static const int HEIGHT = 8;
	static const int WIDTH = 8;
	static const int SIZE = 30;

private:
	enum State : int {
		NONE,
		BLACK,
		WHITE,
	};

	enum Seq : int {
		PLAY,
		PASS,
		GAMEOVER
	};

	//State state[HEIGHT][WIDTH];
	std::array<std::array<State, WIDTH>, HEIGHT> state;
	State turn;
	int blackCnt;
	int whiteCnt;
	std::vector<Point> pos;//‚¨‚¯‚éêŠŠi”[æ
	std::vector<Point> pos2;//‚Ğ‚Á‚­‚è•Ô‚¹‚éêŠŠi”[æ
	Seq seq;
	int posX, posY;

private:
	void turnChange();
	bool onBoard(int x, int y);
	void put(int x, int y, State color);
	void updateCnt();
	std::vector<Point> flipCheck(State color, int x, int y);
	std::vector<Point> flipCheck2(State color, int x, int y, int dx, int dy);
	void searchTurn();//’u‚¯‚éêŠ‚ğ’T‚·
	void printState();
};