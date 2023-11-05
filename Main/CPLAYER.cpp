#include "CPLAYER.h"
CPLAYER::CPLAYER(int firstX, int firstY) {
    this->x = firstX;
    this->y = firstY;
    this->alive = true;
    this->score = 0;
}
CPLAYER::~CPLAYER() {

}
int CPLAYER::getX() {
    return this->x;
}
int CPLAYER::getY() {
    return this->y;
}
int CPLAYER::getScore() {
    return this->score;
}
void CPLAYER::set(int x, int y, bool alive, int score) {
    if (x >= 0)
        this->x = x;
    if (y >= 0)
        this->y = y;
    this->alive = alive;
    if (score >= 0)
        this->score = score;
}
bool CPLAYER::setIsRight() {
    return this->isRight;
}
void CPLAYER::setFinish(bool finish) {
    this->finish = false;
}
void CPLAYER::setAlive(bool alive) {
    this->alive = alive;
}
void CPLAYER::setMove(int moving) {
    this->moving = moving;
}
void CPLAYER::moveCharacter() {
    if (this->moving == UP) {
        if (this->y > 0)
            this->y--;
    }
    else if (this->moving == DOWN) {
        if (this->y < BOARD_HEIGHT - 1)
            this->y++;
        if (this->y + 1 == BOARD_HEIGHT) {
            this->finish = true;
            this->y = 0;
        }
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
}
void CPLAYER::increaseScore(int point) {
    this->score += point;
}
void CPLAYER::decreaseScore(int point) {
    this->score -= point;
}
bool CPLAYER::isFinish() {
    return this->finish;
}
bool CPLAYER::isDead() {
    return !alive;
}
void CPLAYER::drawCharacter(CGRAPHIC& layer) {
    CDINOSAUR character(this->x * BLOCK_WIDTH, this->y * BLOCK_HEIGHT, this->isRight);
    character.DrawBlock(layer);
}
void CPLAYER::eraseCharacter(CGRAPHIC& layer) {
    for (int i = 0; i < BLOCK_WIDTH; i++)
        for (int j = 0; j < BLOCK_HEIGHT; j++)
            layer.screen[this->x * BLOCK_WIDTH + i][this->y * BLOCK_HEIGHT + j] = {L' ', WHITE,-1};
}