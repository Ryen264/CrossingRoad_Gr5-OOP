#include "CTRAIN.h"
CTRAIN::CTRAIN(int x, int y, bool isRight, bool isHead) {
	this->x = x; this->y = y; this->isRight = isRight; this->isHead = isHead;
	this->ID = (isHead) ? TRAIN_HEAD_ID : TRAIN_BODY_ID;
	vector<wstring> frame{};
	if (isRight)
		if (isHead) frame = FRAME_HEAD_RIGHT;
		else frame = FRAME_BODY_RIGHT;
	else
		if (isHead) frame = FRAME_HEAD_LEFT;
		else frame = FRAME_BODY_LEFT;

	this->block = new PIXEL * [BLOCK_WIDTH];
	for (int i = 0; i < BLOCK_WIDTH; i++)
		this->block[i] = new PIXEL[BLOCK_HEIGHT];

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
			if (frame[j][i] != L' ')
				this->block[i][j] = { frame[j][i], LIGHT_GRAY, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };

	//set colors
	if (isRight)
		if (isHead) {
			for (int i = 0; i < 13; i++) {
				block[i][4].txtColor = DARK_GRAY;
				block[i][4].bgdColor = LIGHT_GRAY;
				block[i][5].txtColor = DARK_GRAY;
			}
			for (int i = 0; i <= 2; i++) {
				block[1 + i][5].txtColor = BLACK;
				block[8 + i][5].txtColor = BLACK;
			}
			for (int i = 0; i < 10; i++) {
				block[i][0].bgdColor = WHITE;
				block[i][1].bgdColor = WHITE;
			}
			block[0][2].bgdColor = WHITE;
			block[1][2].bgdColor = WHITE;
			block[0][3].bgdColor = WHITE;
			block[1][3].bgdColor = WHITE;
			block[14][3].bgdColor = WHITE;
			block[13][3].bgdColor = WHITE;
			block[4][2].txtColor = DARK_BLUE;
			block[4][2].bgdColor = LIGHT_GRAY;
			block[4][3].txtColor = DARK_BLUE;
			block[3][2].txtColor = WHITE;
			block[3][2].bgdColor = LIGHT_GRAY;
			block[3][3].txtColor = WHITE;
			block[6][2].txtColor = DARK_BLUE;
			block[7][2].txtColor = DARK_BLUE;
			block[6][2].bgdColor = BLUE;
			block[7][2].bgdColor = BLUE;
			block[8][2].txtColor = BLUE;
			block[9][2].txtColor = BLUE;
			block[9][2].bgdColor = LIGHT_GRAY;
			block[10][2].txtColor = DARK_BLUE;
			block[10][2].bgdColor = LIGHT_GRAY;
			block[11][2].txtColor = DARK_BLUE;
			block[11][2].bgdColor = BLUE;
			for (int i = 12; i < 15; i++) {
				block[i][2].txtColor = BLUE;
				block[i][1].txtColor = BLUE;
			}
			for (int i = 9; i < 12; i++) {
				block[i][0].txtColor = BLUE;
				block[i][1].txtColor = BLUE;
				block[i][1].bgdColor = BLUE;
			}
			block[9][0].bgdColor = LIGHT_GRAY;
			block[9][1].txtColor = DARK_BLUE;
			block[10][0].bgdColor = LIGHT_GREEN;
			block[11][0].bgdColor = LIGHT_GREEN;
			block[14][1].bgdColor = DARK_GREEN;
}
		else {
			for (int i = 0; i < 16; i++) {
				block[i][5].txtColor = LIGHT_GREEN;
				block[i][5].bgdColor = DARK_GRAY;
				block[i][4].txtColor = DARK_GRAY;
				block[i][4].bgdColor = LIGHT_GRAY;
				block[i][0].bgdColor = WHITE;
				block[i][1].bgdColor = WHITE;
				block[i][3].bgdColor = WHITE;
				block[i][2].bgdColor = WHITE;
			}
			block[9][3].txtColor = WHITE;
			for (int i = 0; i < 3; i++) {
				block[2 + i][5].bgdColor = BLACK;
				block[10 + i][5].bgdColor = BLACK;
			}
			for (int i = 0; i < 3; i++) {
				block[1 + i][2].txtColor = DARK_BLUE;
				block[1 + i][2].bgdColor = BLUE;
				block[5 + i][2].txtColor = DARK_BLUE;
				block[5 + i][2].bgdColor = BLUE;
				block[12 + i][2].txtColor = DARK_BLUE;
				block[12 + i][2].bgdColor = BLUE;
			}
			block[10][2].txtColor = DARK_BLUE;
			block[10][3].txtColor = DARK_BLUE;
		}
	else {
		if (isHead) {
			for (int i = 3; i < 16; i++) {
				block[i][4].txtColor = DARK_GRAY;
				block[i][4].bgdColor = LIGHT_GRAY;
				block[i][5].txtColor = DARK_GRAY;
			}
			for (int i = 0; i < 3; i++) {
				block[5 + i][5].txtColor = BLACK;
				block[12 + i][5].txtColor = BLACK;
			}
			for (int i = 7; i < 16; i++) {
				block[i][0].bgdColor = WHITE;
				block[i][1].bgdColor = WHITE;
			}
			block[1][3].bgdColor = WHITE;
			block[2][3].bgdColor = WHITE;
			block[14][2].bgdColor = WHITE;
			block[15][2].bgdColor = WHITE;
			block[14][3].bgdColor = WHITE;
			block[15][3].bgdColor = WHITE;
			block[11][2].txtColor = DARK_BLUE;
			block[11][2].bgdColor = LIGHT_GRAY;
			block[11][3].txtColor = DARK_BLUE;
			block[12][2].txtColor = WHITE;
			block[12][2].bgdColor = LIGHT_GRAY;
			block[12][3].txtColor = WHITE;
			block[8][2].txtColor = DARK_BLUE;
			block[9][2].txtColor = DARK_BLUE;
			block[8][2].bgdColor = BLUE;
			block[9][2].bgdColor = BLUE;
			block[7][2].txtColor = BLUE;
			block[6][2].txtColor = BLUE;
			block[6][2].bgdColor = LIGHT_GRAY;
			block[5][2].txtColor = DARK_BLUE;
			block[5][2].bgdColor = LIGHT_GRAY;
			block[4][2].txtColor = DARK_BLUE;
			block[4][2].bgdColor = BLUE;
			for (int i = 1; i < 4; i++) {
				block[i][2].txtColor = BLUE;
				block[i][1].txtColor = BLUE;
			}
			for (int i = 3; i < 7; i++) {
				block[i][0].txtColor = BLUE;
				block[i][1].txtColor = BLUE;
				block[i][1].bgdColor = BLUE;
			}
			block[6][0].bgdColor = LIGHT_GRAY;
			block[6][1].txtColor = DARK_BLUE;
			block[4][0].bgdColor = LIGHT_GREEN;
			block[5][0].bgdColor = LIGHT_GREEN;
			block[1][1].bgdColor = DARK_GREEN;
			block[3][0].txtColor = -1;

		}
		else {
			for (int i = 0; i < 16; i++) {
				block[i][5].txtColor = LIGHT_GREEN;
				block[i][5].bgdColor = DARK_GRAY;
				block[i][4].txtColor = DARK_GRAY;
				block[i][4].bgdColor = LIGHT_GRAY;
				block[i][1].bgdColor = WHITE;
				block[i][0].bgdColor = WHITE;
				block[i][3].bgdColor = WHITE;
				block[i][2].bgdColor = WHITE;
			}
			block[6][3].txtColor = WHITE;
			for (int i = 0; i < 3; i++) {
				block[3 + i][5].bgdColor = BLACK;
				block[11 + i][5].bgdColor = BLACK;
			}
			for (int i = 0; i < 3; i++) {
				block[1 + i][2].txtColor = DARK_BLUE;
				block[1 + i][2].bgdColor = BLUE;
				block[8 + i][2].txtColor = DARK_BLUE;
				block[8 + i][2].bgdColor = BLUE;
				block[12 + i][2].txtColor = DARK_BLUE;
				block[12 + i][2].bgdColor = BLUE;
			}
			block[5][2].txtColor = DARK_BLUE;
			block[5][3].txtColor = DARK_BLUE;
		}
	}
}

