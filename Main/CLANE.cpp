#include "CLANE.h"
CLANE::CLANE(int xBoard, int yBoard) {
    if (xBoard < 0) xBoard = 0;
    this->x = xBoard * BLOCK_WIDTH;
    if (yBoard < 0) yBoard = 0;
    this->y = yBoard * BLOCK_HEIGHT + START_BOARD_HEIGHT;

    this->block = new PIXEL * [BLOCK_WIDTH];
    for (int i = 0; i < BLOCK_WIDTH; i++)
        this->block[i] = new PIXEL[BLOCK_HEIGHT];
}
CLANE::~CLANE() {
    while (!this->lane.empty()) {
        COBJECT* back = lane.back();
        lane.pop_back();
        if (back != NULL) delete back;
    }
    this->lane.clear();
    for (int i = 0; i < BLOCK_WIDTH; i++)
        delete[] this->block[i];
    delete[] this->block;
}

void CLANE::Move() {}
void CLANE::push_frontObject(int ID) {}
void CLANE::pop_backObject() {
    if (isMoveRight) {
        COBJECT* back = lane.back();
        if (back != NULL) delete back;
        this->lane.pop_back();
    }
    else {
        COBJECT* front = lane.front();
        if (front != NULL) delete front;
        this->lane.pop_front();
    }
}
COBJECT* CLANE::frontObject() const
{
    if (isMoveRight) return this->lane.front();
    return this->lane.back();
}
COBJECT* CLANE::backObject() const
{
    if (isMoveRight) return this->lane.back();
    return this->lane.front();
}
bool CLANE::emptyObject() const
{
    return this->lane.empty();
}
void CLANE::clearObject()
{
    this->lane.clear();
}

void CLANE::setPos(int i, COBJECT* val) {
    if (i < 0) i = 0;
    if (i >= (int)lane.size()) i = (int)lane.size() - 1;
    this->lane[i] = val;
}
void CLANE::setyBoard(int yBoard) {
    if (yBoard < 0) yBoard = 0;
    if (yBoard > BOARD_HEIGHT - 1) yBoard = BOARD_HEIGHT - 1;
    this->y = yBoard * BLOCK_HEIGHT + START_BOARD_HEIGHT;
    updatePosObj();
}
void CLANE::updatePosObj() {
    for (int i = 0; i < (int)lane.size(); i++)
        if (lane[i] != NULL) lane[i]->setPos(i * BLOCK_WIDTH, this->y);
}

void CLANE::injuredPlayer(CPLAYER& player) {
    int i = player.getXBoard();
    if (lane[i] == NULL) return;
    player.setAlive(false);
}
COBJECT* CLANE::getPos(int i) const {
    if (i < 0 || i >(int)lane.size() - 1) return NULL;
    return lane[i];
}

int CLANE::getID() const {
    return ID;
}
bool CLANE::getIsMoveRight() const {
    return isMoveRight;
}
int CLANE::getCondition() const
{
    return 0;
}
int CLANE::getCountObject() const
{
    return 0;
}
int CLANE::getNumberOfConditionObj() const
{
    return 0;
}
int CLANE::getLightPos() const
{
    return -1;
}
int CLANE::getTimeLight() const
{
    return 0;
}
bool CLANE::getIsStop() const
{
    return false;
}
int CLANE::getTimeCount() const {
    return 0;
}
int CLANE::getDelayTime() const {
    return 0;
}

void CLANE::setIsMoveRight(bool isMoveRight) {
    this->isMoveRight = isMoveRight;
}
void CLANE::setCondition(int condition) {}
void CLANE::setCountObject(int countObject) {}
void CLANE::setNumberOfConditionObj(int numberOfConditionObj) {}
void CLANE::setLightPos(int lightPos) {}
void CLANE::setTimeLight(int timeLight) {}
void CLANE::setIsStop(bool isStop) {}
void CLANE::setTimeCount(int timeCount) {}
void CLANE::setDelayTime(int delayTime) {}

void CLANE::DrawLane(CGRAPHIC& layer) {
    for (int k = 0; k < BOARD_WIDTH; k++) {
        for (int i = 0; i < BLOCK_WIDTH; i++)
            for (int j = 0; j < BLOCK_HEIGHT; j++)
                layer.screen[x + i + k * BLOCK_WIDTH][y + j] = block[i][j];
    }
}
void CLANE::DrawObjects(CGRAPHIC& layer) {
    for (int k = 0; k < BOARD_WIDTH; k++)
        if (lane[k] != NULL) lane[k]->DrawBlock(layer);
}

vector<int> operator-(const vector<int> first, const vector<int> second) {
    vector<int> res{};
    for (int i = 0; i < (int)first.size(); i++) {
        bool exist = false;
        for (int j = 0; j < (int)second.size(); j++)
            if (first[i] == second[j]) {
                exist = true;
                break;
            }
        if (!exist) res.push_back(first[i]);
    }
    return res;
}
