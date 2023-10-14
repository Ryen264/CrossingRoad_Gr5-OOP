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
void CPLAYER::setXY(int x, int y) {
    if (x >= 0)
        this->x = x;
    if (y >= 0)
        this->y = y;
}

void CPLAYER::decreaseScore(int point) {
    this->score -= point;
}
void CPLAYER::increaseScore(int point) {
    this->score += point;
}
void CPLAYER::Up(int step) {
    this->y -= step;
}
void CPLAYER::Down(int step) {
    this->y += step;
}
void CPLAYER::Left(int step) {
    this->x -= step;
}
void CPLAYER::Right(int step) {
    this->x += step;
}
bool CPLAYER::isFinish(int finishHeight) {
    return this->y >= finishHeight - 1;
}
bool CPLAYER::isDead() {
    return !alive;
}
void CPLAYER::draw(ostream& outDev) {
    outDev << "V";
}
