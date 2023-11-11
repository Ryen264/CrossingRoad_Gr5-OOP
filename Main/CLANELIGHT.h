#pragma once
#include "CGRAPHIC.h"
class CLANELIGHT
{
	const vector <wstring> FRAME = {
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"        ▄▄▄     ",
L"        ▄▄▄ █▀█ ",
L"▀▀▀ ▀▀▀ ▄▄▄ █▀█ ",
L"        ▄▄▄ ▀█▀ ",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▄",
	};
protected:
	int x, y, numberOfBlock = 1, numberOfHeight = 1, numberOfWidth = 1;
	PIXEL** block;
public:
	CLANELIGHT(int x = 0, int y = 0);
	~CLANELIGHT();
	void DrawBlock(CGRAPHIC& layer);
};

