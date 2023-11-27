#include "CTREE_2_BLOCK.h"
CTREE_2_BLOCK::CTREE_2_BLOCK(int x, int y, bool isRight) {
	this->x = x; this->y = y; this->isRight = isRight;
	this->ID = CAPYBARA_ID;
	vector<wstring> frame = (isRight) ? FRAME_RIGHT : FRAME_LEFT;

	this->block = new PIXEL * [BLOCK_WIDTH];
	for (int i = 0; i < BLOCK_WIDTH; i++)
		this->block[i] = new PIXEL[BLOCK_HEIGHT];

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
			if (frame[j][i] != L' ')
				this->block[i][j] = { frame[j][i], -1, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };

	//set colors
	if (isRight) {
		block[6][4].bgdColor = SADDLE_BROWN;
		block[8][4].bgdColor = SADDLE_BROWN;
		block[7][5].bgdColor = SADDLE_BROWN;
		block[7][4].bgdColor = SADDLE_BROWN;
		block[9][5].bgdColor = SADDLE_BROWN;
		block[11][5].bgdColor = SADDLE_BROWN;
		block[10][6].bgdColor = SADDLE_BROWN;
		block[5][8].bgdColor = SADDLE_BROWN;
		block[6][8].bgdColor = SADDLE_BROWN;
		block[7][8].bgdColor = SADDLE_BROWN;
		block[6][8].bgdColor = SADDLE_BROWN;
		for (int j = 9; j <= 11; j++)
		{
			block[7][j].bgdColor = SADDLE_BROWN;
		}
		block[6][11].bgdColor = SADDLE_BROWN;
		block[7][11].bgdColor = SADDLE_BROWN;
		block[8][11].bgdColor = SADDLE_BROWN;
		for (int i = 4; i <= 8; i++)
		{
			block[i][0].bgdColor = LIGHT_GREEN;
		}
		for (int i = 2; i <= 9; i++)
		{
			block[i][1].bgdColor = LIGHT_GREEN;
		}
		for (int i = 7; i <= 10; i++)
		{
			block[i][2].bgdColor = LIGHT_GREEN;
		}
		block[5][2].bgdColor = LIGHT_GREEN;
		block[5][2].txtColor = DARK_GREEN;
		block[6][2].bgdColor = LIGHT_GREEN;
		block[6][2].txtColor = DARK_GREEN;
		for (int i = 10; i <= 12; i++)
		{
			block[i][4].bgdColor = LIGHT_GREEN;
			block[i][4].txtColor = DARK_GREEN;
		}
		block[11][3].bgdColor = LIGHT_GREEN;
		block[3][6].bgdColor = LIGHT_GREEN;
		block[3][6].txtColor = DARK_GREEN;
		block[4][6].bgdColor = LIGHT_GREEN;
		block[5][6].bgdColor = LIGHT_GREEN;
		block[6][6].bgdColor = LIGHT_GREEN;
		block[7][6].txtColor = DARK_GREEN;
		block[7][6].bgdColor = LIGHT_GREEN;
	}
	else {
		block[6][4].bgdColor = SADDLE_BROWN;
		block[8][4].bgdColor = SADDLE_BROWN;
		block[7][5].bgdColor = SADDLE_BROWN;
		block[7][4].bgdColor = SADDLE_BROWN;
		block[9][5].bgdColor = SADDLE_BROWN;
		block[11][5].bgdColor = SADDLE_BROWN;
		block[10][6].bgdColor = SADDLE_BROWN;
		block[5][8].bgdColor = SADDLE_BROWN;
		block[6][8].bgdColor = SADDLE_BROWN;
		block[7][8].bgdColor = SADDLE_BROWN;
		block[6][8].bgdColor = SADDLE_BROWN;
		for (int j = 9; j <= 11; j++)
		{
			block[7][j].bgdColor = SADDLE_BROWN;
		}
		block[6][11].bgdColor = SADDLE_BROWN;
		block[7][11].bgdColor = SADDLE_BROWN;
		block[8][11].bgdColor = SADDLE_BROWN;
		for (int i = 4; i <= 8; i++)
		{
			block[i][0].bgdColor = LIGHT_GREEN;
		}
		for (int i = 2; i <= 9; i++)
		{
			block[i][1].bgdColor = LIGHT_GREEN;
		}
		for (int i = 7; i <= 10; i++)
		{
			block[i][2].bgdColor = LIGHT_GREEN;
		}
		block[5][2].bgdColor = LIGHT_GREEN;
		block[5][2].txtColor = DARK_GREEN;
		block[6][2].bgdColor = LIGHT_GREEN;
		block[6][2].txtColor = DARK_GREEN;
		for (int i = 10; i <= 12; i++)
		{
			block[i][4].bgdColor = LIGHT_GREEN;
			block[i][4].txtColor = DARK_GREEN;
		}
		block[11][3].bgdColor = LIGHT_GREEN;
		block[3][6].bgdColor = LIGHT_GREEN;
		block[3][6].txtColor = DARK_GREEN;
		block[4][6].bgdColor = LIGHT_GREEN;
		block[5][6].bgdColor = LIGHT_GREEN;
		block[6][6].bgdColor = LIGHT_GREEN;
		block[7][6].txtColor = DARK_GREEN;
		block[7][6].bgdColor = LIGHT_GREEN;
	}
}