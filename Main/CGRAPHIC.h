﻿#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;
const int SCREEN_WIDTH = 208;
const int SCREEN_HEIGHT = 51;
const int BLOCK_WIDTH = 16;
const int BLOCK_HEIGHT = 6;
const int START_HEIGHT = 3;

// LaneIDs
const int VEHICLELANE_ID = 20001;
const int GRASSLANE_ID = 20002;
const int RIVERLANE_LAND_ID = 20003;
const int RIVERLANE_NOLAND_ID = 21003;
const vector<int> LANE_ID_LIST = { VEHICLELANE_ID, GRASSLANE_ID, RIVERLANE_LAND_ID };


struct THEME {
	COLORREF colorTable[16];
	int BLACK, SKY_BLUE, WHITE, DARK_GREEN,
		SADDLE_BROWN, DARK_RED, RED, ORANGE,
		BLUE, DARK_BLUE, DARK_GRAY, LIGHT_GRAY,
		FELD_GRAU, BRIGHT_YELLOW, LIGHT_GREEN, LIGHT_BROWN; //All colors used, <id>: color used, -1: else
};
const THEME THEME_BASIC = { {
	RGB(0, 0, 0), RGB(135, 206, 235), RGB(255, 255, 255), RGB(34,177,76),
	RGB(139, 69, 19), RGB(139, 0, 0), RGB(255, 0, 0), RGB(255, 85, 0),
	RGB(25, 140, 255), RGB(0, 77, 153), RGB(70, 70, 70), RGB(180, 180, 180),
	RGB(77, 93, 83), RGB(255, 170, 29), RGB(144, 238, 144), RGB(181, 101, 29)},
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
const THEME THEME_LAND = { {
	RGB(255, 255, 255), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0),
	RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0)},
	15, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0 };

extern int BLACK, SKY_BLUE, WHITE, DARK_GREEN,
SADDLE_BROWN, DARK_RED, RED, ORANGE,
BLUE, DARK_BLUE, DARK_GRAY, LIGHT_GRAY,
FELD_GRAU, BRIGHT_YELLOW, LIGHT_GREEN, LIGHT_BROWN;

void SetupTheme(THEME theme = THEME_BASIC);

struct PIXEL {
	wchar_t buffer;
	int txtColor, bgdColor;
};

class CGRAPHIC {
public:
	PIXEL** screen;
	CGRAPHIC(PIXEL** screen = NULL);
	~CGRAPHIC();
	void display(int fromX = 0, int fromY = 0, int toX = -1, int toY = -1);
	void clear(int txtColor, int bgdColor);
	void Text(wstring wsContent, int first_x, int first_y, int txtColor, int bgdColor);
	void DrawObject(vector<wstring> contentsArr, int first_x, int first_y, int txtColor, int bgdColor);
};
