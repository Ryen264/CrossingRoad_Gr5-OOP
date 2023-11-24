#include "COBJECT.h"
COBJECT::COBJECT(int x, int y, int isRight) {
	this->x = x; this->y = y; this->isRight = isRight;
	vector<wstring> frame = (isRight) ? FRAME_RIGHT : FRAME_LEFT;

	this->block = new PIXEL * [BLOCK_WIDTH * this->numberOfWidth];
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		this->block[i] = new PIXEL[BLOCK_HEIGHT * this->numberOfHeight];

	//set buffer
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
			if (frame[j][i] != L' ')
				this->block[i][j] = { frame[j][i], RED, -1 };
			else
				this->block[i][j] = { frame[j][i], -1, -1 };

	//set colors
	if (isRight) {

		// VE PERRY

		block[12][2].txtColor = WHITE;
		block[12][2].bgdColor = SKY_BLUE;
		block[13][2].txtColor = BLACK;
		block[13][2].bgdColor = BLACK;
		block[11][2].txtColor = SKY_BLUE;
		block[10][2].txtColor = BLACK;
		block[10][2].bgdColor = SKY_BLUE;
		block[9][2].txtColor = WHITE;
		block[9][2].bgdColor = SKY_BLUE;
		block[8][2].txtColor = SKY_BLUE;
		block[8][3].txtColor = SKY_BLUE;
		block[9][3].txtColor = SKY_BLUE;
		block[9][3].bgdColor = WHITE;
		block[10][3].txtColor = BRIGHT_YELLOW;
		block[10][3].bgdColor = BLACK;
		block[11][3].txtColor = BRIGHT_YELLOW;
		block[12][3].txtColor = BRIGHT_YELLOW;
		block[12][3].bgdColor = WHITE;
		block[13][3].txtColor = BRIGHT_YELLOW;
		block[13][3].bgdColor = BLACK;
		block[14][3].txtColor = BRIGHT_YELLOW;
		block[15][3].txtColor = BRIGHT_YELLOW;
		for (int i = 8; i <= 13; i++)
		{
			block[i][4].txtColor = SKY_BLUE;
		}
		block[4][3].txtColor = BRIGHT_YELLOW;
		block[4][3].bgdColor = ORANGE;
		block[5][3].txtColor = ORANGE;
		block[5][3].bgdColor = BRIGHT_YELLOW;
		block[6][3].txtColor = BRIGHT_YELLOW;
		block[6][3].bgdColor = ORANGE;
		block[7][3].txtColor = ORANGE;
		block[6][4].txtColor = ORANGE;
		block[7][4].txtColor = BRIGHT_YELLOW;

		// VE HOA
        /*block[6][2].txtColor = BRIGHT_YELLOW;
        block[6][2].bgdColor = -1;
        block[7][2].txtColor = RED;
        block[7][2].bgdColor = BRIGHT_YELLOW;
        block[8][2].txtColor = BRIGHT_YELLOW;
        block[8][2].bgdColor = -1;
        block[7][3].txtColor = BRIGHT_YELLOW;
        block[7][3].bgdColor = -1;*/

		//CAPYBARA
		/*block[0][2].txtColor = LIGHT_BROWN;
		block[1][2].txtColor = LIGHT_BROWN;
		block[2][2].txtColor = LIGHT_BROWN;
		block[3][2].txtColor = SADDLE_BROWN;
		for (int i = 4; i <= 8; i++)
		{
			block[i][4].txtColor = LIGHT_BROWN;
		}
		block[0][3].txtColor = LIGHT_BROWN;
		block[1][3].txtColor = LIGHT_BROWN;
		block[2][3].txtColor = SADDLE_BROWN;
		block[2][3].bgdColor = LIGHT_BROWN;
		for (int i = 3; i <= 11; i++)
		{
			block[i][2].txtColor = LIGHT_BROWN;
		}
		block[3][2].txtColor = LIGHT_BROWN;
		block[3][2].bgdColor = SADDLE_BROWN;
		block[4][2].txtColor = SADDLE_BROWN;
		block[5][2].txtColor = LIGHT_BROWN;
		block[5][2].bgdColor = LIGHT_BROWN;
		block[6][2].bgdColor = LIGHT_BROWN;
		block[7][2].txtColor = BLACK;
		block[7][2].bgdColor = LIGHT_BROWN;
		block[8][2].txtColor = LIGHT_BROWN;
		block[9][2].txtColor = LIGHT_BROWN;
		block[10][2].txtColor = LIGHT_BROWN;
		block[10][2].bgdColor = SADDLE_BROWN;
		block[11][2].txtColor = SADDLE_BROWN;
		block[11][2].txtColor = SADDLE_BROWN;
		block[3][1].txtColor = BRIGHT_YELLOW;
		block[4][1].txtColor = BRIGHT_YELLOW;*/

	}
	else {
		// VE PERRY
		block[3][1].txtColor = RED;
		block[3][1].bgdColor = -1;
		block[4][1].txtColor = RED;
		block[4][1].bgdColor = -1;
		block[5][1].txtColor = RED;
		block[5][1].bgdColor = -1;
		block[3][2].txtColor = WHITE;
		block[3][2].bgdColor = SKY_BLUE;
		block[2][2].txtColor = BLACK;
		block[2][2].bgdColor = -1;
		block[4][2].txtColor = SKY_BLUE;
		block[5][2].txtColor = BLACK;
		block[5][2].bgdColor = SKY_BLUE;
		block[6][2].txtColor = WHITE;
		block[6][2].bgdColor = SKY_BLUE;
		block[7][2].txtColor = SKY_BLUE;

		block[0][3].txtColor = BRIGHT_YELLOW;
		block[1][3].txtColor = BRIGHT_YELLOW;
		block[2][3].txtColor = BRIGHT_YELLOW;
		block[2][3].bgdColor = BLACK;
		block[3][3].txtColor = BRIGHT_YELLOW;
		block[3][3].bgdColor = WHITE;
		block[4][3].txtColor = BRIGHT_YELLOW;
		block[5][3].txtColor = BRIGHT_YELLOW;
		block[5][3].bgdColor = BLACK;
		block[6][3].txtColor = BRIGHT_YELLOW;
		block[6][3].bgdColor = WHITE;
		block[7][3].txtColor = SKY_BLUE;
		block[8][3].txtColor = ORANGE;
		block[8][3].bgdColor = -1;
		block[9][3].txtColor = BRIGHT_YELLOW;
		block[9][3].bgdColor = ORANGE;
		block[10][3].txtColor = ORANGE;
		block[10][3].bgdColor = BRIGHT_YELLOW;
		block[11][3].txtColor = BRIGHT_YELLOW;
		block[11][3].bgdColor = ORANGE;
		
		for (int i = 2; i < 8; i++)
		{
			block[i][4].txtColor = SKY_BLUE;
		}
		block[8][4].txtColor = BRIGHT_YELLOW;
		block[9][4].txtColor = ORANGE;

		/*block[7][1].txtColor = SKY_BLUE;
		block[0][2].txtColor = BRIGHT_YELLOW;
		block[1][2].txtColor = BRIGHT_YELLOW;
		block[2][2].txtColor = BRIGHT_YELLOW;
		block[2][2].bgdColor = BLACK;
		block[3][2].txtColor = BRIGHT_YELLOW;
		block[3][2].bgdColor = WHITE;
		block[4][2].txtColor = BRIGHT_YELLOW;
		block[5][2].txtColor = BRIGHT_YELLOW;
		block[5][2].bgdColor = BLACK;
		block[5][2].txtColor = BRIGHT_YELLOW;
		block[5][2].bgdColor = BLACK;
		block[6][2].txtColor = SKY_BLUE;
		block[7][2].txtColor = SKY_BLUE;
		block[8][2].txtColor = ORANGE;
		block[9][2].bgdColor = ORANGE;
		block[9][2].txtColor = BRIGHT_YELLOW;
		block[10][2].bgdColor = BRIGHT_YELLOW;
		block[10][2].txtColor = ORANGE;
		block[11][2].bgdColor = ORANGE;
		block[11][2].txtColor = BRIGHT_YELLOW;
		for (int i = 2; i <= 7; i++)
		{
			block[i][3].txtColor = SKY_BLUE;
		}
		block[8][3].txtColor = BRIGHT_YELLOW;
		block[9][3].txtColor = ORANGE;*/

		//VE HOA
       /* block[6][2].txtColor = RED;
        block[6][2].bgdColor = -1;
        block[7][2].txtColor = BRIGHT_YELLOW;
        block[7][2].bgdColor = RED;
        block[8][2].txtColor = RED;
        block[8][2].bgdColor = -1;
        block[7][3].txtColor = RED;
        block[7][3].bgdColor = -1;*/

		//CAPYBARA
		/*for (int i = 0; i <= 8; i++)
		{
			block[i][3].txtColor = LIGHT_BROWN;
		}
		block[9][3].txtColor = SADDLE_BROWN;
		block[9][3].bgdColor = LIGHT_BROWN;
		block[10][3].txtColor = LIGHT_BROWN;
		block[11][3].txtColor = LIGHT_BROWN;
		for (int i = 3; i <= 7; i++)
		{
			block[i][4].txtColor = LIGHT_BROWN;
		}
		block[8][3].txtColor = SADDLE_BROWN;
		for (int i = 9; i <= 11; i++)
		{
			block[i][4].txtColor = LIGHT_BROWN;
		}
		block[0][2].txtColor = SADDLE_BROWN;
		block[1][2].txtColor = LIGHT_BROWN;
		block[1][2].bgdColor = SADDLE_BROWN;
		block[2][2].txtColor = LIGHT_BROWN;
		block[3][2].txtColor = LIGHT_BROWN;
		block[4][2].bgdColor = LIGHT_BROWN;
		block[4][2].txtColor = BLACK;
		block[5][2].bgdColor = LIGHT_BROWN;
		block[5][2].txtColor = BLACK;
		block[6][2].bgdColor = LIGHT_BROWN;
		block[6][2].txtColor = LIGHT_BROWN;
		block[7][2].txtColor = SADDLE_BROWN;
		block[8][2].txtColor = LIGHT_BROWN;
		block[8][2].bgdColor = SADDLE_BROWN;

		block[8][4].txtColor = LIGHT_BROWN;

		block[7][1].txtColor = BRIGHT_YELLOW;
		block[8][1].txtColor = BRIGHT_YELLOW;*/
	}
}
COBJECT::~COBJECT() {
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		delete[] this->block[i];
	delete[] this->block;
}
void COBJECT::DrawBlock(CGRAPHIC& layer) {
	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
		for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
			layer.screen[this->x + i][this->y + j] = block[i][j];
}
