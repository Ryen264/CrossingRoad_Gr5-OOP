#include "CPLAYER.h"
CPLAYER::CPLAYER(int xBoard, int yBoard, int colorCharacter) {
    this->x = xBoard * BLOCK_WIDTH;
    this->xBoard = xBoard;
    this->y = yBoard * BLOCK_HEIGHT + START_BOARD_HEIGHT;
    this->yBoard = yBoard;
    this->alive = true;
    this->score = 0;
    this->moving = 0;

    this->colorCharacter = colorCharacter;
    this->pCharacterR = new CDINOSAUR(x, y, true, colorCharacter); this->pCharacterL = new CDINOSAUR(x, y, false, colorCharacter);
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
int CPLAYER::getColorCharacter() const {
    return colorCharacter;
}
string CPLAYER::getNameCharacter() const {
    if (colorCharacter == RED) return "RED";
    else if (colorCharacter == BLUE) return "BLUE";
    else if (colorCharacter == DARK_GREEN) return "GREEN";
    else if (colorCharacter == BRIGHT_YELLOW) return "YELLOW";
    else if (colorCharacter == ORANGE) return "ORANGE";
    else if (colorCharacter == SADDLE_BROWN) return "BROWN";
    else if (colorCharacter == DARK_GRAY) return "GRAY";
    else if (colorCharacter == DARK_RED) return "DRED";
    else if (colorCharacter == DARK_BLUE) return "DBLUE";
    else return "GREEN";
}

void CPLAYER::set(int xBoard, int yBoard, bool live, bool right, int score) {
    if (xBoard >= 0)
    {
        this->x = xBoard * BLOCK_WIDTH;
        this->xBoard = xBoard;
    }

    if (yBoard >= 0)
    {
        this->y = yBoard * BLOCK_HEIGHT + START_BOARD_HEIGHT;
        this->yBoard = yBoard;
    }

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
    if (xBoard >= BOARD_WIDTH) xBoard = BOARD_WIDTH - 1;
    if (xBoard >= 0)
    {
        this->x = xBoard * BLOCK_WIDTH;
        this->xBoard = xBoard;
    }

    if (yBoard >= BOARD_HEIGHT) yBoard = BOARD_HEIGHT - 1;
    if (yBoard >= 0)
    {
        this->y = yBoard * BLOCK_HEIGHT + START_BOARD_HEIGHT;
        this->yBoard = yBoard;
    }
}
void CPLAYER::setDependObj(COBJECT* obj) {
    dependObj = obj;
}
void CPLAYER::setxBoard(int xboard) {
    if (xBoard >= BOARD_WIDTH) xBoard = BOARD_WIDTH - 1;
    if (xBoard >= 0) {
        this->x = xBoard * BLOCK_WIDTH;
        this->xBoard = xBoard;
    }
}
void CPLAYER::setyBoard(int yboard) {
    if (yBoard >= BOARD_HEIGHT) yBoard = BOARD_HEIGHT - 1;
    if (yBoard >= 0) {
        this->y = yBoard * BLOCK_HEIGHT + START_BOARD_HEIGHT;
        this->yBoard = yBoard;
    }
}
void CPLAYER::setColorCharacter(int color) {
    this->colorCharacter = color;
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
        this->alive = true;
		return CAPYBARA_ID;
	}
	case PERRY_ID: {
        this->alive = true;
		return PERRY_ID;
	}
	case EGG_ID: {
        this->alive = true;
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
            setxBoard(BOARD_WIDTH);
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
            setxBoard(0);
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
        pCharacterR->DrawBlock(layer, true);
    }
    else {
        pCharacterL->setPos(x, y);
        pCharacterL->DrawBlock(layer, true);
    }
}
