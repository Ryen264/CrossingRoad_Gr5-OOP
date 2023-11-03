#pragma once
#include "CGRAPHIC.h"
class COBJECT {
public:
	int x, y, numberOfBlock, numberOfHeight, numberOfWidth;
	PIXEL block[BLOCK_WIDTH][BLOCK_HEIGHT];
	PIXEL* blocks[BLOCK_WIDTH][BLOCK_HEIGHT];
	void DrawBlock(CGRAPHIC& layer);
};
