#pragma once
#include "CGRAPHIC.h"
class COBJECT {
protected:
	int x, y, numberOfBlock, numberOfHeight, numberOfLength;
	PIXEL block[BLOCK_WIDTH][BLOCK_HEIGHT];
	PIXEL* blocks[BLOCK_WIDTH][BLOCK_HEIGHT];
public:
	void DrawBlock(CGRAPHIC& layer);
};
