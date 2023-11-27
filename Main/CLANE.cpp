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
void CLANE::injuredPlayer(CPLAYER& player) {
    player.setAlive(false);
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
    int laneX = this->x;
    int laneY = this->y;
    for (int k = 0; k < BOARD_WIDTH; k++) {
        int blockStartX = laneX + k * BLOCK_WIDTH;
        int blockStartY = laneY;
        for (int i = 0; i < BLOCK_WIDTH; i++) {
            memcpy(&layer.screen[blockStartX + i][blockStartY], &block[i][0], BLOCK_HEIGHT * sizeof(PIXEL));
        }
    }
}
void CLANE::DrawObjects(CGRAPHIC& layer) {
    int laneY = this->y;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        int laneX = this->x + i * BLOCK_WIDTH;
        if (lane[i] != NULL) {
            lane[i]->setPos(laneX, laneY);
            lane[i]->DrawBlock(layer);
        } else {
            int blockStartX = laneX;
            for (int k = 0; k < BLOCK_WIDTH; k++) {
                int blockStartY = laneY;
                for (int l = 0; l < BLOCK_HEIGHT; l++) {
                    layer.screen[blockStartX + k][blockStartY + l] = { L' ', -1, -1 };
                }
            }
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