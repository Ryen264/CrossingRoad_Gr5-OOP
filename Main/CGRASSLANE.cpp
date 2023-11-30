#include "CGRASSLANE.h"
CGRASSLANE::CGRASSLANE(int x, int y) {
	bool haveEgg = false;
	for (int i = 0; i < BOARD_WIDTH; i++) {
		if (i == 0 || i == 1) this->lane.push_front(new CTREE_1_BLOCK_2(i * BLOCK_WIDTH, this->y));
		else if (!haveEgg && rand() % 30 == 0) {
			this->lane.push_front(new CEGG(i * BLOCK_WIDTH, this->y));
			haveEgg = true;
		}
		else this->lane.push_front(NULL);
	}
	
	this->x = x ; this->y = y; this->ID = GRASSLANE_ID;

	this->block = new PIXEL * [BLOCK_WIDTH];
	for (int i = 0; i < BLOCK_WIDTH; i++)
		this->block[i] = new PIXEL[BLOCK_HEIGHT];

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
            this->block[i][j] = { FRAME[j][i], DARK_GREEN, LIGHT_GREEN };

    //set colors
	/*for (int i = 9; i <= 11; i++)
	{
		block[i][0].txtColor = DARK_GREEN;
	}
	block[3][0].txtColor = LIGHT_GREEN;
	block[3][0].bgdColor = LIGHT_GREEN;
	block[4][0].txtColor = WHITE;
	block[4][0].bgdColor = LIGHT_GREEN;

	block[3][1].txtColor = WHITE;
	block[3][1].bgdColor = LIGHT_GREEN;
	block[4][1].txtColor = RED;
	block[4][1].bgdColor = WHITE;
	block[5][1].txtColor = WHITE;
	block[5][1].bgdColor = LIGHT_GREEN;
	block[12][1].txtColor = WHITE;
	block[12][1].bgdColor = LIGHT_GREEN;

	block[11][2].txtColor = WHITE;
	block[11][2].bgdColor = LIGHT_GREEN;
	block[12][2].txtColor = ORANGE;
	block[12][2].bgdColor = WHITE;
	block[13][2].txtColor = WHITE;
	block[13][2].bgdColor = LIGHT_GREEN;

	block[3][3].txtColor = WHITE;
	block[3][3].bgdColor = LIGHT_GREEN;
	block[4][3].txtColor = LIGHT_GREEN;
	block[4][3].bgdColor = LIGHT_GREEN;

	block[2][4].txtColor = WHITE;
	block[3][4].txtColor = BRIGHT_YELLOW;
	block[3][4].bgdColor = WHITE;
	block[4][4].txtColor = WHITE;*/

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			block[i][j].txtColor = LIGHT_GREEN;
		}
	}
}
void CGRASSLANE::injuredPlayer(CPLAYER& player) {
	int i = player.getX();
	if (lane[i] == NULL) return;
	switch (lane[i]->getID()) {
	case EGG_ID: {
		player.increaseScore(10);
		COBJECT* tmp = lane[i];
		if (tmp != NULL) delete tmp;
		lane[i] = tmp = NULL;
		break;
	}
	}
}

