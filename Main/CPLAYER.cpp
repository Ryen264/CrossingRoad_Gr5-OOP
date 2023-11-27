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
bool CPLAYER::getIsAlive() const {
    return this->alive;
}
void CPLAYER::set(int x, int y, bool live, bool right, int score) {
    if (x >= 0)
        this->x = x;
    if (y >= 0)
        this->y = y;
    this->alive = live;
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
void CPLAYER::moveCharacter() {
    if (this->moving == UP) {
        if (this->y > -1)
            this->y--;
        if (this->y == -1) {
            this->finish = true;
            this->y = BOARD_HEIGHT - 1;
        }
    }
    else if (this->moving == DOWN) {
        if (this->y < BOARD_HEIGHT - 1)
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
    int startX = this->x * BLOCK_WIDTH;
    int startY = this->y * BLOCK_HEIGHT + START_HEIGHT;
    CDINOSAUR character(startX, startY, this->isRight);
    character.DrawBlock(layer);
}
void CPLAYER::eraseCharacter(CGRAPHIC& layer) {
    wchar_t blankChar = L' '; 
    int startX = this->x * BLOCK_WIDTH;
    int startY = this->y * BLOCK_HEIGHT + START_HEIGHT;
    for (int i = 0; i < BLOCK_WIDTH; i++)
        for (int j = 0; j < BLOCK_HEIGHT; j++)
            layer.screen[startX + i][startY + j] = { blankChar, -1, -1 };
}