#include "CGAME.h"
CGAME::CGAME(int numberOfLanes) {
	srand(time(0));
	this->isRunning = true;
	this->cPlayer = new CPLAYER(WIDTH / 2, START_HEIGHT);
	this->numberOfLanes = numberOfLanes;
	for (int i = 0; i < numberOfLanes; i++) {
		switch (rand() % TYPELANENUM) {
		case 0: {
			this->aLanes.push_back(new CVEHICLELANE(WIDTH));
			break;
		}
		}
	}
}
CGAME::~CGAME() {
	delete this->cPlayer;
	this->cPlayer = NULL;
	for (int i = 0; i < this->numberOfLanes; i++) {
		CLANE* pointer = this->aLanes.back();
		this->aLanes.pop_back();
		delete pointer;
		pointer = NULL;
	}
}

//Friend functions
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}
void CGAME::input() {
	if (_kbhit()) {
		switch (toupper(_getch())) {
		case 'W': {
			this->cPlayer->Up();
			break;
		}
		case 'S': {
			this->cPlayer->Down();
			break;
		}
		case 'A': {
			this->cPlayer->Left();
			break;
		}
		case 'D': {
			this->cPlayer->Right();
			break;
		}
		case 'Q': {
			this->isRunning = false;
			break;
		}
		}
	}
}
void CGAME::logic() {
	//ignore the first and the last lanes
	for (int i = 1; i < this->numberOfLanes - 1; i++) {
		//Random move a lane
		if (rand() % 10 == 1)
			this->aLanes[i]->Move();
		//Quit if player has an accident
		if (this->aLanes[i]->checkPos(this->cPlayer->getX()) && this->cPlayer->getY() == i) {
			this->cPlayer->set(-1, -1, false, -1);
		}
	}
	//Player qua được màn
	if (this->cPlayer->isFinish(FINISH_HEIGHT)) {
		//Tăng điểm và reset màn
		this->cPlayer->increaseScore();
		this->cPlayer->set(-1, START_HEIGHT);
		this->finishTell(cout);
		//Change direction of a line
		this->aLanes[rand() % this->numberOfLanes]->changeDirection();
	}
}
void CGAME::start() {
	ShowCur(false);
	this->drawStart(cout);
	while (this->isRunning) {
		this->input();
		this->drawMap(cout);
		this->logic();
		Sleep(1);
		if (this->cPlayer->isDead()) {
			bool isReset = this->isReset();
			this->isRunning = isReset;
			if (isReset)
				this->reset();
		}
	}
	this->quit();
}
void CGAME::quit() {
	this->drawQuit(cout);
	ShowCur(true);
}

bool CGAME::isReset() {
	this->drawIsReset(cout);
	return toupper(_getch()) == 'Y';
}
void CGAME::reset() {
	this->cPlayer->set(WIDTH / 2, START_HEIGHT, true, 0);
}

//Drawing functions
void CGAME::drawMap(ostream& outDev) {
	system("cls");
	for (int i = 0; i < this->numberOfLanes; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (i == 0 && (j == 0 || j == WIDTH - 1))
				cout << "S";
			if (i == this->numberOfLanes - 1 && (j == 0 || j == WIDTH - 1))
				cout << "F";
			if (this->aLanes[i]->checkPos(j) && i != 0 && i != this->numberOfLanes - 1)    //no car in the first and the last lines
				cout << "#";
			else if (this->cPlayer->getX() == j && this->cPlayer->getY() == i)
				cout << "V";
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << "Score: " << this->cPlayer->getScore() << endl;
}
void CGAME::drawStart(ostream& outDev) {
	cout << "START!!!" << endl;
}
void CGAME::finishTell(ostream& outDev) {
	outDev << "\x07"; //Bell~
}
void CGAME::drawQuit(ostream& outDev) {
	outDev << "GAME OVER!" << endl;
}
void CGAME::drawIsReset(ostream& outDev) {
	outDev << "Play again (Y/N)?" << endl;
}
void CGAME::drawDemo() {
	Configure();
	CGRAPHIC grp;
	grp.clear(0, 0);
	grp.screen[6][10] = { L'/', FELDGRAU, LIGHTSKY };
	grp.screen[6][11] = { L'\\', FELDGRAU, LIGHTSKY };
	grp.screen[6][12] = { L'/', FELDGRAU, LIGHTSKY };
	grp.screen[6][13] = { L'\\', FELDGRAU, LIGHTSKY };
	grp.screen[6][14] = { L'/', FELDGRAU, LIGHTSKY };
	grp.display(6, 10, 6, 14);
}

void CGAME::drawlane()
{
	Configure();
	CGRAPHIC lane;
	lane.clear(0, 0);
	int j = 0;
	for (int i = 0; i < 40; i++)
	{	
		for (int j = 0; j < 7; j++)
		{
			lane.screen[i][j] = { L' ', FELDGRAU, GREEN_PERRY };
		}	
	}
	for (int i = 0; i < 39; i++)
	{
		if (i % 5 == 0)
		{
			continue;
		}
		lane.screen[i][3] = { L' ', FELDGRAU, WHITE};
	}
	lane.display(0, 0, 39, 19);
}

void CGAME::drawPerry()
{
	Configure();
	CGRAPHIC perry;
	perry.clear(6, 6);
	//VE THAN PERRY
	for (int i = 5; i < 16; i++)
	{
		for (int j = 3; j < 5; j++)
		{
			perry.screen[i][j] = { L' ', FELDGRAU, GREEN_PERRY };
		}
		
	}
	//VE MAT PERRY
	perry.screen[13][3] = { L'▀', GREEN_PERRY, BLACK };
	perry.screen[16][3] = { L'▀', 6, BLACK };
	//VE TOC PERRY
	perry.screen[15][2] = { L'▀', 6, BLACK };
	perry.screen[14][2] = { L'▄', 6, BLACK };
	perry.screen[16][2] = { L'▄', 6, BLACK };
	//VE MO PERRY
	perry.screen[15][4] = { L'▀', 7,7  };
	perry.screen[16][4] = { L'▀', 7,7 };
	perry.screen[16][4] = { L'▄', 7,6};
	
	//VE CHAN PERRY
	perry.screen[7][5] = { L'▄', 7,GREEN_PERRY };
	perry.screen[5][5] = { L'▄', 7,GREEN_PERRY };
	perry.screen[11][5] = { L'▄', GREEN_PERRY,GREEN_PERRY };
	perry.screen[13][5] = { L'▄', GREEN_PERRY,GREEN_PERRY };
	//VE DUOI PERRY
	perry.screen[1][3] = { L'▄', 7,6 };
	perry.screen[2][3] = { L'▄', 7,6};
	perry.screen[3][4] = { L'▀', 7,6 };
	perry.screen[4][4] = { L'▀', 7,6 };
	//car.screen[15][5] = { L'▀', 7,GREEN_PERRY };
	// ▀▀▀
	//▄▀▄
	/*car.screen[2][4] = {L' ', FELDGRAU, 7};
	car.screen[3][4] = { L' ', FELDGRAU, 7 };
	//▄
	car.screen[4][4] = { L'▄', 7, 6};
	car.screen[10][4] = { L' ', FELDGRAU, 7 };
	car.screen[11][4] = { L' ', FELDGRAU, 7 };
	car.screen[12][4] = { L'▄', 7, 6 };
	//▀
	car.screen[12][1] = { L'▀', GREEN_PERRY, BLACK };
	car.screen[12][2] = { L'▀', BLACK, GREEN_PERRY };
	car.screen[15][2] = { L'▀', 6, 7 };
	car.screen[15][3] = { L'▀', 7, 6 };
	car.screen[16][2] = { L'▀', 6, 7 };
	car.screen[16][3] = { L'▀', 7, 6 };*/
	perry.display(0, 0, 39, 19);
}

void CGAME::drawTrees()
{
	Configure();
	CGRAPHIC tree;
	tree.clear(6, 6);
	//Ve vien den ben tren
	for (int i = 1; i < 10; i++)
	{
		tree.screen[i][0] = { L'▄',BLACK,6 };
	}
	//Ve vien den duoi
	for (int i = 1; i < 10; i++)
	{
		tree.screen[i][3] = { L'▀',BLACK,6 };
	}
	//ve vien den ben trai
	for (int j = 1; j < 3; j++)
	{
		tree.screen[0][j] = { L' ',BLACK,BLACK };
	}
	//ve vien den ben phai
	for (int j = 1; j < 3; j++)
	{
		tree.screen[10][j] = { L' ',BLACK,BLACK };
	}
	//Ve mau xanh la cay dam
	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 3; j++)
		{
			if (i % 2 == 0)
			{
				tree.screen[i][j] = { L'▀',GREEN,NEON_GREEN };
			}
			else
			{
				tree.screen[i][j] = { L'▀',NEON_GREEN,GREEN };
			}
			
		}
	}
	//Ve Than Cay
	for (int i = 4; i < 7; i++)
	{
		for (int j = 3; j < 5; j++)
		{
			tree.screen[i][j] = { L' ',SADDLE_BROWN,SADDLE_BROWN };
		}
	}
	//Vien than cay ben trai
	for (int j = 3; j < 5; j++)
	{
		tree.screen[3][j] = { L' ',BLACK,BLACK};
	}
	//Vien than cay ben phai
	for (int j = 3; j < 5; j++)
	{
		tree.screen[7][j] = { L' ',BLACK,BLACK };
	}
	//Vien than cay ben duoi
	for (int i = 3; i < 8; i++)
	{
		tree.screen[i][5] = { L'▀',BLACK,6 };
	}
	tree.display(0, 0, 39, 19);

}
