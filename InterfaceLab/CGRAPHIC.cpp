#include "CGRAPHIC.h"

int BLACK, SKY_BLUE, WHITE, DARK_GREEN,
SADDLE_BROWN, DARK_RED, RED, ORANGE,
BLUE, DARK_BLUE, LIGHT_CYAN, LIGHT_GRAY,
SAND, BRIGHT_YELLOW, LIGHT_GREEN, LIGHT_BROWN,
CREAMY_AVOCADO, DARK_BROWN, BROWN, LIGHTER_BROWN,
LAVENDER, PURPLE, TEAL, TANGERINE, DARK_ORANGE;

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
	BLUE = theme.BLUE; DARK_BLUE = theme.DARK_BLUE; LIGHT_CYAN = theme.LIGHT_CYAN; LIGHT_GRAY = theme.LIGHT_GRAY;
	SAND = theme.SAND; BRIGHT_YELLOW = theme.BRIGHT_YELLOW; LIGHT_GREEN = theme.LIGHT_GREEN; LIGHT_BROWN = theme.LIGHT_BROWN;
	CREAMY_AVOCADO = theme.CREAMY_AVOCADO; DARK_BROWN = theme.DARK_BROWN; BROWN = theme.BROWN; LIGHTER_BROWN = theme.LIGHTER_BROWN;
	LAVENDER = theme.LAVENDER; PURPLE = theme.PURPLE; TEAL = theme.TEAL; TANGERINE = theme.TANGERINE; DARK_ORANGE = theme.DARK_ORANGE;
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
	if (this->screen == NULL)
		return;
	if (toX < 0)
		toX = SCREEN_WIDTH - 1;
	if (toY < 0)
		toY = SCREEN_HEIGHT - 1;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWritten = 0;
	wchar_t pBuffer{};
	WORD pColor;
	for (int y = fromY; y <= toY; y++)
		for (int x = fromX; x <= toX; x++) {
			COORD cPos = { x, y };
			if (this->screen[x][y].buffer != L' ')
				pBuffer = this->screen[x][y].buffer;
			else
				ReadConsoleOutputCharacter(hStdout, &pBuffer, 1, cPos, &dwBytesWritten);
			ReadConsoleOutputAttribute(hStdout, &pColor, 1, cPos, &dwBytesWritten);
			if (this->screen[x][y].txtColor != -1)
				pColor = pColor - (pColor % 16) + this->screen[x][y].txtColor;
			if (this->screen[x][y].bgdColor != -1)
				pColor = pColor - 16 * (pColor / 16) + 16 * this->screen[x][y].bgdColor;
			WriteConsoleOutputCharacter(hStdout, &pBuffer, 1, cPos, &dwBytesWritten);
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
	for (int i = 0; i < wsContent.length(); i++)
		this->screen[x++][y] = { wsContent[i], txtColor, bgdColor };
}
void CGRAPHIC::DrawObject(vector<wstring> contentsArr, int first_x, int first_y, int txtColor, int bgdColor) {
	int x = first_x, y = first_y;
	for (int i = 0; i < contentsArr.size(); i++)
		for (int j = 0; j < contentsArr[i].length(); j++)
			this->screen[x + j][y + i] = { contentsArr[i][j], txtColor, bgdColor };
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
	for (int i = first_x + 1; i < first_x + width ; i++) {
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