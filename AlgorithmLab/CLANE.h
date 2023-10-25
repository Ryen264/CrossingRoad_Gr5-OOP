#pragma once
#include "COBJECT.h"
#include <deque>
using namespace std;
const int BOARD_HEIGHT = 10;
const int BOARD_WIDTH = 20;
class CLANE {
protected:
	deque<COBJECT*> lane;
	bool isMoveRight; //chiều di chuyển
public:
	void changeDirection();
	bool checkPos(int pos);
	virtual void Move();
};
