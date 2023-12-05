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
            numberOfConditionalObject = 1 + rand() % 3;
            if (numberOfConditionalObject > 1) condition = ID;
            else condition = -ID;
            break;
        }
        case TRUCK_ID: {
            countObject = 1;
            numberOfConditionalObject = 1 + rand() % 2;
            if (numberOfConditionalObject > 1) condition = ID;
            else condition = -ID;
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
    else if (condition < 0) {
        int ID = random(OBJECT_ID_LIST - vector<int>{-condition});
        push_frontObject(ID);
        condition = (ID == BUS_HEAD_ID) ? BUS_TAIL_ID : 0;
    }
    else {
        switch (condition) {
        case CAR_ID: case TRUCK_ID: {
            push_frontObject(condition);
            countObject++;
            if (countObject >= numberOfConditionalObject) {
                condition = -condition;
                countObject = 0;
            }
            break;
        }
        case BUS_TAIL_ID: {
            push_frontObject(BUS_TAIL_ID);
            condition = -BUS_HEAD_ID;
            break;
        }
        default:
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
            pushNormally();
            pop_backObject();
        }
        else {
            //Push with traffic light on
            //push after
            if (lane[lightPos] != NULL && lane[lightPos]->getID() == BUS_HEAD_ID) {
                if (isMoveRight) {
                    if (lightPos > 0) lane.insert(lane.begin() + lightPos - 1, NULL);
                    else push_frontObject(BUS_TAIL_ID);
                }
                else {
                    if (lightPos < BOARD_WIDTH - 2) lane.insert(lane.begin() + lightPos + 2, NULL);
                    else if (lightPos == BOARD_WIDTH - 2) lane.push_back(NULL);
                    else push_frontObject(BUS_TAIL_ID);
                }
            }
            else {
                if (isMoveRight) lane.insert(lane.begin() + lightPos, NULL);
                else {
                    if (lightPos < BOARD_WIDTH - 1) lane.insert(lane.begin() + lightPos + 1, NULL);
                    else lane.push_back(NULL);
                }
            }
            pop_backObject();

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
    if (lightPos >= 0) ptrafficLight->DrawBlock(layer, true);
}
void CVEHICLELANE::DrawLane(CGRAPHIC& layer) {
    for (int k = 0; k < BOARD_WIDTH; k++) {
        if (k != lightPos) {
            for (int i = 0; i < BLOCK_WIDTH; i++)
                for (int j = 0; j < BLOCK_HEIGHT; j++)
                    layer.screen[x + i + k * BLOCK_WIDTH][y + j] = block[i][j];
        }
        else {
            for (int i = 0; i < BLOCK_WIDTH; i++)
                for (int j = 0; j < BLOCK_HEIGHT; j++)
                    layer.screen[x + i + k * BLOCK_WIDTH][y + j] = { FRAME_MARKING[j][i], WHITE, LIGHT_GRAY };
            for (int i = 0; i < 16; i++)
                layer.screen[x + i + k * BLOCK_WIDTH][y].bgdColor = LIGHT_GREEN;
        }
    }
}
