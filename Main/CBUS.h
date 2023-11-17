#pragma once
#include "CGRAPHIC.h"
class CBUS
{
	bool isRight;
	const vector <wstring> FRAME_RIGHT =
	{
L"                                ",
L"      █                ▄▄▄      ",
L"      █▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█        ",
L"      █▄█▄▄█▄▄█▄▄█ █▄▄▄█▄▄      ",
L"      ▀▀▄▄▄▀▀▀▀▀▀▀▀▀▄▄▄▀▀▀      ",
L"                                "
	};
	const vector<wstring> FRAME_LEFT =
	{
L"                                ",
L"      ▄▄▄                █      ",
L"        █▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█      ",
L"      ▄▄█▄▄▄█ █▄▄█▄▄█▄▄█▄█      ",
L"      ▀▀▀▄▄▄▀▀▀▀▀▀▀▀▀▄▄▄▀▀      ",
L"                                "
	};

public:
	PIXEL block[BLOCK_WIDTH * 2][BLOCK_HEIGHT];
	PIXEL* blocks[BLOCK_WIDTH * 2][BLOCK_HEIGHT];
	int x, y, numberOfBlock = 2, numberOfHeight = 1, numberOfWidth = 2;
	CBUS(int x = 0, int y = 0, bool isRight = true);
};

