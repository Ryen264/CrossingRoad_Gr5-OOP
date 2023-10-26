#pragma once
#include "COBJECT.h"
class CDINOSAUR : public COBJECT {
	bool isRight;
	const vector<wstring> FRAME_RIGHT = {
L"    ▄▀▀▀▀▀▀▀▀▀▄ ",
L"    █ ██      █ ",
L"    █         █ ",
L"  █▀█  ▀▀▀▄▄▄▄▀ ",
L"   ▀▄ ▄▄▄▄█     ",
L"    █▀  █▀      ",
	};
	const vector<wstring> FRAME_LEFT = {
L"  ▄▀▀▀▀▀▀▀▀▀▄   ",
L"  █      ██ █   ",
L"  █         █   ",
L"  ▀▄▄▄▄▀▀▀  █▀█ ",
L"      █▄▄▄▄ ▄▀  ",
L"      ▀█   ▀█   ",
	};
public:
	CDINOSAUR(int x = 0, int y = 0, bool isRight = false);
	void DrawDinosaur(CGRAPHIC& layer);
};


