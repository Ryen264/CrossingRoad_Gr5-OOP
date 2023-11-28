#include "CUFO.h"
CUFO::CUFO(int x, int y, bool isRight) {
	this->x = x; this->y = y; this->isRight = isRight;
	this->ID = UFO_ID;
	vector<wstring> frame = (isRight) ? FRAME_RIGHT : FRAME_LEFT;
	int WIDTH = 45;
	int HEIGHT = 55;
	this->block = new PIXEL * [WIDTH];
	for (int i = 0; i < WIDTH; i++)
		this->block[i] = new PIXEL[HEIGHT];

	//set buffer
	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
			if (frame[j][i] != ' ')
				this->block[i][j] = { frame[j][i], BLACK, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };

	//set colors
	if (isRight) {
		
	}
	else {
		
	}
}
