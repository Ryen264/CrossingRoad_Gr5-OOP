#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;
struct THEME {
	COLORREF colorTable[16];
	int BLACK, SKY_BLUE, WHITE, DARK_GREEN,
		SADDLE_BROWN, DARK_RED, RED, ORANGE,
		DARK_VIOLET, TOMATO, LIGHT_CYAN, OXFORD,
		FELD_GRAU, BRIGHT_YELLOW, LIGHT_GREEN, LIGHT_BROWN; //All colors used, <id>: color used, -1: else
};
const THEME THEME_BASIC = { {
	RGB(0, 0, 0), RGB(135, 206, 235), RGB(255, 255, 255), RGB(34,177,76),
	RGB(139, 69, 19), RGB(139, 0, 0), RGB(255, 0, 0), RGB(255, 85, 0),
	RGB(148, 0, 211), RGB(255, 99, 71), RGB(224, 255, 255), RGB(0, 33, 71),
	RGB(77, 93, 83), RGB(255, 170, 29), RGB(144, 238, 144), RGB(181, 101, 29)},
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
const THEME THEME_LAND = { {
	RGB(255, 255, 255), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0),
	RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0)},
	15, 0 };
const vector<wstring> CAR = { L"▄▄████▄▄▄▄",
							  L"██▄▄▄▄████",
							  L"██▄▄▄▄█▄▄▄",
							  L" ▀▀   ▀▀  "
};

const vector<wstring> TRUNCK = { L"▄▄▄▄▄▄████▄▄▄▄",
								L"█▄▄▄▄█▄▄▄▄████",
								L"█▄▄▄▄█▄▄▄▄█▄▄▄",
								L"   ▀▀     ▀▀  "
};



const vector<wstring> DINOSAUR = {L"    ▄▀▀▀▀▀▀▀▀▀▄ ",
								  L"    █ ██      █ ",
								  L"    █         █ ",
								  L"  █▀█  ▀▀▀▄▄▄▄▀ ",
								  L"   ▀▄ ▄▄▄▄█     ",
								  L"    █▀  █▀      ",
};

const vector<wstring> DINOSAUR_REVERSE = { L"    ▄▀▀▀▀▀▀▀▀▀▄ ",
										   L"    █ ██      █ ",
										   L"    █         █ ",
										   L"    ▀▄▄▄▄▀▀▀  █▀█",
										   L"        █▄▄▄▄ ▄▀ ",
										   L"        ▀█   ▀█",
};

const vector<wstring> Tree = { L"▄▀▀▀▀▀▀▀▄", 
							   L"█▄███████",
							   L"████▄▄▄██",
							   L" ▀█▀█▀█▀",
							   L"  ▀▀█▀▀",
							   L"  ▄█▄█▄" };
const vector<wstring> grassland = {L"    ▄    ▄▄▄    ",
								   L"   ▀▀▀ ▄██  ▄   ", 
								   L"   ▀█▄ █▀  ▀▀▀  ", 
								   L"   ▄ ▀▀       █ ", 
								   L"  ▀▀▀   ▀█▄ ▄█▀ ", 
								   L"          ▀ ▀   ", };
                                   
struct PIXEL {
	wchar_t buffer;
	int txtColor, bgdColor;
};
class CGRAPHIC {
	const int WIDTH = 40;
	const int HEIGHT = 20;
public:
	PIXEL** screen;
	CGRAPHIC(PIXEL** screen = NULL);
	~CGRAPHIC();
	void display(int fromX = 0, int fromY = 0, int toX = -1, int toY = -1);
	void clear(int txtColor, int bgdColor);
	void Text(wstring wsContent, int first_x, int first_y, int txtColor, int bgdColor);
	void DrawObject(vector<wstring> contentsArr, int first_x, int first_y, int txtColor, int bgdColor);

	//friend void Text(wstring wsContent, int first_x, int first_y, int txtColor, int bgdColor;
};
