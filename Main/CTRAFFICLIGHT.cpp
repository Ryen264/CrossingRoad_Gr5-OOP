#include "CTRAFFICLIGHT.h"
CTRAFFICLIGHT::CTRAFFICLIGHT(int x, int y) {
	this->x = x; this->y = y; this->ID = TRAFFICLIGHT_ID;

	this->block = new PIXEL * [BLOCK_WIDTH];
	for (int i = 0; i < BLOCK_WIDTH; i++)
		this->block[i] = new PIXEL[BLOCK_HEIGHT];

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
			if (FRAME[j][i] != L' ')
				this->block[i][j] = { FRAME[j][i], RED, -1 };
			else
				this->block[i][j] = { FRAME[j][i], -1, -1 };

	//set colors
	block[12][1].txtColor = BLACK;
	block[13][1].txtColor = BLACK;
	block[13][1].bgdColor = (lightColor == 0) ? RED : BLACK;
	block[14][1].txtColor = BLACK;

	block[12][2].txtColor = BLACK;
	block[13][2].txtColor = BLACK;
	block[13][2].bgdColor = (lightColor == 1) ? BRIGHT_YELLOW : BLACK;
	block[14][2].txtColor = BLACK;

	block[12][3].txtColor = BLACK;
	block[13][3].txtColor = BLACK;
	block[13][3].bgdColor = (lightColor == 2) ? DARK_GREEN : BLACK;
	block[14][3].txtColor = BLACK;

	block[13][4].txtColor = BLACK;
	block[12][4].txtColor = BLACK;
	block[14][4].txtColor = BLACK;
	block[13][5].txtColor = BLACK;
}

void CTRAFFICLIGHT::setLightColor(int lightColor)
{
	lightColor %= 3;
	this->lightColor = lightColor;
	block[13][1].bgdColor = (lightColor == 0) ? RED : BLACK;
	block[13][2].bgdColor = (lightColor == 1) ? BRIGHT_YELLOW : BLACK;
	block[13][3].bgdColor = (lightColor == 2) ? DARK_GREEN : BLACK;
}


