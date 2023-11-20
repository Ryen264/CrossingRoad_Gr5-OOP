#include "CLANE.h"

CLANE::~CLANE() {
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

void CLANE::changeDirection() {
	this->isMoveRight = !this->isMoveRight;
}
bool CLANE::checkPos(int pos) {
    return this->lane[pos] != NULL;
}
void CLANE::Move() {}
bool CLANE::isMove() const
{
    return !this->isStop;
}
void CLANE::pushObj(int x,int ID) {}

int CLANE::PosID(int pos) const {
    if (pos < 0 || pos >= BOARD_WIDTH - 1) return 0;
    return (lane[pos] != NULL) ? lane[pos]->getID() : 0;
}
bool CLANE::getIsMoveRight() {
    return this->isMoveRight;
}
int CLANE::getTimeCount() {
    return this->timeCount;
}
int CLANE::getDelayTime() {
    return this->delayTime;
}
void CLANE::setIsMoveRight(bool right) {
    if (right == 1) {
        this->isMoveRight = true;
    }
    else {
        this->isMoveRight = false;
    }
}
void CLANE::setTimeCount(int time) {
    this->timeCount = time;
}
void CLANE::setDelayTime(int time) {
    this->delayTime = time;
}
int CLANE::getID() const {
    return this->ID;
}

void CLANE::DrawLane(CGRAPHIC& layer) {
    for (int k = 0; k < BOARD_WIDTH; k++) {
        for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
            for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
                layer.screen[this->x + k * BLOCK_WIDTH * this->numberOfWidth + i][this->y + j] = block[i][j];
    }
}

void CLANE::DrawObjects(CGRAPHIC& layer)
{
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        if (lane[i] != NULL) {
            lane[i]->setPos(this->x + i * BLOCK_WIDTH, this->y);
            lane[i]->DrawBlock(layer);
        }
        else {
            for (int k = 0; k < BLOCK_WIDTH; k++)
                for (int l = 0; l < BLOCK_HEIGHT; l++)
                    layer.screen[this-> x + i * BLOCK_WIDTH + k][this->y + l] = { L' ', -1, -1 };
        }
    }
}
