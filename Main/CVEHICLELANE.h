#pragma once
#include "CLANE.h"
#include "CCAR.h"
class CVEHICLELANE : public CLANE {
	const vector <wstring> FRAME = {
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"                ",
L"                ",
L"▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀ ",
L"                ",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
	};
public:
	CVEHICLELANE(int x = 0, int y = 0);
	~CVEHICLELANE();
	void Move();
};