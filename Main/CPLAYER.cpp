#include "CPLAYER.h"
CPLAYER::CPLAYER(int firstX, int firstY) {
    this->x = firstX;
    this->y = firstY;
    this->alive = true;
    this->score = 0;
    this->moving = 0;
}
CPLAYER::~CPLAYER() {

}
int CPLAYER::getX() const {
    return this->x;
}
int CPLAYER::getY() const {
    return this->y;
}
int CPLAYER::getScore() const {
    return this->score;
}
bool CPLAYER::getIsRight() const {
    return this->isRight;
}
void CPLAYER::set(int x, int y, bool right, int score) {
    if (x >= 0)
        this->x = x;
    if (y >= 0)
        this->y = y;
    this->isRight = right;
    if (score >= 0)
        this->score = score;
}
bool CPLAYER::setIsRight() {
    return this->isRight;
}
void CPLAYER::setFinish(bool finish) {
    this->finish = finish;
}
void CPLAYER::setAlive(bool alive) {
    this->alive = alive;
}
void CPLAYER::setMove(int moving) {
    this->moving = moving;
}

bool CPLAYER::moveCharacter() {
    if (this->moving == UP) {
        if (y <= UP_LANE) return true;
        this->y--;
    }
    else if (this->moving == DOWN) {
        if (y >= DOWN_LANE) {
            alive = false; //die when go to the bottom
            return false;
        }
        this->y++;
    }
    else if (this->moving == RIGHT) {
        if (this->x < BOARD_WIDTH - 1)
            this->x++;
        if (!this->isRight)
            this->isRight = true;
    }
    else if (this->moving == LEFT) {
        if (this->x > 0)
            this->x--;
        if (this->isRight)
            this->isRight = false;
    }
    return false;
}
void CPLAYER::increaseScore(int point) {
    this->score += point;
}
void CPLAYER::decreaseScore(int point) {
    this->score -= point;
}
bool CPLAYER::isFinish() const {
    return this->finish;
}
bool CPLAYER::isDead() const{
    return !this->alive;
}
bool CPLAYER::isMoving() const {
    return this->moving != 0;
}
void CPLAYER::drawCharacter(CGRAPHIC& layer) {
    CDINOSAUR character(this->x * BLOCK_WIDTH, this->y * BLOCK_HEIGHT + START_BOARD_HEIGHT, this->isRight);
    character.DrawBlock(layer);
}
void CPLAYER::displayCharacter(CGRAPHIC& layer) {
    int fromX = this->x * BLOCK_WIDTH, fromY = this->y * BLOCK_HEIGHT + START_BOARD_HEIGHT;
    layer.display(fromX, fromY, fromX + BLOCK_WIDTH, fromY + BLOCK_HEIGHT);
}
