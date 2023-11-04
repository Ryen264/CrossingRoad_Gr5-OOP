#pragma once
#include "CGRAPHIC.h"
const int BOARD_HEIGHT = 5;
const int BOARD_WIDTH = 5;
class COBJECT {
	bool isRight;
//	const vector <wstring> FRAME_RIGHT = {
//L"   ▄▀▀▀▀▀▀▀▄    ",
//L"  ████████▀██   ",
//L"  ███▄▄███▄██   ",
//L"   ▀▄▄▄▄▄▄▄▀▀▀▄ ",
//L"     ██▀██▄▄▄██ ",
//L"   ▄▄▄█▄█▀█▀█▀  ",
//L"  █▄███▀██▄▀    ",
//L"  ▀▄▄▄▄▄█       ",
//L"    ▀▄▀ █       ",
//L"      ███       ",
//L"      ███       ",
//L"    ▄█▄▄▄█▄     " 
//	};
//	const vector<wstring> FRAME_LEFT = {
//L"   ▄▀▀▀▀▀▀▀▄    ",
//L"  ███████████   ",
//L"  ███▄▄██████   ",
//L"   ▀▄▄▄▄▄▄▄▀▀▀▄ ",
//L"     █ ▀ █▄▄▄██ ",
//L"   ▄▄▄█▄█▀█▀█▀  ",
//L"  █▄███▀██▄▀    ",
//L"  ▀▄▄▄▄▄█       ",
//L"    ▀▄▀ █       ",
//L"      █ █       ",
//L"      █ █       ",
//L"    ▄█▄▄▄█▄     " 
//	};

	const vector<wstring> FRAME_LEFT =
	{
		L"   ▀▄▀          ",
		L"  ▄▄█▄▄█        ",
		L"▄▄▄▄█▄▄█▄▄▄▄    ",
		L"  ▀▀▀▀▀▀▀▀      ",
		L"                ",
		L"                ",
	};
	const vector<wstring> FRAME_RIGHT =
	{
		L"          ▀▄▀   ",
		L"        █▄▄█▄▄  ",
		L"    ▄▄▄▄█▄▄█▄▄▄▄",
		L"      ▀▀▀▀▀▀▀▀  ",
		L"                ",
		L"                ",
	};
protected:
    int x, y, numberOfBlock = 1, numberOfHeight = 1, numberOfWidth = 1;
    PIXEL** block;
public:
	COBJECT(int x = 0, int y = 0, int isRight = false);
	~COBJECT();
	void DrawBlock(CGRAPHIC& layer);







};
