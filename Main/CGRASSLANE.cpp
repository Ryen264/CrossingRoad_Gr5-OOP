#include "CGRASSLANE.h"
CGRASSLANE::CGRASSLANE(int width, int x, int y) {
    for (int i = 0; i < width; i++)
        this->lane.push_front(NULL);

    this->numberOfBlock = 1;
    this->x = x; this->y = y;

    //set buffers
    for (int i = 0; i < BLOCK_WIDTH; i++)
        for (int j = 0; j < BLOCK_HEIGHT; j++)
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
}
