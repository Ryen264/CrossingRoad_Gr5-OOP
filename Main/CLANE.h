#pragma once
#include "CGRAPHIC.h"
#include"CGRAPHIC.h"
#include "COBJECT.h"
#include <deque>
using namespace std;
class CLANE {
protected:
	deque<COBJECT*> lane;
	bool isMoveRight; //chiều di chuyển
	int timeCount = 0;
	bool isStop = false;
	int delayTime;

	int x, y, numberOfBlock = 1, numberOfHeight = 1, numberOfWidth = 1, ID;
	PIXEL** block = NULL;
public:
	~CLANE();
	int getID() const;
	virtual void changeDirection();
	virtual bool checkPos(int pos);
	virtual void Move();
	virtual bool isMove() const;
	virtual void pushObj(int x, int ID);

	int PosID(int pos) const;
	virtual bool getIsMoveRight();
	virtual int getTimeCount();
	virtual int getDelayTime();

	virtual void setIsMoveRight(bool);
	virtual void setTimeCount(int);
	virtual void setDelayTime(int);
	void setYHeight(int y);
	void updateYObj();

	void DrawLane(CGRAPHIC& layer);
	void DrawObjects(CGRAPHIC& layer);
};
//Lanes IDs
const int VEHICLELANE_ID = 20001;
const int GRASSLANE_ID = 20002;
const int RIVERLANE_LAND_ID = 20003;
const int RIVERLANE_NOLAND_ID = 21003;
const int TRAINLANE_ID = 20004;
