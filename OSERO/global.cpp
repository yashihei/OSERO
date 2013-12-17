#include <Dxlib.h>
#include <string>
#include <map>
using namespace std;

const int KEY_NUM = 256;
int keyState[KEY_NUM];

void KeyUpdate() {
	char tKeyState[KEY_NUM];
	GetHitKeyStateAll(tKeyState);
	for (int i=0; i<KEY_NUM; i++) {
		if (tKeyState[i] == 0) {
			keyState[i] = 0;
		} else {
			keyState[i]++;
		}
	}
}

int GetKey(int keyCode) {
	return keyState[keyCode];
}

map<string, int> dataTbl;

void Load(string fn, string n) {
	int t;
	t = LoadGraph(fn.c_str());
	if (t != -1) {
		dataTbl[n] = t;
	} else {
		printfDx("‰æ‘œ‚È‚¢‚Å‚·II");
	}
}

int GetHandle(string n) {
	return dataTbl[n];
}