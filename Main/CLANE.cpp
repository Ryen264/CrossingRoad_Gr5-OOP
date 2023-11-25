#include "CLANE.h"
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
void CLANE::pushDeque(int ID) {}

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
int CLANE::getID() const {
    return this->ID;
}

void CLANE::setIsMoveRight(bool right) {
    this->isMoveRight = right;
}
void CLANE::setTimeCount(int time) {
    this->timeCount = time;
}
void CLANE::setDelayTime(int time) {
    this->delayTime = time;
}
void CLANE::setYHeight(int y) {
    if (y < 0) y = 0;
    if (y > BOARD_HEIGHT - 1) y = BOARD_HEIGHT - 1;
    this->y = y * BLOCK_HEIGHT + START_BOARD_HEIGHT;

    updateYObj();
}
void CLANE::updateYObj() {
    for (int i = 0; i < (int)this->lane.size(); i++)
        if (lane[i] != NULL) lane[i]->setY(this->y);
}

void CLANE::DrawLane(CGRAPHIC& layer) {
    for (int k = 0; k < BOARD_WIDTH; k++) {
        for (int i = 0; i < BLOCK_WIDTH; i++)
            for (int j = 0; j < BLOCK_HEIGHT; j++)
                layer.screen[this->x + k * BLOCK_WIDTH + i][this->y + j] = block[i][j];
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