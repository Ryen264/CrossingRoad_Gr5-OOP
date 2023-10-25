#include "CLANE.h"
void CLANE::changeDirection() {
    this->isMoveRight = !this->isMoveRight;
}
bool CLANE::checkPos(int pos) {
    return this->lane[pos] != NULL;
}
void CLANE::Move() {
    //Random push a car
    if (this->isMoveRight) {
        if (rand() % 10 == 1)
            this->lane.push_front(new COBJECT);
        else
            this->lane.push_front(NULL);
        COBJECT* back = lane.back();
        if (back != NULL)
            delete back;
        this->lane.pop_back();
    }
    else {
        if (rand() % 10 == 1)
            this->lane.push_back(new COBJECT);
        else
            this->lane.push_back(NULL);
        COBJECT* front = lane.front();
        if (front != NULL)
            delete front;
        this->lane.pop_front();
    }
}