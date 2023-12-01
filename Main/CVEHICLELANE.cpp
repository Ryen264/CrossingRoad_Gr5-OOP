#include "CVEHICLELANE.h"
CVEHICLELANE::CVEHICLELANE(int x, int y, int delayTime) : CLANE(x, y) {
    for (int i = 0; i < BOARD_WIDTH; i++)
        this->lane.push_front(NULL);
    this->ID = VEHICLELANE_ID;
    this->isMoveRight = rand() % 2;
    this->delayTime = delayTime;

    this->lightPos = rand() % (2 * BOARD_WIDTH);
    if (lightPos >= BOARD_WIDTH) lightPos = -1;
    else ptrafficLight = new CTRAFFICLIGHT(lightPos * BLOCK_WIDTH, this->y);

    //set buffer
    for (int i = 0; i < BLOCK_WIDTH; i++)
        for (int j = 0; j < BLOCK_HEIGHT; j++)
            this->block[i][j] = { FRAME[j][i], WHITE, LIGHT_GRAY };

    //set colors
    for (int i = 0; i < 16; i++)
        this->block[i][0].bgdColor = LIGHT_GREEN;
}

CVEHICLELANE::~CVEHICLELANE() {
    if (ptrafficLight != NULL) delete ptrafficLight;
}

void CVEHICLELANE::push_frontObject(int ID) {
    if (isMoveRight) {
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
    updatePosObj();
}
void CVEHICLELANE::pushNormally() {
    if (condition == 0) {
        int ID = random(OBJECT_ID_LIST);
        push_frontObject(ID);
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
            push_frontObject(CAR_ID);
            countObject++;
            if (countObject >= numberOfCar) {
                condition = -CAR_ID;
                countObject = 0;
            }
            break;
        }
        case TRUCK_ID: {
            push_frontObject(TRUCK_ID);
            countObject++;
            if (countObject >= numberOfTruck) {
                condition = -TRUCK_ID;
                countObject = 0;
            }
            break;
        }
        case BUS_TAIL_ID: {
            push_frontObject(BUS_TAIL_ID);
            condition = -BUS_HEAD_ID;
            break;
        }
        case -CAR_ID: {
            int ID = random(OBJECT_ID_LIST - vector<int>{CAR_ID});
            push_frontObject(ID);
            condition = (ID == BUS_HEAD_ID) ? BUS_TAIL_ID : 0;
            break;
        }
        case -TRUCK_ID: {
            int ID = random(OBJECT_ID_LIST - vector<int>{TRUCK_ID});
            push_frontObject(ID);
            condition = (ID == BUS_HEAD_ID) ? BUS_TAIL_ID : 0;
            break;
        }
        case -BUS_HEAD_ID: {
            push_frontObject(random(OBJECT_ID_LIST - vector<int>{BUS_HEAD_ID}));
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
        if (timeLight == TRAFFICLIGHT_DELAY - 5) ptrafficLight->setLightColor(YELLOW_TRAFFICLIGHT);
        return;
    }
    if (timeLight == TRAFFICLIGHT_DELAY) {
        isStop = true;
        ptrafficLight->setLightColor(RED_TRAFFICLIGHT);
    }
    if (timeLight < TRAFFICLIGHT_DELAY + TRAFFICLIGHT_WAIT) {
        timeLight++;
        return;
    }
    isStop = false;
    ptrafficLight->setLightColor(GREEN_TRAFFICLIGHT);
    timeLight = 0;
}

void CVEHICLELANE::Move() {
    if (lightPos >= 0) lightWork();
    timeCount++;
    if (timeCount >= delayTime) {
        timeCount = 0;
        //Random push a car
        if (lightPos < 0 || !isStop) {
            pop_backObject();
            pushNormally();
        }
        else {
            //Push with traffic light on
            //push after
            if (lightPos < BOARD_WIDTH - 2 && lightPos > 0) {
                if (lane[lightPos] != NULL && lane[lightPos]->getID() == BUS_HEAD_ID) {
                    if (isMoveRight) lane.insert(lane.begin() + lightPos - 1, NULL);
                    else lane.insert(lane.begin() + lightPos + 2, NULL);
                }
                else {
                    if (isMoveRight) lane.insert(lane.begin() + lightPos, NULL);
                    else lane.insert(lane.begin() + lightPos + 1, NULL);
                }
                pop_backObject();
            }
            //push before
            if (isMoveRight) {
                int id = lightPos - 1;
                for (; id >= 0 && lane[id] != NULL; id--);
                if (id >= 0) {
                    lane.erase(lane.begin() + id);
                    pushNormally();
                }
            }
            else {
                int id = lightPos + 1;
                for (; id < BOARD_WIDTH && lane[id] != NULL; id++);
                if (id < BOARD_WIDTH) {
                    lane.erase(lane.begin() + id);
                    pushNormally();
                }
            }
        }   
    }
}

void CVEHICLELANE::setyBoard(int yBoard) {
    if (yBoard < 0) yBoard = 0;
    if (yBoard > BOARD_HEIGHT - 1) yBoard = BOARD_HEIGHT - 1;
    this->y = yBoard * BLOCK_HEIGHT + START_BOARD_HEIGHT;
    updatePosObj();
    if (lightPos >= 0) ptrafficLight->setY(y);
}
void CVEHICLELANE::updateYObj() {
    for (int i = 0; i < (int)this->lane.size(); i++)
        if (lane[i] != NULL) lane[i]->setY(this->y);
    if (lightPos >= 0) ptrafficLight->setY(this->y);
}
void CVEHICLELANE::setStop(bool isStop)
{
    this->isStop = isStop;
}
bool CVEHICLELANE::getStop() const
{
    return this->isStop;
}

void CVEHICLELANE::DrawObjects(CGRAPHIC& layer) {
    for (int k = 0; k < BOARD_WIDTH; k++) {
        if (lane[k] != NULL) lane[k]->DrawBlock(layer);
        else {
            for (int i = 0; i < BLOCK_WIDTH; i++)
                for (int j = 0; j < BLOCK_HEIGHT; j++)
                    layer.screen[x + i + k * BLOCK_WIDTH][y + j] = { L' ', -1, -1 };
        }
    }
    if (lightPos >= 0) {
        PIXEL** blockLight = ptrafficLight->getBlock();
        for (int i = 0; i < BLOCK_WIDTH; i++)
            for (int j = 0; j < BLOCK_HEIGHT; j++)
                if (blockLight[i][j].txtColor >= 0) layer.screen[i + ptrafficLight->getX()][j + ptrafficLight->getY()] = blockLight[i][j];
    }
}
