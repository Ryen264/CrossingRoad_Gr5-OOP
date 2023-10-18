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
		this->finishTell();
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
void CGAME::Configure() {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX csbiex{};
	csbiex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hStdout, &csbiex);

	csbiex.ColorTable[0] = RGB(0, 0, 0);		//black
	csbiex.ColorTable[1] = RGB(135, 206, 250);	//light sky blue
	csbiex.ColorTable[2] = RGB(255, 255, 255);	//white
	csbiex.ColorTable[3] = RGB(0, 100, 0);		//dark green
	csbiex.ColorTable[4] = RGB(139, 69, 19);	//saddle brown (nau dam)
	csbiex.ColorTable[5] = RGB(205, 133, 63);	//peru (nau nhat)
	csbiex.ColorTable[6] = RGB(255, 25, 25);	//red
	csbiex.ColorTable[7] = RGB(255, 165, 0);	//orange
	csbiex.ColorTable[8] = RGB(148, 0, 211);	//dark violet
	csbiex.ColorTable[9] = RGB(255, 99, 71);	//tomato
	csbiex.ColorTable[10] = RGB(204, 255, 255);	//light cyan
	csbiex.ColorTable[11] = RGB(0, 17, 51);		//oxford blue
	csbiex.ColorTable[12] = RGB(67, 96, 86);	//feldgrau
	csbiex.ColorTable[13] = RGB(149, 156, 176);	//con chon xanh binh thuong
	csbiex.ColorTable[14] = RGB(201, 255, 229);	//Aero blue
	csbiex.ColorTable[15] = RGB(25, 255, 25);	//Neon green
	SetConsoleScreenBufferInfoEx(hStdout, &csbiex);
}
void CGAME::SetupTheme(THEME theme) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX csbiex{};
	csbiex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hStdout, &csbiex);
	for (int i = 0; i < 16; i++)
		csbiex.ColorTable[i] = theme.colorTable[i];
	this->BLACK = theme.black;
	this->WHITE = theme.white;
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
	//Configure();
	SetupTheme(THEME_LAND);
	CGRAPHIC grp;
	grp.clear(0, 0);
	grp.screen[6][10] = { L'/', BLACK, WHITE };
	grp.screen[6][11] = { L'\\', BLACK, WHITE };
	grp.screen[6][12] = { L'/', BLACK, WHITE };
	grp.screen[6][13] = { L'\\', BLACK, WHITE };
	grp.screen[6][14] = { L'/', BLACK, WHITE };
	grp.display(6, 10, 6, 14);
}

void CGAME::finishTell() {
	cout << "\x07"; //Bell~
}