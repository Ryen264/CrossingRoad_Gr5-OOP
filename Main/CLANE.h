#pragma once
#include "CGRAPHIC.h"
#include "COBJECT.h"
#include"CPLAYER.h"
#include <deque>
using namespace std;
class CLANE {
protected:
	deque<COBJECT*> lane;
	bool isMoveRight; //chiều di chuyển
	int timeCount = 0;
	bool isStop = false;
	int delayTime;

	int x, y, ID;
	PIXEL** block = NULL;
public:
	~CLANE();
	virtual void injuredPlayer(CPLAYER& player);
	virtual void changeDirection();
	virtual bool checkPos(int pos);
	virtual void Move();
	virtual bool isMove() const;
	virtual void pushDeque(int ID);


	int PosID(int pos) const;
	virtual bool getIsMoveRight();
	virtual int getTimeCount();
	virtual int getDelayTime();
	int getID() const;

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
const int RIVERLANE_ID = 20003;
const int TRAINLANE_ID = 20004;

vector<int> operator-(const vector<int> first, const vector<int> second);