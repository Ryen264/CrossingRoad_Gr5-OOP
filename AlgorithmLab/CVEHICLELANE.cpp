#include "CVEHICLELANE.h"
CVEHICLELANE::CVEHICLELANE(int x, int y) {
    for (int i = 0; i < BOARD_WIDTH; i++)
        this->lane.push_front(NULL);
    this->isMoveRight = rand() % 2;
}
CVEHICLELANE::~CVEHICLELANE() {
    while (!this->lane.empty()) {
        COBJECT* cur = this->lane.back();
        if (cur != NULL)
            delete cur;
        this->lane.pop_back();
    }
}
void CVEHICLELANE::Move() {
    //Random push a car
    if (this->isMoveRight) {
        COBJECT* back = lane.back();
        if (back != NULL)
            delete back;
        this->lane.pop_back();
        if (rand() % 10 == 0)
            this->lane.push_front(new CCAR);
        else
            this->lane.push_front(NULL);
    }
    else {
        COBJECT* front = lane.front();
        if (front != NULL)
            delete front;
        this->lane.pop_front();
        if (rand() % 10 == 0)
            this->lane.push_back(new CCAR);
        else
            this->lane.push_back(NULL);
    }
}
