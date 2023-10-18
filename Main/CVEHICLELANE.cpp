#include "CVEHICLELANE.h"
CVEHICLELANE::CVEHICLELANE(int width) {
    for (int i = 0; i < width; i++)
        this->lane.push_front(NULL);
    this->right = rand() % 2;
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
    if (this->right) {
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
bool CVEHICLELANE::checkPos(int pos) {
    return this->lane[pos] != NULL;
}
void CVEHICLELANE::draw(ostream& outDev) {
    for (int i = 0; i < (int)this->lane.size(); i++) {
        if (this->checkPos(i))
            this->lane[i]->draw(cout);
        else
            outDev << " ";
    }
}