#include "CGRASSLANE.h"
CGRASSLANE::CGRASSLANE(int x, int y) {
    for (int i = 0; i < BOARD_WIDTH; i++)
        this->lane.push_front(NULL);

	this->x = x; this->y = y; this->ID = GRASSLANE_ID;

    this->block = new PIXEL * [BLOCK_WIDTH * this->numberOfWidth];
    for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
        this->block[i] = new PIXEL[BLOCK_HEIGHT * this->numberOfHeight];

    //set buffers
    for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
        for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
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
