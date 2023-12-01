#include "CDINOSAUR.h"
CDINOSAUR::CDINOSAUR(int x, int y, bool isRight, vector<int> color) : COBJECT(x, y) {
	this->isRight = isRight; this->ID = DINOSAUR_ID;
	vector<wstring> frame = (isRight) ? FRAME_RIGHT : FRAME_LEFT;

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
			if (frame[j][i] != ' ')
				this->block[i][j] = { frame[j][i], BLACK, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };

	//set colors
	setColor(color);
}

void CDINOSAUR::setColor(vector<int> color) {
	this->color = color;
	if (isRight) {
		for (int i = 5; i <= 13; i++) {
			block[i][0].bgdColor = color[0];
			block[i][1].bgdColor = color[0];
			block[i][2].bgdColor = color[0];
			block[i][3].bgdColor = color[0];
		}

		//for (int i = 5; i <= 9; i++)
		//	block[i][3].txtColor = color[0];

		for (int i = 4; i <= 6; i++)
			block[i][4].bgdColor = color[0];
		block[5][4].txtColor = color[0];

		for (int i = 7; i <= 9; i++) {
			block[i][3].bgdColor = color[1];
			block[i][4].bgdColor = color[1];
		}
	}
	else {
		for (int i = 3; i <= 11; i++) {
			block[i][0].bgdColor = color[0];
			block[i][1].bgdColor = color[0];
			block[i][2].bgdColor = color[0];
			block[i][3].bgdColor = color[0];
		}

		//for (int i = 7; i <= 11; i++)
		//	block[i][3].txtColor = color[0];

		for (int i = 10; i <= 12; i++)
			block[i][4].bgdColor = color[0];
		block[11][4].txtColor = color[0];

		for (int i = 7; i <= 9; i++) {
			block[i][3].bgdColor = color[1];
			block[i][4].bgdColor = color[1];
		}
	}
}
