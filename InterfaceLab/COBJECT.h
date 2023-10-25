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
public:
	COBJECT(int x = 0, int y = 0, int isRight = true);

	int x, y, numberOfBlock, numberOfHeight, numberOfLength;
	PIXEL block[BLOCKLENGTH][BLOCKHEIGHT];
	PIXEL* blocks[BLOCKLENGTH][BLOCKHEIGHT];
	void DrawBlock(CGRAPHIC& layer);
};
