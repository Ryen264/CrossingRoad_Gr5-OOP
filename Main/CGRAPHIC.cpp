#include "CGRAPHIC.h"
void SetupTheme(THEME theme) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFOEX csbiex{};
    csbiex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(hStdout, &csbiex);
    for (int i = 0; i < 16; i++)
        csbiex.ColorTable[i] = theme.colorTable[i];
    this->BLACK = theme.BLACK; this->SKY_BLUE = theme.SKY_BLUE; this->WHITE = theme.WHITE; this->DARK_GREEN = theme.DARK_GREEN;
    this->SADDLE_BROWN = theme.SADDLE_BROWN; this->DARK_RED = theme.DARK_RED; this->RED = theme.RED; this->ORANGE = theme.ORANGE;
    this->DARK_VIOLET = theme.DARK_VIOLET; this->TOMATO = theme.TOMATO; this->LIGHT_CYAN = theme.LIGHT_CYAN; this->OXFORD = theme.OXFORD;
    this->FELD_GRAU = theme.FELD_GRAU; this->BRIGHT_YELLOW = theme.BRIGHT_YELLOW; this->LIGHT_GREEN = theme.LIGHT_GREEN; this->LIGHT_BROWN = theme.LIGHT_BROWN;
    SetConsoleScreenBufferInfoEx(hStdout, &csbiex);
}
void CGRAPHIC::display(int fromX, int fromY, int toX, int toY) {
	if (toX < 0)
		toX = WIDTH - 1;
	if (toY < 0)
		toY = HEIGHT - 1;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwBytesWritten{};
	wchar_t pBuffer{};
	WORD pColor;
	for (int y = fromY; y <= toY; y++)
		for (int x = fromX; x <= toX; x++) {
			COORD cPos = { x, y };
			if (this->screen[x][y].buffer != L' ')
				pBuffer = this->screen[x][y].buffer;
			else
				ReadConsoleOutputCharacter(hStdout, &pBuffer, 1, cPos, &dwBytesWritten);
			if (this->screen[x][y].bgdColor != -1)
				pColor = this->screen[x][y].bgdColor * 16 + this->screen[x][y].txtColor;
			else {
				ReadConsoleOutputAttribute(hStdout, &pColor, 1, cPos, &dwBytesWritten);
				pColor = pColor - (pColor % 16) + this->screen[x][y].txtColor;
			}
			WriteConsoleOutputCharacter(hStdout, &pBuffer, 1, cPos, &dwBytesWritten);
			WriteConsoleOutputAttribute(hStdout, &pColor, 1, cPos, &dwBytesWritten);
		}
}
void CGRAPHIC::clear(int txtColor, int bgdColor) {
	for (int x = 0; x < WIDTH; x++)
		for (int y = 0; y < HEIGHT; y++)
			this->screen[x][y] = { L' ', txtColor, bgdColor };
}
void CGRAPHIC::Text(wstring wsContent, int x, int y, int txtColor, int bgdColor) {
	for (int i = 0; i < wsContent.length(); i++)
		this->screen[x + i][y] = { wsContent[i], txtColor, bgdColor };
}
void CGRAPHIC::DrawObject(vector<wstring> contentsArr, int x, int y, int txtColor, int bgdColor) {
    for (int i = 0; i < contentsArr.size(); i++)
        for (int j = 0; j < contentsArr[i].length(); j++)
            this->screen[x + j][y + i] = { wsContent[i][j], txtColor, bgdColor };
}
void CGRAPHIC::DrawBlock(PIXEL block[16][16], int x, int y) {
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			this->screen[x + i][y + j] = block[i][j];
}

