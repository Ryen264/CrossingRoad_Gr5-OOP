#include "COBJECT.h"
COBJECT::~COBJECT() {
	for (int i = 0; i < BLOCK_WIDTH; i++)
		delete[] this->block[i];
	delete[] this->block;
}
void COBJECT::setY(int y) {
	this->y = y;
}
int COBJECT::getID() const {
	return this->ID;
}
void COBJECT::setPos(int x, int y)
{
	this->x = x; this->y = y;
}
void COBJECT::setY(int y) {
	this->y = y;
}
void COBJECT::DrawBlock(CGRAPHIC& layer) {
	int startX = this->x;
	int startY = this->y;
	int endX = startX + BLOCK_WIDTH * this->numberOfWidth;
	int endY = startY + BLOCK_HEIGHT * this->numberOfHeight;
	for (int i = startX; i < endX; i++)
		for (int j = startY; j < endY; j++)
			layer.screen[i][j] = block[i - startX][j - startY];
}
int random(vector<int> arr) {
	int size = (int)arr.size();
	return arr[rand() % size];
}
