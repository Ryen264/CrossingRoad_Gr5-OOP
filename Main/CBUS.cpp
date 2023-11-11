#include "CBUS.h"
CBUS::CBUS(int x, int y, bool isRight) {
	this->numberOfBlock = 1;
	this->x = x; this->y = y; this->isRight = !isRight;
	vector<wstring> frame = (!isRight) ? FRAME_RIGHT : FRAME_LEFT;

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH * 2; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
			if (frame[j][i] != L' ')
				this->block[i][j] = { frame[j][i], DARK_RED, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };

	//set colors
	if (!isRight) {
		block[25][1].txtColor = BRIGHT_YELLOW;
		block[25][3].txtColor = BRIGHT_YELLOW;
		for (int i = 7; i < 23; i++) {
			block[i][1].bgdColor = RED;
			block[i][2].bgdColor = RED;
		}
		block[24][2].bgdColor = RED;
		block[25][2].bgdColor = RED;
		block[24][3].bgdColor = RED;
		block[25][3].bgdColor = RED;
		block[23][1].txtColor = WHITE;
		block[23][2].txtColor = WHITE;
		for (int i = 0; i < 3; i++) {
			block[8 + i][4].txtColor = BLACK;
			block[8 + i][4].bgdColor = DARK_RED;
			block[20 + i][4].txtColor = BLACK;
			block[20 + i][4].bgdColor = DARK_RED;
		}
	}
	else {
		block[6][1].txtColor = BRIGHT_YELLOW;
		block[6][3].txtColor = BRIGHT_YELLOW;
		for (int i = 9; i < 25; i++) {
			block[i][1].bgdColor = RED;
			block[i][2].bgdColor = RED;
		}
		block[6][2].bgdColor = RED;
		block[7][2].bgdColor = RED;
		block[6][3].bgdColor = RED;
		block[7][3].bgdColor = RED;
		block[8][1].txtColor = WHITE;
		block[8][2].txtColor = WHITE;
		for (int i = 0; i < 3; i++) {
			block[9 + i][4].txtColor = BLACK;
			block[9 + i][4].bgdColor = DARK_RED;
			block[21 + i][4].txtColor = BLACK;
			block[21 + i][4].bgdColor = DARK_RED;
		}
	}
}