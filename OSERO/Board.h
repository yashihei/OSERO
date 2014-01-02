#pragma once
#include <vector>

struct Point {
	int x, y;
	Point(int x, int y) { this->x = x, this->y = y; }
};

class Board {
public:
	Board();

	void Update();
	void Draw();

	static const int HEIGHT = 20;
	static const int WIDTH = 20;
	static const int SIZE = 30;

private:
	enum State : int {
		NONE,
		BLACK,
		WHITE,
	};

	State state[HEIGHT][WIDTH];
	State turn;
	int blackCnt;
	int whiteCnt;
	std::vector<Point> pos;

private:
	void turnChange();
	bool onBoard(int x, int y);
	void put(int x, int y, State color);
	void updateCnt();
	std::vector<Point> flipCheck(int x, int y);
	std::vector<Point> flipCheck2(int x, int y, int dx, int dy);
	void searchTurn();
};