#pragma once
#include <array>

class Board {
	static const int HEIGHT = 8;
	static const int WIDTH = 8;
	static const int SIZE = 30;

	enum State : int {
		NONE,
		BLACK,
		WHITE,
	};

	State state[HEIGHT][WIDTH];
	State turn;

	void turnChange();
	bool onBoard(int x, int y);
	void put(int x, int y, State color);

public:
	Board();

	void Update();
	void Draw();
};