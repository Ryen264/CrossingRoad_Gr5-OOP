#pragma once
#include "CVEHICLE.h"
class CTRUCK : public CVEHICLE {
	bool isRight;
	const vector <wstring> FRAME_RIGHT = {
L"                ",
L" ▄▄▄▄▄▄████▄▄▄▄ ",
L" █▄▄▄▄█▄▄▄▄████ ",
L" █▄▄▄▄█▄▄▄▄█▄▄▄ ",
L"    ▀▀     ▀▀   ",
L"                "
	};
	const vector<wstring> FRAME_LEFT = {
L"                ",
L" ▄▄▄▄▄▄████▄▄▄▄ ",
L" █▄▄▄▄█▄▄▄▄████ ",
L" █▄▄▄▄█▄▄▄▄█▄▄▄ ",
L"    ▀▀     ▀▀   ",
L"                "
	};
public:
	CTRUCK(int x = 0, int y = 0, int isRight = true);
};
