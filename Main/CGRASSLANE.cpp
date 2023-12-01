#include "CGRASSLANE.h"
CGRASSLANE::CGRASSLANE(int x, int y) : CLANE(x, y) {
	bool haveEgg = false, haveTree = false; int countTree = 0;
	for (int i = 0; i < BOARD_WIDTH; i++) {
		//Random push a egg or no more than 3 trees or NULL
		int random = rand() % 20;
		if (random == 0 && !haveEgg) {
			lane.push_front(new CEGG);
			haveEgg = true;
		}
		else if (random % 5 == 0 && !haveTree) {
			lane.push_front(new CTREE(0, this->y));
			countTree++;
			if (countTree >= MAX_NUMBER_OF_TREE) haveTree = true;
		}
		else lane.push_front(NULL);
	}
	updatePosObj();
	
	this->ID = GRASSLANE_ID;

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
            this->block[i][j] = { FRAME[j][i], LIGHT_GREEN, LIGHT_GREEN };
}

void CGRASSLANE::injuredPlayer(CPLAYER& player) {}
