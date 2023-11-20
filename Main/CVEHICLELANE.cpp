#include "CVEHICLELANE.h"
CVEHICLELANE::CVEHICLELANE(int x, int y, int delayTime) {
    for (int i = 0; i < BOARD_WIDTH; i++)
        this->lane.push_front(NULL);
    this->isMoveRight = rand() % 2;
    this->delayTime = delayTime;

    this->x = x; this->y = y;

    this->block = new PIXEL * [BLOCK_WIDTH * this->numberOfWidth];
    for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
        this->block[i] = new PIXEL[BLOCK_HEIGHT * this->numberOfHeight];

    //set buffers
    for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
        for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
            this->block[i][j] = { FRAME[j][i], WHITE, LIGHT_GRAY };

    //set colors
    for (int i = 0; i < 16; i++)
        this->block[i][0].bgdColor = LIGHT_GREEN;
    for (int i = 0; i < 16; i++)
        if (i % 4 != 3) this->block[i][3].txtColor = BRIGHT_YELLOW;
    for (int i = 0; i < 16; i++) {
        this->block[i][5].bgdColor = WHITE;
        this->block[i][5].txtColor = LIGHT_GRAY;
    }
}

void CVEHICLELANE::Move() {
    //Setup speed
    if (timeCount < delayTime) {
        timeCount++;
        return;
    }
    timeCount = 0;
    //Random push a car
    if (this->isMoveRight) {
        COBJECT* back = lane.back();
        if (back != NULL)
            delete back;
        this->lane.pop_back();
        if (rand() % 10 == 0) {
            if (rand() % 2 == 0)
                this->lane.push_front(new CCAR(0, this->y, true));
            else
                this->lane.push_front(new CTRUCK(0, this->y, true));
        }
        else
            this->lane.push_front(NULL);
    }
    else {
        COBJECT* front = lane.front();
        if (front != NULL)
            delete front;
        this->lane.pop_front();
        if (rand() % 10 == 1) {
            if (rand() % 2 == 0)
                this->lane.push_back(new CCAR(0, this->y, false));
            else
                this->lane.push_back(new CTRUCK(0, this->y, false));
        }
        else
            this->lane.push_back(NULL);
    }
}
void CVEHICLELANE::pushObj(int x, int ID) {
    switch (ID) {
    case CAR_ID: {
        (isMoveRight) ? lane.push_front(new CCAR(x, this->y, true)) : lane.push_back(new CCAR(x, this->y, false));
        break;
    }
    case TRUCK_ID: {
        (isMoveRight) ? lane.push_front(new CTRUCK(x, this->y, true)) : lane.push_back(new CTRUCK(x, this->y, false));
        break;
    }
    default: {
        lane.push_front(NULL);
    }
    }
}

void CVEHICLELANE::setStop(bool isStop) {
    this->isStop = isStop;
}
void CVEHICLELANE::setIsMoveRight(bool isMoveRight) {
    this->isMoveRight = isMoveRight;
}

bool CVEHICLELANE::getIsMoveRight() {
    return this->isMoveRight;
}
int CVEHICLELANE::getDelayTime() {
    return this->delayTime;
}
int CVEHICLELANE::getTimeCount() {
    return this->timeCount;
}
bool CVEHICLELANE::getIsStop() {
    return this->isStop;
}
