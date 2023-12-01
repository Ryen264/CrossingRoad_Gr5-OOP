#include "CBUS.h"
CBUS::CBUS(int x, int y, bool isRight, bool isHead) : COBJECT(x, y) {
	this->isRight = isRight; this->isHead = isHead;
	this->ID = (isHead) ? BUS_HEAD_ID : BUS_TAIL_ID;

	vector<wstring> frame{};
	if (isRight)
		if (isHead) frame = FRAME_HEAD_RIGHT;
		else frame = FRAME_TAIL_RIGHT;
	else
		if (isHead) frame = FRAME_HEAD_LEFT;
		else frame = FRAME_TAIL_LEFT;

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++) {
			if (frame[j][i] != L' ')
				this->block[i][j] = { frame[j][i], DARK_RED, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };
		}

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

			block[0][3].bgdColor = WHITE;
			block[0][3].txtColor = DARK_RED;
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
			for (int i = 0; i < 3; i++) {
				block[8 + i][4].txtColor = BLACK;
				block[8 + i][4].bgdColor = DARK_RED;
			}
			block[6][1].txtColor = DARK_RED;
			for(int i=7;i<16;i++)
			{
				block[i][1].txtColor = RED;
				
			}
			block[6][2].txtColor = DARK_RED;
			for (int i = 7; i < 16; i++)
			{
				block[i][2].txtColor = DARK_RED;
				block[i][2].bgdColor = RED;
			}
			block[6][3].txtColor = DARK_RED;

			block[7][3].txtColor = DARK_RED;
			block[7][3].bgdColor = WHITE;

			block[8][3].txtColor = DARK_RED;

			block[9][3].txtColor = DARK_RED;
			block[9][3].bgdColor = WHITE;
			block[10][3].txtColor = DARK_RED;
			block[10][3].bgdColor = WHITE;
	

			block[11][3].txtColor = DARK_RED;

			block[12][3].txtColor = DARK_RED;
			block[12][3].bgdColor = WHITE;
			block[13][3].txtColor = DARK_RED;
			block[13][3].bgdColor = WHITE;

			block[14][3].txtColor = DARK_RED;

			block[15][3].txtColor = DARK_RED;
			block[15][3].bgdColor = WHITE;

		}
	else
		if (isHead) {
			block[6][1].txtColor = BRIGHT_YELLOW;
			block[6][1].bgdColor = -1;
			block[7][1].txtColor = DARK_RED;
			block[7][1].bgdColor = -1;
			block[8][1].txtColor = WHITE;
			block[8][1].bgdColor = -1;
			for(int i=9;i<16;i++)
			{
				block[i][1].txtColor = RED;
			}
			block[6][2].txtColor = RED;
			block[7][2].txtColor = RED;
			block[8][2].txtColor = WHITE;
			for (int i = 9; i < 16; i++)
			{
				block[i][2].txtColor = DARK_RED;
				block[i][2].bgdColor = RED;
			}
			block[6][3].txtColor = BRIGHT_YELLOW;
			block[6][3].bgdColor = RED;
			block[7][3].txtColor = DARK_RED;
			block[7][3].bgdColor = RED;
			block[8][3].txtColor = DARK_RED;

			block[9][3].txtColor = DARK_RED;
			block[9][3].bgdColor = WHITE;
			block[10][3].txtColor = DARK_RED;
			block[10][3].bgdColor = WHITE;
			block[11][3].txtColor = DARK_RED;
			block[11][3].bgdColor = WHITE;

			block[12][3].txtColor = DARK_RED;
			block[13][3].txtColor = WHITE;
			block[14][3].txtColor = DARK_RED;

			block[15][3].txtColor = DARK_RED;
			block[15][3].bgdColor = WHITE;


			for(int i=6;i<9;i++)
			{
				block[i][4].txtColor = DARK_RED;
				block[i][4].bgdColor = -1;
			}
			for(int i=9;i<12;i++)
			{
				block[i][4].txtColor = BLACK;
				block[i][4].bgdColor = DARK_RED;
			}
			for (int i = 12; i < 16; i++)
			{
				block[i][4].txtColor = DARK_RED;
				block[i][4].bgdColor = -1;
			}
		}
		else {
			for(int i=0;i<9;i++)
			{
				block[i][1].txtColor = RED;
			}
			block[9][1].txtColor = DARK_RED;
			for (int i = 0; i < 9; i++)
			{
				block[i][2].txtColor = DARK_RED;
				block[i][2].bgdColor = RED;
			}
			block[9][2].txtColor = DARK_RED;

			block[0][3].txtColor = DARK_RED;
			block[0][3].bgdColor =WHITE ;

			block[1][3].txtColor = DARK_RED;
			
			block[2][3].txtColor = DARK_RED;
			block[2][3].bgdColor = WHITE;
			block[3][3].txtColor = DARK_RED;
			block[3][3].bgdColor = WHITE;

			block[4][3].txtColor = DARK_RED;

			block[5][3].txtColor = DARK_RED;
			block[5][3].bgdColor = WHITE;
			block[6][3].txtColor = DARK_RED;
			block[6][3].bgdColor = WHITE;

			block[7][3].txtColor = DARK_RED;

			block[8][3].txtColor = DARK_RED;
			block[8][3].bgdColor = WHITE;

			block[9][3].txtColor = DARK_RED;

			block[0][4].txtColor = DARK_RED;
			block[0][4].bgdColor = -1;
			
			for (int i = 4; i < 10; i++)
			{
				block[i][4].txtColor = DARK_RED;
				block[i][4].bgdColor = -1;
			}
			for (int i = 0; i < 3; i++)
			{
				block[5 + i][4].txtColor = BLACK;
				block[5 + i][4].bgdColor = DARK_RED;
			}
		}
		
}