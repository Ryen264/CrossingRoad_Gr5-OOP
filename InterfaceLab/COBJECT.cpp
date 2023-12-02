//#include "COBJECT.h"
//COBJECT::COBJECT(int x, int y, int isRight) {
//	this->x = x; this->y = y; this->isRight = isRight;
//	vector<wstring> frame = (isRight) ? FRAME;
//	
//	WIDTH = 16;
//	HEIGHT = 4;
//
//	this->block = new PIXEL * [WIDTH];
//	for (int i = 0; i <WIDTH; i++)
//		this->block[i] = new PIXEL[HEIGHT];
//
//	//set buffer
//	for (int i = 0; i < WIDTH; i++)
//		for (int j = 0; j < HEIGHT; j++)
//			if (frame[j][i] != L' ')
//				this->block[i][j] = { frame[j][i], -1, -1 };
//			else
//				this->block[i][j] = { frame[j][i], BLACK, WHITE };
//
//	//set colors
//
//	if (isRight) {
//		//CLOUD 2
//		block[2][0].bgdColor = -1;
//		block[3][0].bgdColor = -1;
//		block[5][0].bgdColor = -1;
//		block[8][0].bgdColor = -1;
//		block[10][0].bgdColor = -1;
//		block[11][0].bgdColor = -1;
//		block[12][0].bgdColor = -1;
//		for (int i = 1; i < 15; i++)
//		{
//			block[i][1].bgdColor = WHITE;
//		}
//		block[0][1].bgdColor = -1;
//		block[15][1].bgdColor = -1;
//		for (int i = 1; i < 14; i++)
//		{
//			block[i][2].bgdColor = WHITE;
//			block[i][2].txtColor = WHITE;
//		}
//		block[1][3].bgdColor - 1;
//		block[14][3].bgdColor - 1;
//		for (int i = 2; i < 14; i++)
//		{
//			block[i][3].bgdColor = WHITE;
//		}
//		//CLOUD 1
//		/*block[5][0].bgdColor = -1;
//		block[6][0].bgdColor = WHITE;
//		block[7][0].bgdColor = WHITE;
//		block[8][0].bgdColor = -1;
//		block[1][1].bgdColor = -1;
//		block[14][1].bgdColor = -1;
//		for (int i = 2; i < 14; i++)
//		{
//			block[i][1].bgdColor = WHITE;
//		}
//		for (int i = 1; i < 14; i++)
//		{
//			block[i][2].bgdColor = WHITE;
//			block[i][2].txtColor = WHITE;
//		}
//		block[1][3].bgdColor = -1;
//		block[14][3].bgdColor = -1;
//		for (int i = 2; i < 14; i++)
//		{
//			block[i][3].bgdColor = WHITE;
//		}*/
//		//HAT
//		/*block[6][0].txtColor = SADDLE_BROWN;
//		block[6][0].bgdColor = -1;
//		block[7][0].txtColor = SADDLE_BROWN;
//		block[8][0].txtColor = SADDLE_BROWN;
//		block[9][0].txtColor = SADDLE_BROWN;
//		block[0][0].bgdColor = -1;
//
//		block[4][1].txtColor = BLACK;
//		block[4][1].bgdColor = -1;
//		block[5][1].txtColor = SADDLE_BROWN;
//		block[5][1].bgdColor = BLACK;
//		block[6][1].txtColor = SADDLE_BROWN;
//		block[6][1].bgdColor = BLACK;
//		block[7][1].txtColor = SADDLE_BROWN;
//		block[7][1].bgdColor = BLACK;
//		block[8][1].txtColor = SADDLE_BROWN;
//		block[8][1].bgdColor = BLACK;
//		for (int i = 9; i < 12; i++)
//		{
//			block[i][1].txtColor = SADDLE_BROWN;
//		}
//		block[0][2].txtColor = SADDLE_BROWN;
//		block[1][2].txtColor = SADDLE_BROWN;
//		block[2][2].txtColor = SADDLE_BROWN;
//		block[2][2].bgdColor = -1;
//		block[3][2].txtColor = SADDLE_BROWN;
//		block[3][2].bgdColor = -1;
//		block[4][2].txtColor = BLACK;
//		block[4][2].bgdColor = SADDLE_BROWN;
//		block[5][2].txtColor = BLACK;
//		block[5][2].bgdColor = SADDLE_BROWN;
//
//		for (int i = 6; i < 11; i++)
//		{
//			block[i][2].txtColor = BLACK;
//		}
//		block[11][2].txtColor = BLACK;
//		block[11][2].bgdColor = SADDLE_BROWN;
//		for (int i = 1; i <= 14; i++)
//		{
//			block[i][3].txtColor = SADDLE_BROWN;
//			block[i][3].bgdColor = -1;
//		}
//		for (int i = 5; i < 13; i++)
//		{
//			block[i][4].txtColor = SADDLE_BROWN;
//			block[i][4].bgdColor = -1;
//		}*/
//		//BIG DINOSAUR
//		/*for (int i = 23; i < 39; i++)
//		{
//			block[i][0].bgdColor = DARK_GREEN;
//		}
//		for (int i = 21; i < 41; i++)
//		{
//			block[i][1].bgdColor = DARK_GREEN;
//		}
//		for (int j = 2; j < 7; j++)
//		{
//			for (int i = 21; i < 41; i++)
//			{
//				block[i][j].bgdColor = DARK_GREEN;
//			}
//		}
//		for (int i = 21; i < 37; i++)
//		{
//			block[i][7].bgdColor = DARK_GREEN;
//		}
//		for (int i = 20; i < 37; i++)
//		{
//			block[i][8].bgdColor = DARK_GREEN;
//		}
//		block[1][8].bgdColor = DARK_GREEN;
//		block[2][8].bgdColor = DARK_GREEN;
//		for (int i = 17; i < 31; i++)
//		{
//			block[i][9].bgdColor = DARK_GREEN;
//		}
//		block[1][9].bgdColor = DARK_GREEN;
//		block[2][9].bgdColor = DARK_GREEN;
//		for (int i = 13; i < 35; i++)
//		{
//			block[i][10].bgdColor = DARK_GREEN;
//		}
//		block[1][10].bgdColor = DARK_GREEN;
//		block[2][10].bgdColor = DARK_GREEN;
//		block[3][10].bgdColor = DARK_GREEN;
//		block[4][10].bgdColor = DARK_GREEN;
//		for (int i = 11; i < 26; i++)
//		{
//			block[i][11].bgdColor = DARK_GREEN;
//		}
//		for (int i = 26; i < 31; i++)
//		{
//			block[i][11].bgdColor = DARK_GREEN;
//			block[i][11].txtColor = LIGHT_GREEN;
//		}
//		for (int i = 31; i < 35; i++)
//		{
//			block[i][11].bgdColor = DARK_GREEN;
//		}
//		block[1][11].bgdColor = DARK_GREEN;
//		block[2][11].bgdColor = DARK_GREEN;
//		block[3][11].bgdColor = DARK_GREEN;
//		block[4][11].bgdColor = DARK_GREEN;
//		block[5][11].bgdColor = DARK_GREEN;
//		block[6][11].bgdColor = DARK_GREEN;
//		for (int i = 23; i < 31; i++)
//		{
//			block[i][12].txtColor = LIGHT_GREEN;
//		}
//		block[34][12].bgdColor = DARK_GREEN;
//		block[33][12].bgdColor = DARK_GREEN;
//		for (int i = 1; i < 24; i++)
//		{
//			block[i][12].bgdColor = DARK_GREEN;
//		}
//		for (int i = 21; i < 31; i++)
//		{
//			block[i][13].txtColor = LIGHT_GREEN;
//		}
//		for (int i = 1; i < 22; i++)
//		{
//			block[i][13].bgdColor = DARK_GREEN;
//		}
//		for (int i = 21; i < 31; i++)
//		{
//			block[i][14].txtColor = LIGHT_GREEN;
//		}
//		for (int i = 2; i < 22; i++)
//		{
//			block[i][14].bgdColor = DARK_GREEN;
//		}
//		for (int i = 3; i < 22; i++)
//		{
//			block[i][15].bgdColor = DARK_GREEN;
//		}
//		for (int i = 21; i < 29; i++)
//		{
//			block[i][15].txtColor = LIGHT_GREEN;
//		}
//		for (int i = 4; i < 27; i++)
//		{
//			block[i][16].bgdColor = DARK_GREEN;
//		}
//		for (int i = 5; i < 25; i++)
//		{
//			block[i][17].bgdColor = DARK_GREEN;
//		}
//		for (int i = 11; i < 23; i++)
//		{
//			block[i][18].bgdColor = DARK_GREEN;
//		}
//		for (int i = 14; i < 19; i++)
//		{
//			block[i][18].bgdColor = -1;
//		}
//		block[11][19].bgdColor = DARK_GREEN;
//		block[12][19].bgdColor = DARK_GREEN;
//		block[20][19].bgdColor = DARK_GREEN;
//		block[21][19].bgdColor = DARK_GREEN;
//		
//		/*for (int j = 19; j < 22; j++)
//		{
//
//		}*/
//		//PICTURE DINOSAUR
//		/*for (int i = 9; i < 12; i++)
//		{
//			block[i][0].bgdColor = SADDLE_BROWN;
//		}
//		for (int j = 2; j < 11; j++)
//		{
//			block[0][j].txtColor = LIGHT_BROWN;
//			block[20][j].txtColor = LIGHT_BROWN;
//		}
//		for (int i = 1; i < 20; i++)
//		{
//			block[i][10].txtColor = LIGHT_BROWN;
//		}
//		for (int i = 0; i < 5; i++)
//		{
//			block[i][1].txtColor = LIGHT_BROWN;
//		}
//		block[5][1].bgdColor = LIGHT_BROWN;
//		block[6][1].bgdColor = LIGHT_BROWN;
//		for (int i = 7; i < 14; i++)
//		{
//			block[i][1].txtColor = LIGHT_BROWN;
//			block[i][1].bgdColor = SADDLE_BROWN;
//		}
//		block[14][1].bgdColor = LIGHT_BROWN;
//		block[15][1].bgdColor = LIGHT_BROWN;
//		for (int i = 16; i < 21; i++)
//		{
//			block[i][1].txtColor = LIGHT_BROWN;
//		}
//		for (int i = 1; i < 21; i++)
//		{
//			block[i][2].bgdColor = WHITE;
//		}
//		for (int i = 1; i < 5; i++)
//		{
//			block[i][3].bgdColor = WHITE;
//		}
//		block[5][3].bgdColor = WHITE;
//		for (int i = 6; i < 15; i++)
//		{
//			block[i][3].bgdColor = DARK_GREEN;
//		}
//		for (int i = 6; i < 15; i++)
//		{
//			block[i][4].bgdColor = DARK_GREEN;
//		}
//		for (int i = 6; i < 15; i++)
//		{
//			block[i][5].bgdColor = DARK_GREEN;
//		}
//		for (int i = 6; i < 15; i++)
//		{
//			block[i][6].bgdColor = DARK_GREEN;
//		}
//		for (int i = 8; i < 11; i++)
//		{
//			block[i][6].txtColor = DARK_GREEN;
//			block[i][6].bgdColor = LIGHT_GREEN;
//		}
//		block[4][6].bgdColor = DARK_GREEN;
//		for (int i = 8; i < 11; i++)
//		{
//			block[i][7].bgdColor = LIGHT_GREEN;
//		}
//		block[5][7].bgdColor = DARK_GREEN;
//		block[6][7].bgdColor = DARK_GREEN;
//		block[7][7].bgdColor = DARK_GREEN;*/	
//		//DRAWER
//		/*for (int j = 1; j < 26; j++)
//		{
//			for (int i = 1; i < 8; i++)
//			{
//				block[i][j].txtColor = SADDLE_BROWN;
//			}
//		}
//		for (int i = 1; i < 8; i++)
//		{
//			block[i][0].bgdColor = SADDLE_BROWN;
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][0].bgdColor = LIGHT_BROWN;
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][1].txtColor = LIGHT_BROWN;
//		}
//		for (int i = 17; i < 21; i++)
//		{
//			block[i][1].txtColor = LIGHT_BROWN;
//			block[i][1].bgdColor = SADDLE_BROWN;
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][2].txtColor = LIGHT_BROWN;
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][3].txtColor = LIGHT_BROWN;	
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][4].bgdColor = LIGHT_BROWN;
//		}
//		block[26][4].bgdColor = BLACK;
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][5].txtColor = LIGHT_BROWN;
//		}
//		for (int i = 17; i < 21; i++)
//		{
//			block[i][5].txtColor = SADDLE_BROWN;
//			block[i][5].bgdColor = LIGHT_BROWN;
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][6].txtColor =LIGHT_BROWN;
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][7].txtColor = LIGHT_BROWN;
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][8].bgdColor = LIGHT_BROWN;
//		}
//		block[26][8].bgdColor =BLACK;
//		for (int j = 9; j < 13; j++)
//		{
//			for (int i = 8; i < 26; i++)
//			{
//				block[i][j].txtColor = LIGHT_BROWN;
//			}
//		}
//		for (int i = 17; i < 21; i++)
//		{
//			block[i][10].bgdColor = LIGHT_BROWN;
//			block[i][10].txtColor = SADDLE_BROWN;
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][13].bgdColor = LIGHT_BROWN;
//		}
//		block[26][13].bgdColor = BLACK;
//		for (int j = 14; j < 17; j++)
//		{
//			for (int i = 8; i < 26; i++)
//			{
//				block[i][j].txtColor = LIGHT_BROWN;
//			}
//		}
//		for (int i = 17; i < 21; i++)
//		{
//			block[i][14].txtColor = SADDLE_BROWN;
//			block[i][14].bgdColor = LIGHT_BROWN;
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][17].bgdColor = LIGHT_BROWN;
//		}
//		block[26][17].bgdColor = BLACK;
//		for (int j = 18; j < 22; j++)
//		{
//			for (int i = 8; i < 26; i++)
//			{
//				block[i][j].txtColor = LIGHT_BROWN;
//			}
//		}
//		for (int i = 17; i < 21; i++)
//		{
//			block[i][19].txtColor = SADDLE_BROWN;
//			block[i][19].bgdColor = LIGHT_BROWN;
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][22].bgdColor = LIGHT_BROWN;
//		}
//		block[26][22].bgdColor = BLACK;
//		for (int j = 23; j < 26; j++)
//		{
//			for (int i = 8; i < 26; i++)
//			{
//				block[i][j].txtColor = LIGHT_BROWN;
//			}
//		}
//		for (int i = 17; i < 21; i++)
//		{
//			block[i][23].txtColor = SADDLE_BROWN;
//			block[i][23].bgdColor = LIGHT_BROWN;
//		}
//		/*for (int i = 8; i < 26; i++)
//		{
//			block[i][0].bgdColor = LIGHT_BROWN;
//		}
//		for (int j = 1; j < 3; j++)
//		{
//			for (int i = 8; i < 26; i++)
//			{
//				block[i][j].bgdColor = LIGHT_BROWN;
//				block[i][j].txtColor = SADDLE_BROWN;
//			}
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][3].bgdColor = LIGHT_BROWN;
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][4].bgdColor = LIGHT_BROWN;
//		}
//		block[26][4].bgdColor = BLACK;
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][5].bgdColor = LIGHT_BROWN;
//			block[i][5].txtColor = SADDLE_BROWN;
//		}
//		for (int j = 6; j < 8; j++)
//		{
//			for (int i = 8; i < 26; i++)
//			{
//				block[i][j].bgdColor = LIGHT_BROWN;
//			}
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][8].bgdColor = LIGHT_BROWN;
//		}
//		block[26][8].bgdColor = BLACK;
//		for (int j = 9; j < 13; j++)
//		{
//			for (int i = 8; i < 26; i++)
//			{
//				block[i][j].bgdColor = LIGHT_BROWN;
//				block[i][j].txtColor = SADDLE_BROWN;
//			}
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][13].bgdColor = LIGHT_BROWN;
//		}
//		block[26][13].bgdColor = BLACK;
//		for (int j = 14; j < 17; j++)
//		{
//			for (int i = 8; i < 26; i++)
//			{
//				block[i][j].bgdColor = LIGHT_BROWN;
//				block[i][j].txtColor = SADDLE_BROWN;
//			}
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][17].bgdColor = LIGHT_BROWN;
//		}
//		block[26][17].bgdColor = BLACK;
//		for (int j = 18; j < 22; j++)
//		{
//			for (int i = 8; i < 26; i++)
//			{
//				block[i][j].bgdColor = LIGHT_BROWN;
//				block[i][j].txtColor = SADDLE_BROWN;
//			}
//		}
//		for (int i = 8; i < 26; i++)
//		{
//			block[i][22].bgdColor = LIGHT_BROWN;
//		}
//		block[26][22].bgdColor = BLACK;
//		for (int j = 23; j < 26; j++)
//		{
//			for (int i = 8; i < 26; i++)
//			{
//				block[i][j].bgdColor = LIGHT_BROWN;
//				block[i][j].txtColor = SADDLE_BROWN;
//			}
//		}*/
//		//SMALL DRAWER
//		/*block[16][0].bgdColor = BRIGHT_YELLOW;
//		block[17][0].bgdColor = BRIGHT_YELLOW;
//		for (int i = 18; i < 26; i++)
//		{
//			block[i][0].bgdColor = WHITE;
//		}
//			block[26][0].bgdColor = BRIGHT_YELLOW;
//			block[27][0].bgdColor = BRIGHT_YELLOW;
//			// X 15 28
//			// Y 1  2
//			for (int j = 1; j < 3; j++)
//			{
//				for (int i = 15; i < 29; i++)
//				{
//					block[i][j].txtColor = BRIGHT_YELLOW;
//				}
//			}
//
//		for (int i = 1; i < 13; i++)
//		{
//			block[i][3].bgdColor = SADDLE_BROWN;
//		}
//		for (int j = 4; j < 7; j++)
//		{
//			for (int i = 1; i < 13; i++)
//			{
//				block[i][j].txtColor = SADDLE_BROWN;
//			}
//		}
//		for (int i = 13; i < 33; i++)
//		{
//			block[i][3].bgdColor = LIGHT_BROWN;
//		}
//		for (int i = 13; i < 22; i++)
//		{
//			block[i][4].txtColor = LIGHT_BROWN;
//		}
//		for (int i = 22; i < 26; i++)
//		{
//			block[i][4].txtColor = LIGHT_BROWN;
//			block[i][4].bgdColor = SADDLE_BROWN;
//		}
//		for (int i = 22; i < 32; i++)
//		{
//			block[i][4].txtColor = LIGHT_BROWN;
//		}
//		for (int j = 5; j < 7; j++)
//		{
//			for (int i = 13; i < 32; i++)
//			{
//				block[i][j].txtColor = LIGHT_BROWN;
//			}
//		}
//		for (int i = 1; i < 32; i++)
//		{
//			block[i][7].bgdColor = SADDLE_BROWN;
//		}*/
//		//VE UF0
//	    /*for (int i = 17; i < 29; i++)
//		{
//			block[i][0].bgdColor = SKY_BLUE;
//		}
//		
//		block[24][0].bgdColor = WHITE;
//		block[25][0].bgdColor = WHITE;
//
//		block[15][1].txtColor = BLACK;
//		block[15][1].bgdColor = SKY_BLUE;
//		for (int i = 16; i < 31; i++)
//		{
//			block[i][1].txtColor = SKY_BLUE;
//		}
//		block[30][1].txtColor = BLACK;
//		block[30][1].bgdColor = SKY_BLUE;
//		block[23][1].bgdColor = SKY_BLUE;
//		block[23][1].txtColor = WHITE;
//		block[24][1].txtColor = WHITE;
//		block[25][1].txtColor = WHITE;
//		block[26][1].bgdColor = SKY_BLUE;
//		block[26][1].txtColor = WHITE;
//		for (int i = 15; i < 31; i++)
//		{
//			block[i][2].txtColor = SKY_BLUE;
//		}
//		block[28][2].bgdColor = SKY_BLUE;
//		block[28][2].txtColor = WHITE;
//		for (int i = 12; i < 34; i++)
//		{
//			block[i][3].bgdColor = LIGHT_GRAY;
//		}
//		for (int i = 9; i < 37; i++)
//		{
//			block[i][4].txtColor = LIGHT_GRAY;
//		}
//		for (int i = 9; i < 37; i++)
//		{
//			block[i][5].bgdColor = LIGHT_GRAY;
//		}
//		for (int i = 12; i < 34; i++)
//		{
//			block[i][6].bgdColor = LIGHT_GRAY;
//		}
//		int x1 = 17;
//		int x2 = 29;
//		int y = 7;
//		for (int i = x1; i <= x2; i++)
//		{
//			block[i][y].txtColor = BRIGHT_YELLOW;
//
//		}
//		for (int i = y; i < 23; i++)
//		{
//			x1--; x2++; y++;
//			for (int i = x1; i <= x2; i++)
//			{
//				block[i][y].txtColor = BRIGHT_YELLOW;
//
//			}
//		}*/
//		//VE TRUNG
//		/*block[5][1].txtColor = BLACK;
//		block[5][1].bgdColor = -1;
//		block[6][1].txtColor = BLACK;
//		block[6][1].bgdColor = WHITE;
//		block[7][1].txtColor = BLACK;
//		block[7][1].bgdColor = WHITE;
//		block[8][1].txtColor = BLACK;
//		block[8][1].bgdColor = -1;
//
//		block[4][2].txtColor = BLACK;
//		for (int i = 5; i < 9; i++)
//		{
//			block[i][2].txtColor = WHITE;
//		}
//		block[9][2].txtColor = BLACK;
//
//		block[4][3].txtColor = BLACK;
//		block[4][3].bgdColor = -1;
//		block[5][3].txtColor = BLACK;
//		block[5][3].bgdColor = WHITE;
//		block[6][3].txtColor = WHITE;
//		block[7][3].txtColor = WHITE;
//		block[8][3].txtColor = BLACK;
//		block[8][3].bgdColor = WHITE;
//		block[9][3].txtColor = BLACK;
//		block[9][3].bgdColor = -1;
//
//		block[6][4].txtColor = BLACK;
//		block[6][4].bgdColor = -1;
//		block[7][4].txtColor = BLACK;
//		block[7][4].bgdColor = -1;*/
//		// VE PERRY
//		/*block[12][2].txtColor = WHITE;
//		block[12][2].bgdColor = SKY_BLUE;
//		block[13][2].txtColor = BLACK;
//		block[13][2].bgdColor = BLACK;
//		block[11][2].txtColor = SKY_BLUE;
//		block[10][2].txtColor = BLACK;
//		block[10][2].bgdColor = SKY_BLUE;
//		block[9][2].txtColor = WHITE;
//		block[9][2].bgdColor = SKY_BLUE;
//		block[8][2].txtColor = SKY_BLUE;
//		block[8][3].txtColor = SKY_BLUE;
//		block[9][3].txtColor = SKY_BLUE;
//		block[9][3].bgdColor = WHITE;
//		block[10][3].txtColor = BRIGHT_YELLOW;
//		block[10][3].bgdColor = BLACK;
//		block[11][3].txtColor = BRIGHT_YELLOW;
//		block[12][3].txtColor = BRIGHT_YELLOW;
//		block[12][3].bgdColor = WHITE;
//		block[13][3].txtColor = BRIGHT_YELLOW;
//		block[13][3].bgdColor = BLACK;
//		block[14][3].txtColor = BRIGHT_YELLOW;
//		block[15][3].txtColor = BRIGHT_YELLOW;
//		for (int i = 8; i <= 13; i++)
//		{
//			block[i][4].txtColor = SKY_BLUE;
//		}
//		block[4][3].txtColor = BRIGHT_YELLOW;
//		block[4][3].bgdColor = ORANGE;
//		block[5][3].txtColor = ORANGE;
//		block[5][3].bgdColor = BRIGHT_YELLOW;
//		block[6][3].txtColor = BRIGHT_YELLOW;
//		block[6][3].bgdColor = ORANGE;
//		block[7][3].txtColor = ORANGE;
//		block[6][4].txtColor = ORANGE;
//		block[7][4].txtColor = BRIGHT_YELLOW;*/
//		// VE HOA
//        /*block[6][2].txtColor = BRIGHT_YELLOW;
//        block[6][2].bgdColor = -1;
//        block[7][2].txtColor = RED;
//        block[7][2].bgdColor = BRIGHT_YELLOW;
//        block[8][2].txtColor = BRIGHT_YELLOW;
//        block[8][2].bgdColor = -1;
//        block[7][3].txtColor = BRIGHT_YELLOW;
//        block[7][3].bgdColor = -1;*/
//		//CAPYBARA
//		/*block[0][2].txtColor = LIGHT_BROWN;
//		block[1][2].txtColor = LIGHT_BROWN;
//		block[2][2].txtColor = LIGHT_BROWN;
//		block[3][2].txtColor = SADDLE_BROWN;
//		for (int i = 4; i <= 8; i++)
//		{
//			block[i][4].txtColor = LIGHT_BROWN;
//		}
//		block[0][3].txtColor = LIGHT_BROWN;
//		block[1][3].txtColor = LIGHT_BROWN;
//		block[2][3].txtColor = SADDLE_BROWN;
//		block[2][3].bgdColor = LIGHT_BROWN;
//		for (int i = 3; i <= 11; i++)
//		{
//			block[i][2].txtColor = LIGHT_BROWN;
//		}
//		block[3][2].txtColor = LIGHT_BROWN;
//		block[3][2].bgdColor = SADDLE_BROWN;
//		block[4][2].txtColor = SADDLE_BROWN;
//		block[5][2].txtColor = LIGHT_BROWN;
//		block[5][2].bgdColor = LIGHT_BROWN;
//		block[6][2].bgdColor = LIGHT_BROWN;
//		block[7][2].txtColor = BLACK;
//		block[7][2].bgdColor = LIGHT_BROWN;
//		block[8][2].txtColor = LIGHT_BROWN;
//		block[9][2].txtColor = LIGHT_BROWN;
//		block[10][2].txtColor = LIGHT_BROWN;
//		block[10][2].bgdColor = SADDLE_BROWN;
//		block[11][2].txtColor = SADDLE_BROWN;
//		block[11][2].txtColor = SADDLE_BROWN;
//		block[3][1].txtColor = BRIGHT_YELLOW;
//		block[4][1].txtColor = BRIGHT_YELLOW;*/
//		//VE DUONG
//		/*block[0][0].txtColor = WHITE;
//		//block[15][0].txtColor = WHITE;
//		//for (int i = 1; i < 14; i+=4)
//		//{
//		//	block[i][0].txtColor = BLACK;
//		//	block[i+1][0].txtColor = BLACK;
//		//}
//		//for (int i = 3; i < 12; i += 4)
//		//{
//		//	block[i][0].txtColor = WHITE;
//		//	block[i + 1][0].txtColor = WHITE;
//		//}
//
//		//block[0][1].txtColor = BLACK;
//		//block[15][1].txtColor = BLACK;
//		//for (int i = 1; i < 14; i += 4)
//		//{
//		//	block[i][1].txtColor = WHITE;
//		//	block[i + 1][1].txtColor = WHITE;
//		//}
//		//for (int i = 3; i < 12; i += 4)
//		//{
//		//	block[i][1].txtColor = BLACK;
//		//	block[i + 1][1].txtColor = BLACK;
//		//}
//
//		//block[0][2].txtColor = WHITE;
//		//block[15][2].txtColor = WHITE;
//		//for (int i = 1; i < 14; i += 4)
//		//{
//		//	block[i][2].txtColor = BLACK;
//		//	block[i + 1][2].txtColor = BLACK;
//		//}
//		//for (int i = 3; i < 12; i += 4)
//		//{
//		//	block[i][2].txtColor = WHITE;
//		//	block[i + 1][2].txtColor = WHITE;
//		//}
//
//		//block[0][3].txtColor = BLACK;
//		//block[15][3].txtColor = BLACK;
//		//for (int i = 1; i < 14; i += 4)
//		//{
//		//	block[i][3].txtColor = WHITE;
//		//	block[i + 1][3].txtColor = WHITE;
//		//}
//		//for (int i = 3; i < 12; i += 4)
//		//{
//		//	block[i][3].txtColor = BLACK;
//		//	block[i + 1][3].txtColor = BLACK;
//		//}
//
//		//block[0][4].txtColor = WHITE;
//		//block[15][4].txtColor = WHITE;
//		//for (int i = 1; i < 14; i += 4)
//		//{
//		//	block[i][4].txtColor = BLACK;
//		//	block[i + 1][4].txtColor = BLACK;
//		//}
//		//for (int i = 3; i < 12; i += 4)
//		//{
//		//	block[i][4].txtColor = WHITE;
//		//	block[i + 1][4].txtColor = WHITE;
//		//}
//
//		//block[0][5].txtColor = BLACK;
//		//block[15][5].txtColor = BLACK;
//		//for (int i = 1; i < 14; i += 4)
//		//{
//		//	block[i][5].txtColor = WHITE;
//		//	block[i + 1][5].txtColor = WHITE;
//		//}
//		//for (int i = 3; i < 12; i += 4)
//		//{
//		//	block[i][5].txtColor = BLACK;
//		//	block[i + 1][5].txtColor = BLACK;
//		//}*/
//	}
//	else {
//		// VE PERRY
//		/*block[3][1].txtColor = RED;
//		block[3][1].bgdColor = -1;
//		block[4][1].txtColor = RED;
//		block[4][1].bgdColor = -1;
//		block[5][1].txtColor = RED;
//		block[5][1].bgdColor = -1;
//		block[3][2].txtColor = WHITE;
//		block[3][2].bgdColor = SKY_BLUE;
//		block[2][2].txtColor = BLACK;
//		block[2][2].bgdColor = -1;
//		block[4][2].txtColor = SKY_BLUE;
//		block[5][2].txtColor = BLACK;
//		block[5][2].bgdColor = SKY_BLUE;
//		block[6][2].txtColor = WHITE;
//		block[6][2].bgdColor = SKY_BLUE;
//		block[7][2].txtColor = SKY_BLUE;
//
//		block[0][3].txtColor = BRIGHT_YELLOW;
//		block[1][3].txtColor = BRIGHT_YELLOW;
//		block[2][3].txtColor = BRIGHT_YELLOW;
//		block[2][3].bgdColor = BLACK;
//		block[3][3].txtColor = BRIGHT_YELLOW;
//		block[3][3].bgdColor = WHITE;
//		block[4][3].txtColor = BRIGHT_YELLOW;
//		block[5][3].txtColor = BRIGHT_YELLOW;
//		block[5][3].bgdColor = BLACK;
//		block[6][3].txtColor = BRIGHT_YELLOW;
//		block[6][3].bgdColor = WHITE;
//		block[7][3].txtColor = SKY_BLUE;
//		block[8][3].txtColor = ORANGE;
//		block[8][3].bgdColor = -1;
//		block[9][3].txtColor = BRIGHT_YELLOW;
//		block[9][3].bgdColor = ORANGE;
//		block[10][3].txtColor = ORANGE;
//		block[10][3].bgdColor = BRIGHT_YELLOW;
//		block[11][3].txtColor = BRIGHT_YELLOW;
//		block[11][3].bgdColor = ORANGE;
//
//		for (int i = 2; i < 8; i++)
//		{
//			block[i][4].txtColor = SKY_BLUE;
//		}
//		block[8][4].txtColor = BRIGHT_YELLOW;
//		block[9][4].txtColor = ORANGE;
//
//		block[7][1].txtColor = SKY_BLUE;
//		block[0][2].txtColor = BRIGHT_YELLOW;
//		block[1][2].txtColor = BRIGHT_YELLOW;
//		block[2][2].txtColor = BRIGHT_YELLOW;
//		block[2][2].bgdColor = BLACK;
//		block[3][2].txtColor = BRIGHT_YELLOW;
//		block[3][2].bgdColor = WHITE;
//		block[4][2].txtColor = BRIGHT_YELLOW;
//		block[5][2].txtColor = BRIGHT_YELLOW;
//		block[5][2].bgdColor = BLACK;
//		block[5][2].txtColor = BRIGHT_YELLOW;
//		block[5][2].bgdColor = BLACK;
//		block[6][2].txtColor = SKY_BLUE;
//		block[7][2].txtColor = SKY_BLUE;
//		block[8][2].txtColor = ORANGE;
//		block[9][2].bgdColor = ORANGE;
//		block[9][2].txtColor = BRIGHT_YELLOW;
//		block[10][2].bgdColor = BRIGHT_YELLOW;
//		block[10][2].txtColor = ORANGE;
//		block[11][2].bgdColor = ORANGE;
//		block[11][2].txtColor = BRIGHT_YELLOW;
//		for (int i = 2; i <= 7; i++)
//		{
//			block[i][3].txtColor = SKY_BLUE;
//		}
//		block[8][3].txtColor = BRIGHT_YELLOW;
//		block[9][3].txtColor = ORANGE;*/
//		//VE HOA
//	   /* block[6][2].txtColor = RED;
//		block[6][2].bgdColor = -1;
//		block[7][2].txtColor = BRIGHT_YELLOW;
//		block[7][2].bgdColor = RED;
//		block[8][2].txtColor = RED;
//		block[8][2].bgdColor = -1;
//		block[7][3].txtColor = RED;
//		block[7][3].bgdColor = -1;*/
//		//CAPYBARA
//		/*for (int i = 0; i <= 8; i++)
//		{
//			block[i][3].txtColor = LIGHT_BROWN;
//		}
//		block[9][3].txtColor = SADDLE_BROWN;
//		block[9][3].bgdColor = LIGHT_BROWN;
//		block[10][3].txtColor = LIGHT_BROWN;
//		block[11][3].txtColor = LIGHT_BROWN;
//		for (int i = 3; i <= 7; i++)
//		{
//			block[i][4].txtColor = LIGHT_BROWN;
//		}
//		block[8][3].txtColor = SADDLE_BROWN;
//		for (int i = 9; i <= 11; i++)
//		{
//			block[i][4].txtColor = LIGHT_BROWN;
//		}
//		block[0][2].txtColor = SADDLE_BROWN;
//		block[1][2].txtColor = LIGHT_BROWN;
//		block[1][2].bgdColor = SADDLE_BROWN;
//		block[2][2].txtColor = LIGHT_BROWN;
//		block[3][2].txtColor = LIGHT_BROWN;
//		block[4][2].bgdColor = LIGHT_BROWN;
//		block[4][2].txtColor = BLACK;
//		block[5][2].bgdColor = LIGHT_BROWN;
//		block[5][2].txtColor = BLACK;
//		block[6][2].bgdColor = LIGHT_BROWN;
//		block[6][2].txtColor = LIGHT_BROWN;
//		block[7][2].txtColor = SADDLE_BROWN;
//		block[8][2].txtColor = LIGHT_BROWN;
//		block[8][2].bgdColor = SADDLE_BROWN;
//
//		block[8][4].txtColor = LIGHT_BROWN;
//
//		block[7][1].txtColor = BRIGHT_YELLOW;
//		block[8][1].txtColor = BRIGHT_YELLOW;*/
//		//VE DUONG
//		/*block[0][0].txtColor = WHITE;
//		block[15][0].txtColor = WHITE;
//		for (int i = 1; i < 14; i+=4)
//		{
//			block[i][0].txtColor = BLACK;
//			block[i+1][0].txtColor = BLACK;
//		}
//		for (int i = 3; i < 12; i += 4)
//		{
//			block[i][0].txtColor = WHITE;
//			block[i + 1][0].txtColor = WHITE;
//		}
//
//		block[0][1].txtColor = BLACK;
//		block[15][1].txtColor = BLACK;
//		for (int i = 1; i < 14; i += 4)
//		{
//			block[i][1].txtColor = WHITE;
//			block[i + 1][1].txtColor = WHITE;
//		}
//		for (int i = 3; i < 12; i += 4)
//		{
//			block[i][1].txtColor = BLACK;
//			block[i + 1][1].txtColor = BLACK;
//		}
//
//		block[0][2].txtColor = WHITE;
//		block[15][2].txtColor = WHITE;
//		for (int i = 1; i < 14; i += 4)
//		{
//			block[i][2].txtColor = BLACK;
//			block[i + 1][2].txtColor = BLACK;
//		}
//		for (int i = 3; i < 12; i += 4)
//		{
//			block[i][2].txtColor = WHITE;
//			block[i + 1][2].txtColor = WHITE;
//		}
//
//		block[0][3].txtColor = BLACK;
//		block[15][3].txtColor = BLACK;
//		for (int i = 1; i < 14; i += 4)
//		{
//		    block[i][3].txtColor = WHITE;
//			block[i + 1][3].txtColor = WHITE;
//		}
//		for (int i = 3; i < 12; i += 4)
//		{
//			block[i][3].txtColor = BLACK;
//			block[i + 1][3].txtColor = BLACK;
//		}
//
//		block[0][4].txtColor = WHITE;
//		block[15][4].txtColor = WHITE;
//		for (int i = 1; i < 14; i += 4)
//		{
//			block[i][4].txtColor = BLACK;
//			block[i + 1][4].txtColor = BLACK;
//		}
//		for (int i = 3; i < 12; i += 4)
//		{
//			block[i][4].txtColor = WHITE;
//			block[i + 1][4].txtColor = WHITE;
//		}
//
//		block[0][5].txtColor = BLACK;
//		block[15][5].txtColor = BLACK;
//		for (int i = 1; i < 14; i += 4)
//		{
//			block[i][5].txtColor = WHITE;
//			block[i + 1][5].txtColor = WHITE;
//		}
//		for (int i = 3; i < 12; i += 4)
//		{
//			block[i][5].txtColor = BLACK;
//			block[i + 1][5].txtColor = BLACK;
//		}*/
//		//VE UF0
//		/*for (int i = 17; i < 29; i++)
//		{
//			block[i][0].bgdColor = SKY_BLUE;
//		}
//
//		block[24][0].bgdColor = WHITE;
//		block[25][0].bgdColor = WHITE;
//
//		for (int i = 15; i < 31; i++)
//		{
//			block[i][1].bgdColor = SKY_BLUE;
//		}
//		block[23][1].bgdColor = SKY_BLUE;
//		block[23][1].txtColor = WHITE;
//		block[24][1].bgdColor = WHITE;
//		block[25][1].bgdColor = WHITE;
//		block[26][1].bgdColor = SKY_BLUE;
//		block[26][1].txtColor = WHITE;
//		for (int i = 15; i < 31; i++)
//		{
//			block[i][2].bgdColor = SKY_BLUE;
//		}
//		block[28][2].bgdColor = SKY_BLUE;
//		block[28][2].txtColor = WHITE;
//		for (int i = 12; i < 34; i++)
//		{
//			block[i][3].bgdColor = LIGHT_GRAY;
//		}
//		for (int i = 9; i < 37; i++)
//		{
//			block[i][4].bgdColor = LIGHT_GRAY;
//		}
//		for (int i = 9; i < 37; i++)
//		{
//			block[i][5].bgdColor = LIGHT_GRAY;
//		}
//		for (int i = 12; i < 34; i++)
//		{
//			block[i][6].bgdColor = LIGHT_GRAY;
//		}
//		int x1 = 17;
//		int x2 = 29;
//		int y1 = 7;
//		for (int i = x1; i <= x2; i++)
//		{
//			block[i][y1].bgdColor = BRIGHT_YELLOW;
//
//		}
//		for (int i = y1; i < 23; i++)
//		{
//			x1--; x2++; y1++;
//			for (int i = x1; i <= x2; i++)
//			{
//				block[i][y1].bgdColor = BRIGHT_YELLOW;
//
//			}
//		}
//		for (int i = 3; i < 44; i++)
//		{
//			block[i][24].bgdColor = BRIGHT_YELLOW;
//		}
//		for (int i = 7; i < 40; i++)
//		{
//			block[i][25].bgdColor = BRIGHT_YELLOW;
//		}
//		for (int i = 11; i < 36; i++)
//		{
//			block[i][26].bgdColor = BRIGHT_YELLOW;
//		}
//		for (int i = 15; i < 32; i++)
//		{
//			block[i][27].bgdColor = BRIGHT_YELLOW;
//		}*/
//	}
//}
//
//COBJECT::~COBJECT() {
//	for (int i = 0; i < WIDTH; i++)
//		delete[] this->block[i];
//	delete[] this->block;
//}
//void COBJECT::DrawBlock(CGRAPHIC& layer) {
//	for (int i = 0; i < WIDTH; i++)
//		for (int j = 0; j < HEIGHT; j++)
//			layer.screen[this->x + i][this->y + j] = block[i][j];
//}
