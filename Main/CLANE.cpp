#include "CLANE.h"
CLANE::~CLANE() {
    while (!this->lane.empty()) {
        COBJECT* back = lane.back();
        lane.pop_back();
        if (back != NULL) delete back;
    }
    this->lane.clear();
    for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
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
void CLANE::pushObj(int x, int ID) {}

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
void CLANE::updateYObj() {
    for (int i = 0; i < (int)this->lane.size(); i++)
        if (lane[i] != NULL) lane[i]->setY(this->y);
}

void CLANE::DrawLane(CGRAPHIC& layer) {
    int laneX = this->x;
    int laneY = this->y;
    for (int k = 0; k < BOARD_WIDTH; k++) {
        int blockStartX = laneX + k * BLOCK_WIDTH * this->numberOfWidth;
        int blockStartY = laneY;
        for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++) {
            memcpy(&layer.screen[blockStartX + i][blockStartY], &block[i][0], BLOCK_HEIGHT * this->numberOfHeight * sizeof(PIXEL));
        }
    }
}
/*
void CLANE::DrawLane(CGRAPHIC& layer) {
    int laneX = this->x;
    int laneY = this->y;

    for (int k = 0; k < BOARD_WIDTH; k++) {
        int blockStartX = laneX + k * BLOCK_WIDTH * this->numberOfWidth;
        int blockStartY = laneY;

        for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
            for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
                layer.screen[blockStartX + i][blockStartY + j] = block[i][j];
    }
}
*/
/*
void CLANE::DrawObjects(CGRAPHIC& layer) {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        int laneX = this->x + i * BLOCK_WIDTH;
        int laneY = this->y;
        if (lane[i] != NULL) {
            lane[i]->setPos(laneX, laneY);
            lane[i]->DrawBlock(layer);
        }
        else {
            for (int k = 0; k < BLOCK_WIDTH; k++)
                for (int l = 0; l < BLOCK_HEIGHT; l++)
                    layer.screen[laneX + k][laneY + l] = { L' ', -1, -1 };
        }
    }
}
*/

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

