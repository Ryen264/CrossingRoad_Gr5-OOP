#include "CLANE.h"
//CLANE::CLANE(int width) {
//    for (int i = 0; i < width; i++)
//        this->lane.push_front(NULL);
//	this->right = rand() % 2;
//}
//CLANE::~CLANE() {
//    for (int i = 0; i < (int)this->lane.size(); i++) {
//        CNPC* cur = this->lane[i];
//        if (cur != NULL) {
//            delete cur;
//            this->lane[i] = NULL;
//        }
//    }
//}
void CLANE::changeDirection() {
	this->right = !this->right;
}
void CLANE::Move() {
    //Random push a car
    if (this->right) {
        if (rand() % 10 == 1)
            this->lane.push_front(new CNPC);
        else
            this->lane.push_front(NULL);
        CNPC* back = lane.back();
        if (back != NULL)
            delete back;
        this->lane.pop_back();
    }
    else {
        if (rand() % 10 == 1)
            this->lane.push_back(new CNPC);
        else
            this->lane.push_back(NULL);
        CNPC* front = lane.front();
        if (front != NULL)
            delete front;
        this->lane.pop_front();
    }
}
bool CLANE::checkPos(int pos) {
    return this->lane[pos] != NULL;
}
void CLANE::draw(ostream& outDev) {
    for (int i = 0; i < (int)this->lane.size(); i++) {
        if (this->checkPos(i))
            this->lane[i]->draw(cout);
        else
            outDev << " ";
    }
    outDev << endl;
}