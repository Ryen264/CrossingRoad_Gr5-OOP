#pragma once
#include "COBJECT.h"
//extern vector<int> GREEN_CHARACTER;
//vector<int> RED_CHARACTER = { DARK_RED, RED };
//vector<int> BLUE_CHARACTER = { BLUE, SKY_BLUE };
//vector<int> GRAY_CHARACTER = { DARK_GRAY, LIGHT_GRAY };
//vector<int> BROWN_CHARACTER = { SADDLE_BROWN, LIGHT_BROWN };
//vector<int> YELLOW_CHARACTER = { BRIGHT_YELLOW, WHITE };
//vector<int> SAND_CHARACTER = { SAND, BRIGHT_YELLOW };
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
