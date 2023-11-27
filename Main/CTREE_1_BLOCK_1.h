#pragma once
#include "COBJECT.h"
class CTREE_1_BLOCK_1 : public COBJECT {
	bool isRight;
	const vector <wstring> FRAME_RIGHT = {
L"▄▀▀▀▀▀▀▀▄       ",
L"█▄███████       ",
L"████▄▄▄██       ",
L" ▀█▀█▀█▀        ",
L"  ▀▀█▀▀         ",
L"  ▄█▄█▄         " 
};
	const vector <wstring> FRAME_LEFT = {
L"▄▀▀▀▀▀▀▀▄       ",
L"█▄███████       ",
L"████▄▄▄██       ",
L" ▀█▀█▀█▀        ",
L"  ▀▀█▀▀         ",
L"  ▄█▄█▄         "
};

public:
	CTREE_1_BLOCK_1(int x = 0, int y = 0, bool isRight = true);
};

