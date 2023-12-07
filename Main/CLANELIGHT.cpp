#include "CLANELIGHT.h"
CLANELIGHT::CLANELIGHT(int x, int y) {
	this->x = x; this->y = y;

	this->block = new PIXEL * [BLOCK_WIDTH * this->numberOfWidth];
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		this->block[i] = new PIXEL[BLOCK_HEIGHT * this->numberOfHeight];

	//set buffers
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
			this->block[i][j] = { FRAME[j][i], WHITE, LIGHT_GRAY };

	//set colors
	for (int i = 0; i < 16; i++)
		this->block[i][0].bgdColor = DARK_GREEN;
	for (int i = 0; i < 8; i++)
		if (i % 4 != 3) this->block[i][3].txtColor = BRIGHT_YELLOW;
	block[12][3].txtColor = BLACK;
	block[14][3].txtColor = BLACK;
	block[13][3].txtColor = BLACK;
	block[13][3].bgdColor = DARK_GREEN;
	block[13][2].txtColor = BLACK;
	block[13][2].bgdColor = RED;
	block[12][2].txtColor = BLACK;
	block[14][2].txtColor = BLACK;
	block[13][4].txtColor = BLACK;
	block[13][5].txtColor = BLACK;
	block[12][4].txtColor = BLACK;
	block[14][4].txtColor = BLACK;
}
CLANELIGHT::~CLANELIGHT() {
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		delete[] this->block[i];
	delete[] this->block;
}
void CLANELIGHT::DrawBlock(CGRAPHIC& layer) {
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
			layer.screen[this->x + i][this->y + j] = block[i][j];
}
