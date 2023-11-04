#include "CLANE.h"
void CLANE::changeDirection() {
	this->isMoveRight = !this->isMoveRight;
}
bool CLANE::checkPos(int pos) {
    return this->lane[pos] != NULL;
}
void CLANE::Move() {
    //Random push a car
    if (this->isMoveRight) {
        COBJECT* back = lane.back();
        if (back != NULL)
            delete back;
        this->lane.pop_back();
        if (rand() % 10 == 0)
            this->lane.push_front(new COBJECT);
        else
            this->lane.push_front(NULL);
    }
    else {
        COBJECT* front = lane.front();
        if (front != NULL)
            delete front;
        this->lane.pop_front();
        if (rand() % 10 == 0)
            this->lane.push_back(new COBJECT);
        else
            this->lane.push_back(NULL);
    }
}
void CLANE::DrawLane(CGRAPHIC& layer) {
    for (int k = 0; k < BOARD_WIDTH; k++) {
        for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
            for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
                layer.screen[this->x + k * BLOCK_WIDTH * this->numberOfWidth + i][this->y + j] = block[i][j];

    }
}
void CLANE::DrawObject(CGRAPHIC& layer, int pos) {
    this->lane[pos]->DrawBlock(layer);
}
