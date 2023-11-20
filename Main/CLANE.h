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
	int delayTime;

	int x, y, numberOfBlock = 1, numberOfHeight = 1, numberOfWidth = 1;
	PIXEL** block = NULL;
	int ID;
public:
	~CLANE();
	virtual void changeDirection();
	virtual bool checkPos(int pos);
	virtual void Move();
	virtual bool isMove() const;
	virtual void pushObj(int x,int ID);

	int PosID(int pos) const;
	virtual bool getIsMoveRight();
	virtual int getTimeCount();
	virtual int getDelayTime();
	int getID() const;

	virtual void setIsMoveRight(bool);
	virtual void setTimeCount(int);
	virtual void setDelayTime(int);

	void DrawLane(CGRAPHIC& layer);
	void DrawObjects(CGRAPHIC& layer);
};
