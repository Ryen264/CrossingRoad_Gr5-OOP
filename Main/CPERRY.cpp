#include "CPERRY.h"
CPERRY::CPERRY(int x, int y, bool isRight) {
	this->x = x; this->y = y; this->isRight = isRight;
	vector<wstring> frame = (isRight) ? FRAME_RIGHT : FRAME_LEFT;

	this->block = new PIXEL * [BLOCK_WIDTH * this->numberOfWidth];
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		this->block[i] = new PIXEL[BLOCK_HEIGHT * this->numberOfHeight];

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
			if (frame[j][i] != L' ')
				this->block[i][j] = { frame[j][i], RED, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };

	//set colors
	if (isRight) {
		block[12][1].txtColor = WHITE;
		block[12][1].bgdColor = SKY_BLUE;
		block[11][1].txtColor = SKY_BLUE;
		block[10][1].txtColor = BLACK;
		block[10][1].bgdColor = SKY_BLUE;
		block[9][1].txtColor = WHITE;
		block[9][1].bgdColor = SKY_BLUE;
		block[8][1].txtColor = SKY_BLUE;
		block[8][2].txtColor = SKY_BLUE;
		block[9][2].txtColor = SKY_BLUE;
		block[10][2].txtColor = BRIGHT_YELLOW;
		block[10][2].bgdColor = BLACK;
		block[11][2].txtColor = BRIGHT_YELLOW;
		block[12][2].txtColor = BRIGHT_YELLOW;
		block[13][2].txtColor = BRIGHT_YELLOW;
		block[13][2].bgdColor = BLACK;
		block[14][2].txtColor = BRIGHT_YELLOW;
		block[15][2].txtColor = BRIGHT_YELLOW;
		for (int i = 8; i <= 13; i++)
		{
			block[i][3].txtColor = SKY_BLUE;
		}
		block[4][2].txtColor = BRIGHT_YELLOW;
		block[4][2].bgdColor = ORANGE;
		block[5][2].txtColor = ORANGE;
		block[5][2].bgdColor = BRIGHT_YELLOW;
		block[6][2].txtColor = BRIGHT_YELLOW;
		block[6][2].bgdColor = ORANGE;
		block[7][2].txtColor = ORANGE;
		block[6][3].txtColor = ORANGE;
		block[7][3].txtColor = BRIGHT_YELLOW;
	}
	else {
		block[3][1].bgdColor = SKY_BLUE;
		block[3][1].txtColor = WHITE;
		block[4][1].txtColor = SKY_BLUE;
		block[5][1].bgdColor = SKY_BLUE;
		block[6][1].bgdColor = SKY_BLUE;
		block[6][1].txtColor = WHITE;
		block[7][1].txtColor = SKY_BLUE;
		block[0][2].txtColor = BRIGHT_YELLOW;
		block[1][2].txtColor = BRIGHT_YELLOW;
		block[2][2].txtColor = BRIGHT_YELLOW;
		block[2][2].bgdColor = BLACK;
		block[3][2].txtColor = BRIGHT_YELLOW;
		block[3][2].bgdColor = WHITE;
		block[4][2].txtColor = BRIGHT_YELLOW;
		block[5][2].txtColor = BRIGHT_YELLOW;
		block[5][2].bgdColor = BLACK;
		block[5][2].txtColor = BRIGHT_YELLOW;
		block[5][2].bgdColor = BLACK;
		block[6][2].txtColor = SKY_BLUE;
		block[7][2].txtColor = SKY_BLUE;
		block[8][2].txtColor = ORANGE;
		block[9][2].bgdColor = ORANGE;
		block[9][2].txtColor = BRIGHT_YELLOW;
		block[10][2].bgdColor = BRIGHT_YELLOW;
		block[10][2].txtColor = ORANGE;
		block[11][2].bgdColor = ORANGE;
		block[11][2].txtColor = BRIGHT_YELLOW;
		for (int i = 2; i <= 7; i++)
		{
			block[i][3].txtColor = SKY_BLUE;
		}
		block[8][3].txtColor = BRIGHT_YELLOW;
		block[9][3].txtColor = ORANGE;
	}
}
