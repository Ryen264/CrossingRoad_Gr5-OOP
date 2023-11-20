#include "COBJECT.h"

COBJECT::~COBJECT() {
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		delete[] this->block[i];
	delete[] this->block;
}

void COBJECT::setPos(int x, int y)
{
	this->x = x; this->y = y;
}
int COBJECT::getID() const {
	return this->ID;
}

void COBJECT::DrawBlock(CGRAPHIC& layer) {
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
			layer.screen[this->x + i][this->y + j] = block[i][j];
}
