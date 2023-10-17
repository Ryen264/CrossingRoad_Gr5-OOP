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
	//hello
	grp.clear(0, 0);
	grp.screen[6][10] = { L'/', FELDGRAU, SKY_BLUE };
	grp.screen[6][11] = { L'\\', FELDGRAU, SKY_BLUE };
	grp.screen[6][12] = { L'/', FELDGRAU, SKY_BLUE };
	grp.screen[6][13] = { L'\\', FELDGRAU, SKY_BLUE };
	grp.screen[6][14] = { L'/', FELDGRAU, SKY_BLUE };
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

void CGAME::drawTree(int x, int y)
{
	Configure();
	CGRAPHIC tree;
	tree.clear(WHITE, WHITE);
	tree.DrawObject(Tree,x,y, GREEN,WHITE);

	tree.screen[x + 3][y + 3].txtColor = SADDLE_BROWN;
	tree.screen[x + 4][y + 3].txtColor = SADDLE_BROWN;
	tree.screen[x + 5][y + 3].txtColor = SADDLE_BROWN;
	tree.screen[x + 6][y + 3].txtColor = SADDLE_BROWN;

	tree.screen[x + 3][y + 4].txtColor = SADDLE_BROWN;
	tree.screen[x + 4][y + 4].txtColor = SADDLE_BROWN;
	tree.screen[x + 5][y + 4].txtColor = SADDLE_BROWN;
	tree.screen[x + 6][y + 4].txtColor = SADDLE_BROWN;

	tree.screen[x + 3][y + 5].txtColor = SADDLE_BROWN;
	tree.screen[x + 4][y + 5].txtColor = SADDLE_BROWN;
	tree.screen[x + 5][y + 5].txtColor = SADDLE_BROWN;
	tree.screen[x + 6][y + 5].txtColor = SADDLE_BROWN;
	//tree.screen[x + 4][y + 2].txtColor = SADDLE_BROWN;
	//tree.screen[x + 3][y + 3].txtColor = SADDLE_BROWN;
	//tree.screen[x + 4][y + 3].txtColor = SADDLE_BROWN;
	tree.display(x, y, x + 20, y + 5);
}

/*void CGAME::drawTrees()
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

}*/

void CGAME::drawCar(int x, int y) {
	Configure();
	CGRAPHIC Car;
	Car.clear(WHITE, WHITE);
	Car.DrawObject(car, x, y, RED, WHITE);
	/*Car.screen[x][y].txtColor = DARK_RED;
	Car.screen[x + 1][y].txtColor = DARK_RED;
	Car.screen[x + 7][y].txtColor = DARK_RED;
	Car.screen[x + 8][y].txtColor = DARK_RED;
	Car.screen[x + 6][y].txtColor = SKY_BLUE;
	Car.screen[x + 9][y].txtColor = BRIGHTYELLOW;
	Car.screen[x + 2][y + 1].txtColor = DARK_RED;
	Car.screen[x + 2][y + 1].bgdColor = RED;
	Car.screen[x + 3][y + 1].txtColor = DARK_RED;
	Car.screen[x + 3][y + 1].bgdColor = RED;
	Car.screen[x + 4][y + 1].txtColor = DARK_RED;
	Car.screen[x + 4][y + 1].bgdColor = RED;
	Car.screen[x + 5][y + 1].txtColor = DARK_RED;
	Car.screen[x + 5][y + 1].bgdColor = RED;
	Car.screen[x + 6][y + 1].txtColor = SKY_BLUE;
	Car.screen[x][y + 2].txtColor = DARK_RED;
	Car.screen[x + 1][y + 2].txtColor = DARK_RED;
	Car.screen[x + 6][y + 2].txtColor = DARK_RED;
	Car.screen[x + 2][y + 2].txtColor = DARK_RED;
	Car.screen[x + 2][y + 2].bgdColor = SKY_BLUE;
	Car.screen[x + 3][y + 2].txtColor = DARK_RED;
	Car.screen[x + 3][y + 2].bgdColor = SKY_BLUE;
	Car.screen[x + 4][y + 2].txtColor = DARK_RED;
	Car.screen[x + 4][y + 2].bgdColor = SKY_BLUE;
	Car.screen[x + 5][y + 2].txtColor = DARK_RED;
	Car.screen[x + 5][y + 2].bgdColor = SKY_BLUE;
	Car.screen[x + 7][y + 2].txtColor = DARK_RED;
	Car.screen[x + 7][y + 2].bgdColor = RED;
	Car.screen[x + 8][y + 2].txtColor = DARK_RED;
	Car.screen[x + 8][y + 2].bgdColor = RED;
	Car.screen[x + 9][y + 2].txtColor = BRIGHTYELLOW;
	Car.screen[x + 9][y + 2].bgdColor = RED;
	Car.screen[x + 1][y + 3].txtColor = BLACK;
	Car.screen[x + 2][y + 3].txtColor = BLACK;
	Car.screen[x + 6][y + 3].txtColor = BLACK;
	Car.screen[x + 7][y + 3].txtColor = BLACK;
	Car.display(x, y, x + 9, y + 3);*/
}