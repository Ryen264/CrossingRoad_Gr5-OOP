#pragma once
#include "COBJECT.h"
class CDINOSAUR : public COBJECT {
	bool isRight;
	const vector<wstring> FRAME_RIGHT = {
L"    ▄▀▀▀▀▀▀▀▀▀▄ ",
L"    ███████████ ",
L"    ███████████ ",
L"  █▀███▀▀▀▄▄▄▄▀ ",
L"   ▀▄█▄▄▄▄█     ",
L"    █▀  █▀      ",
	}; //5-9, 5
	const vector<wstring> FRAME_LEFT = {
L"  ▄▀▀▀▀▀▀▀▀▀▄   ",
L"  ███████████   ",
L"  ███████████   ",
L"  ▀▄▄▄▄▀▀▀███▀█ ",
L"      █▄▄▄▄█▄▀  ",
L"       ▀█  ▀█   ",
	}; //6-10 , 5
public:
	CDINOSAUR(int x = 0, int y = 0, bool isRight = true);
	~CDINOSAUR();
};
