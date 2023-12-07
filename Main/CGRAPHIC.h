#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <deque>
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
		SAND, BRIGHT_YELLOW, LIGHT_GREEN, LIGHT_BROWN,
		CREAMY_AVOCADO, DARK_BROWN, BROWN, LIGHTER_BROWN,
		LAVENDER, PURPLE, TEAL, TANGERINE, DARK_ORANGE; //All colors used, <id>: color used, -1: else
};
const THEME THEME_BASIC = { {
	RGB(0, 0, 0), RGB(135, 206, 235), RGB(255, 255, 255), RGB(34,177,76),
	RGB(139, 69, 19), RGB(139, 0, 0), RGB(255, 0, 0), RGB(255, 85, 0),
	RGB(25, 140, 255), RGB(0, 77, 153), RGB(70, 70, 70), RGB(180, 180, 180),
	RGB(255, 249, 189), RGB(255, 170, 29), RGB(144, 238, 144), RGB(181, 101, 29)},
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	-1, -1, -1, -1, -1, -1, -1, -1, -1 };

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
BLUE, DARK_BLUE, DARK_GRAY, LIGHT_GRAY,
SAND, BRIGHT_YELLOW, LIGHT_GREEN, LIGHT_BROWN,
CREAMY_AVOCADO, DARK_BROWN, BROWN, LIGHTER_BROWN,
LAVENDER, PURPLE, TEAL, TANGERINE, DARK_ORANGE;

void SetupTheme(THEME theme, HANDLE& hStdout);

struct PIXEL {
	wchar_t buffer;
	int txtColor, bgdColor;
};

class CGRAPHIC {
	int WIDTH, HEIGHT;
public:
	PIXEL** screen;
	CGRAPHIC();
	CGRAPHIC(const CGRAPHIC& second);
	CGRAPHIC(PIXEL pixel);
	~CGRAPHIC();
	void display(HANDLE& hStdout, DWORD& dwBytesWritten, int fromX = 0, int fromY = 0, int toX = -1, int toY = -1);

	void clear(int txtColor, int bgdColor);
	void Text(wstring wsContent, int first_x, int first_y, int txtColor, int bgdColor);
	void DrawObject(vector<wstring> contentsArr, int first_x, int first_y, int txtColor, int bgdColor, bool isPass = true);
	void erasePixel(int fromX, int fromY, int toX, int toY);

	void DrawLetter(char ch, int first_x, int first_y, int txtColor = BLACK, int bgdColor = -1);
	void DrawNumber(int num, int first_x, int first_y, int txtColor, int bgdColor);
	void DrawInputPos(int first_x, int first_y, int txtColor = BLACK, int bgdColor = -1);
	void DrawMINUS(int first_x, int first_y, int txtColor, int bgdColor);
	void DrawPLUS(int first_x, int first_y, int txtColor, int bgdColor);
	void DrawEXCLAMATION_MARK(int first_x, int first_y, int txtColor, int bgdColor);
	void drawString(string str, int x, int y, int txtColor, int bgdColor, int num = -1);
	void drawTime(clock_t second, int first_x, int first_y, int txtColor, int bgdColor);


	void drawCharacterFrame(int first_x, int first_y, int txtColor = BLACK, int bgdColor = -1);
	void drawCheck(int first_x, int first_y, int txtColor = DARK_GREEN, int bgdColor = -1);
	void drawCell(int first_x, int first_y, int txtColor = BLACK, int bgdColor = -1, bool isPass = true);
	void drawButton(int first_x, int first_y, int color, int txtColor = BLACK, int bgdColor = -1, bool isPass = true);
	void drawClipBoard(int first_x, int first_y, int width, int height);
	void drawTag(int first_x, int first_y, string tagName, int tagColor);
	void drawInfiniteSymbol(int first_x, int first_y);
	void drawRegtangle(int first_x, int first_y, int width, int height, int color, bool isFill = false);

	void DrawTextBoard(string contentName, int colorName, vector<string> contentBody, int first_x, int first_y, int width, int height, int txtColor, int bgdColor);

	void DrawDrawer(int first_x, int first_y);
	void DrawSmallDrawer(int first_x, int first_y, int drawerColor = BRIGHT_YELLOW);
	void DrawDinasourPicture(int first_x, int first_y);
	void DrawBigDinoSaur(int first_x, int first_y);
	void DrawHat(int first_x, int first_y);
	void DrawCloud_1(int first_x, int first_y);
	void DrawCloud_2(int first_x, int first_y);
	void DrawDoofCorp(int first_x, int first_y);

	//void DrawFileInfo(int first_x, int first_y, int id, string fileName, int level, int score, string characterName, int txtColor, int bgdColor);
	void DrawSaveScreen(int first_x, int first_y);
	void DrawSettingScreen(int first_x, int first_y);

	void DrawMainMenu();
	void DrawLoadGame(int first_x, int first_y, deque<string> nameList);
	void DrawPauseMenu(int first_x, int first_y);
	void DrawChooseCharacterMenu(int first_x, int first_y);
	void DrawPerryTalk(string message, int first_x, int first_y, int txtColor, int bgdColor);
	void DrawHeader(int first_x, int first_y);

	void DrawChar1pixel(int first_x, int first_y, char ch, int txtColor, int bgdColor);
	void DrawString1pixel(int first_x, int first_y, string str, int txtColor, int bgdColor);
	void DrawNumber1pixel(int first_x, int first_y, int num, int txtColor, int bgdColor);
};
const vector<wstring> COLON = {
	L"█",
	L" ",
	L"█" };
const vector<wstring> CELL = {
	L"█▀▀▀▀▀█",
	L"█     █",
	L"█     █",
	L"▀▀▀▀▀▀▀"
};
const vector<wstring> BUTTON = {
	L"  ████  ",
	L"██    ██",
	L"██    ██",
	L"  ████  "
};
const vector<wstring> CHECK = {
	L"    ▄▀█",
	L"█▀▄▀▄▀ ",
	L" ▀▄▀   "
};
const vector<wstring> INPUT_POS = {
	L"   ",
	L"   ",
	L"▀▀▀"};
const vector<wstring> MINUS ={ 
	L"   ",
	L"▀▀▀",
	L"   " };
const vector<wstring> PLUS = {
	L" ▄ ",
	L"▀█▀",
	L"   " };
const vector<wstring> EXCLAMATION_MARK = {
	L" █ ",
	L" █ ",
	L" ▄ " };

const vector<wstring> CHARACTER_FRAME = {
	L"█               █",
	L"█               █",
	L"█               █",
	L"█               █",
	L"█               █",
	L"█               █",
	L"█               █",
	L"▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀"
};
const vector<vector<wstring>> NUMBER = {
{	L"█▀█",
	L"█ █",
	L"▀▀▀" },
{	L"▄█ ",
	L" █ ",
	L"▀▀▀" },
{	L"▀▀█",
	L"█▀▀",
	L"▀▀▀" },
{	L"▀▀█",
	L"▀▀█",
	L"▀▀▀" },
{	L"█ █",
	L"▀▀█",
	L"  ▀" },
{	L"█▀▀",
	L"▀▀█",
	L"▀▀▀" },
{	L"█▀▀",
	L"█▀█",
	L"▀▀▀" },
{	L"▀▀█",
	L"  █",
	L"  ▀" },
{	L"█▀█",
	L"█▀█",
	L"▀▀▀" },
{	L"█▀█",
	L"▀▀█",
	L"  ▀" },
};
const vector<vector<wstring>> BIG_NUMBER = {
{
L"          ██████████████          ",//1
L"      ████              ████      ",//2
L"    ██                      ██    ",//3
L"  ██            ████          ██  ",//4
L"  ██          ██████          ██  ",//5
L"██          ████████            ██",//6
L"██              ████            ██",//7
L"██              ████            ██",//8
L"██              ████            ██",//9
L"██              ████            ██",//10
L"██              ████            ██",//11
L"██              ████            ██",//12
L"  ██            ████          ██  ",//13
L"  ██            ████          ██  ",//14
L"    ██                      ██    ",//15
L"      ████              ████      ",//16
L"          ██████████████         "},//17

{
L"          ██████████████          ",//1
L"      ████              ████      ",//2
L"    ██                      ██    ",//3
L"  ██        ██████████        ██  ",//4
L"  ██      ██████████████      ██  ",//5
L"██        ████      ████        ██",//6
L"██                  ████        ██",//7
L"██                ██████        ██",//8
L"██              ██████          ██",//9
L"██            ██████            ██",//10
L"██          ██████              ██",//11
L"██        ██████                ██",//12
L" █   ███████   █ ",//13
L" █   ███████   █ ",//14
L"  █           █  ",//15
L"   ██       ██   ",//16
L"     ███████     "},//17

{
L"     ███████     ",//1
L"   ██       ██   ",//2
L"  █           █  ",//3
L" █    █████    █ ",//4
L" █   ███████   █ ",//5
L"█    ██   ██    █",//6
L"█         ██    █",//7
L"█      ████     █",//8
L"█      ████     █",//9
L"█         ██    █",//10
L"█         ██    █",//11
L"█    ██   ██    █",//12
L" █   ███████   █ ",//13
L" █    █████    █ ",//14
L"  █           █  ",//15
L"   ██       ██   ",//16
L"     ███████     "},//17
};
const vector<vector<wstring>> BIG_NUMBER1 = {
	//1 O VUONG = 2 CUC
{
L"███████",
L"██   ██",
L"██   ██",
L"██   ██",
L"██   ██",
L"███████"},

{
L"  ███  ",
L" █ ██  ",
L"█  ██  ",
L"   ██  ",
L"   ██  ",
L"███████"},

{
L"███████",
L"     ██",
L"▄▄▄▄▄██",
L"██▀▀▀▀▀",
L"██     ",
L"███████"},

{
L"███████",
L"     ██",
L"▄▄▄▄▄██",
L"▀▀▀▀▀██",
L"     ██",
L"███████"}
};
const vector<vector<wstring>> LETTER = {
 {  L"█▀█",
	L"█▀█",
	L"▀ ▀"},
 {  L"█▀█",
	L"█▀▄",
	L"▀▀▀"},
{   L"█▀▀",
	L"█  ",
	L"▀▀▀"},
 {  L"█▀▄",
	L"█ █",
	L"▀▀ "},
 {  L"█▀▀",
	L"█▀▀",
	L"▀▀▀"},
 {  L"█▀▀",
	L"█▀▀",
	L"▀  "},
 {  L"█▀▀",
	L"█ █",
	L"▀▀▀"},
 {  L"█ █",
	L"█▀█",
	L"▀ ▀"},
 {  L"▀█▀",
	L" █ ",
	L"▀▀▀"},
 {  L"  █",
	L"▄ █",
	L"▀▀▀"},
 {  L"█ █",
	L"█▀▄",
	L"▀ ▀"},
 {  L"█  ",
	L"█  ",
	L"▀▀▀"},
 {  L"█▄█",
	L"█ █",
	L"▀ ▀"},
 {  L"▄ █",
	L"█▀█",
	L"▀  "},
 {  L"█▀█",
	L"█ █",
	L"▀▀▀"},
 {  L"█▀█",
	L"█▀▀",
	L"▀  "},
 {  L"█▀█",
	L"▀▀█",
	L"  ▀"},
 {  L"█▀▄",
	L"█▀▄",
	L"▀ ▀"},
 {  L"█▀▀",
	L"▀▀█",
	L"▀▀▀"},
 {  L"▀█▀",
	L" █ ",
	L" ▀ "},
 {  L"█ █",
	L"█ █",
	L"▀▀▀"},
 {  L"█ █",
	L"█ █",
	L" ▀ "},
 {  L"█ █",
	L"█▄█",
	L"▀ ▀"},
 {  L"█ █",
	L"▄▀▄",
	L"▀ ▀"},
 {  L"█ █",
	L" █ ",
	L" ▀ "},
 {  L"▀▀█",
	L"▄▀ ",
	L"▀▀▀"}
};

const vector<wstring> PAUSE_MENU = {
		//01234567890123456789012345678901234567890123456789012
		L"▄▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄",//0
		L"█  ▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄  █",//1
		L"█  █ █               █                           █  █",//2
		L"█  █ █               █                           █  █",//3
		L"█  █ █               █                           █  █",//4
		L"█  █ █               █                           █  █",//5
		L"█  █ █               █                           █  █",//6
		L"█  █ █               █                           █  █",//7
		L"█  █ █               █                           █  █",//8
		L"█  █ ▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀                           █  █",//9
		L"█  █      ▄             ▄                ▄▄▄     █  █",//10
		L"█  █   ▄▄██ ▄ █         ██▄▄            █   █    █  █",//11
		L"█  █   ████ █ █         ████▀             █▀     █  █",//12
		L"█  █     ▀█   ▀         █▀                ▄      █  █",//13
		L"█  █                                             █  █",//14
		L"█  █   █▀▀▀▀▀█         █▀▀▀▀▀█         █▀▀▀▀▀█   █  █",//15
		L"█  █   █     █         █     █         █     █   █  █",//16
		L"█  █   █     █         █     █         █     █   █  █",//17
		L"█  █   ▀▀▀▀▀▀▀         ▀▀▀▀▀▀▀         ▀▀▀▀▀▀▀   █  █",//18
		L"█  █           ▄▄▄▄▄▄             ▄              █  █",//19
		L"█  █           █▄▄█▄██         ▄▀ █ ▀▄           █  █",//20
		L"█  █           █     █         █  ▀  █           █  █",//21
		L"█  █           █▄▄▄▄▄█          ▀▄▄▄▀            █  █",//22
		L"█  █                                             █  █",//23
		L"█  █           █▀▀▀▀▀█         █▀▀▀▀▀█           █  █",//24
		L"█  █           █     █         █     █      ▄▄▄▄▄█  █",//25
		L"█  █           █     █         █     █      █  ▄▀   █",//26
		L"█  █           ▀▀▀▀▀▀▀         ▀▀▀▀▀▀▀      █▄▀     █",//27
		L"█  ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀       █",//28
		L"▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀" //29
};

const vector<wstring> CHOOSE_CHARACTER_MENU = {
		L"▄▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄",//0
		L"█  ▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▄▄▄  █",//1
		L"█  █ █               █                           █  █",//2
		L"█  █ █               █                           █  █",//3
		L"█  █ █               █                           █  █",//4
		L"█  █ █               █                           █  █",//5
		L"█  █ █               █                           █  █",//6
		L"█  █ █               █                           █  █",//7
		L"█  █ █               █                           █  █",//8
		L"█  █ ▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀                           █  █",//9
		L"█  █                                             █  █",//10
		L"█  █  █▀▀▀▀▀█       █▀▀▀▀▀█       █▀▀▀▀▀█        █  █",//11
		L"█  █  █     █       █     █       █     █        █  █",//12
		L"█  █  █     █       █     █       █     █        █  █",//13
		L"█  █  ▀▀▀▀▀▀▀       ▀▀▀▀▀▀▀       ▀▀▀▀▀▀▀        █  █",//14
		L"█  █                                             █  █",//15
		L"█  █                                             █  █",//16
		L"█  █  █▀▀▀▀▀█       █▀▀▀▀▀█       █▀▀▀▀▀█        █  █",//17
		L"█  █  █     █       █     █       █     █        █  █",//18
		L"█  █  █     █       █     █       █     █        █  █",//19
		L"█  █  ▀▀▀▀▀▀▀       ▀▀▀▀▀▀▀       ▀▀▀▀▀▀▀        █  █",//20
		L"█  █                                             █  █",//21
		L"█  █                                             █  █",//22
		L"█  █  █▀▀▀▀▀█       █▀▀▀▀▀█       █▀▀▀▀▀█        █  █",//23
		L"█  █  █     █       █     █       █     █        █  █",//24
		L"█  █  █     █       █     █       █     █   ▄▄▄▄▄█  █",//25
		L"█  █  ▀▀▀▀▀▀▀       ▀▀▀▀▀▀▀       ▀▀▀▀▀▀▀   █  ▄▀   █",//26
		L"█  █                                        █▄▀     █",//27
		L"█  ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀       █",//28
		L"▀▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀" //29
};

const vector<wstring> Drawer = {
//012345678901234567890123456
L"        ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄ ",
L"        █████████▀▀▀▀█████ ",
L"        ██████████████████ ",
L"        ██████████████████ ",
L"        ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄ ",
L"        █████████▀▀▀▀█████ ",
L"        ██████████████████ ",
L"        ██████████████████ ",
L"        ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄ ",
L"        █████████▀▀▀▀█████ ",
L"        ██████████████████ ",
L"        ██████████████████ ",
L"        ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄ ",
L"        █████████▀▀▀▀█████ ",
L"        ██████████████████ ",
L"        ██████████████████ ",
L"        ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄ ",
L"        █████████▀▀▀▀█████ ",
L"        ██████████████████ ",
L"        ██████████████████ ",
L"        ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄ ",
L"        █████████▀▀▀▀█████ ",
L"        ██████████████████ ",
L"        ██████████████████ "
};
const vector<wstring> SmallDrawer = {
	//0123456789012345678901234567890	
	L"               ▄▀▀▀▀▀▀▀▀▀▀▀▀▄  ",//0
	L"              ████████████████ ",//1
	L"              ████████████████ ",//2
	L"             ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",//3
	L"             █████████▀▀▀▀█████",//4
	L"             ██████████████████",//5
	L"             ██████████████████",//6
};


const vector<wstring> FLOPPY_DISC = {
		L"██████████████████████████████████████████████████    ",//0
		L"██                                                ██  ",//1
		L"██                              █████               ██",//2
		L"██                              █████               ██",//3
		L"██                              █████               ██",//4
		L"██                              █████               ██",//5
		L"██                              █████               ██",//6
		L"██                              █████               ██",//7
		L"██                              █████               ██",//8
		L"██                              █████               ██",//9
		L"██                                                  ██",//10
		L"██                                                  ██",//11
		L"██                                                  ██",//12
		L"██        ██████████████████████████████████        ██",//13
		L"██        ██████████████████████████████████        ██",//14
		L"██        ██████████████████████████████████        ██",//15
		L"██                                                  ██",//16
		L"██                                                  ██",//17
		L"██                                                  ██",//18
		L"██                                                  ██",//19
		L"██                                                  ██",//20
		L"██                                                  ██",//21
		L"██                          ████       ████         ██",//22
		L"██                        ██    ██   ██    ██       ██",//23
		L"██                        ██    ██   ██    ██       ██",//24
		L"██                          ████       ████         ██",//25
		L"██                                                  ██",//26
		L"██                                                  ██",//27
		L"██████████████████████████████████████████████████████"//28
};

const vector<wstring> FLOPPY_DISC_2 = {
		L"██████████████████████████████████████████████████    ",//0
		L"██                                                ██  ",//1
		L"██                              █████               ██",//2
		L"██                              █████               ██",//3
		L"██                              █████               ██",//4
		L"██                              █████               ██",//5
		L"██                              █████               ██",//6
		L"██                              █████               ██",//7
		L"██                              █████               ██",//8
		L"██                              █████               ██",//9
		L"██                                                  ██",//10
		L"██                                                  ██",//11
		L"██                                                  ██",//12
		L"██        ██████████████████████████████████        ██",//13
		L"██        ██████████████████████████████████        ██",//14
		L"██        ██████████████████████████████████        ██",//15
		L"██                                                  ██",//16
		L"██        ██████████████████████████████████        ██",//17
		L"██        ██████████████████████████████████        ██",//18
		L"██        ██████████████████████████████████        ██",//19
		L"██                                                  ██",//20
		L"██                                                  ██",//21
		L"██                          ████       ████         ██",//22
		L"██                        ██    ██   ██    ██       ██",//23
		L"██                        ██    ██   ██    ██       ██",//24
		L"██                          ████       ████         ██",//25
		L"██                                                  ██",//26
		L"██                                                  ██",//27
		L"██████████████████████████████████████████████████████"//28
};


const vector<wstring> TAGS = {
L"   ▄▄█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█",
L"▄█▀▀ ▄                                 █",
L"█▄  ▀█                                 █",
L" ▀▀█▄▄                                 █",
L"     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀"
};

const vector<wstring> infinite = {
	L"▄█▀▀█▄ ▄█▀▀█▄",
	L"█    ▄█▀    █",
	L"▀█▄▄█▀ ▀█▄▄█▀"
};

const vector<wstring>DINOSAUR_PICTURE = {
L"       ▄▄▀▀▀▄▄       ",
L"▄▄▄▄▄▀▀▄▄▄▄▄▄▄▀▀▄▄▄▄▄",
L"█                   █",
L"█    ▄▀▀▀▀▀▀▀▀▀▄    █",
L"█    █ ██      █    █",
L"█    █         █    █",
L"█  █▀█  ▀▀▀▄▄▄▄▀    █",
L"█   ▀▄ ▄▄▄▄█        █",
L"█    █▀  █▀         █",
L"█                   █",
L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀"
};
const vector<wstring>BIG_DINASOUR = {
L"                      █▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█  ",
L"                    █▀▀                ▀▀█",
L"                    █      ███           █",
L"                    █      ▀▀▀           █",
L"                    █                    █",
L"                    █                    █",
L"                    █           ▄▄▄▄▄▄▄▄▄█",
L"                    █           ▀▀▀▀▀█    ",
L"█▀▀█               █▀          ▄▄▄▄▄▄█    ",
L"█  █            █▀▀▀           █          ",
L"█  ▀▀█      █▀▀▀▀              ▀▀▀▀█      ",
L"█    ▀▀█▄▄█▀▀             ▄▄▄▄▄▄▄  █      ",
L"█                       █████████▄▄█      ",
L"█                     ██████████          ",
L" █                    ██████████          ",
L"  █                   ████████▀▀          ",
L"   █                     ▄▄█▀▀            ",
L"    █▄▄▄▄▄▄    ▄▄▄    ▄▄█▀                ",
L"          █  ▄▀   ▀▄  █                   ",
L"          █  █     █  █                   "};
const vector<wstring>HAT = {
L"      ▄██▄     ",
L"    ▄▀▀▀████   ",
L"██▄▄▀▀█████▄   ",
L" ▀▀███████████▄",
L"     ▀▀▀▀▀▀▀▀  ",
};
const vector<wstring>FRAME_CLOUD_1 = {
L"     ▄▀▀▄      ",
L" ▄▀▀▀    ▀▀▀▀▄ ",
L"█             █",
L" ▀▄▄▄▄▄▄▄▄▄▄▄▀ "
};
const vector<wstring>FRAME_CLOUD_2 = {
L"  ▄▄ ▄▀▀▄ ▄▄▄  ",
L"▄▀  ▀    ▀   ▀▄",
L"█             █",
L" ▀▄▄▄▄▄▄▄▄▄▄▄▀ ",
};
const vector<wstring>PERRY_TALK = {
//012345678901234567890123456789012345678901234567890123456789012
L" ▄█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█▄                       ",//0
L"█▀                                     ▀█                      ",//1
L"█                                       █                      ",//2
L"█                                       █                      ",//3
L"█                                       █                      ",//4
L"█                                       █                      ",//5
L"█                                       █                      ",//6
L"█                                       █                      ",//7
L"▀█▄                                   ▄█▀                      ",//8
L"  ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█   █▀▀▀▀                        ",//9
L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄  █▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",//10
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▀▄  █▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",//11
L"                                  ▀▄▄█                         ",//12
L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",//13
L"                                       ▄▄▀▄▄▄▄▄▄▄▄▄▄▄▄         ",//14
L"                                      ██▄█████████████ ▄▄▄▀▀▀▀▄",//15
L"                                     ▄▄▄██▄███████████▀▄▀█▀▄█▄▀",//16
L"                                      ▀▀▀▄█▀██▀▀██▀▀██▀▀▀▀     ",//17
L"                                         ▀▀ ▀▀ ▀▀▀ ▀▀▀         " //18
};

const vector <wstring> DOOF_CORP = {
//0123456789012345678901
L"    ▄▄▄  █  ▄▄▄       ",//0
L"  ▄▄▄ ▀▄ █ ▄▀ ▄▄▄     ",//1
L" ▄   ▀▄▀▄█▄▀▄▀   ▄    ",//2
L"███████████████████   ",//3
L" █▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█    ",//4
L" █               █    ",//5
L" ██             ██    ",//6
L" ▀███████████████▀    ",//7
L"  ███████████████     ",//8
L"  ██▀▀▀▀▀█████████████",//9
L"  █▀     █████████████",//10
L"         ████████████▀",//11
L"         ████████████ ",//12
L"█████████████████████ ",//13
L"███████████████       ",//14
L"███████████████       ",//15
L"███████████████       ",//16
L"███████████████       ",//17
L" ██████████████       ",//18
L" █████████████        ",//19
L" █████████████        "///20
};

const vector <wstring> MAIN_MENU_FRAME = {
//0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
L"                                            ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄    ",//0
L"                                            ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████    ",//1
L"                                            ███                                                                                                                                                          ███    ",//2
L"                                            ███                                                                                                                                                          ███    ",//3
L"                                            ███                                                                                                                                                          ███    ",//4
L"                                            ███                                                                                                                                                          ███    ",//5
L"                                            ███                                                                                                                                                          ███    ",//6
L"                                            ███                                                                                                                                                          ███    ",//7
L"                                            ███                                                                                                                                                          ███    ",//8
L"                                            ███                                                                                                                                                          ███    ",//9
L"                                            ███                                                                                                                                                          ███    ",//10
L"                                            ███                                                                                                                                                          ███    ",//11
L"                                            ███                                                                                                                                                          ███    ",//12
L"                                            ███                                                                                                                                                          ███    ",//13
L"                                            ███                                                                                                                                                          ███    ",//14
L"                                            ███                                                                                                                                                          ███    ",//15
L"                                            ███                                                                                                                                                          ███    ",//16
L"                                            ███                                                                                                                                                          ███    ",//17
L"                                            ███                                                                                                                                                          ███    ",//18
L"                                            ███                                                                                                                                                          ███    ",//19
L"                                            ███                                                                                                                                                          ███    ",//20
L"                                            ███                                                                                                                                                          ███    ",//21
L"                                            ███                                                                                                                                                          ███    ",//22
L"                                            ███                                                                                                                                                          ███    ",//23
L"                                            ███                                                                                                                                                          ███    ",//24
L"                                            ███                                                                                                                                                          ███    ",//25
L"                                            ███                                                                                                                                                          ███    ",//26
L"                                            ███                                                                                                                                                          ███    ",//27
L"                                            ███                                                                                                                                                          ███    ",//28
L"                                            ███                                                                                                                                                          ███    ",//29
L"                                            ███                                                                                                                                                          ███    ",//30
L"                                            ███                                                                                                                                                          ███    ",//31
L"                                            ███                                                                                                                                                          ███    ",//32
L"                                            ███                                                                                                                                                          ███    ",//33
L"                                            ███                                                                                                                                                          ███    ",//34
L"                                            ███                                                                                                                                                          ███    ",//35
L"                                            ███                                                                                                                                                          ███    ",//36
L"                                            ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████    ",//37
L"                                            ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀    ",//38
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",//39
L"████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████",//40
L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",//41
L"                                                                                                                                                                                                                ",//42
L"                                                                                                                                                                                                                ",//43
L"                                                                                                                                                                                                                ",//44
L"                                                                                                                                                                                                                ",//45
L"                                                                                                                                                                                                                ",//46
L"                                                                                                                                                                                                                ",//47
L"                                                                                                                                                                                                                ",//48
L"                                                                                                                                                                                                                ",//49
L"                                                                                                                                                                                                                ",//50
};

const vector<wstring> HEADER = {
	//01234567890123456789012345678901234567890123456789012345
	L"  ▄▀▀▀▀▀▄  ▄▀▀▀▀▀▄  ▄▀▀▀▀▀▄  ▄▀▀▀▀▀▄  ▄▀▀▀▀▀▄  ▄▀▀█▀▀▄  ",//0
	L"█▀█     █▀▀█  ▄  █▀▀█     █▀▀█   ▄▄█▀▀█   ▄▄█▀▀█  ▀  █▀█",//1
	L"█ █  ▀▀▀▄  █    ▄█  █  ▀  █  █▄▄   █  █▄▄   █  ▀▄   ▄▀ █",//2
	L"▀▀█     █▀▀█  █  █▀▀█     █▀▀█     █▀▀█     █▀▀▀█   █▀▀▀",//3
	L"   ▀▀▀▀▀    ▀▀ ▀▀    ▀▀▀▀▀    ▀▀▀▀▀    ▀▀▀▀▀     ▀▀▀    ",//4
	L"            ▄▄▄▄▄    ▄▄▄▄▄    ▄▄▄▄▄   ▄▄▄▄▄▄            ",//5
	L"        ▄▄▄█     █▄▄█     █▄▄█     █▄▄█     █▄▄▄        ",//6
	L"        █  █  ▀  █  █  ▄  █  █  ▀  █  █  ▄  █  █        ",//7
	L"        █▄▄█  ▄ ▀█▄▄█     █▄▄█  ▄  █▄▄█     █▄▄█        ",//8
	L"           ▀▄▄█▄▄▀  ▀▄▄▄▄▄▀  ▀▄▄▀▄▄▀  █▄▄▄▄▄▀           "//9
};