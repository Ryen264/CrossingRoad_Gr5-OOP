#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;


const vector<wstring> car = { L"▄▄████▄▄▄▄",
                              L"██▄▄▄▄████",
                              L"██▄▄▄▄█▄▄▄",
                              L" ▀▀   ▀▀  "
};

const vector<wstring> truck = { L"▄▄▄▄▄▄████▄▄▄▄",
                                L"█▄▄▄▄█▄▄▄▄████",
                                L"█▄▄▄▄█▄▄▄▄█▄▄▄",
                                L"   ▀▀     ▀▀  "
};

const vector<wstring> Tree = {  L"██████████",
								L"██████████",
								L"██████████",
							    L"    ██",
                                L"    ██"};

struct PIXEL {
	wchar_t buffer;
	int txtColor, bgdColor;
};
const int BLACK		= 0;
const int SKY_BLUE = 1;
const int WHITE	    = 2;
const int GREEN		= 3;
const int SADDLE_BROWN = 4;
const int DARK_RED = 5;
const int RED		= 6;
const int FELDGRAU	= 12;
const int BRIGHTYELLOW = 13;
const int NEON_GREEN = 14;
const int GREEN_PERRY = 15;
void Configure();

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
