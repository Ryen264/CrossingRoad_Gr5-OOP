#include "CPLAYER.h"
CPLAYER::CPLAYER(int firstX, int firstY) {
    this->x = firstX;
    this->y = firstY;
    this->alive = true;
    this->score = 0;
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
void CPLAYER::increaseScore(int point) {
    this->score += point;
}
void CPLAYER::decreaseScore(int point) {
    this->score -= point;
}
void CPLAYER::Up(int step) {
    if (this->y > 0)
        this->y -= step;
}
void CPLAYER::Down(int step) {
    if (this->y < BOARD_HEIGHT - 1)
        this->y += step;
}
void CPLAYER::Left(int step) {
    if (this->x > 0)
        this->x -= step;
}
void CPLAYER::Right(int step) {
    if (this->x < BOARD_WIDTH - 1)
        this->x += step;
}
bool CPLAYER::isFinish(int finishHeight) {
    return this->y >= finishHeight - 1;
}
bool CPLAYER::isDead() {
    return !alive;
}
