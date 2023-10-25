#pragma once
#include "CGRAPHIC.h"
#include "COBJECT.h"
#include <deque>
using namespace std;
class CLANE {
protected:
	deque<COBJECT*> lane;
	bool isMoveRight; //chiều di chuyển
public:
	int x, y, numberOfBlock;
	PIXEL block[BLOCKLENGTH][BLOCKHEIGHT];
	PIXEL* blocks[BLOCKLENGTH][BLOCKHEIGHT];
	void changeDirection();
	bool checkPos(int pos);
	virtual void Move();
	void DrawBlock(CGRAPHIC& layer);
};
