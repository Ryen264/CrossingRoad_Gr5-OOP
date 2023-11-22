#pragma once
#include "COBJECT.h"
class CCAPYBARA : public COBJECT {
	bool isRight;
	const vector <wstring> FRAME_RIGHT =
	{
L"   ▄▄           ",
L"   ▄█▄▄▄██▄█    ",
L"▄█▄█████████    ",
L"████████▀       ",
L"                ",
L"                "
	};
	const vector <wstring> FRAME_LEFT =
	{
L"       ▄▄       ",
L"█▄██▄▄▄█▄       ",
L"█████████▄█▄    ",
L"   ▀████████    ",
L"                ",
L"                "
	};

public:
	CCAPYBARA(int x = 0, int y = 0, bool isRight = true);
};