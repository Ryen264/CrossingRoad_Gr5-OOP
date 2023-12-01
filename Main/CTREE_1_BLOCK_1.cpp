#include "CTREE_1_BLOCK_1.h"
CTREE_1_BLOCK_1::CTREE_1_BLOCK_1(int x, int y, bool isRight) {
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
		for (int i = 1; i <= 5; i++)
		{
			block[i][0].bgdColor = LIGHT_GREEN;
		}
		block[6][0].bgdColor = DARK_GREEN;
		block[7][y].bgdColor = DARK_GREEN;
		for (int i = 1; i <= 7; i++)
		{
			if (i == 1)
			{
				block[i][1].txtColor = DARK_GREEN;
				block[i][1].bgdColor = LIGHT_GREEN;
			}
			else if (i == 7)
			{
				block[i][1].txtColor = DARK_GREEN;
			}
			else
			{
				block[i][1].txtColor = LIGHT_GREEN;
			}
		}
		for (int i = 1; i <= 3; i++)
		{
			block[i][2].txtColor = DARK_GREEN;
		}
		for (int i = 4; i <= 6; i++)
		{
			block[i][2].txtColor = DARK_GREEN;
			block[i][2].bgdColor = LIGHT_GREEN;
		}
		block[7][2].txtColor = DARK_GREEN;
		
		block[3][3].bgdColor = SADDLE_BROWN;
		block[5][3].bgdColor = SADDLE_BROWN;

		block[3][4].txtColor = SADDLE_BROWN;
		block[3][4].bgdColor = BLACK;
		block[4][4].txtColor = SADDLE_BROWN;
		block[4][4].bgdColor = BLACK;
		block[5][4].txtColor = SADDLE_BROWN;
		block[5][4].bgdColor = BLACK;
	}
	else {
		for (int i = 1; i <= 5; i++)
		{
			block[i][0].bgdColor = LIGHT_GREEN;
		}
		block[6][0].bgdColor = DARK_GREEN;
		block[7][y].bgdColor = DARK_GREEN;
		for (int i = 1; i <= 7; i++)
		{
			if (i == 1)
			{
				block[i][1].txtColor = DARK_GREEN;
				block[i][1].bgdColor = LIGHT_GREEN;
			}
			else if (i == 7)
			{
				block[i][1].txtColor = DARK_GREEN;
			}
			else
			{
				block[i][1].txtColor = LIGHT_GREEN;
			}
		}
		for (int i = 1; i <= 3; i++)
		{
			block[i][2].txtColor = DARK_GREEN;
		}
		for (int i = 4; i <= 6; i++)
		{
			block[i][2].txtColor = DARK_GREEN;
			block[i][2].bgdColor = LIGHT_GREEN;
		}
		block[7][2].txtColor = DARK_GREEN;

		block[3][3].bgdColor = SADDLE_BROWN;
		block[5][3].bgdColor = SADDLE_BROWN;

		block[3][4].txtColor = SADDLE_BROWN;
		block[3][4].bgdColor = BLACK;
		block[4][4].txtColor = SADDLE_BROWN;
		block[4][4].bgdColor = BLACK;
		block[5][4].txtColor = SADDLE_BROWN;
		block[5][4].bgdColor = BLACK;
	}
}
