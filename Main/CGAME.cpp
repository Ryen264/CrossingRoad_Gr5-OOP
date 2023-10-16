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