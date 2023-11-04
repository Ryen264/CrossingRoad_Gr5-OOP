#include "CGRASSLANE.h"
CGRASSLANE::CGRASSLANE(int x, int y) {
    for (int i = 0; i < BOARD_WIDTH; i++)
        this->lane.push_front(NULL);

    this->x = x; this->y = y; this->heightID = y;

    this->block = new PIXEL * [BLOCK_WIDTH * this->numberOfWidth];
    for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
        this->block[i] = new PIXEL[BLOCK_HEIGHT * this->numberOfHeight];

    //set buffers
    for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
        for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
            this->block[i][j] = { FRAME[j][i], WHITE, LIGHT_GRAY };

    //set colors
    for (int i = 0; i < 16; i++)
        this->block[i][0].bgdColor = DARK_GREEN;
    for (int i = 0; i < 16; i++)
        if (i % 4 != 3) this->block[i][3].txtColor = BRIGHT_YELLOW;
}
CGRASSLANE::~CGRASSLANE() {
    for (int i = 0; i < (int)this->lane.size(); i++) {
        COBJECT* cur = this->lane[i];
        if (cur != NULL) {
            delete cur;
            this->lane[i] = NULL;
        }
    }
    for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
        delete[] this->block[i];
    delete[] this->block;
}
