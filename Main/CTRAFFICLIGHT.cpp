#include "CTRAFFICLIGHT.h"
CTRAFFICLIGHT::CTRAFFICLIGHT(int x, int y) : COBJECT(x, y) {
	this->ID = TRAFFICLIGHT_ID;

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++)
			if (FRAME[j][i] != L' ')
				this->block[i][j] = { FRAME[j][i], BLACK, -1 };
			else
				this->block[i][j] = { FRAME[j][i], -1, -1 };

	//set colors
	block[13][1].bgdColor = (lightColor == RED_TRAFFICLIGHT) ? RED : BLACK;
	block[13][2].bgdColor = (lightColor == YELLOW_TRAFFICLIGHT) ? BRIGHT_YELLOW : BLACK;
	block[13][3].bgdColor = (lightColor == GREEN_TRAFFICLIGHT) ? DARK_GREEN : BLACK;
}

void CTRAFFICLIGHT::setLightColor(int lightColor)
{
	lightColor %= 3;
	this->lightColor = lightColor;
	block[13][1].bgdColor = (lightColor == RED_TRAFFICLIGHT) ? RED : BLACK;
	block[13][2].bgdColor = (lightColor == YELLOW_TRAFFICLIGHT) ? BRIGHT_YELLOW : BLACK;
	block[13][3].bgdColor = (lightColor == GREEN_TRAFFICLIGHT) ? DARK_GREEN : BLACK;
}

PIXEL** CTRAFFICLIGHT::getBlock() const {
	return this->block;
}
