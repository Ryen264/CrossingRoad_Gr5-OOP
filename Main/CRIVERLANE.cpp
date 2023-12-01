#include "CRIVERLANE.h"
CRIVERLANE::CRIVERLANE(int x, int y, int delayTime) : CLANE(x, y) {
	for (int i = 0; i < BOARD_WIDTH; i++)
		this->lane.push_front(NULL);
	this->isMoveRight = rand() % 2;
	this->delayTime = delayTime;

	this->ID = RIVERLANE_ID;

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
			this->block[i][j] = { FRAME[j][i], LIGHT_GREEN, WHITE };

	//set colors
	for (int i = 0; i < 16; i++)
		block[i][0].bgdColor = LIGHT_GREEN;
	block[2][0].txtColor = SADDLE_BROWN;
	block[2][0].bgdColor = LIGHT_GREEN;
	block[8][0].txtColor = SADDLE_BROWN;
	block[8][0].bgdColor = LIGHT_GREEN;
	block[12][0].txtColor = SADDLE_BROWN;
	block[12][0].bgdColor = LIGHT_GREEN;

	block[0][1].txtColor = WHITE;
	block[0][1].bgdColor = SADDLE_BROWN;
	block[1][1].txtColor = SADDLE_BROWN;
	block[2][1].txtColor = WHITE;
	block[2][1].bgdColor = SADDLE_BROWN;
	block[3][1].txtColor = SADDLE_BROWN;
	block[3][1].bgdColor = LIGHT_GREEN;
	block[4][1].txtColor = WHITE;
	block[4][1].bgdColor = SADDLE_BROWN;
	block[5][1].txtColor = WHITE;
	block[5][1].bgdColor = SADDLE_BROWN;
	block[6][1].txtColor = SADDLE_BROWN;
	block[6][1].bgdColor = LIGHT_GREEN;
	block[7][1].txtColor = SADDLE_BROWN;
	block[7][1].bgdColor = SADDLE_BROWN;
	block[8][1].txtColor = WHITE;
	block[8][1].bgdColor = SADDLE_BROWN;
	block[9][1].txtColor = WHITE;
	block[9][1].bgdColor = SADDLE_BROWN;
	block[10][1].txtColor = SADDLE_BROWN;
	block[10][1].bgdColor = LIGHT_GREEN;
	block[11][1].txtColor = WHITE;
	block[11][1].bgdColor = SADDLE_BROWN;
	block[12][1].txtColor = WHITE;
	block[12][1].bgdColor = SADDLE_BROWN;
	for (int i = 13; i <= 15; i++)
	{
		block[i][1].txtColor = SADDLE_BROWN;
		block[i][1].bgdColor = LIGHT_GREEN;
	}
	block[0][2].txtColor = BLUE;
	block[0][2].bgdColor = DARK_BLUE;
	block[1][2].txtColor = BLUE;
	block[2][2].txtColor = BLUE;
	block[2][2].bgdColor = DARK_BLUE;
	block[3][2].txtColor = DARK_BLUE;
	block[4][2].txtColor = BLUE;
	block[4][2].bgdColor = DARK_BLUE;
	block[5][2].txtColor = BLUE;
	block[5][2].bgdColor = DARK_BLUE;
	block[6][2].txtColor = DARK_BLUE;
	block[7][2].txtColor = DARK_BLUE;
	block[8][2].txtColor = BLUE;
	block[8][2].bgdColor = DARK_BLUE;
	block[9][2].txtColor = BLUE;
	block[9][2].bgdColor = DARK_BLUE;
	block[10][2].txtColor = DARK_BLUE;
	block[11][2].txtColor = BLUE;
	block[11][2].bgdColor = DARK_BLUE;
	block[12][2].txtColor = BLUE;
	block[12][2].bgdColor = DARK_BLUE;
	block[13][2].txtColor = DARK_BLUE;
	block[14][2].txtColor = BLUE;
	block[15][2].txtColor = BLUE;

	block[0][3].txtColor = BLUE;
	block[1][3].txtColor = BLUE;
	for (int i = 2; i <= 4; i++)
		block[i][3].txtColor = BLUE;
	block[5][3].txtColor = BLUE;
	block[6][3].txtColor = BLUE;
	for (int i = 7; i <= 9; i++)
		block[i][3].txtColor = BLUE;
	for (int i = 10; i <= 12; i++)
		block[i][3].txtColor = BLUE;
	block[13][3].txtColor = BLUE;
	block[14][3].txtColor = BLUE;
	block[15][3].txtColor = BLUE;
	for (int i = 0; i < 16; i++)
		block[i][4].txtColor = BLUE;
	for (int i = 8; i <= 10; i++)
		block[i][4].txtColor = BLUE;
	block[12][4].txtColor = BLUE;
	for (int i = 0; i < 16; i++)
		block[i][5].txtColor = BLUE;
	for (int i = 2; i <= 4; i++)
		block[i][5].txtColor = BLUE;
	block[6][5].txtColor = BLUE;
}
void CRIVERLANE::push_frontObject(int ID) {
	if (isMoveRight) {
		switch (ID) {
		case PERRY_ID: {
			lane.push_front(new CPERRY(0, this->y, true));
			break;
		}
		case CAPYBARA_ID: {
			lane.push_front(new CCAPYBARA(0, this->y, true));
			break;
		}
		default:
			lane.push_front(NULL);
		}
	}
	else {
		switch (ID) {
		case PERRY_ID: {
			lane.push_back(new CPERRY(0, this->y, false));
			break;
		}
		case CAPYBARA_ID: {
			lane.push_back(new CCAPYBARA(0, this->y, false));
			break;
		}
		default:
			lane.push_back(NULL);
		}
	}
	updatePosObj();
}
void CRIVERLANE::Move() {
	timeCount++;
	if (timeCount >= delayTime) {
		timeCount = 0;
		//Random push a perry or 1-3 capybaras
		if (condition == 0) {
			int ID = random(OBJECT_ID_LIST);
			pop_backObject();
			push_frontObject(ID);
			switch (ID) {
			case CAPYBARA_ID: {
				countObject = 1;
				numberOfCapybara = 1 + rand() % 4;
				if (numberOfCapybara > 1) condition = CAPYBARA_ID;
				else condition = -CAPYBARA_ID;
				break;
			}
			case PERRY_ID: {
				condition = -PERRY_ID;
				break;
			}
			default:
				condition = 0;
			}
		}
		else {
			switch (condition) {
			case CAPYBARA_ID: {
				pop_backObject();
				push_frontObject(CAPYBARA_ID);
				countObject++;
				if (countObject >= numberOfCapybara) {
					condition = -CAPYBARA_ID;
					countObject = 0;
				}
				break;
			}
			case -CAPYBARA_ID: {
				pop_backObject();
				push_frontObject(random(OBJECT_ID_LIST - vector<int>{CAPYBARA_ID}));
				condition = 0;
				break;
			}
			case -PERRY_ID: {
				pop_backObject();
				push_frontObject(random(OBJECT_ID_LIST - vector<int>{PERRY_ID}));
				condition = 0;
				break;
			} default:
				condition = 0;
			}
		}
	}
}
void CRIVERLANE::injuredPlayer(CPLAYER& player) {
	int i = player.getXBoard();
	if (lane[i] == NULL) {
		player.setAlive(false);
		return;
	}
}