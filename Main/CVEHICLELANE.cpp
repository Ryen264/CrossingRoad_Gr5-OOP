#include "CVEHICLELANE.h"
CVEHICLELANE::CVEHICLELANE(int x, int y) {
    for (int i = 0; i < BOARD_WIDTH; i++)
        this->lane.push_front(NULL);
    this->isMoveRight = rand() % 2;

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
CVEHICLELANE::~CVEHICLELANE() {
    for (int i = 0; i < (int)this->lane.size(); i++) {
        COBJECT* cur = this->lane[i];
        if (cur != NULL) {
            delete cur;
            this->lane[i] = NULL;
        }
    }
}
void CVEHICLELANE::Move() {
    //Random push a car
    if (this->isMoveRight) {
        if (rand() % 10 == 0)
            this->lane.push_front(new CCAR);
        else
            this->lane.push_front(NULL);
        COBJECT* back = lane.back();
        if (back != NULL)
            delete back;
        this->lane.pop_back();
    }
    else {
        if (rand() % 10 == 1)
            this->lane.push_back(new CCAR);
        else
            this->lane.push_back(NULL);
        COBJECT* front = lane.front();
        if (front != NULL)
            delete front;
        this->lane.pop_front();
    }
}
