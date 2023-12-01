#include "CUFO.h"
CUFO::CUFO(int x, int y, bool isRight) {
	this->x = x; this->y = y; this->isRight = isRight;
	this->ID = UFO_ID;
	vector<wstring> frame = (isRight) ? FRAME_RIGHT : FRAME_LEFT;
	int WIDTH = 48;
	int HEIGHT = 30;
	this->block = new PIXEL * [WIDTH];
	for (int i = 0; i < WIDTH; i++)
		this->block[i] = new PIXEL[HEIGHT];

	//set buffer
	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
			if (frame[j][i] != ' ')
				this->block[i][j] = { frame[j][i], -1, -1 };
			else
				this->block[i][j] = { frame[j][i], BLACK, -1 };

	//set colors
	if (isRight) {
		for (int i = 17; i < 29; i++)
		{
			block[i][0].bgdColor = SKY_BLUE;
		}

		block[24][0].bgdColor = WHITE;
		block[25][0].bgdColor = WHITE;

		block[15][1].txtColor = BLACK;
		block[15][1].bgdColor = SKY_BLUE;
		for (int i = 16; i < 31; i++)
		{
			block[i][1].txtColor = SKY_BLUE;
		}
		block[30][1].txtColor = BLACK;
		block[30][1].bgdColor = SKY_BLUE;
		block[23][1].bgdColor = SKY_BLUE;
		block[23][1].txtColor = WHITE;
		block[24][1].txtColor = WHITE;
		block[25][1].txtColor = WHITE;
		block[26][1].bgdColor = SKY_BLUE;
		block[26][1].txtColor = WHITE;
		for (int i = 15; i < 31; i++)
		{
			block[i][2].txtColor = SKY_BLUE;
		}
		block[28][2].bgdColor = SKY_BLUE;
		block[28][2].txtColor = WHITE;
		for (int i = 12; i < 34; i++)
		{
			block[i][3].bgdColor = LIGHT_GRAY;
		}
		for (int i = 9; i < 37; i++)
		{
			block[i][4].txtColor = LIGHT_GRAY;
		}
		for (int i = 9; i < 37; i++)
		{
			block[i][5].bgdColor = LIGHT_GRAY;
		}
		for (int i = 12; i < 34; i++)
		{
			block[i][6].bgdColor = LIGHT_GRAY;
		}
		int x1 = 17;
		int x2 = 29;
		int y = 7;
		for (int i = x1; i <= x2; i++)
		{
			block[i][y].txtColor = BRIGHT_YELLOW;

		}
		for (int i = y; i < 23; i++)
		{
			x1--; x2++; y++;
			for (int i = x1; i <= x2; i++)
			{
				block[i][y].txtColor = BRIGHT_YELLOW;

			}
		}
	}
	else {
		for (int i = 17; i < 29; i++)
		{
			block[i][0].bgdColor = SKY_BLUE;
		}

		block[24][0].bgdColor = WHITE;
		block[25][0].bgdColor = WHITE;

		block[15][1].txtColor = BLACK;
		block[15][1].bgdColor = SKY_BLUE;
		for (int i = 16; i < 31; i++)
		{
			block[i][1].txtColor = SKY_BLUE;
		}
		block[30][1].txtColor = BLACK;
		block[30][1].bgdColor = SKY_BLUE;
		block[23][1].bgdColor = SKY_BLUE;
		block[23][1].txtColor = WHITE;
		block[24][1].txtColor = WHITE;
		block[25][1].txtColor = WHITE;
		block[26][1].bgdColor = SKY_BLUE;
		block[26][1].txtColor = WHITE;
		for (int i = 15; i < 31; i++)
		{
			block[i][2].txtColor = SKY_BLUE;
		}
		block[28][2].bgdColor = SKY_BLUE;
		block[28][2].txtColor = WHITE;
		for (int i = 12; i < 34; i++)
		{
			block[i][3].bgdColor = LIGHT_GRAY;
		}
		for (int i = 9; i < 37; i++)
		{
			block[i][4].txtColor = LIGHT_GRAY;
		}
		for (int i = 9; i < 37; i++)
		{
			block[i][5].bgdColor = LIGHT_GRAY;
		}
		for (int i = 12; i < 34; i++)
		{
			block[i][6].bgdColor = LIGHT_GRAY;
		}
		int x1 = 17;
		int x2 = 29;
		int y = 7;
		for (int i = x1; i <= x2; i++)
		{
			block[i][y].txtColor = BRIGHT_YELLOW;

		}
		for (int i = y; i < 23; i++)
		{
			x1--; x2++; y++;
			for (int i = x1; i <= x2; i++)
			{
				block[i][y].txtColor = BRIGHT_YELLOW;

			}
		}
	}
}
