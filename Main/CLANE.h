#pragma once
#include "CGRAPHIC.h"
#include "COBJECT.h"
#include"CPLAYER.h"
#include <deque>
using namespace std;
class CLANE {
protected:
	bool isMoveRight = true;
	int ID = 0;

	deque<COBJECT*> lane;
	int x, y;
	PIXEL** block = NULL;
public:
	CLANE(int x = 0, int y = 0);
	virtual ~CLANE();
	virtual void Move();
	virtual void push_frontObject(int ID);
	virtual void push_backObject(int ID);
	void pop_backObject();
	COBJECT* frontObject() const;
	COBJECT* backObject() const;
	bool emptyObject() const;
	void clearObject();

	void setPos(int i, COBJECT* val);
	virtual void setyBoard(int yBoard);
	void updatePosObj();

	virtual void injuredPlayer(CPLAYER& player);
	COBJECT* getPos(int i) const;

	int getID() const;
	bool getIsMoveRight() const;
	virtual int getCondition() const;
	virtual int getCountObject() const;
	virtual int getNumberOfConditionObj() const;
	virtual int getLightPos() const;
	virtual int getTimeLight() const;
	virtual bool getIsStop() const;
	virtual int getTimeCount() const;
	virtual int getDelayTime() const;

	void setIsMoveRight(bool isMoveRight);
	virtual void setCondition(int condition);
	virtual void setCountObject(int countObject);
	virtual void setNumberOfConditionObj(int numberOfConditionObj);
	virtual void setLightPos(int lightPos);
	virtual void setTimeLight(int timeLight);
	virtual void setIsStop(bool isStop);
	virtual void setTimeCount(int timeCount);
	virtual void setDelayTime(int delayTime);

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