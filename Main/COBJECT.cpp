#include "COBJECT.h"
COBJECT::COBJECT(int x, int y) {
	if (x < 0) x = 0;
	this->x = x;
	if (y < 0) y = 0;
	this->y = y;

	this->block = new PIXEL * [BLOCK_WIDTH];
	for (int i = 0; i < BLOCK_WIDTH; i++)
		this->block[i] = new PIXEL[BLOCK_HEIGHT];
}
COBJECT::~COBJECT() {
	for (int i = 0; i < BLOCK_WIDTH; i++)
		delete[] this->block[i];
	delete[] this->block;
}
int COBJECT::getID() const {
	if (this == NULL) return 0;
	return this->ID;
}
int COBJECT::getX() const {
	return this->x;
}
int COBJECT::getY() const {
	return this->y;
}
void COBJECT::setPos(int x, int y)
{
	this->x = x; this->y = y;
}
void COBJECT::setX(int x) {
	this->x = x;
}
void COBJECT::setY(int y) {
	this->y = y;
}

void COBJECT::DrawBlock(CGRAPHIC& layer) {
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
			layer.screen[i + x][j + y] = block[i][j];
}
void COBJECT::setColor(vector<int> color) {}

int random(vector<int> arr) {
	int size = (int)arr.size();
	return arr[rand() % size];
}
