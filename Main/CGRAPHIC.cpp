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
	WIDTH = SCREEN_WIDTH; HEIGHT = SCREEN_HEIGHT;
	this->screen = new PIXEL * [SCREEN_WIDTH];
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		this->screen[i] = new PIXEL[SCREEN_HEIGHT];
		if (screen == NULL) {
			for (int j = 0; j < SCREEN_HEIGHT; j++)
				this->screen[i][j] = { L' ', BLACK, WHITE };
		}
		else {
			for (int j = 0; j < SCREEN_HEIGHT; j++)
				this->screen[i][j] = screen[i][j];
		}
	}
}
CGRAPHIC::CGRAPHIC(PIXEL pixel, int fromX, int fromY, int toX, int toY) {
	if (toX < 0) toX = SCREEN_WIDTH;
	if (toY < 0) toY = SCREEN_HEIGHT;
	WIDTH = toX - fromX + 1; HEIGHT = toY - fromY + 1;
	this->screen = new PIXEL * [WIDTH];
	for (int i = 0; i < WIDTH; i++) {
		this->screen[i] = new PIXEL[HEIGHT];
		for (int j = 0; j < HEIGHT; j++)
			this->screen[i][j] = pixel;
	}
}
CGRAPHIC::~CGRAPHIC() {
	for (int i = 0; i < WIDTH; i++) {
		delete[] this->screen[i];
		this->screen[i] = NULL;
	}
	delete[] this->screen;
	this->screen = NULL;
}

void CGRAPHIC::displayPixel(int x, int y) {
	if (x < 0) x = 0;
	if (x > SCREEN_WIDTH - 1) x = SCREEN_WIDTH - 1;
	if (y < 0) y = 0;
	if (y > SCREEN_HEIGHT - 1) y = SCREEN_HEIGHT - 1;

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWritten = 0;
	COORD cPos = { x, y };
	wchar_t pBuffer = screen[x][y].buffer;
	WORD pColor = screen[x][y].bgdColor * 16 + screen[x][y].txtColor;

	WriteConsoleOutputCharacter(hStdout, &pBuffer, 1, cPos, &dwBytesWritten);
	WriteConsoleOutputAttribute(hStdout, &pColor, 1, cPos, &dwBytesWritten);
}
void CGRAPHIC::display(int fromX, int fromY, int toX, int toY) {
	if (fromX < 0 || fromX > SCREEN_WIDTH - 1) fromX = 0;
	if (fromY < 0 || fromY > SCREEN_HEIGHT - 1) fromY = 0;
	if (toX < 0 || toX > SCREEN_WIDTH - 1) toX = SCREEN_WIDTH - 1;
	if (toY < 0 || toY > SCREEN_HEIGHT - 1) toY = SCREEN_HEIGHT - 1;

	for (int y = fromY; y <= toY; y++)
		for (int x = fromX; x <= toX; x++)
			if (screen[x][y].txtColor >= 0) displayPixel(x, y);
}
void CGRAPHIC::clear(int txtColor, int bgdColor) {
	for (int x = 0; x < SCREEN_WIDTH; x++)
		for (int y = 0; y < SCREEN_HEIGHT; y++)
			this->screen[x][y] = { L' ', txtColor, bgdColor };
}
void CGRAPHIC::Text(wstring wsContent, int first_x, int first_y, int txtColor, int bgdColor) {
	int x = first_x, y = first_y;
	for (int i = 0; i < wsContent.length(); i++)
		if (x + i < SCREEN_WIDTH && y < SCREEN_HEIGHT) this->screen[x + i][y] = { wsContent[i], txtColor, bgdColor };
}
void CGRAPHIC::DrawObject(vector<wstring> contentsArr, int first_x, int first_y, int txtColor, int bgdColor) {
	int x = first_x, y = first_y;
	for (int i = 0; i < contentsArr.size(); i++) {
		if (y + i < SCREEN_HEIGHT) {
			for (int j = 0; j < contentsArr[i].length(); j++)
				if (x + j < SCREEN_WIDTH) this->screen[x + j][y + i] = { contentsArr[i][j], txtColor, bgdColor };
		}
	}
}
void CGRAPHIC::DrawPauseMenu(int first_x, int first_y) {
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
void CGRAPHIC::DrawDrawer(int first_x, int first_y)
{
	vector<wstring> frame = Drawer;
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			this->screen[first_x + i][j] = { frame[j][i], BLACK, -1 };
	int x = first_x;
	int y = first_y;
	for (int j = 1; j < 26; j++)
	{
		for (int i = 1; i < 8; i++)
		{
			this->screen[x+i][y+j].txtColor = SADDLE_BROWN;
		}
	}
	for (int i = 1; i < 8; i++)
	{
		this->screen[x+i][y].bgdColor = SADDLE_BROWN;
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x+i][y].bgdColor = LIGHT_BROWN;
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x+i][y+1].txtColor = LIGHT_BROWN;
	}
	for (int i = 17; i < 21; i++)
	{
		this->screen[x+i][y+1].txtColor = LIGHT_BROWN;
		this->screen[x+i][y+1].bgdColor = SADDLE_BROWN;
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x+i][y+2].txtColor = LIGHT_BROWN;
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x+i][y+3].txtColor = LIGHT_BROWN;
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x+i][y+4].bgdColor = LIGHT_BROWN;
	}
	this->screen[x+26][y+4].bgdColor = BLACK;
	for (int i = 8; i < 26; i++)
	{
		this->screen[x+i][y+5].txtColor = LIGHT_BROWN;
	}
	for (int i = 17; i < 21; i++)
	{
		this->screen[x+i][y+5].txtColor = SADDLE_BROWN;
		this->screen[x+i][y+5].bgdColor = LIGHT_BROWN;
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x+i][y+6].txtColor = LIGHT_BROWN;
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x+i][y+7].txtColor = LIGHT_BROWN;
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x+i][y+8].bgdColor = LIGHT_BROWN;
	}
	this->screen[26][8].bgdColor = BLACK;
	for (int j = 9; j < 13; j++)
	{
		for (int i = 8; i < 26; i++)
		{
			this->screen[x+i][y+j].txtColor = LIGHT_BROWN;
		}
	}
	for (int i = 17; i < 21; i++)
	{
		this->screen[x+i][y+10].bgdColor = LIGHT_BROWN;
		this->screen[x+i][y+10].txtColor = SADDLE_BROWN;
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x+i][y+13].bgdColor = LIGHT_BROWN;
	}
	this->screen[x+26][y+13].bgdColor = BLACK;
	for (int j = 14; j < 17; j++)
	{
		for (int i = 8; i < 26; i++)
		{
			this->screen[x+i][y+j].txtColor = LIGHT_BROWN;
		}
	}
	for (int i = 17; i < 21; i++)
	{
		this->screen[x+i][y+14].txtColor = SADDLE_BROWN;
		this->screen[x+i][y+14].bgdColor = LIGHT_BROWN;
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x+i][y+17].bgdColor = LIGHT_BROWN;
	}
	this->screen[x+26][y+17].bgdColor = BLACK;
	for (int j = 18; j < 22; j++)
	{
		for (int i = 8; i < 26; i++)
		{
			this->screen[x+i][y+j].txtColor = LIGHT_BROWN;
		}
	}
	for (int i = 17; i < 21; i++)
	{
		this->screen[x+i][y+19].txtColor = SADDLE_BROWN;
		this->screen[x+i][y+19].bgdColor = LIGHT_BROWN;
	}
	for (int i = 8; i < 26; i++)
	{
		this->screen[x+i][y+22].bgdColor = LIGHT_BROWN;
	}
	this->screen[x+26][y+22].bgdColor = BLACK;
	for (int j = 23; j < 26; j++)
	{
		for (int i = 8; i < 26; i++)
		{
			this->screen[x+i][y+j].txtColor = LIGHT_BROWN;
		}
	}
	for (int i = 17; i < 21; i++)
	{
		this->screen[x+i][y+23].txtColor = SADDLE_BROWN;
		this->screen[x+i][y+23].bgdColor = LIGHT_BROWN;
	}
}
void CGRAPHIC::DrawSmallDrawer(int first_x, int first_y, int drawerColor)
{
	vector<wstring> frame = SmallDrawer;
	for (int i = 0; i < 34; i++)
		for (int j = 0; j < 8; j++)
			this->screen[first_x + i][j] = { frame[j][i], BLACK, -1 };
	int x = first_x, y = first_y;
	this->screen[x+16][y].bgdColor = drawerColor;
	this->screen[x+17][y].bgdColor = drawerColor;
	for (int i = 18; i < 26; i++)
	{
		this->screen[x+i][y].bgdColor = WHITE;
	}
	this->screen[x+26][y].bgdColor = drawerColor;
	this->screen[x+27][y].bgdColor = drawerColor;
	for (int j = 1; j < 3; j++)
	{
		for (int i = 15; i < 29; i++)
		{
			this->screen[x+i][y+j].txtColor = drawerColor;
		}
	}

	for (int i = 1; i < 13; i++)
	{
		this->screen[x+i][y+3].bgdColor = SADDLE_BROWN;
	}
	for (int j = 4; j < 7; j++)
	{
		for (int i = 1; i < 13; i++)
		{
			this->screen[x+i][y+j].txtColor = SADDLE_BROWN;
		}
	}
	for (int i = 13; i < 33; i++)
	{
		this->screen[x+i][y+3].bgdColor = LIGHT_BROWN;
	}
	for (int i = 13; i < 22; i++)
	{
		this->screen[x+i][y+4].txtColor = LIGHT_BROWN;
	}
	for (int i = 22; i < 26; i++)
	{
		this->screen[x+i][y+4].txtColor = LIGHT_BROWN;
		this->screen[x+i][y+4].bgdColor = SADDLE_BROWN;
	}
	for (int i = 22; i < 32; i++)
	{
		this->screen[x+i][y+4].txtColor = LIGHT_BROWN;
	}
	for (int j = 5; j < 7; j++)
	{
		for (int i = 13; i < 32; i++)
		{
			this->screen[x+i][y+j].txtColor = LIGHT_BROWN;
		}
	}
	for (int i = 1; i < 32; i++)
	{
		this->screen[x+i][y+7].bgdColor = SADDLE_BROWN;
	}

}
void CGRAPHIC::DrawDinasourPicture(int first_x, int first_y, int drawerColor, int Belly)
{
	vector<wstring>frame = DINOSAUR_PICTURE;
	//set buffer
	for (int i = 0; i < 22; i++)
		for (int j = 0; j < 11; j++)
			this->screen[first_x + i][first_y + j] = { frame[j][i], BLACK, DARK_GREEN };
	//set color
	int x = first_x;
	int y = first_y;
	for (int i = 9; i < 12; i++)
		{
			this->screen[x+i][y].bgdColor = SADDLE_BROWN;
		}
		for (int j = 2; j < 11; j++)
		{
			this->screen[x][y+j].txtColor = LIGHT_BROWN;
			this->screen[x+20][y+j].txtColor = LIGHT_BROWN;
		}
		for (int i = 1; i < 20; i++)
		{
			this->screen[x+i][y+10].txtColor = LIGHT_BROWN;
		}
		for (int i = 0; i < 5; i++)
		{
			this->screen[x+i][y+1].txtColor = LIGHT_BROWN;
		}
		this->screen[x+5][y+1].bgdColor = LIGHT_BROWN;
		this->screen[x+6][y+1].bgdColor = LIGHT_BROWN;
		for (int i = 7; i < 14; i++)
		{
			this->screen[x+i][y+1].txtColor = LIGHT_BROWN;
			this->screen[x+i][y+1].bgdColor = SADDLE_BROWN;
		}
		this->screen[x+14][y+1].bgdColor = LIGHT_BROWN;
		this->screen[x+15][y+1].bgdColor = LIGHT_BROWN;
		for (int i = 16; i < 21; i++)
		{
			this->screen[x+i][y+1].txtColor = LIGHT_BROWN;
		}
		for (int i = 1; i < 21; i++)
		{
			this->screen[x+i][y+2].bgdColor = WHITE;
		}
		for (int i = 1; i < 5; i++)
		{
			this->screen[x+i][y+3].bgdColor = WHITE;
		}
		this->screen[5][3].bgdColor = WHITE;
		for (int i = 6; i < 15; i++)
		{
			this->screen[x+i][y+3].bgdColor = DARK_GREEN;
		}
		for (int i = 6; i < 15; i++)
		{
			this->screen[x+i][y+4].bgdColor = DARK_GREEN;
		}
		for (int i = 6; i < 15; i++)
		{
			this->screen[x+i][y+5].bgdColor = DARK_GREEN;
		}
		for (int i = 6; i < 15; i++)
		{
			this->screen[x+i][y+6].bgdColor = DARK_GREEN;
		}
		for (int i = 8; i < 11; i++)
		{
			this->screen[x+i][y+6].txtColor = DARK_GREEN;
			this->screen[x+i][y+6].bgdColor = LIGHT_GREEN;
		}
		this->screen[x+4][y+6].bgdColor = DARK_GREEN;
		for (int i = 8; i < 11; i++)
		{
			this->screen[i][7].bgdColor = LIGHT_GREEN;
		}
		this->screen[x+5][y+7].bgdColor = DARK_GREEN;
		this->screen[x+6][y+7].bgdColor = DARK_GREEN;
		this->screen[x+7][y+7].bgdColor = DARK_GREEN;
}
void CGRAPHIC::DrawSaveScreen(vector<wstring> FLOPPY_DISC, int first_x, int first_y) {
	vector<wstring> frame = FLOPPY_DISC;

	//set buffer
	for (int i = 0; i < 54; i++)
		for (int j = 0; j < 29; j++)
			this->screen[first_x + i][first_y + j] = { frame[j][i], BLACK, DARK_BLUE };

	//set colors
	screen[first_x + 50][first_y + 0].bgdColor = -1;
	screen[first_x + 51][first_y + 0].bgdColor = -1;
	screen[first_x + 52][first_y + 0].bgdColor = -1;
	screen[first_x + 53][first_y + 0].bgdColor = -1;
	screen[first_x + 52][first_y + 1].bgdColor = -1;
	screen[first_x + 53][first_y + 1].bgdColor = -1;
	for (int i = 12; i < 41; i++)
		for (int j = 1; j < 10; j++)
			screen[first_x + i][first_y + j].bgdColor = LIGHT_GRAY;
	for (int i = 8; i < 46; i++)
		screen[first_x + i][first_y + 11].bgdColor = WHITE;
	for (int i = 5; i < 49; i++)
		for (int j = 12; j < 28; j++)
			screen[first_x + i][first_y + j].bgdColor = WHITE;
	for (int i = 0; i < 4; i++) {
		screen[first_x + 28 + i][first_y + 23].bgdColor = LIGHT_GRAY;
		screen[first_x + 39 + i][first_y + 23].bgdColor = LIGHT_GRAY;
		screen[first_x + 28 + i][first_y + 24].bgdColor = LIGHT_GRAY;
		screen[first_x + 39 + i][first_y + 24].bgdColor = LIGHT_GRAY;
	}
}

void CGRAPHIC::DrawLetter(char ch, int first_x, int first_y, int txtColor, int bgdColor) {
	DrawObject(LETTER[ch - 'A'], first_x, first_y,txtColor, bgdColor);
}
void CGRAPHIC::drawString(string str, int x, int y, int txtColor, int bgdColor, int num) {
	if (num < 0) num = str.length();
	for (int i = str.length() - num; i < str.length(); i++)
		DrawLetter(str[i], x + i * 3, y, txtColor, bgdColor);
}
void CGRAPHIC::drawTime(clock_t second, int first_x, int first_y, int txtColor, int bgdColor) {
	clock_t minute = second / 60;
	second %= 60;
	int width = 3;
	int startX = first_x;
	DrawObject(NUMBER[minute / 10], startX, first_y, txtColor, bgdColor);
	startX += width + 1;
	DrawObject(NUMBER[minute % 10], startX, first_y, txtColor, bgdColor);
	startX += width + 1;
	DrawObject(COLON, startX, first_y, txtColor, bgdColor);
	startX += 2;
	DrawObject(NUMBER[second / 10], startX, first_y, txtColor, bgdColor);
	startX += width + 1;
	DrawObject(NUMBER[second % 10], startX, first_y, txtColor, bgdColor);
}
void CGRAPHIC::drawDot(int first_x, int first_y, int txtColor, int bgdColor) {
	DrawObject(DOT, first_x, first_y, txtColor, bgdColor);
}
void CGRAPHIC::erasePixel(int fromX, int fromY, int toX, int toY) {
	for (int i = fromX; i <= toX; i++)
		for (int j = fromY; j <= toY; j++)
			screen[i][j] = { L' ', -1, -1 };
}