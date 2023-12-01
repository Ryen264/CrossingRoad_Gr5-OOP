#include "CPLAYER.h"
CPLAYER::CPLAYER(int xBoard, int yBoard, vector<int> color) {
    this->x = xBoard * BLOCK_WIDTH;
    this->xBoard = xBoard;
    this->y = yBoard * BLOCK_HEIGHT + START_BOARD_HEIGHT;
    this->yBoard = yBoard;
    this->alive = true;
    this->score = 0;
    this->moving = 0;

    this->color = color;
    this->pCharacterR = new CDINOSAUR(x, y, true, color), this->pCharacterL = new CDINOSAUR(x, y, false, color);
}
CPLAYER::~CPLAYER() {
    if (pCharacterR != NULL) delete pCharacterR;
    if (pCharacterL != NULL) delete pCharacterL;
    pCharacterR = pCharacterL = NULL;
}
int CPLAYER::getX() const {
    return this->x;
}
int CPLAYER::getY() const {
    return this->y;
}
int CPLAYER::getXBoard() const {
    return this->xBoard;
}
int CPLAYER::getYBoard() const {
    return this->yBoard;
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
COBJECT* CPLAYER::getDependObj() const {
    return dependObj;
}
int CPLAYER::getMoving() const {
    return this->moving;
}
vector<int> CPLAYER::getColorCharacter() const {
    return color;
}

void CPLAYER::set(int xBoard, int yBoard, bool live, bool right, int score) {
    if (xBoard < 0) xBoard = 0;
    this->x = xBoard * BLOCK_WIDTH;
    this->xBoard = xBoard;

    if (yBoard < 0) yBoard = 0;
    this->y = yBoard * BLOCK_HEIGHT + START_BOARD_HEIGHT;
    this->yBoard = yBoard;

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
void CPLAYER::setPos(int xBoard, int yBoard) {
    if (xBoard < 0) xBoard = 0;
    if (xBoard >= BOARD_WIDTH) xBoard = BOARD_WIDTH - 1;
    this->x = xBoard * BLOCK_WIDTH;
    this->xBoard = xBoard;

    if (yBoard < 0) yBoard = 0;
    if (yBoard >= BOARD_HEIGHT) yBoard = BOARD_HEIGHT - 1;
    this->y = yBoard * BLOCK_HEIGHT + START_BOARD_HEIGHT;
    this->yBoard = yBoard;
}
void CPLAYER::setDependObj(COBJECT* obj) {
    dependObj = obj;
}
void CPLAYER::setxBoard(int xboard) {
    if (xBoard < 0) xBoard = 0;
    if (xBoard >= BOARD_WIDTH) xBoard = BOARD_WIDTH - 1;
    this->x = xBoard * BLOCK_WIDTH;
    this->xBoard = xBoard;
}
void CPLAYER::setyBoard(int yboard) {
    if (yBoard < 0) yBoard = 0;
    if (yBoard >= BOARD_HEIGHT) yBoard = BOARD_HEIGHT - 1;
    this->y = yBoard * BLOCK_HEIGHT + START_BOARD_HEIGHT;
    this->yBoard = yBoard;
}
void CPLAYER::setColorCharacter(vector<int> color) {
    this->color = color;
    pCharacterR->setColor(color); pCharacterL->setColor(color);
}
int CPLAYER::updateDepend() {
	if (dependObj == NULL) return 0;
	switch (dependObj->getID()) {
	case CAPYBARA_ID: {
		this->x = dependObj->getX();
		this->xBoard = this->x / BLOCK_WIDTH;
		this->y = dependObj->getY();
		this->yBoard = (this->y - START_BOARD_HEIGHT) / BLOCK_HEIGHT;
		return CAPYBARA_ID;
	}
	case PERRY_ID: {
		// this->setyBoard(yBoard - 1);
		return PERRY_ID;
	}
	case EGG_ID: {
		this->increaseScore(10);
		return EGG_ID;
	}
	case CAR_ID: case TRUCK_ID: case TRAIN_HEAD_ID: case TRAIN_BODY_ID: {
		this->alive = false;
		return CAR_ID;
	}
	}
	if (this->x == 0 || this->x == BOARD_WIDTH - 1) this->alive = false;
	return CAR_ID;
}
bool CPLAYER::moveCharacter() {

    if (this->moving == UP) {
        if (yBoard <= UP_LANE) return true;
        this->y -= BLOCK_HEIGHT;
        this->yBoard--;
    }
    else if (this->moving == DOWN) {
        if (yBoard >= DOWN_LANE) {
            alive = false; //die when go to the bottom
            return false;
        }
        this->y += BLOCK_HEIGHT;
        this->yBoard++;
    }
    else if (this->moving == RIGHT) {
        if (xBoard < BOARD_WIDTH) {
            this->x += BLOCK_WIDTH;
            this->xBoard++;
        }
        if (xBoard == BOARD_WIDTH) {
            this->x = 0;
            this->xBoard = 0;
            this->alive = false;
            return false;
        }
        if (!this->isRight) this->isRight = true;
    }
    else if (this->moving == LEFT) {
        if (xBoard > -1) {
            this->x -= BLOCK_WIDTH;
            this->xBoard--;
        }
        if (xBoard == -1) {
            this->x = 0;
            this->xBoard = 0;
            this->alive = false;
            return false;
        }
        if (this->isRight) this->isRight = false;
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
    if (isRight) {
        pCharacterR->setPos(x, y);
        pCharacterR->DrawBlock(layer);
    }
    else {
        pCharacterL->setPos(x, y);
        pCharacterL->DrawBlock(layer);
    }
}
