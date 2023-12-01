#include "CTRAINLANE.h"
CTRAINLANE::CTRAINLANE(int x, int y, int delayTime, int numberOfTrain) : CLANE(x, y) {
    for (int i = 0; i < BOARD_WIDTH; i++)
        this->lane.push_front(NULL);
    this->isMoveRight = rand() % 2;
    this->delayTime = delayTime; this->numberOfTrain = numberOfTrain;

    this->ID = TRAINLANE_ID;

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
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

void CTRAINLANE::push_frontObject(int ID) {
	if (isMoveRight) {
		switch (ID) {
		case TRAIN_HEAD_ID: {
			lane.push_front(new CTRAIN(0, this->y, true, true));
			break;
		}
		case TRAIN_BODY_ID: {
			lane.push_front(new CTRAIN(0, this->y, true, false));
			break;
		}
		default:
			lane.push_front(NULL);
		}
	}
	else {
		switch (ID) {
		case TRAIN_HEAD_ID: {
			lane.push_back(new CTRAIN(0, this->y, false, true));
			break;
		}
		case TRAIN_BODY_ID: {
			lane.push_back(new CTRAIN(0, this->y, false, false));
			break;
		}
		default:
			lane.push_back(NULL);
		}
	}
	updatePosObj();
}
void CTRAINLANE::Move()
{
	timeCount++;
	if (timeCount >= delayTime) {
		timeCount = 0;
		//Push head first and n train body respectively
		if (countTrain <= numberOfTrain) {
			pop_backObject();
			if (countTrain == 0) push_frontObject(TRAIN_HEAD_ID);
			else push_frontObject(TRAIN_BODY_ID);
			countTrain++;
		}
		else if (countTrain <= numberOfTrain + BOARD_WIDTH) {
			pop_backObject();
			push_frontObject();
			countTrain++;
		}
		else if (rand() % 5 == 0) countTrain = 0;
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
