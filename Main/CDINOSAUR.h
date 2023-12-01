#pragma once
#include "COBJECT.h"
class CDINOSAUR : public COBJECT {
	bool isRight;
	int color;
	const vector<wstring> FRAME_RIGHT =
	{
L"    ▄▀▀▀▀▀▀▀▀▀▄ ",
L"    █ ██      █ ",
L"    █         █ ",
L"  █▀█  ▀▀▀▄▄▄▄▀ ",
L"   ▀▄ ▄▄▄▄█     ",
L"    █▀  █▀      "
	};
	const vector<wstring> FRAME_LEFT =
	{
L"  ▄▀▀▀▀▀▀▀▀▀▄   ",
L"  █      ██ █   ",
L"  █         █   ",
L"  ▀▄▄▄▄▀▀▀  █▀█ ",
L"      █▄▄▄▄ ▄▀  ",
L"       ▀█  ▀█   "
	};
public:
	CDINOSAUR(int x = 0, int y = 0, bool isRight = true, int color = DARK_GREEN);
	void setColor(int color);
};
