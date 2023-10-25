#pragma once
#include "CGRAPHIC.h"
class COBJECT {
public:
	int x, y, numberOfBlock, numberOfHeight, numberOfLength;
	PIXEL block[BLOCKLENGTH][BLOCKHEIGHT];
	PIXEL* blocks[BLOCKLENGTH][BLOCKHEIGHT];
	void DrawBlock(CGRAPHIC& layer);
};
