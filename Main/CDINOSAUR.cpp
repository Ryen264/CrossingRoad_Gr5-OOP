#include "CDINOSAUR.h"

CDINOSAUR::CDINOSAUR(int x, int y, bool isRight) {
	this->numberOfBlock = 1;
	this->x = x; this->y = y; this->isRight = isRight;
	vector<wstring> frame = (isRight) ? FRAME_RIGHT : FRAME_LEFT;

	//set buffers
	for (int i = 0; i < BLOCKLENGTH; i++)
		for (int j = 0; j < BLOCKHEIGHT; j++)
			if (frame[j][i] != ' ')
				this->block[i][j] = { frame[j][i], BLACK, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };

	//set colors
	if (isRight) {
		for (int i = 5; i <= 13; i++)
			block[i][0].bgdColor = DARK_GREEN;

		block[5][1].bgdColor = DARK_GREEN;
		for (int i = 8; i <= 13; i++)
			block[i][1].bgdColor = DARK_GREEN;

		for (int i = 5; i <= 13; i++)
			block[i][2].bgdColor = DARK_GREEN;

		block[3][3].bgdColor = DARK_GREEN;
		block[5][3].txtColor = DARK_GREEN;
		block[6][3].txtColor = DARK_GREEN;
		block[5][3].bgdColor = DARK_GREEN;
		block[6][3].bgdColor = DARK_GREEN;
		block[7][3].txtColor = DARK_GREEN;
		block[7][3].bgdColor = LIGHT_GREEN;
		block[8][3].txtColor = DARK_GREEN;
		block[8][3].bgdColor = LIGHT_GREEN;
		block[9][3].txtColor = DARK_GREEN;
		block[9][3].bgdColor = LIGHT_GREEN;
		block[10][3].bgdColor = DARK_GREEN;
		block[11][3].bgdColor = DARK_GREEN;
		block[12][3].bgdColor = DARK_GREEN;
		block[13][3].bgdColor = DARK_GREEN;

		block[4][4].bgdColor = DARK_GREEN;
		block[5][4].bgdColor = DARK_GREEN;
		block[6][4].bgdColor = DARK_GREEN;
		block[7][4].bgdColor = LIGHT_GREEN;
		block[8][4].bgdColor = LIGHT_GREEN;
		block[9][4].bgdColor = LIGHT_GREEN;
	}
	else {
		block[5][1].bgdColor = DARK_GREEN;
		for (int i = 3; i <= 11; i++)
			block[i][1].bgdColor = DARK_GREEN;

		for (int i = 2; i <= 11; i++)
			block[i][2].bgdColor = DARK_GREEN;

		for (int i = 3; i <= 13; i++)
			block[i][3].bgdColor = DARK_GREEN;
		block[7][3].bgdColor = LIGHT_GREEN;
		block[7][3].txtColor = DARK_GREEN;
		block[8][3].bgdColor = LIGHT_GREEN;
		block[8][3].txtColor = DARK_GREEN;
		block[9][3].bgdColor = LIGHT_GREEN;
		block[9][3].txtColor = DARK_GREEN;
		block[10][3].txtColor = DARK_GREEN;

		for (int i = 7; i <= 9; i++)
			block[i][4].bgdColor = LIGHT_GREEN;
		for (int i = 10; i <= 12; i++)
			block[i][4].bgdColor = DARK_GREEN;
	}
}
