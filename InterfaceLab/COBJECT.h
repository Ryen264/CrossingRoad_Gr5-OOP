#pragma once
#include "CGRAPHIC.h"
class COBJECT {
	bool isRight;
	const vector <wstring> FRAME_RIGHT = {
L"                ",
L"   ▄▄████▄▄▄▄   ",
L"   ██▄▄▄▄████   ",
L"   ██▄▄▄▄█▄▄▄   ",
L"    ▀▀   ▀▀     ",
L"                ",
	};
	const vector<wstring> FRAME_LEFT = {
L"                ",
L"   ▄▄▄▄████▄▄   ",
L"   ████▄▄▄▄██   ",
L"   ▄▄▄█▄▄▄▄██   ",
L"     ▀▀   ▀▀    ",
L"                "
	};

protected:
    int x, y, numberOfBlock, numberOfHeight, numberOfLength;
    PIXEL block[BLOCK_WIDTH][BLOCK_HEIGHT];
    PIXEL* blocks[BLOCK_WIDTH][BLOCK_HEIGHT];
public:
	COBJECT(int x = 0, int y = 0, int isRight = true);
	void DrawBlock(CGRAPHIC& layer);
	
};
