#include "CVEHICLELANE.h"
CVEHICLELANE::CVEHICLELANE(int x, int y, int delayTime) {
    for (int i = 0; i < BOARD_WIDTH; i++)
        this->lane.push_front(NULL);
    this->isMoveRight = rand() % 2;
    this->delayTime = delayTime;
    this->lightPos = 6;
    if (lightPos >= BOARD_WIDTH) lightPos = -1;

    this->x = x * BLOCK_WIDTH; this->y = y * BLOCK_HEIGHT + START_BOARD_HEIGHT; this->ID = VEHICLELANE_ID;

    this->block = new PIXEL * [BLOCK_WIDTH];
    for (int i = 0; i < BLOCK_WIDTH; i++)
        this->block[i] = new PIXEL[BLOCK_HEIGHT];

    //set buffer
    for (int i = 0; i < BLOCK_WIDTH; i++)
        for (int j = 0; j < BLOCK_HEIGHT; j++)
            this->block[i][j] = { FRAME[j][i], WHITE, LIGHT_GRAY };

    //set colors
    for (int i = 0; i < 16; i++)
        this->block[i][0].bgdColor = LIGHT_GREEN;
}
void CVEHICLELANE::pushDeque(int ID) {
    if (isMoveRight) {
        COBJECT* back = lane.back();
        if (back != NULL) delete back;
        this->lane.pop_back();

        switch (ID) {
        case CAR_ID: {
            lane.push_front(new CCAR(0, this->y, true));
            break;
        }
        case TRUCK_ID: {
            lane.push_front(new CTRUCK(0, this->y, true));
            break;
        }
        case BUS_HEAD_ID: {
            lane.push_front(new CBUS(0, this->y, true, true));
            break;
        }
        case BUS_TAIL_ID: {
            lane.push_front(new CBUS(0, this->y, true, false));
            break;
        }
        default:
            lane.push_front(NULL);
        }
    }
    else {
        COBJECT* front = lane.front();
        if (front != NULL) delete front;
        this->lane.pop_front();

        switch (ID) {
        case CAR_ID: {
            lane.push_back(new CCAR(0, this->y, false));
            break;
        }
        case TRUCK_ID: {
            lane.push_back(new CTRUCK(0, this->y, false));
            break;
        }
        case BUS_HEAD_ID: {
            lane.push_back(new CBUS(0, this->y, false, true));
            break;
        }
        case BUS_TAIL_ID: {
            lane.push_back(new CBUS(0, this->y, false, false));
            break;
        }
        default:
            lane.push_back(NULL);
        }
    }
}
void CVEHICLELANE::pushNormally() {
    if (condition == 0) {
        int ID = random(OBJECT_ID_LIST);
        pushDeque(ID);
        switch (ID) {
        case CAR_ID: {
            countObject = 1;
            numberOfCar = 1 + rand() % 3;
            if (numberOfCar > 1) condition = CAR_ID;
            else condition = -CAR_ID;
            break;
        }
        case TRUCK_ID: {
            countObject = 1;
            numberOfTruck = 1 + rand() % 2;
            if (numberOfTruck > 1) condition = TRUCK_ID;
            else condition = -TRUCK_ID;
            break;
        }
        case BUS_HEAD_ID: {
            condition = BUS_TAIL_ID;
            break;
        }
        default:
            condition = 0;
        }
    }
    else {
        switch (condition) {
        case CAR_ID: {
            pushDeque(CAR_ID);
            countObject++;
            if (countObject >= numberOfCar) {
                condition = -CAR_ID;
                countObject = 0;
            }
            break;
        }
        case TRUCK_ID: {
            pushDeque(TRUCK_ID);
            countObject++;
            if (countObject >= numberOfTruck) {
                condition = -TRUCK_ID;
                countObject = 0;
            }
            break;
        }
        case BUS_TAIL_ID: {
            pushDeque(BUS_TAIL_ID);
            condition = -BUS_HEAD_ID;
            break;
        }
        case -CAR_ID: {
            int ID = random(OBJECT_ID_LIST - vector<int>{CAR_ID});
            pushDeque(ID);
            condition = (ID == BUS_HEAD_ID) ? BUS_TAIL_ID : 0;
            break;
        }
        case -TRUCK_ID: {
            int ID = random(OBJECT_ID_LIST - vector<int>{TRUCK_ID});
            pushDeque(ID);
            condition = (ID == BUS_HEAD_ID) ? BUS_TAIL_ID : 0;
            break;
        }
        case -BUS_HEAD_ID: {
            pushDeque(random(OBJECT_ID_LIST - vector<int>{BUS_HEAD_ID}));
            condition = 0;
            break;
        } default:
            condition = 0;
        }
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

void CVEHICLELANE::Move() {
    lightWork();
    timeCount++;
    if (timeCount >= delayTime) {
        timeCount = 0;
        //Random push a car
        if (lightPos < 0 || !isStop) pushNormally();
        else {
            //Push with traffic light on
            //push after
            if (lightPos < BOARD_WIDTH - 2) {
                if (lane[lightPos] != NULL && lane[lightPos]->getID() == BUS_HEAD_ID) {
                    if (isMoveRight) lane.insert(lane.begin() + lightPos - 1, NULL);
                    else lane.insert(lane.begin() + lightPos + 1, NULL);
                }
                else lane.insert(lane.begin() + lightPos, NULL);

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
            }
            //push before
            if (isMoveRight) {
                int id = lightPos - 1;
                for (; id >= 0 && lane[id] != NULL; id--);
                if (id >= 0) {
                    cout << id << endl;
                    char ch{};
                    cin >> ch;
                    //lane.erase(lane.begin() + id);
                    //pushNormally();
                }
            }
            else {
                int id = lightPos + 1;
                for (; id < BOARD_WIDTH && lane[id] != NULL; id++);
                if (id < BOARD_WIDTH) {
                    cout << id << endl;
                    char ch{};
                    cin >> ch;
                    //lane.erase(lane.begin() + id);
                    //pushNormally();
                }
            }
        }   
    }
}


void CVEHICLELANE::setStop(bool isStop)
{
    this->isStop = isStop;
}
bool CVEHICLELANE::getStop() const
{
    return this->isStop;
}
