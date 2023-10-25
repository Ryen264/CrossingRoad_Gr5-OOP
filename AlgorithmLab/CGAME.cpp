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

CGAME::CGAME() {
	srand(time(0));
	this->cPlayer = new CPLAYER(BOARD_WIDTH / 2, START_HEIGHT);
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
void CGAME::start() {
	ShowCur(false);
	system("cls");
	this->intro();
	_getch();
	while (this->Menu() != QUIT_CODE);
	this->outtro();
	_getch();
	system("cls");
	//resetConsole(); - anti-Configure 
}
void CGAME::resetData() {
	this->cPlayer->set(BOARD_WIDTH / 2, START_HEIGHT, true, 0);
	for (int i = 0; i < (int)this->aLanes.size(); i++) {
		CLANE* pointer = this->aLanes.back();
		this->aLanes.pop_back();
		if (pointer != NULL)
			delete pointer;
		pointer = NULL;
	}
	this->aLanes.clear();
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		switch (rand() % NUMBER_OF_TYPE_LANE) {
		case 0: {
			this->aLanes.push_back(new CVEHICLELANE);
			break;
		}
		default:
			this->aLanes.push_back(NULL);
		}
	}
}
int CGAME::Menu() {
	system("cls");
	this->drawMenu();
	int key = toupper(_getch());
	switch (key) {
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
	case '6':
		return QUIT_CODE;
	}
	return 0;
}
void CGAME::NewGame() {
	system("cls");
	isThreadRunning = true;
	thread threadNewGame(&CGAME::SubThreadNewGame, this);
	this->resetData();
	while (!this->cPlayer->isDead()) {
		if (!_kbhit()) continue;
		int temp = toupper(_getch());
		switch (temp) {
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
		case 'P': {
			if (Pause(threadNewGame.native_handle()) == BACK_TO_MENU_CODE) {
				exitThread(&threadNewGame);
				return;
			}
		}
		case 'Y': {
			cout << "Press again!" << endl;
			break;
		}
		}
		temp = 0;
	}
	threadNewGame.join();
}
void CGAME::LoadGame() {

}
void CGAME::Setting() {

}
void CGAME::Help() {

}
void CGAME::About() {

}

void CGAME::SubThreadNewGame() {
	while (isThreadRunning) {
		unique_lock<mutex> lock(mtx);
		cv.wait(lock, [this] {return isThreadRunning; });
		//Update object pos
		//ignore the first and the last lanes
		for (int i = 1; i < BOARD_HEIGHT - 1; i++)
			this->aLanes[i]->Move();
		this->drawMap();
		//Xu ly va cham
		if (this->isInjured()) {
			if (this->isReset())
				this->resetData();
			else {
				this->cPlayer->set(-1, -1, false);
				isThreadRunning = false;
				cv.notify_all();
				return;
			}
		}

		//Xy ly finish
		if (this->cPlayer->isFinish(FINISH_HEIGHT)) {
			this->cPlayer->increaseScore();
			this->cPlayer->set(-1, START_HEIGHT);

			//Change direction of a line
			this->aLanes[rand() % BOARD_HEIGHT]->changeDirection();
		}
		lock.unlock();
		Sleep(100);
	}
}
void CGAME::exitThread(thread* t) {
	system("cls");
	isThreadRunning = false;
	t->join();
}
void CGAME::resumeThread(HANDLE t) {
	//drawResumeGame(); //count down
	if (t != NULL)
		ResumeThread(t);
}
int CGAME::Pause(HANDLE t) {
	unique_lock<mutex> lock(mtx);
	SuspendThread(t);
	//setup tmpLayers
	system("cls");
	this->drawPause();
	int key = toupper(_getch());
	switch (key) {
	case '1': {
		this->resumeThread(t);
		cv.notify_all();
		break;
	}
	case'6': {
		this->resumeThread(t);
		lock.unlock();
		return BACK_TO_MENU_CODE;
	}
	default:
		this->resumeThread(t);
		cv.notify_all();
	}
	return 0;
}

bool CGAME::isInjured() {
	return this->aLanes[this->cPlayer->getY()]->checkPos(this->cPlayer->getX());
}
bool CGAME::isReset() {
	this->drawPlayAgain();
	return toupper(_getch()) == 'Y';
}

//Drawing functions
void CGAME::intro() {
	cout << "START!!!" << endl;
}
void CGAME::outtro() {
	cout << "End game" << endl;
}
void CGAME::drawMap() {
	system("cls");
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (i == 0 && (j == 0 || j == BOARD_WIDTH - 1))
				cout << "S";
			if (i == BOARD_HEIGHT - 1 && (j == 0 || j == BOARD_WIDTH - 1))
				cout << "F";
			if (this->aLanes[i]->checkPos(j) && i != 0 && i != BOARD_HEIGHT - 1)    //no car in the first and the last lines
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
void CGAME::drawMenu() {
	cout << "CROSSING ROAD" << endl;
	cout << "1: New game" << endl;
	cout << "2: Load game" << endl;
	cout << "3: Setting" << endl;
	cout << "4: Help" << endl;
	cout << "5: About" << endl;
	cout << "6: Quit" << endl;
	cout << "Enter: ";
}
void CGAME::drawPause() {
	cout << "PAUSE" << endl;
	cout << "1: Resume" << endl;
	cout << "2: Save game" << endl;
	cout << "3. Setting" << endl;
	cout << "4. Help" << endl;
	cout << "5. About" << endl;
	cout << "6. Back to menu" << endl;
	cout << "Enter: ";
}
void CGAME::drawPlayAgain() {
	cout << "Play again (Y/N)?" << endl;
}
