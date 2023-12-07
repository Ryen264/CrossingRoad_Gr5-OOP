#include "CFLOPPYDISC.h"
CFLOPPYDISC::CFLOPPYDISC(int x, int y, bool isRight) {
	this->numberOfBlock = 1;
	this->x = x; this->y = y; this->isRight = isRight;
	vector<wstring> frame = FLOPPY_DISC;

	//set buffer
	for (int i = 0; i < 22; i++)
		for (int j = 0; j < 11; j++)
			this->block[i][j] = { frame[j][i], BLACK, DARK_BLUE };

	//set colors
	for (int i = 0; i < 22; i++)
		block[i][0].bgdColor = -1;
	block[21][1].bgdColor = -1;
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 3; j++)
			block[5 + i][1 + j].bgdColor = LIGHT_GRAY;
	for (int i = 3; i < 18; i++)
		block[i][4].txtColor = WHITE;
	for (int i = 3; i < 19; i++)
		for (int j = 5; j < 11; j++)
			block[i][j].bgdColor = WHITE;
	block[11][8].bgdColor = LIGHT_GRAY;
	block[12][8].bgdColor = LIGHT_GRAY;
	block[16][8].bgdColor = LIGHT_GRAY;
	block[17][8].bgdColor = LIGHT_GRAY;
	block[11][9].bgdColor = LIGHT_GRAY;
	block[12][9].bgdColor = LIGHT_GRAY;
	block[16][9].bgdColor = LIGHT_GRAY;
	block[17][9].bgdColor = LIGHT_GRAY;
	if (isRight) {
		block[11][9].bgdColor = LIGHT_GREEN;
		block[12][9].bgdColor = LIGHT_GREEN;
		block[16][9].bgdColor = LIGHT_GREEN;
		block[17][9].bgdColor = LIGHT_GREEN; 
	}
	else {
		block[11][8].bgdColor = RED;
		block[12][8].bgdColor = RED;
		block[16][8].bgdColor = RED;
		block[17][8].bgdColor = RED;
	}
}