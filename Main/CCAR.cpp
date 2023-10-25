#include "CCAR.h"
CCAR::CCAR(int x, int y, int isRight) {
	this->numberOfBlock = 1;
	this->x = x; this->y = y; this->isRight = isRight;
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
		block[3][1].txtColor = DARK_RED;
		block[4][1].txtColor = DARK_RED;
		block[10][1].txtColor = DARK_RED;
		block[11][1].txtColor = DARK_RED;
		block[9][1].txtColor = SKY_BLUE;
		block[12][1].txtColor = BRIGHT_YELLOW;

		block[5][2].txtColor = DARK_RED;
		block[5][2].bgdColor = RED;
		block[6][2].txtColor = DARK_RED;
		block[6][2].bgdColor = RED;
		block[7][2].txtColor = DARK_RED;
		block[7][2].bgdColor = RED;
		block[8][2].txtColor = DARK_RED;
		block[8][2].bgdColor = RED;
		block[9][2].txtColor = SKY_BLUE;

		block[3][3].txtColor = DARK_RED;
		block[4][3].txtColor = DARK_RED;
		block[9][3].txtColor = DARK_RED;
		block[5][3].txtColor = DARK_RED;
		block[5][3].bgdColor = SKY_BLUE;
		block[6][3].txtColor = DARK_RED;
		block[6][3].bgdColor = SKY_BLUE;
		block[7][3].txtColor = DARK_RED;
		block[7][3].bgdColor = SKY_BLUE;
		block[8][3].txtColor = DARK_RED;
		block[8][3].bgdColor = SKY_BLUE;
		block[10][3].txtColor = DARK_RED;
		block[10][3].bgdColor = RED;
		block[11][3].txtColor = DARK_RED;
		block[11][3].bgdColor = RED;
		block[12][3].txtColor = BRIGHT_YELLOW;
		block[12][3].bgdColor = RED;

		block[4][4].txtColor = BLACK;
		block[5][4].txtColor = BLACK;
		block[9][4].txtColor = BLACK;
		block[10][4].txtColor = BLACK;
	}
	else {

	}
}