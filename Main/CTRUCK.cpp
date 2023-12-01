#include "CTRUCK.h"
CTRUCK::CTRUCK(int x, int y, bool isRight) : COBJECT(x, y) {
	this->isRight = isRight; this->ID = TRUCK_ID;
	vector<wstring> frame = (isRight) ? FRAME_RIGHT : FRAME_LEFT;

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
			if (frame[j][i] != L' ')
				this->block[i][j] = { frame[j][i], DARK_GREEN, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };

	//set colors
	if (isRight) {
		block[14][1].txtColor = BRIGHT_YELLOW;
		block[14][3].txtColor = BRIGHT_YELLOW;
		for (int i = 12; i <= 14; i++) {
			block[i][2].txtColor = LIGHT_GREEN;
			block[i][3].bgdColor = LIGHT_GREEN;
		}
		block[11][1].txtColor = WHITE;
		block[11][2].txtColor = WHITE;
		block[3][4].txtColor = BLACK;
		block[4][4].txtColor = BLACK;
		block[11][4].txtColor = BLACK;
		block[12][4].txtColor = BLACK;
		for (int i = 8; i <= 10; i++) {
			block[i][1].txtColor = LIGHT_GREEN;
			block[i][2].bgdColor = LIGHT_GREEN;
			block[i][3].bgdColor = WHITE;
		}
		block[7][1].txtColor = LIGHT_GREEN;
		block[7][2].txtColor = LIGHT_GREEN;
		for (int i = 2; i <= 6; i++) {
			block[i][2].txtColor = LIGHT_GRAY;
			block[i][2].bgdColor = DARK_GRAY;
			block[i][3].bgdColor = DARK_GRAY;
		}
	}
	else {
		block[1][1].txtColor = BRIGHT_YELLOW;
		block[1][3].txtColor = BRIGHT_YELLOW;
		for (int i = 1; i <= 3; i++) {
			block[i][2].txtColor = LIGHT_GREEN;
			block[i][3].bgdColor = LIGHT_GREEN;
		}
		block[4][1].txtColor = WHITE;
		block[4][2].txtColor = WHITE;
		block[3][4].txtColor = BLACK;
		block[4][4].txtColor = BLACK;
		block[11][4].txtColor = BLACK;
		block[12][4].txtColor = BLACK;
		for (int i = 5; i <= 8; i++) {
			block[i][1].txtColor = LIGHT_GREEN;
			block[i][2].bgdColor = LIGHT_GREEN;
			block[i][3].bgdColor = WHITE;
		}
		block[8][1].txtColor = LIGHT_GREEN;
		block[8][2].txtColor = LIGHT_GREEN;
		for (int i = 9; i <= 13; i++) {
			block[i][2].txtColor = LIGHT_GRAY;
			block[i][2].bgdColor = DARK_GRAY;
			block[i][3].bgdColor = DARK_GRAY;
		}
	}
}

