#include "CVEHICLELANE.h"
CVEHICLELANE::CVEHICLELANE(int x, int y, int delayTime) {
    for (int i = 0; i < BOARD_WIDTH; i++)
        this->lane.push_front(NULL);
    this->isMoveRight = rand() % 2;
    this->delayTime = delayTime;
    //this->lightPos = 6;
    this->lightPos = -1;

    if (lightPos >= BOARD_WIDTH) lightPos = -1;

    this->x = x * BLOCK_WIDTH; this->y = y * BLOCK_HEIGHT + START_BOARD_HEIGHT; this->ID = VEHICLELANE_ID;

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
}

void CVEHICLELANE::pushDeque(int redPoint ) {
    
    //push normally
    if (redPoint < 0) {
        if (condition == 0)
        {
            int objCase = random(OBJECT_ID_LIST);
            if (this->isMoveRight) {
                COBJECT* back = lane.back();
                if (back != NULL) delete back;
                this->lane.pop_back();

                switch (objCase) {
                case CAR_ID: {
                    lane.push_front(new CCAR(0, this->y, true));
                    condition = 0;
                    break;
                }
                case TRUCK_ID: {
                    lane.push_front(new CTRUCK(0, this->y, true));
                    condition = 0;
                    break;
                }
                case BUS_HEAD_ID: {
                    lane.push_front(new CBUS(0, this->y, true, true));
                    condition = BUS_TAIL_ID;
                    break;
                }
                default:
                    lane.push_front(NULL);
                    condition = 0;
                }
            }
            else {
                COBJECT* front = lane.front();
                if (front != NULL) delete front;
                this->lane.pop_front();

                switch (objCase) {
                case CAR_ID: {
                    lane.push_back(new CCAR(0, this->y, false));
                    condition = 0;
                    break;
                }
                case TRUCK_ID: {
                    lane.push_back(new CTRUCK(0, this->y, false));
                    condition = 0;
                    break;
                }
                case BUS_HEAD_ID: {
                    lane.push_back(new CBUS(0, this->y, false, true));
                    condition = BUS_TAIL_ID;
                    break;
                }
                default:
                    lane.push_back(NULL);
                    condition = 0;
                }
            }
        }
        else {
            switch (condition) {
            case BUS_TAIL_ID: {
                if (this->isMoveRight) {
                    COBJECT* back = lane.back();
                    if (back != NULL) delete back;
                    this->lane.pop_back();

                    lane.push_front(new CBUS(0, this->y, true, false));
                    condition = 0;
                }
                else {
                    COBJECT* front = lane.front();
                    if (front != NULL) delete front;
                    this->lane.pop_front();

                    lane.push_back(new CBUS(0, this->y, false, false));
                    condition = 0;
                }
                break;
            }

            default:
                lane.push_front(NULL);
                condition = 0;
            }
        }
        return;
    }
    int size = (int)lane.size();
    //push after
    if (redPoint < size - 2) {
        if (isMoveRight) {
            COBJECT* back = lane.back();
            if (back != NULL) delete back;
            this->lane.pop_back();
        }
        else {
            COBJECT* back = lane.front();
            if (back != NULL) delete back;
            this->lane.pop_front();
        }
        if (lane[redPoint]->getID() == BUS_HEAD_ID) {
            if (isMoveRight) lane.insert(lane.begin() + redPoint - 1, NULL);
            else lane.insert(lane.begin() + redPoint + 1, NULL);
        } else
            lane.insert(lane.begin() + redPoint, NULL);
    }
    //push front
    if (isMoveRight) {
        int id = redPoint - 1;
        for (; id >= 0 && lane[id] != NULL; id--);
        if (id >= 0) {
            COBJECT* back = lane[id];
            if (back != NULL) delete back;
            lane.erase(lane.begin() + id);

            if (condition == 0) {
                int objCase = random(OBJECT_ID_LIST);
                switch (objCase) {
                case CAR_ID: {
                    lane.push_front(new CCAR(0, this->y, true));
                    condition = 0;
                    break;
                }
                case TRUCK_ID: {
                    lane.push_front(new CTRUCK(0, this->y, true));
                    condition = 0;
                    break;
                }
                case BUS_HEAD_ID: {
                    lane.push_front(new CBUS(0, this->y, true, true));
                    condition = BUS_TAIL_ID;
                    break;
                }
                default:
                    lane.push_front(NULL);
                    condition = 0;
                }
            }
            else {
                switch (condition) {
                case BUS_TAIL_ID: {
                    COBJECT* back = lane.back();
                    if (back != NULL) delete back;
                    this->lane.pop_back();

                    lane.push_front(new CBUS(0, this->y, true, false));
                    condition = 0;
                    break;
                }
                default:
                    lane.push_front(NULL);
                    condition = 0;
                }
            }
        }
    }
    else {
        int id = redPoint + 1;
        for (; id < size && lane[id] != NULL; id++);
        if (id < size) {
            COBJECT* back = lane[id];
            if (back != NULL) delete back;
            lane.erase(lane.begin() + id);

            if (condition == 0) {
                int objCase = random(OBJECT_ID_LIST);
                switch (objCase) {
                case CAR_ID: {
                    lane.push_back(new CCAR(0, this->y, false));
                    condition = 0;
                    break;
                }
                case TRUCK_ID: {
                    lane.push_back(new CTRUCK(0, this->y, false));
                    condition = 0;
                    break;
                }
                case BUS_HEAD_ID: {
                    lane.push_back(new CBUS(0, this->y, false, true));
                    condition = BUS_TAIL_ID;
                    break;
                }
                default:
                    lane.push_back(NULL);
                    condition = 0;
                }
            }
            else {
                switch (condition) {
                case BUS_TAIL_ID: {
                    COBJECT* front = lane.front();
                    if (front != NULL) delete front;
                    this->lane.pop_front();

                    lane.push_back(new CBUS(0, this->y, false, false));
                    condition = 0;
                    break;
                }
                default:
                    lane.push_front(NULL);
                    condition = 0;
                }
            }
        }
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
        case BUS_HEAD_ID: {
            (isMoveRight) ? lane.push_front(new CBUS(x, this->y, true, true)) : lane.push_back(new CBUS(x, this->y, false, true));
            break;
        }
        case BUS_TAIL_ID: {
            (isMoveRight) ? lane.push_front(new CBUS(x, this->y, true, false)) : lane.push_back(new CBUS(x, this->y, false, false));
            break;
        }
        default:
            lane.push_back(NULL);
        }
}
void CVEHICLELANE::Move() {
    lightWork();
    timeCount++;
    if (timeCount >= delayTime) {
        timeCount = 0;
        //Random push a car
        pushDeque((isStop) ? lightPos : -1);
    }
}

void CVEHICLELANE::lightWork()
{
    if (timeLight < TRAFFICLIGHT_DELAY) {
        timeLight++;
        //change to yellow
        return;
    }
    if (timeLight == TRAFFICLIGHT_DELAY) {
        isStop = true;
        //change to red
    }
    if (timeLight < TRAFFICLIGHT_DELAY + TRAFFICLIGHT_WAIT) {
        timeLight++;
        return;
    }
    isStop = false;
    //change to green
    timeLight = 0;
}


void CVEHICLELANE::setStop(bool isStop)
{
    this->isStop = isStop;
}
bool CVEHICLELANE::getStop() const
{
    return this->isStop;
}
