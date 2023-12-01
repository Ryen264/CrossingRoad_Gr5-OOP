#pragma once
#include "COBJECT.h"
class CTREE : public COBJECT {
	bool isDouble;
	const vector <wstring> FRAME_DOUBLE = {
L" ▄▄▄▄▄▄▄▀▀▀▀▀▀▀▄",
L"██████▀ ████████",
L"██▄▄▄██████▄▄▄▄█",
L"▀▄▄▄▄▄▄▄▀█▀█▀█▀ ",
L"  █ ▀ █  ▀▄ ▄▀  ",
L"  ▄█▄█▄  ▄█▄█▄  "
	};
	const vector <wstring> FRAME_SINGLE = {
L"▄▀▀▀▀▀▀▀▄       ",
L"█▄███████       ",
L"████▄▄▄██       ",
L" ▀█▀█▀█▀        ",
L"  ▀▀█▀▀         ",
L"  ▄█▄█▄         "
	};

public:
	CTREE(int x = 0, int y = 0, bool isDouble = true);
};