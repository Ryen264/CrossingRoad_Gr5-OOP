#include "CCAPYBARA.h"
CCAPYBARA::CCAPYBARA(int x, int y, bool isRight) {
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
		block[0][4].txtColor = LIGHT_BROWN;
		block[1][4].txtColor = LIGHT_BROWN;
		block[2][4].txtColor = LIGHT_BROWN;
		block[3][4].txtColor = SADDLE_BROWN;
		for (int i = 4; i <= 8; i++)
		{
			block[i][4].txtColor = LIGHT_BROWN;
		}
		block[0][3].txtColor = LIGHT_BROWN;
		block[1][3].txtColor = LIGHT_BROWN;
		block[2][3].txtColor = SADDLE_BROWN;
		block[2][3].bgdColor = LIGHT_BROWN;
		for (int i = 3; i <= 11; i++)
		{
			block[i][2].txtColor = LIGHT_BROWN;
		}
		block[3][2].txtColor = LIGHT_BROWN;
		block[3][2].bgdColor = SADDLE_BROWN;
		block[4][2].txtColor = SADDLE_BROWN;
		block[5][2].txtColor = LIGHT_BROWN;
		block[5][2].bgdColor = LIGHT_BROWN;
		block[6][2].bgdColor = LIGHT_BROWN;
		block[7][2].txtColor = BLACK;
		block[7][2].bgdColor = LIGHT_BROWN;
		block[8][2].txtColor = LIGHT_BROWN;
		block[9][2].txtColor = LIGHT_BROWN;
		block[10][2].txtColor = LIGHT_BROWN;
		block[10][2].bgdColor = SADDLE_BROWN;
		block[11][2].txtColor = SADDLE_BROWN;
		block[11][2].txtColor = SADDLE_BROWN;
		block[3][1].txtColor = BRIGHT_YELLOW;
		block[4][1].txtColor = BRIGHT_YELLOW;
	}
	else {
		for (int i = 0; i <= 8; i++)
		{
			block[i][3].txtColor = LIGHT_BROWN;
		}
		block[9][3].txtColor = SADDLE_BROWN;
		block[9][3].bgdColor = LIGHT_BROWN;
		block[10][3].txtColor = LIGHT_BROWN;
		block[11][3].txtColor = LIGHT_BROWN;
		for (int i = 3; i <= 7; i++)
		{
			block[i][4].txtColor = LIGHT_BROWN;
		}
		block[8][3].txtColor = SADDLE_BROWN;
		for (int i = 9; i <= 11; i++)
		{
			block[i][4].txtColor = LIGHT_BROWN;
		}
		block[0][2].txtColor = SADDLE_BROWN;
		block[1][2].txtColor = LIGHT_BROWN;
		block[1][2].bgdColor = SADDLE_BROWN;
		block[2][2].txtColor = LIGHT_BROWN;
		block[3][2].txtColor = LIGHT_BROWN;
		block[4][2].bgdColor = LIGHT_BROWN;
		block[5][2].bgdColor = LIGHT_BROWN;
		block[6][2].bgdColor = LIGHT_BROWN;
		block[6][2].txtColor = LIGHT_BROWN;
		block[7][2].txtColor = SADDLE_BROWN;
		block[8][2].txtColor = LIGHT_BROWN;
		block[8][2].bgdColor = SADDLE_BROWN;

		block[7][1].txtColor = BRIGHT_YELLOW;
		block[8][1].txtColor = BRIGHT_YELLOW;
	}
}
