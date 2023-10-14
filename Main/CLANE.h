#pragma once
#include "CNPC.h"
#include <deque>
#include <iostream>
using namespace std;
class CLANE {
protected:
	deque<CNPC*> lane;
	bool right; //chiều di chuyển
public:
	//CLANE(int width);
	//~CLANE();
	void changeDirection();
	virtual void Move();
	virtual bool checkPos(int pos);
	virtual void draw(ostream& outDev);
};

