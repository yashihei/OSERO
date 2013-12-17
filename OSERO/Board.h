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

	int turn;

	void flipCheck();
public:
	Board();

	void Update();
};