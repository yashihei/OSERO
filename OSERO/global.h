#pragma once
#include <string>

extern void InputUpdate();
extern int GetKey(int KeyCode);
extern int GetMouse();
extern void Load(std::string fn, std::string n);
extern int GetHandle(std::string);

struct Point {
	int x, y;
	Point(int x, int y) { this->x = x, this->y = y; }
};
