#pragma once
#include "CGRAPHIC.h"
#include "COBJECT.h"
#include <deque>
using namespace std;
const int BOARD_HEIGHT = 10;
const int BOARD_WIDTH = 20;
class CLANE {
protected:
	deque<COBJECT*> lane;
	bool isMoveRight; //chiều di chuyển
	int x, y, numberOfBlock;
	PIXEL block[BLOCK_WIDTH][BLOCK_HEIGHT];
	PIXEL* blocks[BLOCK_WIDTH][BLOCK_HEIGHT];
public:
	void changeDirection();
	bool checkPos(int pos);
	virtual void Move();
	void DrawBlock(CGRAPHIC& layer);
};
