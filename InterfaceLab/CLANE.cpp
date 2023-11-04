#include "CLANE.h"
CLANE::CLANE(int x, int y) {
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
	for (int i = 0; i < 16; i++)
		if (i % 4 != 3) this->block[i][3].txtColor = BRIGHT_YELLOW;
}
CLANE::~CLANE() {
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		delete[] this->block[i];
	delete[] this->block;
}
void CLANE::DrawBlock(CGRAPHIC& layer) {
	for (int k = 0; k < BOARD_WIDTH; k++)
		for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
			for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
				layer.screen[this->x + k * BLOCK_WIDTH * this->numberOfWidth + i][this->y + j] = block[i][j];
}
