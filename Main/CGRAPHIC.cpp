#include "CGRAPHIC.h"
void Configure() {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX csbiex;
	csbiex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hStdout, &csbiex);

	csbiex.ColorTable[0] = RGB(0, 0, 0);		//black
	csbiex.ColorTable[1] = RGB(153, 217, 234);	//sky blue
	csbiex.ColorTable[2] = RGB(255, 255, 255);	//white
	csbiex.ColorTable[3] = RGB(0, 100, 0);		//dark green
	csbiex.ColorTable[4] = RGB(139, 69, 19);	//saddle brown (nau dam)
	csbiex.ColorTable[5] = RGB(158, 19, 26);	//Dark Red
	csbiex.ColorTable[6] = RGB(237, 28, 36);	//Red
	csbiex.ColorTable[7] = RGB(255, 165, 0);	//orange
	csbiex.ColorTable[8] = RGB(148, 0, 211);	//dark violet
	csbiex.ColorTable[9] = RGB(255, 99, 71);	//tomato
	csbiex.ColorTable[10] = RGB(204, 255, 255);	//light cyan
	csbiex.ColorTable[11] = RGB(0, 17, 51);		//oxford blue
	csbiex.ColorTable[12] = RGB(67, 96, 86);	//feldgrau
	csbiex.ColorTable[13] = RGB(255, 242, 0);	//bright yellow
	//csbiex.ColorTable[14] = RGB(201, 255, 229);	//Aero blue
	csbiex.ColorTable[14] = RGB(25, 255, 25);	//Neon green
	csbiex.ColorTable[15] = RGB(0, 153, 153);	//GREEN PERRY
	SetConsoleScreenBufferInfoEx(hStdout, &csbiex);
}

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
	wchar_t pBuffer;
	WORD pColor;
	for (int y = fromY; y <= toY; y++)
		for (int x = fromX; x <= toX; x++) {
			COORD cPos = { x, y };
			wchar_t pBuffer = this->screen[x][y].buffer;
			pColor = this->screen[x][y].bgdColor * 16 + this->screen[x][y].txtColor;
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
