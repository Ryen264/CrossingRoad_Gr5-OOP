#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;
const int SCREEN_WIDTH = 208;
const int SCREEN_HEIGHT = 51;
const int BLOCK_WIDTH = 16;
const int BLOCK_HEIGHT = 6;
const int START_BOARD_HEIGHT = 3;

struct THEME {
	COLORREF colorTable[16];
	int BLACK, SKY_BLUE, WHITE, DARK_GREEN,
		SADDLE_BROWN, DARK_RED, RED, ORANGE,
		BLUE, DARK_BLUE, DARK_GRAY, LIGHT_GRAY,
		SAND, BRIGHT_YELLOW, LIGHT_GREEN, LIGHT_BROWN; //All colors used, <id>: color used, -1: else
};
const THEME THEME_BASIC = { {
	RGB(0, 0, 0), RGB(135, 206, 235), RGB(255, 255, 255), RGB(34,177,76),
	RGB(139, 69, 19), RGB(139, 0, 0), RGB(255, 0, 0), RGB(255, 85, 0),
	RGB(25, 140, 255), RGB(0, 77, 153), RGB(70, 70, 70), RGB(180, 180, 180),
	RGB(255, 249, 189), RGB(255, 170, 29), RGB(144, 238, 144), RGB(181, 101, 29)},
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
const THEME THEME_LAND = { {
	RGB(255, 255, 255), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0),
	RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0)},
	15, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0 };

extern int BLACK, SKY_BLUE, WHITE, DARK_GREEN,
SADDLE_BROWN, DARK_RED, RED, ORANGE,
BLUE, DARK_BLUE, DARK_GRAY, LIGHT_GRAY,
SAND, BRIGHT_YELLOW, LIGHT_GREEN, LIGHT_BROWN;

void SetupTheme(THEME theme = THEME_BASIC);

struct PIXEL {
	wchar_t buffer;
	int txtColor, bgdColor;
};

const vector<wstring> PAUSE_MENU = {
		L"   ▄▄▀▀▀▀▀▀▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▄▄   ",//0
		L" ▄▀▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▀▄ ",//1
		L"▄▀ █ █    ▄▄▄▄▄▄▄▄▄  █                          █ ▀▄",//2
		L"█  █ █   █ ▄▄      █ █    ▄▄                    █  █",//3
		L"█  █ █   █ ▀▀      █ █  ▄▀  ▀▄  ▄               █  █",//4
		L"█  █ █ ▄▄█         █ █  █    █  ▄               █  █",//5
		L"█  █ █ ▀▄▀     █▀▀▀  █   ▀▄▄▀                   █  █",//6
		L"█  █ █   █▄▀▀██▀     █                          █  █",//7
		L"█  █ █   ▀   ▀       █                          █  █",//8
		L"█  █  ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀                           █  █",//9
		L"█  █      ▄             ▄               ▄▄▄     █  █",//10
		L"█  █   ▄▄██ ▄ █         ██▄▄           █   █    █  █",//11
		L"█  █   ████ █ █         ████▀            █▀     █  █",//12
		L"█  █     ▀█   ▀         █▀               ▄      █  █",//13
		L"█  █                                            █  █",//14
		L"█  █   █▀▀▀▀▀█         █▀▀▀▀▀█        █▀▀▀▀▀█   █  █",//15
		L"█  █   █     █         █     █        █     █   █  █",//16
		L"█  █   █     █         █     █        █     █   █  █",//17
		L"█  █   ▀▀▀▀▀▀▀         ▀▀▀▀▀▀▀        ▀▀▀▀▀▀▀   █  █",//18
		L"█  █           ▄▄▄▄▄▄             ▄             █  █",//19
		L"█  █           █▄▄█▄██         ▄▀ █ ▀▄          █  █",//20
		L"█  █           █     █         █  ▀  █          █  █",//21
		L"█  █           █▄▄▄▄▄█          ▀▄▄▄▀           █  █",//22
		L"█  █                                            █  █",//23
		L"█  █           █▀▀▀▀▀█         █▀▀▀▀▀█          █  █",//24
		L"█  █           █     █         █     █     ▄▄▄▄▄█  █",//25
		L"█  █           █     █         █     █     █  ▄▀   █",//26
		L"█  █           ▀▀▀▀▀▀▀         ▀▀▀▀▀▀▀     █▄▀     █",//27
		L"█  ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀       █",//28
		L"▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀" //29
};
const vector<wstring> Drawer = {
L"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█"
L"█                ▀▀▀▀     █",
L"█                         █",
L"█                         █",
L"█       ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",
L"█                ▄▄▄▄     █",
L"█                         █",
L"█                         █",
L"█       ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"█                         █",
L"█                ▀▀▀▀     █",
L"█                         █",
L"█                         █",
L"█       ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",
L"█                ▄▄▄▄     █",
L"█                         █",
L"█                         █",
L"█       ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"█                         █",
L"█                ▀▀▀▀     █",
L"█                         █",
L"█                         █",
L"█       ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",
L"█                ▄▄▄▄     █",
L"█                         █",
L"█                         █",
L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀"
};
const vector<wstring> SmallDrawer= {
L"               ▄▀▀▀▀▀▀▀▀▀▀▀▀▄    ",
L"              ████████████████   ",
L"              ████████████████   ",
L"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█",
L"██████████████████████▀▀▀▀███████",
L"█████████████████████████████████",
L"█████████████████████████████████",
L"█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█"
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
	void DrawPauseMenu(vector<wstring> PauseMenu, int first_x, int first_y);
	void DrawDrawer(vector<wstring>contentsArr, int first_x, int first_y, int txtColor = 0, int bgdColor = -1);
	void DrawSmallDrawer(vector<wstring>contentsArr, int first_x, int first_y, int txtColor = 0, int bgdColor = -1);
	
};
