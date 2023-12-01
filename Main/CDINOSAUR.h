#pragma once
#include "COBJECT.h"
class CDINOSAUR : public COBJECT {
	bool isRight;
	vector<int> color;
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
	CDINOSAUR(int x = 0, int y = 0, bool isRight = true, vector<int> color = {DARK_GREEN, LIGHT_GREEN});
	void setColor(vector<int> color = { DARK_GREEN, LIGHT_GREEN });
};
