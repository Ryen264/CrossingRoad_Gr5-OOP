#include "CGRAPHIC.h"
CGRAPHIC::CGRAPHIC(PIXEL** screen) {
	this->screen = new PIXEL*[WIDTH];
	for (int i = 0; i < WIDTH; i++)
		this->screen[i] = new PIXEL[HEIGHT];

	if (screen != NULL) {
		for (int x = 0; x < WIDTH; x++)
			for (int y = 0; y < HEIGHT; y++)
				this->screen[x][y] = screen[x][y];
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
void CGRAPHIC::display(int fromX, int fromY, int toX, int toY) {
	if (toX < 0)
		toX = WIDTH - 1;
	if (toY < 0)
		toY = HEIGHT - 1;
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
	this->display();
}
void CGRAPHIC::Text(wstring wsContent, int first_x, int first_y, int txtColor, int bgdColor) {
	int x = first_x, y = first_y;
	for (int i = 0; i < wsContent.length(); i++)
		this->screen[x++][y] = { wsContent[i], txtColor, bgdColor };
}
void CGRAPHIC::DrawObject(vector<wstring> contentsArr, int first_x, int first_y, int txtColor, int bgdColor) {
	int x = first_x, y = first_y;
	for (int i = 0; i < contentsArr.size(); i++)
		this->Text(contentsArr[i], x, y++, txtColor, bgdColor);
}
