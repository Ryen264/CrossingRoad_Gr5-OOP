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

CGRAPHIC::CGRAPHIC() {
	WIDTH = SCREEN_WIDTH; HEIGHT = SCREEN_HEIGHT;
	this->screen = new PIXEL * [WIDTH];
	for (int i = 0; i < WIDTH; i++) {
		this->screen[i] = new PIXEL[HEIGHT];
		for (int j = 0; j < HEIGHT; j++)
			this->screen[i][j] = { L' ', BLACK, WHITE };
	}
}
CGRAPHIC::CGRAPHIC(const CGRAPHIC& second) {
	WIDTH = second.WIDTH; HEIGHT = second.HEIGHT;
	this->screen = new PIXEL * [WIDTH];
	for (int i = 0; i < WIDTH; i++) {
		this->screen[i] = new PIXEL[HEIGHT];
		for (int j = 0; j < HEIGHT; j++)
			this->screen[i][j] = screen[i][j];
	}
}
CGRAPHIC::CGRAPHIC(PIXEL pixel) {
	WIDTH = SCREEN_WIDTH; HEIGHT = SCREEN_HEIGHT;
	this->screen = new PIXEL * [WIDTH];
	for (int i = 0; i < WIDTH; i++) {
		this->screen[i] = new PIXEL[HEIGHT];
		for (int j = 0; j < HEIGHT; j++)
			this->screen[i][j] = pixel;
	}
}
CGRAPHIC::~CGRAPHIC() {
	for (int i = 0; i < WIDTH; i++) {
		if (this->screen[i] != NULL) delete[] this->screen[i];
		this->screen[i] = NULL;
	}
	if (this->screen != NULL) delete[] this->screen;
	this->screen = NULL;
}

void CGRAPHIC::display(HANDLE& hStdout, DWORD& dwBytesWritten, int fromX, int fromY, int toX, int toY) {
	if (fromX < 0 || fromX > WIDTH - 1) fromX = 0;
	if (fromY < 0 || fromY > HEIGHT - 1) fromY = 0;
	if (toX < 0 || toX > WIDTH - 1) toX = WIDTH - 1;
	if (toY < 0 || toY > HEIGHT - 1) toY = HEIGHT - 1;
	int width = toX - fromX + 1;
	COORD cPos{};
	wchar_t* pBuffer = new wchar_t[width];
	WORD* pColor = new WORD[width];
	for (int y = fromY; y <= toY; y++) {
		cPos.X = fromX; cPos.Y = y;
		for (int x = fromX; x <= toX; x++) {
			pBuffer[x - fromX] = screen[x][y].buffer;
			pColor[x - fromX] = screen[x][y].bgdColor * 16 + screen[x][y].txtColor;
		}
		WriteConsoleOutputCharacter(hStdout, pBuffer, width, cPos, &dwBytesWritten);
		WriteConsoleOutputAttribute(hStdout, pColor, width, cPos, &dwBytesWritten);
	}
	if (pBuffer != NULL) delete[] pBuffer;
	pBuffer = NULL;
	if (pColor != NULL) delete[] pColor;
	pColor = NULL;
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
void CGRAPHIC::DrawObject(vector<wstring> contentsArr, int first_x, int first_y, int txtColor, int bgdColor, bool isPass) {
	int x = first_x, y = first_y;
	for (int i = 0; i < contentsArr.size(); i++) {
		if (y + i < SCREEN_HEIGHT) {
			for (int j = 0; j < contentsArr[i].length(); j++)
				if (x + j < SCREEN_WIDTH) {
					if (isPass) {
						if (contentsArr[i][j] != L' ') screen[x + j][y + i] = { contentsArr[i][j], txtColor, bgdColor };
					} else screen[x + j][y + i] = { contentsArr[i][j], txtColor, bgdColor };
				}
		}
	}
}
void CGRAPHIC::erasePixel(int fromX, int fromY, int toX, int toY) {
	for (int i = fromX; i <= toX; i++)
		for (int j = fromY; j <= toY; j++)
			screen[i][j] = { L' ', -1, -1 };
}

void CGRAPHIC::DrawLetter(char ch, int first_x, int first_y, int txtColor, int bgdColor) {
	DrawObject(LETTER[ch - 'A'], first_x, first_y, txtColor, bgdColor);
}
void CGRAPHIC::drawString(string str, int x, int y, int txtColor, int bgdColor, int num) {
	if (num < 0) num = str.length();
	for (int i = str.length() - num; i < str.length(); i++, x++)
		DrawLetter(str[i], x + 1 + i * 3, y, txtColor, bgdColor);
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

void CGRAPHIC::drawCharacterFrame(int first_x, int first_y, int txtColor, int bgdColor) {
	DrawObject(CHARACTER_FRAME, first_x, first_y, txtColor, bgdColor);
}
void CGRAPHIC::drawCheck(int first_x, int first_y, int txtColor, int bgdColor) {
	DrawObject(CHECK, first_x, first_y, txtColor, bgdColor);
	screen[first_x + 1][first_y + 1].bgdColor = LIGHT_GREEN;
	screen[first_x + 2][first_y + 2].bgdColor = LIGHT_GREEN;
	screen[first_x + 3][first_y + 1].bgdColor = LIGHT_GREEN;
	screen[first_x + 4][first_y + 1].bgdColor = LIGHT_GREEN;
	screen[first_x + 5][first_y + 0].bgdColor = LIGHT_GREEN;
}
void CGRAPHIC::drawCell(int first_x, int first_y, int txtColor, int bgdColor, bool isPass) {
	DrawObject(CELL, first_x, first_y, txtColor, bgdColor, isPass);
	for (int i = 0; i < 8; i++)
		screen[first_x + i][first_y + 3].bgdColor = -1;
}
void CGRAPHIC::drawClipBoard(int first_x, int first_y, int width, int height) {
	//top
	for (int i = first_x + 1; i < first_x + width; i++) {
		screen[i][first_y] = { L'▀' , BLACK, DARK_BLUE };
		screen[i][first_y + 1] = { L'▄' , BLACK, DARK_BLUE };
	}
	screen[first_x][first_y] = { L'▄' , BLACK, -1 };
	screen[first_x + width][first_y] = { L'▄' , BLACK, -1 };
	screen[(int)((first_x + width) * 0.32)][first_y].buffer = L'█';
	screen[(int)((first_x + width) * 0.68)][first_y].buffer = L'█';
	screen[(int)((first_x + width) * 0.32)][first_y + 1].buffer = L'█';
	screen[(int)((first_x + width) * 0.68)][first_y + 1].buffer = L'█';
	for (int i = (int)((first_x + width) * 0.32); i < (int)((first_x + width) * 0.68); i++) {
		screen[i][first_y].bgdColor = LIGHT_GRAY;
		screen[i][first_y + 1].bgdColor = LIGHT_GRAY;
	}
	//bottom
	for (int i = first_x + 1; i < first_x + width; i++) {
		screen[i][first_y + height - 1] = { L'▀' , BLACK, DARK_BLUE };
		screen[i][first_y + height] = { L'▄' , BLACK, DARK_BLUE };
	}
	screen[first_x][first_y + height] = { L'▀' , BLACK, -1 };
	screen[first_x + width][first_y + height] = { L'▀' , BLACK, -1 };
	//mid
	for (int i = first_x + 4; i <= first_x + width - 4; i++)
		for (int j = first_y + 2; j <= first_y + height - 2; j++)
			screen[i][j] = { L' ',SAND, SAND };
	for (int i = first_y + 1; i < first_y + height; i++) {
		screen[first_x][i] = { L'█',BLACK, DARK_BLUE };
		screen[first_x + 1][i] = { L' ', DARK_BLUE, DARK_BLUE };
		screen[first_x + 2][i] = { L' ', DARK_BLUE, DARK_BLUE };
		screen[first_x + 3][i] = { L'█',BLACK, DARK_BLUE };
		screen[first_x + width][i] = { L'█',BLACK, DARK_BLUE };
		screen[first_x + width - 3][i] = { L'█',BLACK, DARK_BLUE };
		screen[first_x + width - 1][i] = { L' ', DARK_BLUE, DARK_BLUE };
		screen[first_x + width - 2][i] = { L' ', DARK_BLUE, DARK_BLUE };
	}
	screen[first_x + 3][first_y + 1].buffer = L'▄';
	screen[first_x + width - 3][first_y + 1].buffer = L'▄';
	screen[first_x + 3][first_y + height - 1].buffer = L'▀';
	screen[first_x + width - 3][first_y + height - 1].buffer = L'▀';
	for (int i = 0; i < 5; i++)
		screen[first_x + width - (4 + i)][first_y + height - 4] = { L'▄', BLACK, SAND };

	screen[first_x + width - 3][first_y + height - 3] = { L' ', BLACK, DARK_BLUE };
	screen[first_x + width - 4][first_y + height - 3] = { L'▀', BLACK, DARK_BLUE };
	screen[first_x + width - 5][first_y + height - 3] = { L'▄', BLACK, SAND };
	screen[first_x + width - 6][first_y + height - 3] = { L' ', BLACK, SAND };
	screen[first_x + width - 7][first_y + height - 3] = { L' ', BLACK, SAND };
	screen[first_x + width - 8][first_y + height - 3] = { L'█', BLACK, SAND };

	screen[first_x + width - 3][first_y + height - 2] = { L' ', BLACK, DARK_BLUE };
	screen[first_x + width - 4][first_y + height - 2] = { L' ', BLACK, DARK_BLUE };
	screen[first_x + width - 5][first_y + height - 2] = { L' ', BLACK, DARK_BLUE };
	screen[first_x + width - 6][first_y + height - 2] = { L'▀', BLACK, DARK_BLUE };
	screen[first_x + width - 7][first_y + height - 2] = { L'▄', BLACK, SAND };
	screen[first_x + width - 8][first_y + height - 2] = { L'█', BLACK, SAND };

	for (int i = 0; i < 5; i++)
		screen[first_x + width - (3 + i)][first_y + height - 1] = { L' ', BLACK, DARK_BLUE };
}


void CGRAPHIC::DrawDrawer(int first_x, int first_y)
{
	vector<wstring> frame = Drawer;
	for (int i = 0; i <= 26; i++)
		for (int j = 0; j < 24; j++)
			this->screen[first_x + i][j + first_y] = { frame[j][i], LIGHT_BROWN, SADDLE_BROWN };

}
void CGRAPHIC::DrawSmallDrawer(int first_x, int first_y, int drawerColor)
{
	vector<wstring> frame = SmallDrawer;
	for (int i = 0; i < 32; i++)
		for (int j = 0; j < 7; j++)
			this->screen[first_x + i][j + first_y] = { frame[j][i], LIGHT_BROWN, -1 };

	int x = first_x, y = first_y;
	for (int i = 0; i <= 12; i++)
		for (int j = 0; j <= 2; j++)
			this->screen[x + i][y + j].txtColor = -1;

	for (int i = 13; i <= 28; i++)
		for (int j = 0; j <= 2; j++)
			this->screen[x + i][y + j].txtColor = BLACK;
	this->screen[x + 13][y].txtColor = -1;
	this->screen[x + 14][y].bgdColor = -1;

	this->screen[x+15][y].bgdColor = drawerColor;
	this->screen[x+16][y].bgdColor = drawerColor;
	for (int i = 17; i <= 24; i++)
		this->screen[x+i][y].bgdColor = WHITE;
	this->screen[x+25][y].bgdColor = drawerColor;
	this->screen[x+26][y].bgdColor = drawerColor;
	for (int j = 1; j <= 2; j++)
		for (int i = 14; i <= 27; i++)
			this->screen[x+i][y+j].txtColor = drawerColor;

	for (int i = 0; i <= 30; i++)
		this->screen[x+i][y+3].bgdColor = SADDLE_BROWN;
	for (int i = 3; i <= 6; i++)
		this->screen[x + 31][y + i].bgdColor = SADDLE_BROWN;

	for (int i = 21; i <= 24; i++)
		this->screen[x + i][y + 4].bgdColor = SADDLE_BROWN;
}
void CGRAPHIC::DrawDinasourPicture(int first_x, int first_y, int drawerColor, int Belly)
{
	vector<wstring>frame = DINOSAUR_PICTURE;
	//set buffer
	for (int i = 0; i < 22; i++)
		for (int j = 0; j < 11; j++)
			this->screen[first_x + i][first_y + j] = { frame[j][i], BLACK, -1 };
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
void CGRAPHIC::DrawBigDinoSaur(int first_x, int first_y)
{
	vector<wstring>frame = BIG_DINASOUR;
	//set buffer
	for (int i = 0; i < 43; i++)
		for (int j = 0; j < 21; j++)
			this->screen[first_x + i][first_y + j] = { frame[j][i], BLACK, -1 };
	//set color
	int x = first_x;
	int y = first_y;
	for (int i = 23; i < 39; i++)
	{
		this->screen[x+i][y].bgdColor = DARK_GREEN;
	}
	for (int i = 21; i < 41; i++)
	{
		this->screen[x+i][y+1].bgdColor = DARK_GREEN;
	}
	for (int j = 2; j < 7; j++)
	{
		for (int i = 21; i < 41; i++)
		{
			this->screen[x+i][y+j].bgdColor = DARK_GREEN;
		}
	}
	for (int i = 21; i < 37; i++)
	{
		this->screen[x+i][y+7].bgdColor = DARK_GREEN;
	}
	for (int i = 20; i < 37; i++)
	{
		this->screen[x+i][y+8].bgdColor = DARK_GREEN;
	}
	this->screen[x+1][y+8].bgdColor = DARK_GREEN;
	this->screen[x+2][y+8].bgdColor = DARK_GREEN;
	for (int i = 17; i < 31; i++)
	{
		this->screen[x+i][y+9].bgdColor = DARK_GREEN;
	}
	this->screen[x+1][y+9].bgdColor = DARK_GREEN;
	this->screen[x+2][y+9].bgdColor = DARK_GREEN;
	for (int i = 13; i < 35; i++)
	{
		this->screen[x+i][y+10].bgdColor = DARK_GREEN;
	}
	this->screen[x+1][y+10].bgdColor = DARK_GREEN;
	this->screen[x+2][y+10].bgdColor = DARK_GREEN;
	this->screen[x+3][y+10].bgdColor = DARK_GREEN;
	this->screen[x+4][y+10].bgdColor = DARK_GREEN;
	for (int i = 11; i < 26; i++)
	{
		this->screen[x+i][y+11].bgdColor = DARK_GREEN;
	}
	for (int i = 26; i < 31; i++)
	{
		this->screen[x+i][y+11].bgdColor = DARK_GREEN;
		this->screen[x+i][y+11].txtColor = LIGHT_GREEN;
	}
	for (int i = 31; i < 35; i++)
	{
		this->screen[x+i][y+11].bgdColor = DARK_GREEN;
	}
	this->screen[x+1][y+11].bgdColor = DARK_GREEN;
	this->screen[x+2][y+11].bgdColor = DARK_GREEN;
	this->screen[x+3][y+11].bgdColor = DARK_GREEN;
	this->screen[x+4][y+11].bgdColor = DARK_GREEN;
	this->screen[x+5][y+11].bgdColor = DARK_GREEN;
	this->screen[x+6][y+11].bgdColor = DARK_GREEN;
	for (int i = 23; i < 31; i++)
	{
		this->screen[x+i][y+12].txtColor = LIGHT_GREEN;
	}
	this->screen[x+34][y+12].bgdColor = DARK_GREEN;
	this->screen[x+33][y+12].bgdColor = DARK_GREEN;
	for (int i = 1; i < 24; i++)
	{
		this->screen[x+i][y+12].bgdColor = DARK_GREEN;
	}
	for (int i = 21; i < 31; i++)
	{
		this->screen[x+i][y+13].txtColor = LIGHT_GREEN;
	}
	for (int i = 1; i < 22; i++)
	{
		this->screen[x+i][y+13].bgdColor = DARK_GREEN;
	}
	for (int i = 21; i < 31; i++)
	{
		this->screen[x+i][y+14].txtColor = LIGHT_GREEN;
	}
	for (int i = 2; i < 22; i++)
	{
		this->screen[x+i][y+14].bgdColor = DARK_GREEN;
	}
	for (int i = 3; i < 22; i++)
	{
		this->screen[x+i][y+15].bgdColor = DARK_GREEN;
	}
	for (int i = 21; i < 29; i++)
	{
		this->screen[x+i][y+15].txtColor = LIGHT_GREEN;
	}
	for (int i = 4; i < 27; i++)
	{
		this->screen[x+i][y+16].bgdColor = DARK_GREEN;
	}
	for (int i = 5; i < 25; i++)
	{
		this->screen[x+i][y+17].bgdColor = DARK_GREEN;
	}
	for (int i = 11; i < 23; i++)
	{
		this->screen[x+i][y+18].bgdColor = DARK_GREEN;
	}
	for (int i = 14; i < 19; i++)
	{
		this->screen[x+i][y+18].bgdColor = -1;
	}
	this->screen[x+11][y+19].bgdColor = DARK_GREEN;
	this->screen[x+12][y+19].bgdColor = DARK_GREEN;
	this->screen[x+20][y+19].bgdColor = DARK_GREEN;
	this->screen[x+21][y+19].bgdColor = DARK_GREEN;

}
void CGRAPHIC::DrawHat(int first_x, int first_y)
{
	vector<wstring>frame = HAT;
	//set buffer
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 5; j++)
			this->screen[first_x + i][first_y + j] = { frame[j][i], SADDLE_BROWN, -1 };
	//set color
	int x = first_x;
	int y = first_y;
	this->screen[x+6][y].txtColor = SADDLE_BROWN;
	this->screen[x+6][y].bgdColor = -1;
	this->screen[x+7][y].txtColor = SADDLE_BROWN;
	this->screen[x+8][y].txtColor = SADDLE_BROWN;
	this->screen[x+9][y].txtColor = SADDLE_BROWN;
	this->screen[x+9][y].bgdColor = -1;

	this->screen[x+4][y+1].txtColor = BLACK;
	this->screen[x+4][y+1].bgdColor = -1;
	this->screen[x+5][y+1].txtColor = SADDLE_BROWN;
	this->screen[x+5][y+1].bgdColor = BLACK;
	this->screen[x+6][y+1].txtColor = SADDLE_BROWN;
	this->screen[x+6][y+1].bgdColor = BLACK;
	this->screen[x+7][y+1].txtColor = SADDLE_BROWN;
	this->screen[x+7][y+1].bgdColor = BLACK;
	this->screen[x+8][y+1].txtColor = SADDLE_BROWN;
	this->screen[x+8][y+1].bgdColor = BLACK;
	for (int i = 9; i < 12; i++)
	{
		this->screen[x+i][y+1].txtColor = SADDLE_BROWN;
	}
	this->screen[x][y+2].txtColor = SADDLE_BROWN;
	this->screen[x+1][y+2].txtColor = SADDLE_BROWN;
	this->screen[x+2][y+2].txtColor = SADDLE_BROWN;
	this->screen[x+2][y+2].bgdColor = -1;
	this->screen[x+3][y+2].txtColor = SADDLE_BROWN;
	this->screen[x+3][y+2].bgdColor = -1;
	this->screen[x+4][y+2].txtColor = BLACK;
	this->screen[x+4][y+2].bgdColor = SADDLE_BROWN;
	this->screen[x+5][y+2].txtColor = BLACK;
	this->screen[x+5][y+2].bgdColor = SADDLE_BROWN;

	for (int i = 6; i < 11; i++)
	{
		this->screen[x+i][y+2].txtColor = BLACK;
	}
	this->screen[x+11][y+2].txtColor = BLACK;
	this->screen[x+11][y+2].bgdColor = SADDLE_BROWN;
	for (int i = 1; i <= 14; i++)
	{
		this->screen[x+i][y+3].txtColor = SADDLE_BROWN;
		this->screen[x+i][y+3].bgdColor = -1;
	}
}
void CGRAPHIC::DrawCloud_1(int first_x, int first_y)
{
	vector<wstring>frame = FRAME_CLOUD_1;
	//set buffer
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 24; j++)
			this->screen[first_x + i][first_y + j] = { frame[j][i], BLACK, -1 };
	//set color
	int x = first_x;
	int y = first_y;
	this->screen[x+5][y].bgdColor = -1;
	this->screen[x+6][y].bgdColor = WHITE;
	this->screen[x+7][y].bgdColor = WHITE;
	this->screen[x+8][y].bgdColor = -1;
	this->screen[x+1][y+1].bgdColor = -1;
	this->screen[x+14][y+1].bgdColor = -1;
	for (int i = 2; i < 14; i++)
	{
		this->screen[x+i][y+1].bgdColor = WHITE;
	}
	for (int i = 1; i < 14; i++)
	{
		this->screen[x+i][y+2].bgdColor = WHITE;
		this->screen[x+i][y+2].txtColor = WHITE;
	}
	this->screen[x+1][y+3].bgdColor = -1;
	this->screen[x+14][y+3].bgdColor = -1;
	for (int i = 2; i < 14; i++)
	{
		this->screen[x+i][y+3].bgdColor = WHITE;
	}
}
void CGRAPHIC::DrawCloud_2(int first_x, int first_y)
{
	vector<wstring> frame = FRAME_CLOUD_2;

	//set buffer
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 4; j++)
			this->screen[first_x + i][first_y + j] = { frame[j][i], BLACK, -1 };

	//set color
	int x = first_x;
	int y = first_y;
	this->screen[x+2][y].bgdColor = -1;
	this->screen[x+3][y].bgdColor = -1;
	this->screen[x+5][y].bgdColor = -1;
	this->screen[x+8][y].bgdColor = -1;
	this->screen[x+10][y].bgdColor = -1;
	this->screen[x+11][y].bgdColor = -1;
	this->screen[x+12][y].bgdColor = -1;
	for (int i = 1; i < 15; i++)
	{
		this->screen[x+i][y+1].bgdColor = WHITE;
	}
	this->screen[x][y+1].bgdColor = -1;
	this->screen[x+15][y+1].bgdColor = -1;
	for (int i = 1; i < 14; i++)
	{
		this->screen[x+i][y+2].bgdColor = WHITE;
		this->screen[x+i][y+2].txtColor = WHITE;
	}
	this->screen[x+1][y+3].bgdColor - 1;
	this->screen[x+14][y+3].bgdColor - 1;
	for (int i = 2; i < 14; i++)
	{
		this->screen[x + i][y + 3].bgdColor = WHITE;
	}
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

void CGRAPHIC::DrawChooseCharacterMenu(int first_x, int first_y) {
	//set buffer
	for (int i = 0; i < 53; i++)
		for (int j = 0; j < 30; j++)
			screen[first_x + i][first_y + j] = { CHOOSE_CHARACTER_MENU[j][i], BLACK, DARK_BLUE };

	//set colors
	//frame board
	screen[first_x][first_y].bgdColor = LIGHT_GRAY;
	screen[first_x + 52][first_y].bgdColor = LIGHT_GRAY;
	screen[first_x][first_y + 29].bgdColor = LIGHT_GRAY;
	screen[first_x + 52][first_y + 29].bgdColor = LIGHT_GRAY;

	screen[first_x][first_y].bgdColor = LIGHT_GRAY;
	screen[first_x + 52][first_y].bgdColor = LIGHT_GRAY;
	screen[first_x][first_y + 29].bgdColor = LIGHT_GRAY;
	screen[first_x + 52][first_y + 29].bgdColor = LIGHT_GRAY;

	for (int i = 0; i < 18; i++) {
		screen[first_x + 17 + i][first_y + 0].bgdColor = LIGHT_GRAY;
		screen[first_x + 17 + i][first_y + 1].bgdColor = LIGHT_GRAY;
	}
	for (int i = 4; i < 49; i++)
		for (int j = 2; j < 28; j++)
			screen[first_x + i][first_y + j].bgdColor = SAND;

	screen[first_x + 48][first_y + 26].bgdColor = DARK_BLUE;
	screen[first_x + 46][first_y + 27].bgdColor = DARK_BLUE;
	screen[first_x + 47][first_y + 27].bgdColor = DARK_BLUE;
	screen[first_x + 48][first_y + 27].bgdColor = DARK_BLUE;

	//character frame
	for (int i = 6; i <= 20; i++)
		for (int j = 2; j <= 9; j++)
			screen[first_x + i][first_y + j].bgdColor = WHITE;

	//color cells
	vector<vector<int>> colorArr = { {RED, BLUE, DARK_GREEN}, {BRIGHT_YELLOW, ORANGE, SADDLE_BROWN}, {DARK_GRAY, DARK_RED, DARK_BLUE} };
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			int x = 6 + j * 14 + first_x, y = 11 + i * 6 + first_y;
			DrawObject(CELL, x, y, BLACK, colorArr[i][j], false);
			for (int k = 0; k < 8; k++)
				screen[x + k][y + 3].bgdColor = SAND;
		}
}
void CGRAPHIC::DrawPerryTalk(int first_x, int first_y)
{
	//set buffer
	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 19; j++)
			screen[first_x + i][first_y + j] = { PAUSE_MENU[j][i], BLACK, -1 };
	//set color
	int x = first_x;
	int y = first_y;
	for (int i = 3; i < 38; i++)
	{
		this->screen[x+i][y].bgdColor = WHITE;
	}
	for (int i = 1; i < 40; i++)
	{
		this->screen[x+i][y+1].bgdColor = WHITE;
	}
	for (int j = 2; j < 8; j++)
	{
		for (int i = 1; i < 40; i++)
		{
			this->screen[x+i][y+j].bgdColor = WHITE;
		}
	}

	for (int i = 2; i < 39; i++)
	{
		this->screen[x+i][y+8].bgdColor = WHITE;
	}
	this->screen[x+31][y+9].bgdColor = WHITE;
	this->screen[x+32][y+9].bgdColor = WHITE;
	this->screen[x+33][y+9].bgdColor = WHITE;
	for (int i = 32; i < 35; i++)
	{
		this->screen[x+i][y+10].bgdColor = WHITE;
	}
	for (int i = 33; i < 36; i++)
	{
		this->screen[x+i][y+11].bgdColor = WHITE;
	}
	this->screen[x+35][y+12].bgdColor = WHITE;
	this->screen[x+36][y+12].bgdColor = WHITE;
	for (int i = 39; i < 55; i++)
	{
		this->screen[x+i][y+14].txtColor = SKY_BLUE;
	}
	this->screen[x+41][y+14].txtColor = BLACK;
	this->screen[x+41][y+14].bgdColor = SKY_BLUE;
	this->screen[x+39][y+15].txtColor = WHITE;
	this->screen[x+40][y+15].bgdColor = SKY_BLUE;
	this->screen[x+40][y+15].txtColor = BRIGHT_YELLOW;
	this->screen[x+41][y+15].txtColor = SKY_BLUE;
	this->screen[x+42][y+15].txtColor = SKY_BLUE;
	this->screen[x+43][y+15].txtColor = WHITE;
	for (int i = 45; i < 54; i++)
	{
		this->screen[x+i][y+15].txtColor = SKY_BLUE;
	}
	this->screen[x+54][y+15].txtColor = BRIGHT_YELLOW;
	this->screen[x+54][y+15].bgdColor = -1;
	this->screen[x+55][y+15].txtColor = BRIGHT_YELLOW;
	this->screen[x+55][y+15].bgdColor = -1;
	this->screen[x+56][y+15].txtColor = BRIGHT_YELLOW;
	this->screen[x+56][y+15].bgdColor = -1;
	this->screen[x+57][y+15].txtColor = ORANGE;
	this->screen[x+57][y+15].bgdColor = -1;
	this->screen[x+58][y+15].txtColor = ORANGE;
	this->screen[x+58][y+15].bgdColor = BRIGHT_YELLOW;
	this->screen[x+59][y+15].txtColor = BRIGHT_YELLOW;
	this->screen[x+59][y+15].bgdColor = ORANGE;
	this->screen[x+60][y+15].txtColor = ORANGE;
	this->screen[x+60][y+15].bgdColor = BRIGHT_YELLOW;
	this->screen[x+61][y+15].txtColor = BRIGHT_YELLOW;
	this->screen[x+61][y+15].bgdColor = ORANGE;
	this->screen[x+62][y+15].txtColor = BRIGHT_YELLOW;
	this->screen[x+62][y+15].bgdColor = -1;

	this->screen[x+40][y+16].txtColor = BRIGHT_YELLOW;
	this->screen[x+41][y+16].txtColor = BRIGHT_YELLOW;
	this->screen[x+42][y+16].txtColor = BRIGHT_YELLOW;
	this->screen[x+42][y+16].bgdColor = SKY_BLUE;

	this->screen[x+40][y+16].txtColor = BRIGHT_YELLOW;
	this->screen[x+40][y+16].bgdColor = ORANGE;
	this->screen[x+39][y+16].txtColor = BRIGHT_YELLOW;
	this->screen[x+39][y+16].bgdColor = -1;
	this->screen[x+38][y+16].txtColor = BRIGHT_YELLOW;
	this->screen[x+38][y+16].bgdColor = SKY_BLUE;
	this->screen[x+39][y+16].txtColor = BRIGHT_YELLOW;
	this->screen[x+39][y+16].bgdColor = SKY_BLUE;
	this->screen[x+37][y+16].txtColor = BRIGHT_YELLOW;
	this->screen[x+37][y+16].bgdColor = -1;

	for (int i = 43; i < 54; i++)
	{
		this->screen[x+i][y+16].txtColor = SKY_BLUE;
	}
	this->screen[x+54][y+16].txtColor = ORANGE;
	this->screen[x+54][y+16].bgdColor = BRIGHT_YELLOW;
	this->screen[x+55][y+16].txtColor = ORANGE;
	this->screen[x+55][y+16].bgdColor = BRIGHT_YELLOW;
	this->screen[x+56][y+16].txtColor = ORANGE;
	this->screen[x+56][y+16].bgdColor = BRIGHT_YELLOW;
	this->screen[x+57][y+16].txtColor = BRIGHT_YELLOW;
	this->screen[x+58][y+16].txtColor = ORANGE;
	this->screen[x+58][y+16].bgdColor = BRIGHT_YELLOW;
	this->screen[x+59][y+16].txtColor = ORANGE;
	this->screen[x+59][y+16].bgdColor = BRIGHT_YELLOW;
	this->screen[x+60][y+16].txtColor = BRIGHT_YELLOW;
	this->screen[x+61][y+16].txtColor = ORANGE;
	this->screen[x+61][y+16].bgdColor = BRIGHT_YELLOW;
	this->screen[x+62][y+16].txtColor = ORANGE;
	this->screen[x+62][y+16].bgdColor = BRIGHT_YELLOW;
	for (int i = 38; i < 40; i++)
	{
		this->screen[x+i][y+17].txtColor = ORANGE;
		this->screen[x+i][y+17].bgdColor = -1;
	}
	this->screen[x+40][y+17].txtColor = ORANGE;
	this->screen[x+40][y+17].bgdColor = -1;
	this->screen[x+41][y+17].txtColor = SKY_BLUE;
	this->screen[x+41][y+17].bgdColor = BRIGHT_YELLOW;
	for (int i = 42; i < 54; i++)
	{
		this->screen[x+i][y+17].txtColor = SKY_BLUE;
		this->screen[x+i][y+17].bgdColor = -1;
	}
	this->screen[x+54][y+17].txtColor = BRIGHT_YELLOW;
	this->screen[x+54][y+17].bgdColor = -1;
	this->screen[x+55][y+17].txtColor = BRIGHT_YELLOW;
	this->screen[x+55][y+17].bgdColor = -1;
	this->screen[x+56][y+17].txtColor = ORANGE;
	this->screen[x+56][y+17].bgdColor = -1;
	this->screen[x+57][y+17].txtColor = ORANGE;
	this->screen[x+57][y+17].bgdColor = -1;
	for (int i = 40; i < 54; i++)
	{
		this->screen[x+i][y+18].txtColor = SKY_BLUE;
		this->screen[x+i][y+18].bgdColor = -1;
	}
	for (int i = 47; i < 50; i++)
	{
		this->screen[x+i][y+18].txtColor = ORANGE;
		this->screen[x+i][y+18].bgdColor = -1;
	}
	for (int i = 51; i < 54; i++)
	{
		this->screen[x+i][y+18].txtColor = BRIGHT_YELLOW;
		this->screen[x+i][y+18].bgdColor = -1;
	}
}
void CGRAPHIC::DrawPauseMenu(int first_x, int first_y) {
	//set buffer
	for (int j = 0; j < 30; j++)
		for (int i = 0; i < 53; i++)
			screen[i + first_x][j + first_y] = { PAUSE_MENU[j][i], BLACK, DARK_BLUE };

	//set colors
	//frame board
	screen[first_x][first_y].bgdColor = LIGHT_GRAY;
	screen[first_x + 52][first_y].bgdColor = LIGHT_GRAY;
	screen[first_x][first_y + 29].bgdColor = LIGHT_GRAY;
	screen[first_x + 52][first_y + 29].bgdColor = LIGHT_GRAY;

	for (int i = 0; i < 18; i++) {
		screen[first_x + 17 + i][first_y + 0].bgdColor = LIGHT_GRAY;
		screen[first_x + 17 + i][first_y + 1].bgdColor = LIGHT_GRAY;
	}
	for (int i = 4; i < 49; i++)
		for (int j = 2; j < 28; j++)
			screen[first_x + i][first_y + j].bgdColor = SAND;

	screen[first_x + 48][first_y + 26].bgdColor = DARK_BLUE;
	screen[first_x + 46][first_y + 27].bgdColor = DARK_BLUE;
	screen[first_x + 47][first_y + 27].bgdColor = DARK_BLUE;
	screen[first_x + 48][first_y + 27].bgdColor = DARK_BLUE;

	//character frame
	for (int i = 6; i <= 20; i++)
		for (int j = 2; j <= 9; j++)
			screen[first_x + i][first_y + j].bgdColor = WHITE;

	//buttons
	for (int i = 7; i <= 14; i++)
		for (int j = 10; j <= 13; j++)
			screen[first_x + i][first_y + j].txtColor = DARK_GRAY;
	for (int i = 24; i <= 28; i++)
		for (int j = 10; j <= 13; j++)
			screen[first_x + i][first_y + j].txtColor = DARK_GREEN;
	for (int i = 40; i <= 44; i++)
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
}

void CGRAPHIC::drawTag(int first_x, int first_y, int tagColor) {
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 5; j++)
			screen[first_x + i][first_y + j] = { TAGS[j][i], BLACK, WHITE };
	for (int i = 0; i < 40; i++)
		screen[first_x + i][first_y].bgdColor = -1;
	screen[first_x][first_y + 1].bgdColor = -1;
	screen[first_x + 1][first_y + 3].bgdColor = -1;
	screen[first_x + 2][first_y + 3].bgdColor = -1;
	screen[first_x][first_y + 4].bgdColor = -1;
	screen[first_x + 1][first_y + 4].bgdColor = -1;
	screen[first_x + 2][first_y + 4].bgdColor = -1;
	screen[first_x + 3][first_y + 4].bgdColor = -1;
	screen[first_x + 4][first_y + 4].bgdColor = -1;
	for (int i = 1; i < 5; i++)
		screen[first_x + 7][first_y + i].bgdColor = tagColor;
	for (int i = 33; i < 39; i++)
		for (int j = 1; j < 5; j++)
			screen[first_x + i][first_y + j].bgdColor = tagColor;
}

void CGRAPHIC::drawInfiniteSymbol(int first_x, int first_y) {
	for (int i = 0; i < 13; i++)
		for (int j = 0; i < 3; j++)
			screen[first_x + i][first_y + j] = { infinite[j][i], BLACK, -1 };
}