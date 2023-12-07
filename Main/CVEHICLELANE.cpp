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
            numberOfConditionObj = 1 + rand() % 3;
            if (numberOfConditionObj > 1) condition = CAR_ID;
            else condition = -CAR_ID;
            break;
        }
        case TRUCK_ID: {
            countObject = 1;
            numberOfConditionObj = 1 + rand() % 2;
            if (numberOfConditionObj > 1) condition = TRUCK_ID;
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
            if (countObject >= numberOfConditionObj) {
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
            int ID = random(OBJECT_ID_LIST);
            push_frontObject(ID);
            condition = (ID == BUS_HEAD_ID) ? BUS_TAIL_ID : 0;
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

int CVEHICLELANE::getCondition() const {
    return condition;
}
int CVEHICLELANE::getCountObject() const {
    return countObject;
}
int CVEHICLELANE::getNumberOfConditionObj() const {
    return numberOfConditionObj;
}
int CVEHICLELANE::getLightPos() const
{
    return lightPos;
}
int CVEHICLELANE::getTimeLight() const
{
    return timeLight;
}
bool CVEHICLELANE::getIsStop() const
{
    return this->isStop;
}
int CVEHICLELANE::getTimeCount() const
{
    return timeCount;
}
int CVEHICLELANE::getDelayTime() const
{
    return delayTime;
}

void CVEHICLELANE::setCondition(int condition)
{
    if (!checkinList(condition, { 0, -CAR_ID, -TRUCK_ID, -BUS_HEAD_ID, CAR_ID, TRUCK_ID, BUS_TAIL_ID, BUS_HEAD_ID })) condition = 0;
    this->condition = condition;
}
void CVEHICLELANE::setCountObject(int countObject)
{
    if (countObject < 0) countObject = 0;
    this->countObject = countObject;
}
void CVEHICLELANE::setNumberOfConditionObj(int numberOfConditionObj)
{
    if (numberOfConditionObj < 0) numberOfConditionObj = 0;
    this->numberOfConditionObj = numberOfConditionObj;
}
void CVEHICLELANE::setLightPos(int lightPos)
{
    this->lightPos = lightPos;
    if (ptrafficLight != NULL) delete ptrafficLight;
    ptrafficLight = NULL;
    if (lightPos >= 0) ptrafficLight = new CTRAFFICLIGHT(lightPos * BLOCK_WIDTH, this->y);
}
void CVEHICLELANE::setTimeLight(int timeLight)
{
    if (timeLight < 0) timeLight = 0;
    this->timeLight = timeLight;
}
void CVEHICLELANE::setIsStop(bool isStop)
{
    this->isStop = isStop;
}
void CVEHICLELANE::setTimeCount(int timeCount)
{
    if (timeCount < 0) timeCount = 0;
    this->timeCount = timeCount;
}
void CVEHICLELANE::setDelayTime(int delayTime)
{
    if (delayTime < 0) delayTime = 0;
    this->delayTime = delayTime;
}

void CVEHICLELANE::DrawObjects(CGRAPHIC& layer) {
    for (int k = 0; k < BOARD_WIDTH; k++)
        if (lane[k] != NULL) lane[k]->DrawBlock(layer);
    if (ptrafficLight != NULL) ptrafficLight->DrawBlock(layer, true);
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

bool checkinList(int val, vector<int> list) {
    for (int& mem : list)
        if (val == mem) return true;
    return false;
}

