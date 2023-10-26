#pragma once
#include "CGRAPHIC.h"
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
    int x, y, numberOfBlock;
    PIXEL block[BLOCK_WIDTH][BLOCK_HEIGHT];
    PIXEL* blocks[BLOCK_WIDTH][BLOCK_HEIGHT];
public:
	CLANE(int width, int x = 0, int y = 0);
	void DrawBlock(CGRAPHIC& layer);
};