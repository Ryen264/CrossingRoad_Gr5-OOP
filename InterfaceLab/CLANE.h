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
public:
	CLANE(int width, int x = 0, int y = 0);

	int x, y, numberOfBlock;
	PIXEL block[BLOCK_WIDTH][BLOCK_HEIGHT];
	PIXEL* blocks[BLOCK_WIDTH][BLOCK_HEIGHT];
	void DrawBlock(CGRAPHIC& layer);
};