#include "CEGG.h"
CEGG::CEGG(int x, int y) : COBJECT(x, y) {
	this->ID = EGG_ID;

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
			if (FRAME[j][i] != L' ')
				this->block[i][j] = { FRAME[j][i], WHITE, -1 };
			else
				this->block[i][j] = { FRAME[j][i], -1, -1 };

	//set colors
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

	block[6][3].txtColor = BLACK;
	block[6][3].bgdColor = WHITE;
	block[7][3].txtColor = BLACK;
	block[7][3].bgdColor = WHITE;

	block[8][3].txtColor = BLACK;
	block[8][3].bgdColor = WHITE;
	block[9][3].txtColor = BLACK;
	block[9][3].bgdColor = -1;

	block[6][4].txtColor = BLACK;
	block[6][4].bgdColor = -1;
	block[7][4].txtColor = BLACK;
	block[7][4].bgdColor = -1;
}