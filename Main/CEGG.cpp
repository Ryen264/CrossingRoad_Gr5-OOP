#include "CEGG.h"
CEGG::CEGG(int x, int y, bool isRight) {
	this->x = x; this->y = y; this->isRight = isRight;
	this->ID = CAPYBARA_ID;
	vector<wstring> frame = (isRight) ? FRAME_RIGHT : FRAME_LEFT;

	this->block = new PIXEL * [BLOCK_WIDTH * this->numberOfWidth];
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		this->block[i] = new PIXEL[BLOCK_HEIGHT * this->numberOfHeight];

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
			if (frame[j][i] != L' ')
				this->block[i][j] = { frame[j][i], -1, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };


	//set colors
	if (isRight) {
		block[5][1].txtColor = BLACK;
		block[5][1].bgdColor = -1;
		block[6][1].txtColor = BLACK;
		block[6][1].bgdColor = WHITE;
		block[7][1].txtColor = BLACK;
		block[7][1].bgdColor = WHITE;
		block[8][1].txtColor = BLACK;
		block[8][1].bgdColor = -1;

		block[4][2].txtColor = BLACK;
		for (int i = 5; i < 9; i++)
		{
			block[i][2].txtColor = WHITE;
		}
		block[9][2].txtColor = BLACK;

		block[4][3].txtColor = BLACK;
		block[4][3].bgdColor = -1;
		block[5][3].txtColor = BLACK;
		block[5][3].bgdColor = WHITE;
		block[6][3].txtColor = WHITE;
		block[7][3].txtColor = WHITE;
		block[8][3].txtColor = BLACK;
		block[8][3].bgdColor = WHITE;
		block[9][3].txtColor = BLACK;
		block[9][3].bgdColor = -1;

		block[6][4].txtColor = BLACK;
		block[6][4].bgdColor = -1;
		block[7][4].txtColor = BLACK;
		block[7][4].bgdColor = -1;

	}
	else {
		block[5][1].txtColor = BLACK;
		block[5][1].bgdColor = -1;
		block[6][1].txtColor = BLACK;
		block[6][1].bgdColor = WHITE;
		block[7][1].txtColor = BLACK;
		block[7][1].bgdColor = WHITE;
		block[8][1].txtColor = BLACK;
		block[8][1].bgdColor = -1;

		block[4][2].txtColor = BLACK;
		for (int i = 5; i < 9; i++)
		{
			block[i][2].txtColor = WHITE;
		}
		block[9][2].txtColor = BLACK;

		block[4][3].txtColor = BLACK;
		block[4][3].bgdColor = -1;
		block[5][3].txtColor = BLACK;
		block[5][3].bgdColor = WHITE;
		block[6][3].txtColor = WHITE;
		block[7][3].txtColor = WHITE;
		block[8][3].txtColor = BLACK;
		block[8][3].bgdColor = WHITE;
		block[9][3].txtColor = BLACK;
		block[9][3].bgdColor = -1;

		block[6][4].txtColor = BLACK;
		block[6][4].bgdColor = -1;
		block[7][4].txtColor = BLACK;
		block[7][4].bgdColor = -1;
	}

}