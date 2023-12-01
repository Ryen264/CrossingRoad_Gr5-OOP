#pragma once
#include "CGRAPHIC.h"
#include "COBJECT.h"
#include"CPLAYER.h"
#include <deque>
using namespace std;
class CLANE {
protected:
	deque<COBJECT*> lane;
	bool isMoveRight = true; //chiều di chuyển
	int timeCount = 0;
	bool isStop = false;
	int delayTime;

	int x, y, ID;
	PIXEL** block = NULL;
public:
	CLANE(int x = 0, int y = 0);
	virtual ~CLANE();
	virtual void injuredPlayer(CPLAYER& player);
	virtual void changeDirection();
    virtual bool checkPos(int pos);
	virtual void Move();
	virtual bool isMove() const;
	virtual void push_frontObject(int ID);
	void pop_backObject();


	int PosID(int pos) const;
	virtual bool getIsMoveRight();
	virtual int getTimeCount();
	virtual int getDelayTime();
	int getID() const;
	COBJECT* getPos(int i) const;

	virtual void setIsMoveRight(bool);
	virtual void setTimeCount(int);
	virtual void setDelayTime(int);
	void setPos(int i, COBJECT* val);
	virtual void setyBoard(int yBoard);
	void updatePosObj();


	virtual void DrawLane(CGRAPHIC& layer);
	virtual void DrawObjects(CGRAPHIC& layer);
};
//Lanes IDs
const int VEHICLELANE_ID = 20001;
const int GRASSLANE_ID = 20002;
const int GRASSLANE_FULL_ID = 21002;
const int GRASSLANE_SURROUND_ID = 22002;
const int GRASSLANE_AROUND_ID = 23002;
const int RIVERLANE_ID = 20003;
const int TRAINLANE_ID = 20004;
const int FINISHLANE_ID = 20005;

vector<int> operator-(const vector<int> first, const vector<int> second);