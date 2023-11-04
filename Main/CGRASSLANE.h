#pragma once
#include "CLANE.h"
class CGRASSLANE : public CLANE {
	const vector <wstring> FRAME = {
L"    ▄    ▄▄▄    ",
L"   ▀▀▀ ▄██  ▄   ",
L"   ▀█▄ █▀  ▀▀▀  ",
L"   ▄ ▀▀       █ ",
L"  ▀▀▀   ▀█▄ ▄█▀ ",
L"          ▀ ▀   "
	};
public:
	CGRASSLANE(int x = 0, int y = 0);
	~CGRASSLANE();
};