#pragma once
#include "CGRAPHIC.h"
#include "COBJECT.h"
#include <deque>
using namespace std;
class CLANE {
protected:
	deque<COBJECT*> lane;
	bool isMoveRight; //chiều di chuyển
	bool isStop = false;
	int timeCount = 0;

	int x, y, numberOfBlock = 1, numberOfHeight = 1, numberOfWidth = 1;
	PIXEL** block = NULL;
public:
	virtual void changeDirection();
	bool checkPos(int pos);
	virtual void Move();
	virtual bool isMove() const;
	void DrawLane(CGRAPHIC& layer);
	void DrawObjects(CGRAPHIC& layer);
};
