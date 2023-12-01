#pragma once
#include "COBJECT.h"
class CTREE_2_BLOCK : public COBJECT {
	bool isRight;
	const vector<wstring> FRAME_RIGHT = {
	L"   ▄▀▀▀▀▀▀▀▄    ",
	L"  █         █   ",
	L"  █  ▄▄     █   ",
	L"   ▀▄▄▄▄▄▄▄▀▀▀▄ ",
	L"     █ ▀ █▄▄▄ █ ",
	L"   ▄▄▄█▄█▀█▀█▀  ",
	L"  █▄   ▀██▄▀    ",
	L"  ▀▄▄▄▄▄█       ",
	L"    ▀▄▀ █       ",
	L"      █ █       ",
	L"      █ █       ",
	L"    ▄█▄▄▄█▄     "
	};
	const vector<wstring> FRAME_LEFT = {
	L"   ▄▀▀▀▀▀▀▀▄    ",
	L"  █         █   ",
	L"  █  ▄▄     █   ",
	L"   ▀▄▄▄▄▄▄▄▀▀▀▄ ",
	L"     █ ▀ █▄▄▄ █ ",
	L"   ▄▄▄█▄█▀█▀█▀  ",
	L"  █▄   ▀██▄▀    ",
	L"  ▀▄▄▄▄▄█       ",
	L"    ▀▄▀ █       ",
	L"      █ █       ",
	L"      █ █       ",
	L"    ▄█▄▄▄█▄     "
	};

public:
	CTREE_2_BLOCK(int x = 0, int y = 0, bool isRight = true);
};

