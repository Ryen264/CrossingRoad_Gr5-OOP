#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;
const int SCREEN_HEIGHT = 51;
const int SCREEN_WIDTH = 208;
const int BLOCK_HEIGHT = 6;
const int BLOCK_WIDTH = 16;

struct THEME {
	COLORREF colorTable[16];
	int BLACK, SKY_BLUE, WHITE, DARK_GREEN,
		SADDLE_BROWN, DARK_RED, RED, ORANGE,
		BLUE, DARK_BLUE, LIGHT_CYAN, LIGHT_GRAY,
		SAND, BRIGHT_YELLOW, LIGHT_GREEN, LIGHT_BROWN,
		CREAMY_AVOCADO, DARK_BROWN, BROWN, LIGHTER_BROWN,
		LAVENDER, PURPLE, TEAL, TANGERINE, DARK_ORANGE; //All colors used, <id>: color used, -1: else
};
const THEME THEME_BASIC = { {
	RGB(0, 0, 0), RGB(135, 206, 235), RGB(255, 255, 255), RGB(34,177,76),
	RGB(139, 69, 19), RGB(139, 0, 0), RGB(255, 0, 0), RGB(255, 85, 0),
	RGB(25, 140, 255), RGB(0, 77, 153), RGB(224, 255, 255), RGB(180, 180, 180),
	RGB(255, 249, 189), RGB(255, 170, 29), RGB(144, 238, 144), RGB(181, 101, 29)},
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	-1, -1, -1, -1, -1, -1, -1, -1, -1};

const THEME MAIN_MENU_THEME = { {
	RGB(212, 240, 149), RGB(87, 41, 23), RGB(156, 90, 60), RGB(117, 63, 40), RGB(201, 136, 87), RGB(180, 180, 180), RGB(0, 0, 0), RGB(255, 255, 255),
	RGB(34, 177, 76), RGB(52, 235, 103), RGB(160, 224, 250), RGB(178, 153, 196), RGB(112, 86, 130), RGB(15, 191, 191), RGB(252, 176, 52), RGB(222, 121, 27)},
	6, 10, 7, 8,
	-1, -1, -1, -1,
	-1, -1, -1, 5,
	-1, -1, 9, 2,
	0, 1, 3, 4,
	11, 12, 13, 14, 15 };

extern int BLACK, SKY_BLUE, WHITE, DARK_GREEN,
SADDLE_BROWN, DARK_RED, RED, ORANGE,
BLUE, DARK_BLUE, LIGHT_CYAN, LIGHT_GRAY,
SAND, BRIGHT_YELLOW, LIGHT_GREEN, LIGHT_BROWN,
CREAMY_AVOCADO, DARK_BROWN, BROWN, LIGHTER_BROWN,
LAVENDER, PURPLE, TEAL, TANGERINE, DARK_ORANGE;

void SetupTheme(THEME theme = THEME_BASIC);

struct PIXEL {
	wchar_t buffer;
	int txtColor, bgdColor;
};
class CGRAPHIC {
public:
	PIXEL** screen = NULL;
	CGRAPHIC(PIXEL** screen = NULL);
	~CGRAPHIC();
	void display(int fromX = 0, int fromY = 0, int toX = -1, int toY = -1);
	void clear(int txtColor, int bgdColor);
	void Text(wstring wsContent, int first_x, int first_y, int txtColor, int bgdColor);
	void DrawObject(vector<wstring> contentsArr, int first_x, int first_y, int txtColor, int bgdColor);
	void drawClipBoard(int first_x, int first_y, int width, int height);
	void drawMainMenu();
	void drawTag(int first_x, int first_y, int tagColor);
	void DrawSaveScreen(vector<wstring> FLOPPY_DISC, int first_x, int first_y);
};

const vector<wstring> FLOPPY_DISC = {
		L"██████████████████████████████████████████████████    ",
		L"██                                                ██  ",
		L"██                              █████               ██",
		L"██                              █████               ██",
		L"██                              █████               ██",
		L"██                              █████               ██",
		L"██                              █████               ██",
		L"██                              █████               ██",
		L"██                              █████               ██",
		L"██                              █████               ██",
		L"██                                                  ██",
		L"██                                                  ██",
		L"██                                                  ██",
		L"██        ██████████████████████████████████        ██",
		L"██        ██████████████████████████████████        ██",
		L"██        ██████████████████████████████████        ██",
		L"██                                                  ██",
		L"██                                                  ██",
		L"██                                                  ██",
		L"██                                                  ██",
		L"██                                                  ██",
		L"██                                                  ██",
		L"██                          ████       ████         ██",
		L"██                        ██    ██   ██    ██       ██",
		L"██                        ██    ██   ██    ██       ██",
		L"██                          ████       ████         ██",
		L"██                                                  ██",
		L"██                                                  ██",
		L"██████████████████████████████████████████████████████"
};

const vector <wstring> MAIN_MENU_FRAME = {
L"                                            ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄    ",
L"                                            ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ███                                                                                                                                                          ███    ",
L"                                            ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████    ",
L"                                            ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀    ",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████",
L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",
L"                                                                                                                                                                                                                ",
L"                                                                                                                                                                                                                ",
L"                                                                                                                                                                                                                ",
L"                                                                                                                                                                                                                ",
L"                                                                                                                                                                                                                ",
L"                                                                                                                                                                                                                ",
L"                                                                                                                                                                                                                ",
L"                                                                                                                                                                                                                ",
L"                                                                                                                                                                                                                ",
};


const vector<wstring> TAGS = {
L"     ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L" ▄▄█▀▀                                 █",
L"█▀  ▄█                                 █",
L"▀█▄▄ ▀                                 █",
L"   ▀▀█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█"
};