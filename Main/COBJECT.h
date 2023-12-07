#pragma once
#include "CGRAPHIC.h"
const int BOARD_WIDTH = 13;
const int BOARD_HEIGHT = 8;

class COBJECT {
protected:
	int ID;

	int x, y;
	PIXEL** block;
public:
	COBJECT(int x = 0, int y = 0);
	virtual ~COBJECT();
	int getX() const;
	int getY() const;

	void setPos(int x, int y);
	void setX(int x);
	void setY(int y);

	int getID() const;
	virtual bool getIsRight() const;
	virtual bool getIsHead() const;

	virtual void setIsRight(bool isRight);
	virtual void setIsHead(bool isHead);

	virtual void setColor(int color);

	void DrawObject(CGRAPHIC& layer, int width, int height);
	void DrawBlock(CGRAPHIC& layer, bool isPass = false);

};
//Object IDs
const int CAR_ID = 30001;
const int TRUCK_ID = 30002;
const int DINOSAUR_ID = 30003;
const int PERRY_ID = 30004;
const int CAPYBARA_ID = 30005;
const int TRAIN_HEAD_ID = 30006;
const int TRAIN_BODY_ID = 31006;
const int BUS_HEAD_ID = 30007;
const int BUS_TAIL_ID = 31007;

const int TRAFFICLIGHT_ID = 40001;
const int EGG_ID = 40002;
const int TREE_DOUBLE_ID = 40003;
const int TREE_SINGLE_ID = 41003;

int random(vector<int> arr);
