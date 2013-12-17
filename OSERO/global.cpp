#include <Dxlib.h>
#include <string>
#include <map>
using namespace std;

const int KEY_NUM = 256;
int keyState[KEY_NUM];
int mouseState;

void InputUpdate() {
	char tKeyState[KEY_NUM];
	GetHitKeyStateAll(tKeyState);
	for (int i=0; i<KEY_NUM; i++) {
		if (tKeyState[i] == 0) {
			keyState[i] = 0;
		} else {
			keyState[i]++;
		}
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		mouseState++;
	} else {
		mouseState = 0;
	}
}

int GetKey(int keyCode) {
	return keyState[keyCode];
}

int GetMouse() {
	return mouseState;
}

map<string, int> dataTbl;

void Load(string fn, string n) {
	int t;
	t = LoadGraph(fn.c_str());
	if (t != -1) {
		dataTbl[n] = t;
	} else {
		printfDx("ÉfÅ[É^Ç»Ç¢Ç≈Ç∑:%s", fn.c_str());
	}
}

int GetHandle(string n) {
	return dataTbl[n];
}