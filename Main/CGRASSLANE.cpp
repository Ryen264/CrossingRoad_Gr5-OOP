#include "CGRASSLANE.h"
CGRASSLANE::CGRASSLANE(int x, int y) {
    for (int i = 0; i < BOARD_WIDTH; i++)
        this->lane.push_front(NULL);

    this->x = x; this->y = y;

    this->block = new PIXEL * [BLOCK_WIDTH * this->numberOfWidth];
    for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
        this->block[i] = new PIXEL[BLOCK_HEIGHT * this->numberOfHeight];

    //set buffers
    for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
        for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
            this->block[i][j] = { FRAME[j][i], DARK_GREEN, LIGHT_GREEN };

    //set colors

}
