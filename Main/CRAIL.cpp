#include "CRAIL.h"

CRAIL::CRAIL(int x, int y) {
	this->numberOfBlock = 1;
	this->x = x; this->y = y;

	this->block = new PIXEL * [BLOCK_WIDTH * this->numberOfWidth];
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		this->block[i] = new PIXEL[BLOCK_HEIGHT * this->numberOfHeight];

	//set buffers
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
			this->block[i][j] = { FRAME[j][i], LIGHT_GREEN, LIGHT_BROWN };
	//set colors
	for (int i = 0; i < 16; i++) {
		block[i][1].txtColor = DARK_GREEN;
		block[i][2].txtColor = WHITE;
		block[i][3].txtColor = SADDLE_BROWN;
		block[i][4].txtColor = SADDLE_BROWN;
		block[i][5].bgdColor = WHITE;
	}
	for (int i = 1; i <= 16; i++) {
		if ((i + 3) % 4 == 0) {
			block[i][3].txtColor = LIGHT_GRAY;
			block[i][4].txtColor = LIGHT_GRAY;
		}
	}
	block[1][1].bgdColor = SADDLE_BROWN;
	block[3][2].bgdColor = SADDLE_BROWN;
	block[4][1].bgdColor = SADDLE_BROWN;
	block[5][1].bgdColor = SADDLE_BROWN;
	block[6][1].bgdColor = SADDLE_BROWN;
	block[6][2].bgdColor = SADDLE_BROWN;
	block[9][2].bgdColor = SADDLE_BROWN;
	block[11][1].bgdColor = SADDLE_BROWN;
	block[12][2].bgdColor = SADDLE_BROWN;
	block[13][2].bgdColor = SADDLE_BROWN;
	block[15][1].bgdColor = SADDLE_BROWN;
	block[15][1].bgdColor = SADDLE_BROWN;
}
CRAIL::~CRAIL() {
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		delete[] this->block[i];
	delete[] this->block;
}