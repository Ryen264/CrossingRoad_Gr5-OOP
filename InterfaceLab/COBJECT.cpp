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
		block[6][4].txtColor = SADDLE_BROWN;
		block[8][4].txtColor = SADDLE_BROWN;
		block[7][5].bgdColor = SADDLE_BROWN;
		block[7][4].bgdColor = SADDLE_BROWN;
		block[11][5].bgdColor = SADDLE_BROWN;
		block[10][6].bgdColor = SADDLE_BROWN;
		block[5][8].bgdColor = SADDLE_BROWN;
		block[6][8].bgdColor = SADDLE_BROWN;
		block[7][8].bgdColor = SADDLE_BROWN;
		block[6][8].bgdColor = SADDLE_BROWN;
		block[7][9].txtColor = SADDLE_BROWN;
		block[7][10].txtColor = SADDLE_BROWN;
		block[6][11].bgdColor = SADDLE_BROWN;
		block[7][11].bgdColor = SADDLE_BROWN;
		block[8][11].bgdColor = SADDLE_BROWN;
		for (int i = 4; i <= 8; i++)
		{
			block[i][0].bgdColor = LIGHT_GREEN;
		}
		for (int i = 3; i <= 9; i++)
		{
			block[i][1].txtColor = LIGHT_GREEN;
		}
		block[10][1].txtColor = DARK_GREEN;
		block[10][1].bgdColor = LIGHT_GREEN;
		block[11][1].txtColor = DARK_GREEN;
		for (int i = 7; i <= 10; i++)
		{
			block[i][2].bgdColor = LIGHT_GREEN;
		}
		block[3][2].txtColor = DARK_GREEN;
		block[4][2].txtColor = DARK_GREEN;
		block[5][2].bgdColor = LIGHT_GREEN;
		block[5][2].txtColor = DARK_GREEN;
		block[6][2].bgdColor = LIGHT_GREEN;
		block[6][2].txtColor = DARK_GREEN;
		block[7][2].txtColor = LIGHT_GREEN;
		block[8][2].txtColor = LIGHT_GREEN;
		block[9][2].txtColor = LIGHT_GREEN;
		block[10][2].bgdColor = LIGHT_GREEN;
		block[10][2].txtColor = DARK_GREEN;
		block[11][2].txtColor = DARK_GREEN;
		block[11][3].bgdColor = LIGHT_GREEN;
		for (int i = 4; i <= 10; i++)
			block[i][3].bgdColor = DARK_GREEN;
		block[12][3].bgdColor = DARK_GREEN;
		block[13][3].bgdColor = DARK_GREEN;
		for (int i = 10; i <= 12; i++)
		{
			block[i][4].bgdColor = LIGHT_GREEN;
			block[i][4].txtColor = DARK_GREEN;
		}
		block[13][4].txtColor = DARK_GREEN;
		block[3][6].bgdColor = LIGHT_GREEN;
		block[3][6].txtColor = DARK_GREEN;
		block[4][6].txtColor = LIGHT_GREEN;
		block[5][6].txtColor = LIGHT_GREEN;
		block[6][6].txtColor = DARK_GREEN;
		block[6][6].bgdColor = LIGHT_GREEN;
		block[7][6].txtColor = DARK_GREEN;
		for (int i = 3; i <= 7; i++)
			block[i][7].bgdColor = DARK_GREEN;
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
