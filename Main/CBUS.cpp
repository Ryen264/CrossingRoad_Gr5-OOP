#include "CBUS.h"
CBUS::CBUS(int x, int y, bool isRight, bool isHead) {
	this->x = x; this->y = y; this->isRight = isRight; this->isHead = isHead;	
	vector<wstring> frame{};
	if (isRight)
		if (isHead) frame = FRAME_HEAD_RIGHT;
		else frame = FRAME_TAIL_RIGHT;
	else
		if (isHead) frame = FRAME_HEAD_LEFT;
		else frame = FRAME_TAIL_LEFT;

	this->block = new PIXEL * [BLOCK_WIDTH * this->numberOfWidth];
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		this->block[i] = new PIXEL[BLOCK_HEIGHT * this->numberOfHeight];

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH * 2; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
			if (frame[j][i] != L' ')
				this->block[i][j] = { frame[j][i], DARK_RED, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };

	//set colors
	if (isRight)
		if (isHead) {
			for (int i = 0; i < 7; i++)
			{
				block[i][1].txtColor = RED;
			}
			block[7][1].txtColor = WHITE;
			block[7][1].bgdColor = -1;
			block[8][1].txtColor = DARK_RED;
			block[8][1].bgdColor = -1;
			block[9][1].txtColor = BRIGHT_YELLOW;
			block[9][1].bgdColor = -1;
			for (int i = 0; i < 7; i++)
			{
				block[i][2].txtColor = DARK_RED;
				block[i][2].bgdColor = RED;
			}
			block[7][2].txtColor = WHITE;
			block[8][2].txtColor = RED;
			block[9][2].txtColor = RED;

			block[0][3].txtColor = DARK_RED;
			block[0][3].txtColor = WHITE;
			block[1][3].txtColor = DARK_RED;
			block[2][3].txtColor = WHITE;
			block[3][3].txtColor = DARK_RED;
			for (int i = 4; i < 7; i++)
			{
				block[i][3].txtColor = DARK_RED;
				block[i][3].bgdColor = WHITE;
			}
			block[7][3].txtColor = DARK_RED;
			block[8][3].txtColor = DARK_RED;
			block[8][3].bgdColor = RED;
			block[9][3].txtColor = BRIGHT_YELLOW;
			block[9][3].bgdColor = RED;
			for (int i = 0; i < 4; i++) {
				block[i][4].txtColor = DARK_RED;
				block[i][4].bgdColor = -1;
			}
			for (int i = 4; i < 7; i++) {
				block[i][4].txtColor = BLACK;
				block[i][4].bgdColor = DARK_RED;
			}
			for (int i = 7; i < 10; i++) {
				block[i][4].txtColor = DARK_RED;
				block[i][4].bgdColor = -1;
			}
		}
		else {
			block[6][1].txtColor = DARK_RED;
			for(int i=7;i<16;i++)
			{
				block[i][1].txtColor = RED;
				
			}
			block[0][2].txtColor = DARK_RED;
			for (int i = 7; i < 16; i++)
			{
				block[i][2].txtColor = DARK_RED;
				block[i][2].bgdColor = RED;
			}
			block[0][3].txtColor = DARK_RED;

			block[1][3].txtColor = DARK_RED;
			block[1][3].bgdColor = WHITE;

			block[2][3].txtColor = DARK_RED;

			block[3][3].txtColor = DARK_RED;
			block[3][3].bgdColor = WHITE;
			block[4][3].txtColor = DARK_RED;
			block[4][3].bgdColor = WHITE;
			block[5][3].txtColor = DARK_RED;
			block[5][3].bgdColor = WHITE;

			block[6][3].txtColor = DARK_RED;

			block[7][3].txtColor = DARK_RED;
			block[7][3].bgdColor = WHITE;
			block[8][3].txtColor = DARK_RED;
			block[8][3].bgdColor = WHITE;

			block[9][3].txtColor = DARK_RED;
			block[10][3].txtColor = DARK_RED;

			block[11][3].txtColor = DARK_RED;
			block[11][3].bgdColor = WHITE;
		}
	else
		if (isHead) {

		}
		else {

		}
}