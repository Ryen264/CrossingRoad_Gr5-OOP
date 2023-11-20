#pragma once
#include "CGRAPHIC.h"
const int BOARD_WIDTH = 13;
const int BOARD_HEIGHT = 8;

class COBJECT {
protected:
	int x, y, numberOfBlock = 1, numberOfHeight = 1, numberOfWidth = 1;
	PIXEL** block;
	int ID;
public:
	~COBJECT();
	void setPos(int x, int y);
	int getID() const;
	void DrawBlock(CGRAPHIC& layer);
};
//Object IDs
const int CAR_ID = 30001;
const int TRUCK_ID = 30002;
const int DINOSAUR_ID = 30003;
