#include "CFINISHLANE.h"
CFINISHLANE::CFINISHLANE(int x, int y, bool isRight) {
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
	else {
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

}
