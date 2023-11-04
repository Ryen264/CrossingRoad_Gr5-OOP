#pragma once
#include "CGRAPHIC.h"
#include "COBJECT.h"
#include <deque>
using namespace std;
class CLANE {
protected:
	deque<COBJECT*> lane;
	bool isMoveRight; //chiều di chuyển
	int heightID;

	int x, y, numberOfBlock = 1, numberOfHeight = 1, numberOfWidth = 1;
	PIXEL** block = NULL;
public:
	void changeDirection();
	bool checkPos(int pos);
	virtual void Move();
	void DrawLane(CGRAPHIC& layer);
	void DrawObject(CGRAPHIC& layer, int pos);
};
