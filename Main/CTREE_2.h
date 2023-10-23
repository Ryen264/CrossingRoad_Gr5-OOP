#pragma once
#include "COBJECT.h"
class CTREE_2 : public COBJECT {
	int x, y;
	bool isRight;
	PIXEL block[16][16];
	const vector<wstring> FRAME_RIGHT = {
L"   ▄▀▀▀▀▀▀▀▄    ",
L"  █         █   ",
L"  █         █   ",
L"   ▀▄▄▄▄▄▄▄▀▀▀▄ ",
L"     █ ▀ █▄▄▄ █ ",
L"   ▄▄▄█▄█▀█▀█▀  ",
L"  █     ██▄▀    ",
L"  ▀▄▄▄▄▄█       ",
L"    ▀▄▀ █       ",
L"      ▄ █       ",
L"      █ █       ",
L"    ▄█▄▄▄█▄     " };
	const vector<wstring> FRAME_LEFT = {
L"   ▄▀▀▀▀▀▀▀▄    ",
L"  █         █   ",
L"  █         █   ",
L"   ▀▄▄▄▄▄▄▄▀▀▀▄ ",
L"     █ ▀ █▄▄▄ █ ",
L"   ▄▄▄█▄█▀█▀█▀  ",
L"  █     ██▄▀    ",
L"  ▀▄▄▄▄▄█       ",
L"    ▀▄▀ █       ",
L"      ▄ █       ",
L"      █ █       ",
L"    ▄█▄▄▄█▄     " };
	public:
		CTREE_2(int x = 0, int y = 0, int isRight = true);
};
