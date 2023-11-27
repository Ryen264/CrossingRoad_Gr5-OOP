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


