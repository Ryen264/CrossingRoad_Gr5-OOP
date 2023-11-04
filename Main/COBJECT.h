#pragma once
#include "CGRAPHIC.h"
const int BOARD_HEIGHT = 5;
const int BOARD_WIDTH = 5;
class COBJECT {
protected:
	int x, y, numberOfBlock = 1, numberOfHeight = 1, numberOfWidth = 1;
	PIXEL** block;
public:
	void DrawBlock(CGRAPHIC& layer);
};
