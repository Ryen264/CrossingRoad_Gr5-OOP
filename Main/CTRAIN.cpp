#include "CTRAIN.h"
CTRAIN::CTRAIN(int x, int y, bool isRight, bool isHead) {
	this->x = x; this->y = y; this->isRight = isRight; this->isHead = isHead;
	vector<wstring> frame{};
	if (isRight)
		if (isHead) frame = FRAME_HEAD_RIGHT;
		else frame = FRAME_BODY_RIGHT;
	else
		if (isHead) frame = FRAME_HEAD_LEFT;
		else frame = FRAME_BODY_LEFT;

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
}
		else {
			for (int i = 0; i < 16; i++) {
				block[i][5].txtColor = LIGHT_GREEN;
				block[i][5].bgdColor = DARK_GRAY;
				block[i][4].txtColor = DARK_GRAY;
				block[i][4].bgdColor = LIGHT_GRAY;
			}
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
		//Bo sung chieu nguoc lai
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
		}
		else {
			for (int i = 0; i < 16; i++) {
				block[i][5].txtColor = LIGHT_GREEN;
				block[i][5].bgdColor = DARK_GRAY;
				block[i][4].txtColor = DARK_GRAY;
				block[i][4].bgdColor = LIGHT_GRAY;
			}
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
	}
}

