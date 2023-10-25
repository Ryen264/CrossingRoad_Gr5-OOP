#include "COBJECT.h"
void COBJECT::DrawBlock(CGRAPHIC& layer) {
	if (this->numberOfBlock == 1) {
		for (int i = 0; i < BLOCK_WIDTH; i++)
			for (int j = 0; j < BLOCK_HEIGHT; j++)
				layer.screen[this->x + i][this->y + j] = block[i][j];
	}
}
