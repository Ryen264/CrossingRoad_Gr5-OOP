//#include "CLANE.h"
//CLANE::CLANE(int x, int y, int delayTime, bool haveLand) {
//	/*for (int i = 0; i < BOARD_WIDTH; i++)
//		this->lane.push_front(NULL);
//	this->isMoveRight = rand() % 2;
//	this->delayTime = delayTime;*/
//
//	this->x = x; this->y = y; this->haveLand = haveLand;
//	vector<wstring> frame = (haveLand) ? FRAME_LAND : FRAME_NOLAND;
//
//	this->block = new PIXEL * [BLOCK_WIDTH * this->numberOfWidth];
//	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
//		this->block[i] = new PIXEL[BLOCK_HEIGHT * this->numberOfHeight];
//
//	//set buffers
//	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
//		for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
//			this->block[i][j] = { frame[j][i], DARK_GREEN, LIGHT_GREEN };
//
//	//set colors
//	if (haveLand) {
//		for (int i = 0; i < 2; i++)
//		{
//			block[i][0].txtColor = LIGHT_GREEN;
//		}
//		block[2][0].txtColor = SADDLE_BROWN;
//		block[2][0].bgdColor = LIGHT_GREEN;
//		for (int i = 3; i <= 7; i++)
//		{
//			block[i][0].txtColor = LIGHT_GREEN;
//		}
//		block[8][0].txtColor = SADDLE_BROWN;
//		block[8][0].bgdColor = LIGHT_GREEN;
//		for (int i = 9; i <= 11; i++)
//		{
//			block[i][0].txtColor = LIGHT_GREEN;
//		}
//		block[12][0].txtColor = SADDLE_BROWN;
//		block[12][0].bgdColor = LIGHT_GREEN;
//		for (int i = 13; i <= 15; i++)
//		{
//			block[i][0].txtColor = LIGHT_GREEN;
//		}
//
//		block[0][1].txtColor = WHITE;
//		block[0][1].bgdColor = SADDLE_BROWN;
//		block[1][1].txtColor = SADDLE_BROWN;
//		block[2][1].txtColor = WHITE;
//		block[2][1].bgdColor = SADDLE_BROWN;
//		block[3][1].txtColor = SADDLE_BROWN;
//		block[3][1].bgdColor = LIGHT_GREEN;
//		block[4][1].txtColor = WHITE;
//		block[4][1].bgdColor = SADDLE_BROWN;
//		block[5][1].txtColor = WHITE;
//		block[5][1].bgdColor = SADDLE_BROWN;
//		block[6][1].txtColor = SADDLE_BROWN;
//		block[6][1].bgdColor = LIGHT_GREEN;
//		block[7][1].txtColor = SADDLE_BROWN;
//		block[7][1].bgdColor = SADDLE_BROWN;
//		block[8][1].txtColor = WHITE;
//		block[8][1].bgdColor = SADDLE_BROWN;
//		block[9][1].txtColor = WHITE;
//		block[9][1].bgdColor = SADDLE_BROWN;
//		block[10][1].txtColor = SADDLE_BROWN;
//		block[10][1].bgdColor = LIGHT_GREEN;
//		block[11][1].txtColor = WHITE;
//		block[11][1].bgdColor = SADDLE_BROWN;
//		block[12][1].txtColor = WHITE;
//		block[12][1].bgdColor = SADDLE_BROWN;
//		for (int i = 13; i <= 15; i++)
//		{
//			block[i][1].txtColor = SADDLE_BROWN;
//			block[i][1].bgdColor = LIGHT_GREEN;
//		}
//		block[0][2].txtColor = BLUE;
//		block[0][2].bgdColor = DARK_BLUE;
//		block[1][2].txtColor = BLUE;
//		block[1][2].bgdColor = WHITE;
//		block[2][2].txtColor = BLUE;
//		block[2][2].bgdColor = DARK_BLUE;
//		block[3][2].txtColor = DARK_BLUE;
//		block[3][2].bgdColor = WHITE;
//		block[4][2].txtColor = BLUE;
//		block[4][2].bgdColor = DARK_BLUE;
//		block[5][2].txtColor = BLUE;
//		block[5][2].bgdColor = DARK_BLUE;
//		block[6][2].txtColor = DARK_BLUE;
//		block[6][2].bgdColor = WHITE;
//		block[7][2].txtColor = DARK_BLUE;
//		block[7][2].bgdColor = WHITE;
//		block[8][2].txtColor = BLUE;
//		block[8][2].bgdColor = DARK_BLUE;
//		block[9][2].txtColor = BLUE;
//		block[9][2].bgdColor = DARK_BLUE;
//		block[10][2].txtColor = DARK_BLUE;
//		block[10][2].bgdColor = WHITE;
//
//		block[11][2].txtColor = BLUE;
//		block[11][2].bgdColor = DARK_BLUE;
//		block[12][2].txtColor = BLUE;
//		block[12][2].bgdColor = DARK_BLUE;
//		block[13][2].txtColor = DARK_BLUE;
//		block[13][2].bgdColor = WHITE;
//		block[14][2].txtColor = BLUE;
//		block[14][2].bgdColor = WHITE;
//		block[15][2].txtColor = BLUE;
//		block[15][2].bgdColor = WHITE;
//
//		block[0][3].txtColor = BLUE;
//		block[1][3].txtColor = BLUE;
//		for (int i = 2; i <= 4; i++)
//		{
//			block[i][3].txtColor = BLUE;
//			block[i][3].bgdColor = WHITE;
//		}
//		block[5][3].txtColor = BLUE;
//		block[6][3].txtColor = BLUE;
//		block[6][3].bgdColor = WHITE;
//		for (int i = 7; i <= 9; i++)
//		{
//			block[i][3].txtColor = BLUE;
//		}
//		for (int i = 10; i <= 12; i++)
//		{
//			block[i][3].txtColor = BLUE;
//			block[i][3].bgdColor = WHITE;
//		}
//		block[13][3].txtColor = BLUE;
//		block[14][3].txtColor = BLUE;
//		block[14][3].bgdColor = WHITE;
//		block[15][3].txtColor = BLUE;
//		for (int i = 0; i < 16; i++)
//		{
//			block[i][4].txtColor = BLUE;
//		}
//		for (int i = 8; i <= 10; i++)
//		{
//			block[i][4].txtColor = BLUE;
//			block[i][4].bgdColor = WHITE;
//		}
//		block[12][4].txtColor = BLUE;
//		block[12][4].bgdColor = WHITE;
//		for (int i = 0; i < 16; i++)
//		{
//			block[i][5].txtColor = BLUE;
//		}
//		for (int i = 2; i <= 4; i++)
//		{
//			block[i][5].txtColor = BLUE;
//			block[i][5].bgdColor = WHITE;
//		}
//		block[6][5].txtColor = BLUE;
//		block[6][5].bgdColor = WHITE;
//	}
//	else {
//		for (int i = 0; i < 2; i++)
//		{
//			block[i][0].txtColor = LIGHT_GREEN;
//		}
//		block[2][0].txtColor = SADDLE_BROWN;
//		block[2][0].bgdColor = LIGHT_GREEN;
//		for (int i = 3; i <= 7; i++)
//		{
//			block[i][0].txtColor = LIGHT_GREEN;
//		}
//		block[8][0].txtColor = SADDLE_BROWN;
//		block[8][0].bgdColor = LIGHT_GREEN;
//		for (int i = 9; i <= 11; i++)
//		{
//			block[i][0].txtColor = LIGHT_GREEN;
//		}
//		block[12][0].txtColor = SADDLE_BROWN;
//		block[12][0].bgdColor = LIGHT_GREEN;
//		for (int i = 13; i <= 15; i++)
//		{
//			block[i][0].txtColor = LIGHT_GREEN;
//		}
//
//
//		block[0][1].txtColor = WHITE;
//		block[0][1].bgdColor = SADDLE_BROWN;
//		block[1][1].txtColor = SADDLE_BROWN;
//		block[2][1].txtColor = WHITE;
//		block[2][1].bgdColor = SADDLE_BROWN;
//		block[3][1].txtColor = SADDLE_BROWN;
//		block[3][1].bgdColor = LIGHT_GREEN;
//		block[4][1].txtColor = WHITE;
//		block[4][1].bgdColor = SADDLE_BROWN;
//		block[5][1].txtColor = WHITE;
//		block[5][1].bgdColor = SADDLE_BROWN;
//		block[6][1].txtColor = SADDLE_BROWN;
//		block[6][1].bgdColor = LIGHT_GREEN;
//		block[7][1].txtColor = SADDLE_BROWN;
//		block[7][1].bgdColor = SADDLE_BROWN;
//		block[8][1].txtColor = WHITE;
//		block[8][1].bgdColor = SADDLE_BROWN;
//		block[9][1].txtColor = WHITE;
//		block[9][1].bgdColor = SADDLE_BROWN;
//		block[10][1].txtColor = SADDLE_BROWN;
//		block[10][1].bgdColor = LIGHT_GREEN;
//		block[11][1].txtColor = WHITE;
//		block[11][1].bgdColor = SADDLE_BROWN;
//		block[12][1].txtColor = WHITE;
//		block[12][1].bgdColor = SADDLE_BROWN;
//		for (int i = 13; i <= 15; i++)
//		{
//			block[i][1].txtColor = SADDLE_BROWN;
//			block[i][1].bgdColor = LIGHT_GREEN;
//		}
//		block[0][2].txtColor = BLUE;
//		block[0][2].bgdColor = DARK_BLUE;
//		block[1][2].txtColor = BLUE;
//		block[1][2].bgdColor = WHITE;
//		block[2][2].txtColor = BLUE;
//		block[2][2].bgdColor = DARK_BLUE;
//		block[3][2].txtColor = DARK_BLUE;
//		block[3][2].bgdColor = WHITE;
//		block[4][2].txtColor = BLUE;
//		block[4][2].bgdColor = DARK_BLUE;
//		block[5][2].txtColor = BLUE;
//		block[5][2].bgdColor = DARK_BLUE;
//		block[6][2].txtColor = DARK_BLUE;
//		block[6][2].bgdColor = WHITE;
//		block[7][2].txtColor = DARK_BLUE;
//		block[7][2].bgdColor = WHITE;
//		block[8][2].txtColor = BLUE;
//		block[8][2].bgdColor = DARK_BLUE;
//		block[9][2].txtColor = BLUE;
//		block[9][2].bgdColor = DARK_BLUE;
//		block[10][2].txtColor = DARK_BLUE;
//		block[10][2].bgdColor = WHITE;
//
//		block[11][2].txtColor = BLUE;
//		block[11][2].bgdColor = DARK_BLUE;
//		block[12][2].txtColor = BLUE;
//		block[12][2].bgdColor = DARK_BLUE;
//		block[13][2].txtColor = DARK_BLUE;
//		block[13][2].bgdColor = WHITE;
//		block[14][2].txtColor = BLUE;
//		block[14][2].bgdColor = WHITE;
//		block[15][2].txtColor = BLUE;
//		block[15][2].bgdColor = WHITE;
//
//		block[0][3].txtColor = BLUE;
//		block[1][3].txtColor = BLUE;
//		for (int i = 2; i <= 4; i++)
//		{
//			block[i][3].txtColor = BLUE;
//			block[i][3].bgdColor = WHITE;
//		}
//		block[5][3].txtColor = BLUE;
//		block[6][3].txtColor = BLUE;
//		block[6][3].bgdColor = WHITE;
//		for (int i = 7; i <= 9; i++)
//		{
//			block[i][3].txtColor = BLUE;
//		}
//		for (int i = 10; i <= 12; i++)
//		{
//			block[i][3].txtColor = BLUE;
//			block[i][3].bgdColor = WHITE;
//		}
//		block[13][3].txtColor = BLUE;
//		block[14][3].txtColor = BLUE;
//		block[14][3].bgdColor = WHITE;
//		block[15][3].txtColor = BLUE;
//		for (int i = 0; i < 16; i++)
//		{
//			block[i][4].txtColor = BLUE;
//		}
//		for (int i = 8; i <= 10; i++)
//		{
//			block[i][4].txtColor = BLUE;
//			block[i][4].bgdColor = WHITE;
//		}
//		block[12][4].txtColor = BLUE;
//		block[12][4].bgdColor = WHITE;
//		for (int i = 0; i < 16; i++)
//		{
//			block[i][5].txtColor = BLUE;
//		}
//		for (int i = 2; i <= 4; i++)
//		{
//			block[i][5].txtColor = BLUE;
//			block[i][5].bgdColor = WHITE;
//		}
//		block[6][5].txtColor = BLUE;
//		block[6][5].bgdColor = WHITE;
//	}
//}
//CLANE::~CLANE() {
//	for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
//		delete[] this->block[i];
//	delete[] this->block;
//}
//void CLANE::DrawBlock(CGRAPHIC& layer) {
//	for (int k = 0; k < BOARD_WIDTH; k++)
//		for (int i = 0; i < BLOCK_WIDTH * this->numberOfWidth; i++)
//			for (int j = 0; j < BLOCK_HEIGHT * this->numberOfHeight; j++)
//				layer.screen[this->x + k * BLOCK_WIDTH * this->numberOfWidth + i][this->y + j] = block[i][j];
//}
