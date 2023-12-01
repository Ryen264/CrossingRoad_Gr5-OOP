#include "CTREE.h"
CTREE::CTREE(int x, int y, bool isDouble) : COBJECT(x, y) {
	this->isDouble = isDouble; this->ID = TREE_ID;
	vector<wstring> frame = (isDouble) ? FRAME_DOUBLE : FRAME_SINGLE;

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
			if (frame[j][i] != L' ')
				this->block[i][j] = { frame[j][i], BLACK, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };

	//set colors
	if (isDouble) {
		for (int i = 1; i < 6; i++)
		{
			block[i][1].txtColor = LIGHT_GREEN;
		}
		block[6][1].txtColor = DARK_GREEN;
		block[6][1].bgdColor = LIGHT_GREEN;
		block[7][1].bgdColor = DARK_GREEN;

		block[1][2].txtColor = DARK_GREEN;
		block[2][2].bgdColor = LIGHT_GREEN;
		block[2][2].txtColor = DARK_GREEN;
		block[3][2].bgdColor = LIGHT_GREEN;
		block[3][2].txtColor = DARK_GREEN;
		block[4][2].bgdColor = LIGHT_GREEN;
		block[4][2].txtColor = DARK_GREEN;

		block[5][2].txtColor = LIGHT_GREEN;
		block[6][2].txtColor = LIGHT_GREEN;
		block[7][2].txtColor = DARK_GREEN;
		for (int i = 1; i < 8; i++)
		{
			block[i][3].bgdColor = DARK_GREEN;
		}
		block[3][4].bgdColor = SADDLE_BROWN;
		block[3][4].txtColor = SADDLE_BROWN;
		block[4][4].bgdColor = SADDLE_BROWN;
		block[5][4].bgdColor = SADDLE_BROWN;
		block[5][4].txtColor = SADDLE_BROWN;
		block[4][5].bgdColor = SADDLE_BROWN;

		for (int i = 8; i < 13; i++)
		{
			block[i][0].bgdColor = LIGHT_GREEN;
		}
		block[13][0].bgdColor = DARK_GREEN;
		block[14][0].bgdColor = DARK_GREEN;
		for (int i = 9; i < 14; i++)
		{
			block[i][1].txtColor = LIGHT_GREEN;
		}
		block[14][1].txtColor = DARK_GREEN;

		block[9][2].txtColor = DARK_GREEN;
		block[10][2].txtColor = DARK_GREEN;
		for (int i = 11; i < 15; i++)
		{
			block[i][2].bgdColor = LIGHT_GREEN;
			block[i][2].txtColor = DARK_GREEN;
		}
		block[14][2].bgdColor = DARK_GREEN;

		block[10][3].bgdColor = SADDLE_BROWN;
		block[12][3].bgdColor = SADDLE_BROWN;
		block[10][4].bgdColor = SADDLE_BROWN;
		block[10][4].bgdColor = SADDLE_BROWN;
		block[11][4].bgdColor = SADDLE_BROWN;
		block[11][4].txtColor = SADDLE_BROWN;
		block[12][4].bgdColor = SADDLE_BROWN;

		block[11][5].bgdColor = SADDLE_BROWN;
		
	}
	else {
		for (int i = 1; i <= 5; i++)
			block[i][0].bgdColor = LIGHT_GREEN;
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
				block[i][1].txtColor = DARK_GREEN;
		}
		for (int i = 1; i <= 3; i++)
			block[i][2].txtColor = DARK_GREEN;
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
