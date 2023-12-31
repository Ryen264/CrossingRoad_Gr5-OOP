#include "CPERRY.h"
CPERRY::CPERRY(int x, int y, bool isRight) : COBJECT(x, y) {
	this->isRight = isRight; this->ID = PERRY_ID;
	vector<wstring> frame = (isRight) ? FRAME_RIGHT : FRAME_LEFT;

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
			if (frame[j][i] != L' ')
				this->block[i][j] = { frame[j][i], RED, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };

	//set colors
	if (isRight) {
		block[12][2].txtColor = WHITE;
		block[12][2].bgdColor = SKY_BLUE;
		block[13][2].txtColor = BLACK;
		block[13][2].bgdColor = SKY_BLUE;
		block[11][2].txtColor = SKY_BLUE;
		block[10][2].txtColor = BLACK;
		block[10][2].bgdColor = SKY_BLUE;
		block[9][2].txtColor = WHITE;
		block[9][2].bgdColor = SKY_BLUE;
		block[8][2].txtColor = SKY_BLUE;
		block[8][3].txtColor = SKY_BLUE;
		block[9][3].txtColor = SKY_BLUE;
		block[9][3].bgdColor = WHITE;
		block[10][3].txtColor = BRIGHT_YELLOW;
		block[10][3].bgdColor = BLACK;
		block[11][3].txtColor = BRIGHT_YELLOW;
		block[12][3].txtColor = BRIGHT_YELLOW;
		block[12][3].bgdColor = WHITE;
		block[13][3].txtColor = BRIGHT_YELLOW;
		block[13][3].bgdColor = BLACK;
		block[14][3].txtColor = BRIGHT_YELLOW;
		block[15][3].txtColor = BRIGHT_YELLOW;
		for (int i = 8; i <= 13; i++)
		{
			block[i][4].txtColor = SKY_BLUE;
		}
		block[4][3].txtColor = BRIGHT_YELLOW;
		block[4][3].bgdColor = ORANGE;
		block[5][3].txtColor = ORANGE;
		block[5][3].bgdColor = BRIGHT_YELLOW;
		block[6][3].txtColor = BRIGHT_YELLOW;
		block[6][3].bgdColor = ORANGE;
		block[7][3].txtColor = ORANGE;
		block[6][4].txtColor = ORANGE;
		block[7][4].txtColor = BRIGHT_YELLOW;
	}
	else {
		block[3][1].txtColor = RED;
		block[3][1].bgdColor = -1;
		block[4][1].txtColor = RED;
		block[4][1].bgdColor = -1;
		block[5][1].txtColor = RED;
		block[5][1].bgdColor = -1;
		block[3][2].txtColor = WHITE;
		block[3][2].bgdColor = SKY_BLUE;
		block[2][2].txtColor = BLACK;
		block[2][2].bgdColor = SKY_BLUE;
		block[4][2].txtColor = SKY_BLUE;
		block[5][2].txtColor = BLACK;
		block[5][2].bgdColor = SKY_BLUE;
		block[6][2].txtColor = WHITE;
		block[6][2].bgdColor = SKY_BLUE;
		block[7][2].txtColor = SKY_BLUE;

		block[0][3].txtColor = BRIGHT_YELLOW;
		block[1][3].txtColor = BRIGHT_YELLOW;
		block[2][3].txtColor = BRIGHT_YELLOW;
		block[2][3].bgdColor = BLACK;
		block[3][3].txtColor = BRIGHT_YELLOW;
		block[3][3].bgdColor = WHITE;
		block[4][3].txtColor = BRIGHT_YELLOW;
		block[5][3].txtColor = BRIGHT_YELLOW;
		block[5][3].bgdColor = BLACK;
		block[6][3].txtColor = BRIGHT_YELLOW;
		block[6][3].bgdColor = WHITE;
		block[7][3].txtColor = SKY_BLUE;
		block[8][3].txtColor = ORANGE;
		block[8][3].bgdColor = -1;
		block[9][3].txtColor = BRIGHT_YELLOW;
		block[9][3].bgdColor = ORANGE;
		block[10][3].txtColor = ORANGE;
		block[10][3].bgdColor = BRIGHT_YELLOW;
		block[11][3].txtColor = BRIGHT_YELLOW;
		block[11][3].bgdColor = ORANGE;

		for (int i = 2; i < 8; i++)
			block[i][4].txtColor = SKY_BLUE;
		block[8][4].txtColor = BRIGHT_YELLOW;
		block[9][4].txtColor = ORANGE;
	}
}
bool CPERRY::getIsRight() const
{
	return isRight;
}

void CPERRY::setIsRight(bool isRight)
{
	this->isRight = isRight;

	vector<wstring> frame = (isRight) ? FRAME_RIGHT : FRAME_LEFT;

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
			if (frame[j][i] != L' ')
				this->block[i][j] = { frame[j][i], RED, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };

	//set colors
	if (isRight) {
		block[12][2].txtColor = WHITE;
		block[12][2].bgdColor = SKY_BLUE;
		block[13][2].txtColor = BLACK;
		block[13][2].bgdColor = SKY_BLUE;
		block[11][2].txtColor = SKY_BLUE;
		block[10][2].txtColor = BLACK;
		block[10][2].bgdColor = SKY_BLUE;
		block[9][2].txtColor = WHITE;
		block[9][2].bgdColor = SKY_BLUE;
		block[8][2].txtColor = SKY_BLUE;
		block[8][3].txtColor = SKY_BLUE;
		block[9][3].txtColor = SKY_BLUE;
		block[9][3].bgdColor = WHITE;
		block[10][3].txtColor = BRIGHT_YELLOW;
		block[10][3].bgdColor = BLACK;
		block[11][3].txtColor = BRIGHT_YELLOW;
		block[12][3].txtColor = BRIGHT_YELLOW;
		block[12][3].bgdColor = WHITE;
		block[13][3].txtColor = BRIGHT_YELLOW;
		block[13][3].bgdColor = BLACK;
		block[14][3].txtColor = BRIGHT_YELLOW;
		block[15][3].txtColor = BRIGHT_YELLOW;
		for (int i = 8; i <= 13; i++)
		{
			block[i][4].txtColor = SKY_BLUE;
		}
		block[4][3].txtColor = BRIGHT_YELLOW;
		block[4][3].bgdColor = ORANGE;
		block[5][3].txtColor = ORANGE;
		block[5][3].bgdColor = BRIGHT_YELLOW;
		block[6][3].txtColor = BRIGHT_YELLOW;
		block[6][3].bgdColor = ORANGE;
		block[7][3].txtColor = ORANGE;
		block[6][4].txtColor = ORANGE;
		block[7][4].txtColor = BRIGHT_YELLOW;
	}
	else {
		block[3][1].txtColor = RED;
		block[3][1].bgdColor = -1;
		block[4][1].txtColor = RED;
		block[4][1].bgdColor = -1;
		block[5][1].txtColor = RED;
		block[5][1].bgdColor = -1;
		block[3][2].txtColor = WHITE;
		block[3][2].bgdColor = SKY_BLUE;
		block[2][2].txtColor = BLACK;
		block[2][2].bgdColor = SKY_BLUE;
		block[4][2].txtColor = SKY_BLUE;
		block[5][2].txtColor = BLACK;
		block[5][2].bgdColor = SKY_BLUE;
		block[6][2].txtColor = WHITE;
		block[6][2].bgdColor = SKY_BLUE;
		block[7][2].txtColor = SKY_BLUE;

		block[0][3].txtColor = BRIGHT_YELLOW;
		block[1][3].txtColor = BRIGHT_YELLOW;
		block[2][3].txtColor = BRIGHT_YELLOW;
		block[2][3].bgdColor = BLACK;
		block[3][3].txtColor = BRIGHT_YELLOW;
		block[3][3].bgdColor = WHITE;
		block[4][3].txtColor = BRIGHT_YELLOW;
		block[5][3].txtColor = BRIGHT_YELLOW;
		block[5][3].bgdColor = BLACK;
		block[6][3].txtColor = BRIGHT_YELLOW;
		block[6][3].bgdColor = WHITE;
		block[7][3].txtColor = SKY_BLUE;
		block[8][3].txtColor = ORANGE;
		block[8][3].bgdColor = -1;
		block[9][3].txtColor = BRIGHT_YELLOW;
		block[9][3].bgdColor = ORANGE;
		block[10][3].txtColor = ORANGE;
		block[10][3].bgdColor = BRIGHT_YELLOW;
		block[11][3].txtColor = BRIGHT_YELLOW;
		block[11][3].bgdColor = ORANGE;

		for (int i = 2; i < 8; i++)
			block[i][4].txtColor = SKY_BLUE;
		block[8][4].txtColor = BRIGHT_YELLOW;
		block[9][4].txtColor = ORANGE;
	}
}
