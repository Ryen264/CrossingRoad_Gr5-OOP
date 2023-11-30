#include "CGRAPHIC.h"
int BLACK, SKY_BLUE, WHITE, DARK_GREEN,
SADDLE_BROWN, DARK_RED, RED, ORANGE,
BLUE, DARK_BLUE, DARK_GRAY, LIGHT_GRAY,
SAND, BRIGHT_YELLOW, LIGHT_GREEN, LIGHT_BROWN;

void SetupTheme(THEME theme) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX csbiex{};
	csbiex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hStdout, &csbiex);

	//setup colors
	for (int i = 0; i < 16; i++)
		csbiex.ColorTable[i] = theme.colorTable[i];

	//setup color ids
	BLACK = theme.BLACK; SKY_BLUE = theme.SKY_BLUE; WHITE = theme.WHITE; DARK_GREEN = theme.DARK_GREEN;
	SADDLE_BROWN = theme.SADDLE_BROWN; DARK_RED = theme.DARK_RED; RED = theme.RED; ORANGE = theme.ORANGE;
	BLUE = theme.BLUE; DARK_BLUE = theme.DARK_BLUE; DARK_GRAY= theme.DARK_GRAY; LIGHT_GRAY = theme.LIGHT_GRAY;
	SAND = theme.SAND; BRIGHT_YELLOW = theme.BRIGHT_YELLOW; LIGHT_GREEN = theme.LIGHT_GREEN; LIGHT_BROWN = theme.LIGHT_BROWN;
	SetConsoleScreenBufferInfoEx(hStdout, &csbiex);
}

CGRAPHIC::CGRAPHIC(PIXEL** screen) {
	this->screen = new PIXEL * [SCREEN_WIDTH];
	for (int i = 0; i < SCREEN_WIDTH; i++)
		this->screen[i] = new PIXEL[SCREEN_HEIGHT];
	if (screen != NULL) {
		for (int x = 0; x < SCREEN_WIDTH; x++)
			for (int y = 0; y < SCREEN_HEIGHT; y++)
				this->screen[x][y] = screen[x][y];
	}
}
CGRAPHIC::~CGRAPHIC() {
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		delete[] this->screen[i];
		this->screen[i] = NULL;
	}
	delete[] this->screen;
	this->screen = NULL;
}

void CGRAPHIC::display(int fromX, int fromY, int toX, int toY) {
	if (toX < 0 || toX > SCREEN_WIDTH - 1) toX = SCREEN_WIDTH - 1;
	if (toY < 0 || toY > SCREEN_HEIGHT - 1) toY = SCREEN_HEIGHT - 1;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWritten = 0;
	wchar_t pBuffer{};
	WORD pColor;

	for (int y = fromY; y <= toY; y++)
		for (int x = fromX; x <= toX; x++) {
			auto& currentScreen = screen[x][y];
			pBuffer = (currentScreen.buffer == L'@') ? L' ' : currentScreen.buffer;
			COORD cPos = { x, y };
			WriteConsoleOutputCharacter(hStdout, &pBuffer, 1, cPos, &dwBytesWritten);

			pColor = currentScreen.bgdColor * 16 + currentScreen.txtColor;
			WriteConsoleOutputAttribute(hStdout, &pColor, 1, cPos, &dwBytesWritten);
		}
}
void CGRAPHIC::clear(int txtColor, int bgdColor) {
	for (int x = 0; x < SCREEN_WIDTH; x++)
		for (int y = 0; y < SCREEN_HEIGHT; y++)
			this->screen[x][y] = { L' ', txtColor, bgdColor };
}
void CGRAPHIC::Text(wstring wsContent, int first_x, int first_y, int txtColor, int bgdColor) {
	int x = first_x, y = first_y;
	for (int i = 0; i < wsContent.length(); i++) {
		if (x + i < SCREEN_WIDTH && y < SCREEN_HEIGHT) {
			this->screen[x + i][y] = { wsContent[i], txtColor, bgdColor };
		}
	}
}

void CGRAPHIC::DrawObject(vector<wstring> contentsArr, int first_x, int first_y, int txtColor, int bgdColor) {
	int x = first_x, y = first_y;

	for (int i = 0; i < contentsArr.size(); i++) {
		if (y + i < SCREEN_HEIGHT) {
			for (int j = 0; j < contentsArr[i].length(); j++) {
				if (x + j < SCREEN_WIDTH) {
					this->screen[x + j][y + i] = { contentsArr[i][j], txtColor, bgdColor };
				}
			}
		}
	}
}

void CGRAPHIC::DrawPauseMenu(vector<wstring> PauseMenu, int first_x, int first_y) {
	vector<wstring> frame = PAUSE_MENU;
	//set buffer
	for (int i = 0; i < 52; i++)
		for (int j = 0; j < 30;	 j++)
			screen[first_x + i][j] = { frame[j][i], BLACK, DARK_BLUE };
	//set colors
	for (int i = 0; i < 5; i++) {
		screen[first_x + i][first_y + 0].bgdColor = -1;
		screen[first_x + 47 + i][first_y + 0].bgdColor = -1;
	}
	screen[first_x+0][first_y + 1].bgdColor = -1;
	screen[first_x + 1][first_y + 1].bgdColor = -1;
	screen[first_x + 0][first_y + 2].bgdColor = -1;
	screen[first_x+ 51][first_y + 1].bgdColor = -1;
	screen[first_x + 50][first_y + 1].bgdColor = -1;
	screen[first_x + 51][first_y + 2].bgdColor = -1;
	for (int i = 0; i < 18; i++) {
		screen[first_x + 17 + i][first_y + 0].bgdColor = LIGHT_GRAY;
		screen[first_x + 17 + i][first_y + 1].bgdColor = LIGHT_GRAY;
	}
	for (int i = 4; i < 48; i++)
		for (int j = 2; j < 28; j++)
			screen[first_x + i][first_y + j].bgdColor = SAND;
	screen[first_x + 47][first_y + 26].bgdColor = DARK_BLUE;
	screen[first_x + 45][first_y + 27].bgdColor = DARK_BLUE;
	screen[first_x + 46][first_y + 27].bgdColor = DARK_BLUE;
	screen[first_x + 47][first_y + 27].bgdColor = DARK_BLUE;
	for (int i = 7; i <= 14; i++)
		for (int j = 10; j <= 13; j++)
			screen[first_x + i][first_y + j].txtColor = DARK_GRAY;
	for (int i = 24; i <= 28; i++)
		for (int j = 10; j <= 13; j++)
			screen[first_x + i][first_y + j].txtColor = DARK_GREEN;
	for (int i = 39; i <= 43; i++)
		for (int j = 10; j <= 13; j++)
			screen[first_x + i][first_y + j].txtColor = BRIGHT_YELLOW;
	for (int i = 15; i <= 22; i++)
		for (int j = 19; j <= 22; j++)
			screen[first_x + i][first_y + j].txtColor = DARK_BLUE;
	screen[first_x + 16][first_y + 19].txtColor = LIGHT_GRAY;
	screen[first_x + 17][first_y + 19].txtColor = WHITE;
	screen[first_x + 19][first_y + 19].txtColor = LIGHT_GRAY;
	screen[first_x + 16][first_y + 20].bgdColor = LIGHT_GRAY;
	screen[first_x + 17][first_y + 20].bgdColor = LIGHT_GRAY;
	screen[first_x + 19][first_y + 20].bgdColor = WHITE;
	screen[first_x + 16][first_y + 21].bgdColor = LIGHT_GRAY;
	screen[first_x + 17][first_y + 21].bgdColor = WHITE;
	screen[first_x + 18][first_y + 21].bgdColor = WHITE;
	screen[first_x + 19][first_y + 21].bgdColor = WHITE;
	screen[first_x + 20][first_y + 21].bgdColor = LIGHT_GRAY;
	screen[first_x + 16][first_y + 22].bgdColor = LIGHT_GRAY;
	screen[first_x + 17][first_y + 22].bgdColor = LIGHT_GRAY;
	screen[first_x + 18][first_y + 22].bgdColor = LIGHT_GRAY;
	screen[first_x + 19][first_y + 22].bgdColor = WHITE;
	screen[first_x + 20][first_y + 22].bgdColor = LIGHT_GRAY;
	for (int i = 31; i <= 39; i++)
		for (int j = 19; j <= 22; j++)
			screen[first_x + i][first_y + j].txtColor = RED;
	for (int i = 6; i <= 20; i++)
		for (int j = 2; j <= 8; j++)
			screen[first_x + i][first_y + j].bgdColor = WHITE;
	for (int i = 10; i <= 18; i++)
		for (int j = 3; j <= 5; j++)
			screen[first_x + i][first_y + j].bgdColor = DARK_GREEN;
	screen[first_x + 8][first_y + 6].bgdColor = DARK_GREEN;
	screen[first_x + 9][first_y + 6].bgdColor = DARK_GREEN;
	screen[first_x + 10][first_y + 6].bgdColor = DARK_GREEN;
	screen[first_x + 11][first_y + 6].bgdColor = DARK_GREEN;
	screen[first_x + 10][first_y + 7].bgdColor = DARK_GREEN;
	screen[first_x + 12][first_y + 6].bgdColor = LIGHT_GREEN;
	screen[first_x + 13][first_y + 6].bgdColor = LIGHT_GREEN;
	screen[first_x + 14][first_y + 6].bgdColor = LIGHT_GREEN;
}

void CGRAPHIC::DrawDrawer(vector<wstring> contentsArr, int first_x, int first_y, int txtColor, int bgdColor)
{
	vector<wstring> frame = Drawer;
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			this->screen[first_x + i][j] = { frame[j][i], BLACK, -1 };
	int x = first_x;
	int y = first_y;
	for (int j = 0; j < 26; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			this->screen[x + i][y + j].bgdColor = SADDLE_BROWN;
		}
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x + i][y].bgdColor = LIGHT_BROWN;
	}
	for (int j = 1; j < 3; j++)
	{
		for (int i = 8; i < 26; i++)
		{
			this->screen[x + i][y + j].bgdColor = LIGHT_BROWN;
			this->screen[x + i][y + j].txtColor = SADDLE_BROWN;
		}
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x + i][y + 3].bgdColor = LIGHT_BROWN;
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x + i][y + 4].bgdColor = LIGHT_BROWN;
	}
	this->screen[26][4].bgdColor = BLACK;
	for (int i = 8; i < 26; i++)
	{
		this->screen[x + i][y + 5].bgdColor = LIGHT_BROWN;
		this->screen[x + i][y + 5].txtColor = SADDLE_BROWN;
	}
	for (int j = 6; j < 8; j++)
	{
		for (int i = 8; i < 26; i++)
		{
			this->screen[x + i][y + j].bgdColor = LIGHT_BROWN;
		}
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x + i][y + 8].bgdColor = LIGHT_BROWN;
	}
	this->screen[26][8].bgdColor = BLACK;
	for (int j = 9; j < 13; j++)
	{
		for (int i = 8; i < 26; i++)
		{
			this->screen[x + i][y + j].bgdColor = LIGHT_BROWN;
			this->screen[x + i][y + j].txtColor = SADDLE_BROWN;
		}
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x + i][y + 13].bgdColor = LIGHT_BROWN;
	}
	this->screen[26][13].bgdColor = BLACK;
	for (int j = 14; j < 17; j++)
	{
		for (int i = 8; i < 26; i++)
		{
			this->screen[x + i][y + j].bgdColor = LIGHT_BROWN;
			this->screen[x + i][y + j].txtColor = SADDLE_BROWN;
		}
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x + i][17].bgdColor = LIGHT_BROWN;
	}
	this->screen[26][17].bgdColor = BLACK;
	for (int j = 18; j < 22; j++)
	{
		for (int i = 8; i < 26; i++)
		{
			this->screen[x + i][y + j].bgdColor = LIGHT_BROWN;
			this->screen[x + i][y + j].txtColor = SADDLE_BROWN;
		}
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x + i][y + 22].bgdColor = LIGHT_BROWN;
	}
	this->screen[26][22].bgdColor = BLACK;
	for (int j = 23; j < 26; j++)
	{
		for (int i = 8; i < 26; i++)
		{
			this->screen[x + i][y + j].bgdColor = LIGHT_BROWN;
			this->screen[x + i][y + j].txtColor = SADDLE_BROWN;
		}
	}
}

void CGRAPHIC::DrawSmallDrawer(vector<wstring> contentsArr, int first_x, int first_y, int txtColor, int bgdColor)
{
	vector<wstring> frame = SmallDrawer;
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			this->screen[first_x + i][j] = { frame[j][i], BLACK, -1 };
	int x = first_x;
	int y = first_y;
}
