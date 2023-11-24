#pragma once
#include "COBJECT.h"
class CEGG : public COBJECT {
	bool isRight;
	const vector <wstring> FRAME_LEFT = {
L"                ",
L"     ▄▀▀▄       ",
L"    ██████      ",
L"    ▀▄██▄▀      ",
L"      ▀▀        ",
L"                "
	};
const vector <wstring> FRAME_RIGHT = {
L"                ",
L"     ▄▀▀▄       ",
L"    ██████      ",
L"    ▀▄██▄▀      ",
L"      ▀▀        ",
L"                "
};


public:
	CEGG(int x = 0, int y = 0, bool isRight = true);
};

