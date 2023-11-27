#pragma once
#include "COBJECT.h"
class CEGG : public COBJECT {
	const vector <wstring> FRAME = {
L"                ",
L"     ▄▀▀▄       ",
L"    ██████      ",
L"    ▀▄██▄▀      ",
L"      ▀▀        ",
L"                "
	};

public:
	CEGG(int x = 0, int y = 0);
};

