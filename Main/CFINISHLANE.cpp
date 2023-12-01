#include "CFINISHLANE.h"
CFINISHLANE::CFINISHLANE(int x, int y) : CLANE(x, y) {
	for (int i = 0; i < BOARD_WIDTH; i++)
		this->lane.push_front(NULL);

	this->ID = FINISHLANE_ID;

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
				this->block[i][j] = { FRAME[j][i], BLACK, WHITE };

	//set colors
	block[0][0].txtColor = WHITE;
	block[15][0].txtColor = WHITE;
	for (int i = 1; i < 14; i += 4)
	{
		block[i][0].txtColor = BLACK;
		block[i + 1][0].txtColor = BLACK;
	}
	for (int i = 3; i < 12; i += 4)
	{
		block[i][0].txtColor = WHITE;
		block[i + 1][0].txtColor = WHITE;
	}


	block[0][1].txtColor = BLACK;
	block[15][1].txtColor = BLACK;
	for (int i = 1; i < 14; i += 4)
	{
		block[i][1].txtColor = WHITE;
		block[i + 1][1].txtColor = WHITE;
	}
	for (int i = 3; i < 12; i += 4)
	{
		block[i][1].txtColor = BLACK;
		block[i + 1][1].txtColor = BLACK;
	}


	block[0][2].txtColor = WHITE;
	block[15][2].txtColor = WHITE;
	for (int i = 1; i < 14; i += 4)
	{
		block[i][2].txtColor = BLACK;
		block[i + 1][2].txtColor = BLACK;
	}
	for (int i = 3; i < 12; i += 4)
	{
		block[i][2].txtColor = WHITE;
		block[i + 1][2].txtColor = WHITE;
	}


	block[0][3].txtColor = BLACK;
	block[15][3].txtColor = BLACK;
	for (int i = 1; i < 14; i += 4)
	{
		block[i][3].txtColor = WHITE;
		block[i + 1][3].txtColor = WHITE;
	}
	for (int i = 3; i < 12; i += 4)
	{
		block[i][3].txtColor = BLACK;
		block[i + 1][3].txtColor = BLACK;
	}

	block[0][4].txtColor = WHITE;
	block[15][4].txtColor = WHITE;
	for (int i = 1; i < 14; i += 4)
	{
		block[i][4].txtColor = BLACK;
		block[i + 1][4].txtColor = BLACK;
	}
	for (int i = 3; i < 12; i += 4)
	{
		block[i][4].txtColor = WHITE;
		block[i + 1][4].txtColor = WHITE;
	}

	block[0][5].txtColor = BLACK;
	block[15][5].txtColor = BLACK;
	for (int i = 1; i < 14; i += 4)
	{
		block[i][5].txtColor = WHITE;
		block[i + 1][5].txtColor = WHITE;
	}
	for (int i = 3; i < 12; i += 4)
	{
		block[i][5].txtColor = BLACK;
		block[i + 1][5].txtColor = BLACK;
	}
}
