#include "CTRAINLANE.h"

CTRAINLANE::CTRAINLANE(int x, int y, int delayTime, int trainDelay, int trainWait) {
    for (int i = 0; i < BOARD_WIDTH; i++)
        this->lane.push_front(NULL);
    this->isMoveRight = rand() % 2;
    this->delayTime = delayTime; this->trainDelay = trainDelay; this->trainWait = trainWait;

    this->x = x * BLOCK_WIDTH; this->y = y * BLOCK_HEIGHT + START_BOARD_HEIGHT; this->ID = TRAINLANE_ID;

    this->block = new PIXEL * [BLOCK_WIDTH * this->numberOfWidth];
    for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
        this->block[i] = new PIXEL[BLOCK_HEIGHT * this->numberOfHeight];

    //set buffers
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
			this->block[i][j] = { FRAME[j][i], LIGHT_GREEN, LIGHT_BROWN };
	//set colors
	for (int i = 0; i < 16; i++) {
        block[i][0].bgdColor = LIGHT_GREEN;
		block[i][1].txtColor = DARK_GREEN;
		block[i][2].txtColor = WHITE;
		block[i][3].txtColor = SADDLE_BROWN;
		block[i][4].txtColor = SADDLE_BROWN;
        block[i][5].bgdColor = LIGHT_GREEN;
		block[i][5].txtColor = WHITE;
	}
	for (int i = 1; i <= 16; i++) {
		if ((i + 3) % 4 == 0) {
			block[i][3].txtColor = LIGHT_GRAY;
			block[i][4].txtColor = LIGHT_GRAY;
		}
	}
	block[1][1].bgdColor = SADDLE_BROWN;
	block[3][2].bgdColor = SADDLE_BROWN;
	block[4][1].bgdColor = SADDLE_BROWN;
	block[5][1].bgdColor = SADDLE_BROWN;
	block[6][1].bgdColor = SADDLE_BROWN;
	block[6][2].bgdColor = SADDLE_BROWN;
	block[9][2].bgdColor = SADDLE_BROWN;
	block[11][1].bgdColor = SADDLE_BROWN;
	block[12][2].bgdColor = SADDLE_BROWN;
	block[13][2].bgdColor = SADDLE_BROWN;
    block[14][4].bgdColor = SADDLE_BROWN;
	block[15][1].bgdColor = SADDLE_BROWN;
	block[15][1].bgdColor = SADDLE_BROWN;
}

void CTRAINLANE::fillDeque(int ID)
{
    //clear
    while (!this->lane.empty()) {
        COBJECT* back = lane.back();
        lane.pop_back();
        if (back != NULL) delete back;
    }
    this->lane.clear();
    //fill
    switch (ID) {
    case TRAIN_BODY_ID: {
        if (isMoveRight) {
            for (int i = 0; i < BOARD_WIDTH; i++)
                lane.push_front(new CTRAIN(0, this->y, true, false));
        }
        else {
            for (int i = 0; i < BOARD_WIDTH; i++)
                lane.push_back(new CTRAIN(0, this->y, false, false));
        }
        break;
    }
    default:
        for (int i = 0; i < BOARD_WIDTH; i++)
            lane.push_back(NULL);
    }
}

void CTRAINLANE::Move()
{
    timeTrain++;
    if (timeTrain == trainDelay - TRAIN_BEFORE) {
        //push head
        if (isMoveRight) {
            COBJECT* back = lane.back();
            if (back != NULL) delete back;
            this->lane.pop_back();
            lane.push_front(new CTRAIN(0, this->y, true, true));
        }
        else {
            COBJECT* front = lane.front();
            if (front != NULL) delete front;
            this->lane.pop_front();
            lane.push_back(new CTRAIN(0, this->y, false, true));
        }
    }
    
    if (timeTrain >= trainDelay) {
        if (timeTrain == trainDelay)
            fillDeque(TRAIN_BODY_ID);
        if (timeTrain >= trainDelay + trainWait) {
            if (timeTrain == trainDelay + trainWait) timeCount = delayTime;
            else timeCount++;
            if (timeCount >= delayTime) {
                timeCount = 0;
                //Respectively push NULL
                if (isMoveRight) {
                    COBJECT* back = lane.back();
                    if (back != NULL) delete back;
                    this->lane.pop_back();
                    lane.push_front(NULL);
                }
                else {
                    COBJECT* front = lane.front();
                    if (front != NULL) delete front;
                    this->lane.pop_front();
                    lane.push_back(NULL);
                }
            }
            if (isMoveRight && lane.back() == NULL || !isMoveRight && lane.front() == NULL)
                timeTrain = 0;
        }
    }
}

void CTRAINLANE::setStop(bool isStop)
{
    this->isStop = isStop;
}

bool CTRAINLANE::getStop() const
{
    return isStop;
}
