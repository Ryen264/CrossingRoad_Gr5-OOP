#include "CCAPYBARA.h"
CCAPYBARA::CCAPYBARA(int x, int y, bool isRight) : COBJECT(x, y) {
	this->isRight = isRight; this->ID = CAPYBARA_ID;
	vector<wstring> frame = (isRight) ? FRAME_RIGHT : FRAME_LEFT;

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
			if (frame[j][i] != L' ')
				this->block[i][j] = { frame[j][i], LIGHT_BROWN, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };

	//set colors
	if (isRight) {
		block[2][3].txtColor = SADDLE_BROWN;
		block[2][3].bgdColor = LIGHT_BROWN;
		block[3][3].txtColor = SADDLE_BROWN;

		block[3][2].bgdColor = SADDLE_BROWN;
		block[4][2].txtColor = SADDLE_BROWN;
		block[5][2].bgdColor = LIGHT_BROWN;
		block[6][2].bgdColor = LIGHT_BROWN;
		block[6][2].txtColor = BLACK;
		block[7][2].txtColor = BLACK;
		block[7][2].bgdColor = LIGHT_BROWN;
		block[10][2].bgdColor = SADDLE_BROWN;
		block[11][2].txtColor = SADDLE_BROWN;
		block[11][2].txtColor = SADDLE_BROWN;

		block[3][1].txtColor = BRIGHT_YELLOW;
		block[4][1].txtColor = BRIGHT_YELLOW;
	}
	else {
		block[9][3].txtColor = SADDLE_BROWN;
		block[9][3].bgdColor = LIGHT_BROWN;
		block[8][3].txtColor = SADDLE_BROWN;

		block[0][2].txtColor = SADDLE_BROWN;
		block[1][2].bgdColor = SADDLE_BROWN;
		block[4][2].bgdColor = LIGHT_BROWN;
		block[4][2].txtColor = BLACK;
		block[5][2].bgdColor = LIGHT_BROWN;
		block[5][2].txtColor = BLACK;
		block[6][2].bgdColor = LIGHT_BROWN;
		block[7][2].txtColor = SADDLE_BROWN;
		block[8][2].bgdColor = SADDLE_BROWN;

		block[7][1].txtColor = BRIGHT_YELLOW;
		block[8][1].txtColor = BRIGHT_YELLOW;
	}
}
