#pragma once
#include "CGRAPHIC.h"
#include "COBJECT.h"
class CLANE {
	const vector <wstring> FRAME = {
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"                ",
L"                ",
L"▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀ ",
L"                ",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
	};
protected:
	int x, y, numberOfBlock = 1, numberOfHeight = 1, numberOfWidth = 1;
	PIXEL** block;
public:
	CLANE(int x = 0, int y = 0);
	~CLANE();
	void DrawBlock(CGRAPHIC& layer);
};