#include "CGAME.h"
//Friend functions
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf{};

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}

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
		default:
			this->aLanes.push_back(NULL);
		}
	}
	SetupTheme();
	BgdScreen.clear(BLACK, WHITE);
	ObjScreen.clear(BLACK, -1);
}
CGAME::~CGAME() {
	delete this->cPlayer;
	this->cPlayer = NULL;
	for (int i = 0; i < (int)this->aLanes.size(); i++) {
		CLANE* pointer = this->aLanes.back();
		this->aLanes.pop_back();
		if (pointer != NULL)
			delete pointer;
		pointer = NULL;
	}
	ShowCur(true);
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
			this->Quit();
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
		//Change direction of a line
		this->aLanes[rand() % this->numberOfLanes]->changeDirection();
	}
}
void CGAME::start() {
	ShowCur(false);
	this->intro();
	_getch();
	while (this->isRunning) {
		this->Menu();
	}
}
bool CGAME::isReset() {
	this->drawIsReset();
	return toupper(_getch()) == 'Y';
}
void CGAME::reset() {
	this->cPlayer->set(WIDTH / 2, START_HEIGHT, true, 0);
	this->aLanes.clear();
	for (int i = 0; i < this->numberOfLanes; i++) {
		switch (rand() % TYPELANENUM) {
		case 0: {
			this->aLanes.push_back(new CVEHICLELANE(WIDTH));
			break;
		}
		default:
			this->aLanes.push_back(NULL);
		}
	}
}
void CGAME::saveGame() {

}

void CGAME::Menu() {
	system("cls");
	this->drawMenu();
	switch (toupper(_getch())) {
	case '1': {
		this->NewGame();
		break;
	}
	case '2': {
		this->LoadGame();
		break;
	}
	case '3': {
		this->Setting();
		break;
	}
	case '4': {
		this->Help();
		break;
	}
	case '5': {
		this->About();
		break;
	}
	case '6': {
		this->Quit();
		break;
	}
	default:
		this->Quit();
	}
}
void CGAME::NewGame() {
	while (this->isRunning) {
		this->input();
		this->drawMap();
		this->logic();
		Sleep(1);
		if (this->cPlayer->isDead()) {
			this->reset();
			if (!this->isReset())
				return;
		}
	}
}
void CGAME::LoadGame() {

}
void CGAME::Setting() {

}
void CGAME::Help() {

}
void CGAME::About() {

}
void CGAME::Quit() {
	system("cls");
	this->drawQuit();
	this->isRunning = false;
}

//Drawing functions
void CGAME::SetupTheme(THEME theme) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX csbiex{};
	csbiex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hStdout, &csbiex);
	for (int i = 0; i < 16; i++)
		csbiex.ColorTable[i] = theme.colorTable[i];
	this->BLACK = theme.BLACK; this->SKY_BLUE = theme.SKY_BLUE; this->WHITE = theme.WHITE; this->DARK_GREEN = theme.DARK_GREEN;
	this->SADDLE_BROWN = theme.SADDLE_BROWN; this->DARK_RED = theme.DARK_RED; this->RED = theme.RED; this->ORANGE = theme.ORANGE;
	this->DARK_VIOLET = theme.DARK_VIOLET; this->TOMATO = theme.TOMATO; this->LIGHT_CYAN = theme.LIGHT_CYAN; this->OXFORD = theme.OXFORD;
	this->FELD_GRAU = theme.FELD_GRAU; this->BRIGHT_YELLOW = theme.BRIGHT_YELLOW; this->LIGHT_GREEN = theme.LIGHT_GREEN; this->LIGHT_BROWN = theme.LIGHT_BROWN;
	SetConsoleScreenBufferInfoEx(hStdout, &csbiex);
}

void CGAME::intro() {
	cout << "START!!!" << endl;
}
void CGAME::drawMenu() {
	system("cls");
	cout << "CROSSING ROAD" << endl;
	cout << "1: New game" << endl;
	cout << "2: Load game" << endl;
	cout << "3: Setting" << endl;
	cout << "4: Help" << endl;
	cout << "5: About" << endl;
	cout << "6: Quit" << endl;
	cout << "Enter: ";
}
void CGAME::drawMap() {
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
void CGAME::drawQuit() {
	cout << "GAME OVER!" << endl;
}
void CGAME::drawIsReset() {
	cout << "Play again (Y/N)?" << endl;
}
void CGAME::drawDemo() {
	SetupTheme();
	CGRAPHIC grp;
	//hello
	grp.clear(0, 0);
	grp.screen[6][10] = { L'/', BLACK, WHITE };
	grp.screen[6][11] = { L'\\', BLACK, WHITE };
	grp.screen[6][12] = { L'/', BLACK, WHITE };
	grp.screen[6][13] = { L'\\', BLACK, WHITE };
	grp.screen[6][14] = { L'/', BLACK, WHITE };
	grp.display(6, 10, 6, 14);
}

/*void CGAME::drawlane()
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
}*/

void CGAME::drawTree(int x, int y)
{
	SetupTheme();
	CGRAPHIC tree;
	tree.clear(WHITE, WHITE);
	tree.DrawObject(Tree, x, y, BLACK, WHITE);
	for (int i = 1; i <= 5; i++)
	{
		tree.screen[x + i][y].bgdColor = LIGHT_GREEN;
	}
	tree.screen[x + 6][y].bgdColor = DARK_GREEN;
	tree.screen[x + 7][y].bgdColor = DARK_GREEN;
	for (int i = 1; i <= 7; i++)
	{
		if (i == 1)
		{
			tree.screen[x + i][y + 1].txtColor = DARK_GREEN;
			tree.screen[x + i][y + 1].bgdColor = LIGHT_GREEN;
		}
		else if (i == 7)
		{
			tree.screen[x + i][y + 1].txtColor = DARK_GREEN;
		}
		else
		{
			tree.screen[x + i][y + 1].txtColor = LIGHT_GREEN;
		}
	}
	for (int i = 1; i <= 3; i++)
	{
		tree.screen[x + i][y + 2].txtColor = DARK_GREEN;
	}
	for (int i = 4; i <= 6; i++)
	{
		tree.screen[x + i][y + 2].txtColor = DARK_GREEN;
		tree.screen[x + i][y + 2].bgdColor = LIGHT_GREEN;
	}
	tree.screen[x + 7][y + 2].txtColor = DARK_GREEN;
	/*for (int i = 1; i <= 7; i++)
	{
		for (int j = 1; j <= 2; j++)
		{
			tree.screen[x + i][y+j].bgdColor = DARK_GREEN;
		}
	}*/
	tree.screen[x + 3][y + 3].bgdColor = SADDLE_BROWN;
	tree.screen[x + 5][y + 3].bgdColor = SADDLE_BROWN;

	tree.screen[x + 3][y + 4].txtColor = SADDLE_BROWN;
	tree.screen[x + 3][y + 4].bgdColor = BLACK;
	tree.screen[x + 4][y + 4].txtColor = SADDLE_BROWN;
	tree.screen[x + 4][y + 4].bgdColor = BLACK;
	tree.screen[x + 5][y + 4].txtColor = SADDLE_BROWN;
	tree.screen[x + 5][y + 4].bgdColor = BLACK;

	tree.screen[x + 4][y + 5].bgdColor = SADDLE_BROWN;
    tree.display(x, y, 39, 19);

}

void CGAME::drawCar(int x, int y) {
	SetupTheme();
	CGRAPHIC Car;
	Car.clear(WHITE, WHITE);
	Car.DrawObject(CAR, x, y, RED, WHITE);
	Car.screen[x][y].txtColor = DARK_RED;
	Car.screen[x + 1][y].txtColor = DARK_RED;
	Car.screen[x + 7][y].txtColor = DARK_RED;
	Car.screen[x + 8][y].txtColor = DARK_RED;
	Car.screen[x + 6][y].txtColor = SKY_BLUE;
	Car.screen[x + 9][y].txtColor = BRIGHT_YELLOW;
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
	Car.screen[x + 9][y + 2].txtColor = BRIGHT_YELLOW;
	Car.screen[x + 9][y + 2].bgdColor = RED;
	Car.screen[x + 1][y + 3].txtColor = BLACK;
	Car.screen[x + 2][y + 3].txtColor = BLACK;
	Car.screen[x + 6][y + 3].txtColor = BLACK;
	Car.screen[x + 7][y + 3].txtColor = BLACK;
	Car.display(x, y, x + 9, y + 3);
}

void CGAME::drawDinosaur(int x, int y)
{
	SetupTheme();
	ObjScreen.DrawObject(DINOSAUR, x, y, BLACK, -1);
	//L"    ▄▀▀▀▀▀▀▀▀▀▄ ",
	//L"    █ ██      █ ",
	//L"    █         █ ",
	//L"  █▀█  ▀▀▀▄▄▄▄▀ ",
	//L"   ▀▄ ▄▄▄▄█     ",
	//L"    █▀  █▀      ",
	for (int i = 5; i <= 13; i++)
		ObjScreen.screen[x + i][y].bgdColor = DARK_GREEN;

	ObjScreen.screen[x + 5][y + 1].bgdColor = DARK_GREEN;
	for (int i = 8; i <= 13; i++)
		ObjScreen.screen[x + i][y + 1].bgdColor = DARK_GREEN;

	for (int i = 5; i <= 13; i++)
		ObjScreen.screen[x + i][y + 2].bgdColor = DARK_GREEN;

	ObjScreen.screen[x + 3][y + 3].bgdColor = DARK_GREEN;
	ObjScreen.screen[x + 5][y + 3].bgdColor = DARK_GREEN;
	ObjScreen.screen[x + 6][y + 3].bgdColor = DARK_GREEN;
	ObjScreen.screen[x + 7][y + 3].txtColor = DARK_GREEN;
	ObjScreen.screen[x + 7][y + 3].bgdColor = LIGHT_GREEN;
	ObjScreen.screen[x + 8][y + 3].txtColor = DARK_GREEN;
	ObjScreen.screen[x + 8][y + 3].bgdColor = LIGHT_GREEN;
	ObjScreen.screen[x + 9][y + 3].txtColor = DARK_GREEN;
	ObjScreen.screen[x + 9][y + 3].bgdColor = LIGHT_GREEN;
	ObjScreen.screen[x + 10][y + 3].bgdColor = DARK_GREEN;
	ObjScreen.screen[x + 11][y + 3].bgdColor = DARK_GREEN;
	ObjScreen.screen[x + 12][y + 3].bgdColor = DARK_GREEN;
	ObjScreen.screen[x + 13][y + 3].bgdColor = DARK_GREEN;

	ObjScreen.screen[x + 4][y + 4].bgdColor = DARK_GREEN;
	ObjScreen.screen[x + 5][y + 4].bgdColor = DARK_GREEN;
	ObjScreen.screen[x + 6][y + 4].bgdColor = DARK_GREEN;
	ObjScreen.screen[x + 7][y + 4].bgdColor = LIGHT_GREEN;
	ObjScreen.screen[x + 8][y + 4].bgdColor = LIGHT_GREEN;
	ObjScreen.screen[x + 9][y + 4].bgdColor = LIGHT_GREEN;

	BgdScreen.display(x, y, 39, 19);
	ObjScreen.display(x, y, 39, 19);
	/*SetupTheme();
	CGRAPHIC dino;
	dino.clear(WHITE, WHITE);
	dino.DrawObject(Dinasour, x, y, BLACK, WHITE);

	for (int i = 3; i < 15; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			dino.screen[x + i][y+j].bgdColor = DARK_GREEN;
		}
		
	}
	for (int i = 2; i < 11; i++)
	{
		dino.screen[x + i][y + 4].bgdColor = DARK_GREEN;
	}
	dino.screen[x + 1][y + 3].bgdColor = DARK_GREEN;
	dino.screen[x + 9][y + 3].bgdColor = DARK_GREEN;
	dino.screen[x + 9][y + 3].txtColor = LIGHT_GREEN;
	dino.screen[x + 10][y + 3].bgdColor = DARK_GREEN;
	dino.screen[x + 10][y + 3].txtColor = LIGHT_GREEN;
	dino.screen[x + 9][y + 4].bgdColor = LIGHT_GREEN;
	dino.screen[x + 10][y + 4].bgdColor = LIGHT_GREEN;
	dino.screen[x + 8][y + 3].txtColor = LIGHT_GREEN;
	dino.screen[x + 8][y + 3].bgdColor = DARK_GREEN;
	dino.screen[x + 8][y + 4].bgdColor = LIGHT_GREEN;
	dino.display(x, y, 39, 19);*/
}

void CGAME::drawGrassLand(int x, int y)
{
	/* {L"    ▄    ▄▄▄    ",
		L"   ▀▀▀ ▄██  ▄   ",
		L"   ▀█▄ █▀  ▀▀▀  ",
		L"   ▄ ▀▀       █ ",
		L"  ▀▀▀   ▀█▄ ▄█▀ ",
		L"          ▀ ▀   ", };*/
	SetupTheme();
	ObjScreen.DrawObject(grassland,x, y, LIGHT_GREEN, DARK_GREEN);
	ObjScreen.screen[x + 4][y].txtColor = ORANGE;
	ObjScreen.screen[x + 3][y + 1].txtColor = ORANGE;
	ObjScreen.screen[x + 4][y + 1].txtColor = RED;
	ObjScreen.screen[x + 4][y + 1].bgdColor = ORANGE;
	ObjScreen.screen[x + 5][y + 1].txtColor = ORANGE;
	ObjScreen.screen[x + 12][y + 1].txtColor = WHITE;
	ObjScreen.screen[x + 11][y + 2].txtColor = WHITE;
	ObjScreen.screen[x + 12][y + 2].txtColor = BRIGHT_YELLOW;
	ObjScreen.screen[x + 12][y + 2].bgdColor = WHITE;
	ObjScreen.screen[x + 13][y + 2].txtColor = WHITE;
	ObjScreen.screen[x + 12][y + 3].txtColor = WHITE;
	ObjScreen.screen[x + 2][y + 4].txtColor = WHITE;
	ObjScreen.screen[x + 3][y + 3].bgdColor = DARK_GREEN;
	ObjScreen.screen[x + 3][y + 3].txtColor = WHITE;
	ObjScreen.screen[x + 3][y + 4].txtColor = DARK_RED;
	ObjScreen.screen[x + 3][y + 4].bgdColor = WHITE;
	ObjScreen.screen[x + 4][y + 4].txtColor = WHITE;
	//ObjScreen.screen[x + 3][y + 4].bgdColor = WHITE;
	BgdScreen.display(x, y, 39, 19);
	ObjScreen.display(x, y, 39, 19);
}
