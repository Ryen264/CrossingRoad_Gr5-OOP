#include "COBJECT.h"
COBJECT::COBJECT(int x, int y, int isRight) {
	this->numberOfBlock = 2;
	this->numberOfHeight = 2; this->numberOfWidth = 1;
	this->x = x; this->y = y; this->isRight = isRight;
	vector<wstring> frame = (isRight) ? FRAME_RIGHT : FRAME_LEFT;

	this->block = new PIXEL * [BLOCK_WIDTH * this->numberOfWidth];
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		this->block[i] = new PIXEL[BLOCK_HEIGHT * this->numberOfHeight];

	//set buffers
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
			if (frame[j][i] != ' ')
				this->block[i][j] = { frame[j][i], BLACK, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };

	//set colors
	if (isRight) {
		block[x + 6][y + 4].bgdColor = SADDLE_BROWN;
		block[x + 8][y + 4].bgdColor = SADDLE_BROWN;
		block[x + 7][y + 5].bgdColor = SADDLE_BROWN;
		block[x + 7][y + 4].bgdColor = SADDLE_BROWN;
		block[x + 9][y + 5].bgdColor = SADDLE_BROWN;
		block[x + 11][y + 5].bgdColor = SADDLE_BROWN;
		block[x + 10][y + 6].bgdColor = SADDLE_BROWN;
		block[x + 5][y + 8].bgdColor = SADDLE_BROWN;
		block[x + 6][y + 8].bgdColor = SADDLE_BROWN;
		block[x + 7][y + 8].bgdColor = SADDLE_BROWN;
		block[x + 6][y + 8].bgdColor = SADDLE_BROWN;
		for (int j = 9; j <= 11; j++)
		{
			block[x + 7][y + j].bgdColor = SADDLE_BROWN;
		}
		block[x + 6][y + 11].bgdColor = SADDLE_BROWN;
		block[x + 7][y + 11].bgdColor = SADDLE_BROWN;
		block[x + 8][y + 11].bgdColor = SADDLE_BROWN;
		for (int i = 4; i <= 8; i++)
		{
			block[x + i][y].bgdColor = LIGHT_GREEN;
		}
		for (int i = 2; i <= 9; i++)
		{
			block[x + i][y + 1].bgdColor = LIGHT_GREEN;
		}
		for (int i = 7; i <= 10; i++)
		{
			block[x + i][y + 2].bgdColor = LIGHT_GREEN;
		}
		block[x + 5][y + 2].bgdColor = LIGHT_GREEN;
		block[x + 5][y + 2].txtColor = DARK_GREEN;
		block[x + 6][y + 2].bgdColor = LIGHT_GREEN;
		block[x + 6][y + 2].txtColor = DARK_GREEN;
		for (int i = 10; i <= 12; i++)
		{
			block[x + i][y + 4].bgdColor = LIGHT_GREEN;
			block[x + i][y + 4].txtColor = DARK_GREEN;
		}
		block[x + 11][y + 3].bgdColor = LIGHT_GREEN;
		block[x + 3][y + 6].bgdColor = LIGHT_GREEN;
		block[x + 3][y + 6].txtColor = DARK_GREEN;
		block[x + 4][y + 6].bgdColor = LIGHT_GREEN;
		block[x + 5][y + 6].bgdColor = LIGHT_GREEN;
		block[x + 6][y + 6].bgdColor = LIGHT_GREEN;
		block[x + 7][y + 6].txtColor = DARK_GREEN;
		block[x + 7][y + 6].bgdColor = LIGHT_GREEN;
	}
	else {
		block[5][1].bgdColor = DARK_GREEN;
		for (int i = 3; i <= 11; i++)
			block[i][1].bgdColor = DARK_GREEN;

		for (int i = 2; i <= 11; i++)
			block[i][2].bgdColor = DARK_GREEN;

		for (int i = 3; i <= 13; i++)
			block[i][3].bgdColor = DARK_GREEN;
		block[7][3].bgdColor = LIGHT_GREEN;
		block[7][3].txtColor = DARK_GREEN;
		block[8][3].bgdColor = LIGHT_GREEN;
		block[8][3].txtColor = DARK_GREEN;
		block[9][3].bgdColor = LIGHT_GREEN;
		block[9][3].txtColor = DARK_GREEN;
		block[10][3].txtColor = DARK_GREEN;

		for (int i = 7; i <= 9; i++)
			block[i][4].bgdColor = LIGHT_GREEN;
		for (int i = 10; i <= 12; i++)
			block[i][4].bgdColor = DARK_GREEN;
	}
}
COBJECT::~COBJECT() {
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		delete[] this->block[i];
	delete[] this->block;
}
void COBJECT::DrawBlock(CGRAPHIC& layer) {
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
			layer.screen[this->x + i][this->y + j] = block[i][j];
}
