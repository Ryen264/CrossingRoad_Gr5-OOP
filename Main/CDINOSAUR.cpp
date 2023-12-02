#include "CDINOSAUR.h"
CDINOSAUR::CDINOSAUR(int x, int y, bool isRight, int color) : COBJECT(x, y) {
	this->isRight = isRight; this->ID = DINOSAUR_ID;
	vector<wstring> frame = (isRight) ? FRAME_RIGHT : FRAME_LEFT;
	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
			if (frame[j][i] != ' ')
				this->block[i][j] = { frame[j][i], BLACK, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };

	
	this->color = color;
	this->setColor(color);
}

void CDINOSAUR::setColor(int color) {
	this->color = color;
	vector<int> colorArr{};
	if (color == DARK_GREEN) colorArr = { color, LIGHT_GREEN };
	else if (color == DARK_RED) colorArr = { color, RED };
	else if (color == DARK_GRAY) colorArr = { color, LIGHT_GRAY };
	else if (color == SADDLE_BROWN) colorArr = { color, LIGHT_BROWN };
	else if (color == BRIGHT_YELLOW) colorArr = { color, WHITE };
	else if (color == SAND) colorArr = { ORANGE, SAND };
	else if (color == RED) colorArr = { color, BRIGHT_YELLOW };
	else if (color == DARK_BLUE) colorArr = { color, BLUE };
	else if (color == BLUE) colorArr = { color, SKY_BLUE };
	else colorArr = { DARK_GREEN, LIGHT_GREEN };

	if (isRight) {
		block[4][0].bgdColor = -1;
		block[4][3].bgdColor = -1;
		block[14][0].bgdColor = -1;
		for (int i = 5; i <= 13; i++) {
			block[i][0].txtColor == BLACK;
			block[i][0].bgdColor = colorArr[0];

		}
		block[5][1].txtColor=block[5][1].bgdColor = colorArr[0];
		block[6][1].txtColor = BLACK;
		block[7][1].txtColor = BLACK;
		for (int i = 8; i <= 13; i++)
		{
			block[i][1].txtColor = block[i][1].bgdColor = colorArr[0];
		}
		for (int i = 5; i <= 13; i++)
		{
			block[i][2].txtColor = block[i][2].bgdColor = colorArr[0];
		}
		block[3][3].bgdColor = colorArr[0];
		block[5][3].txtColor = block[5][3].bgdColor = colorArr[0];
		block[6][3].txtColor = block[6][3].bgdColor = colorArr[0];
		for (int i = 7; i <= 9; i++)
		{
			block[i][3].txtColor =colorArr[0];
			block[i][3].bgdColor = colorArr[1];
		}
		for (int i = 10; i <= 13; i++)
		{
			block[i][3].bgdColor = colorArr[0];
		}
		block[4][4].bgdColor = colorArr[0];
		block[5][4].txtColor = block[5][4].bgdColor = colorArr[0];
		block[6][4].bgdColor = colorArr[0];
		for (int i = 7; i <= 9; i++)
		{
			block[i][4].txtColor = colorArr[0];
			block[i][4].bgdColor = colorArr[1];
		}
	}
	else {
		block[2][0].bgdColor = -1;
		block[2][3].bgdColor = -1;
		block[12][0].bgdColor = -1;
		for (int i = 3; i <= 11; i++) {
		     block[i][0].bgdColor = colorArr[0];
		}
		for (int i = 3; i <= 11; i++) {
			block[i][1].txtColor = block[i][1].bgdColor = colorArr[0];
		}
		block[9][1].txtColor = BLACK;
		block[10][1].txtColor = BLACK;
		for (int i = 3; i <= 11; i++) {
			block[i][2].bgdColor = colorArr[0];
			block[i][2].txtColor = colorArr[0];
		}
		for (int i = 3; i <= 6; i++)
		{
			block[i][3].bgdColor = colorArr[0];
		}
		for (int i = 7; i <= 9; i++) {
			block[i][3].bgdColor = colorArr[1];
			block[i][3].txtColor = colorArr[0];
		}
		for (int i = 7; i <= 9; i++) {
			block[i][4].bgdColor = colorArr[1];
			block[i][4].txtColor = BLACK;
		}
		for (int i = 10; i <= 11; i++)
		{
			block[i][3].bgdColor = colorArr[0];
			block[i][3].txtColor = colorArr[0];
		}
		block[13][3].bgdColor = colorArr[0];

		for (int i = 10; i <= 12; i++)
			block[i][4].bgdColor = colorArr[0];
		block[11][4].txtColor = colorArr[0];

		for (int i = 7; i <= 9; i++) {
			block[i][3].bgdColor = colorArr[1];
		}
	}
}
