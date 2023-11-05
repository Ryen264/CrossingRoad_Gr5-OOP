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
	this->cPlayer = new CPLAYER(BOARD_WIDTH / 2, 0);

	SetupTheme();
	BgdLayer.clear(BLACK, WHITE);
	ObjLayer.clear(BLACK, -1);
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
void CGAME::playGame() {
	this->startMap();
	system("cls");
	isThreadRunning = true;
	thread threadNewGame(&CGAME::SubThreadNewGame, this);
	while (1) {
		if (!this->cPlayer->isDead()) {
			int temp = toupper(_getch());
			switch (temp) {
			case 'W': case 'S': case 'A': case 'D': {
				this->cPlayer->setMove(temp);
				break;
			}
			case 'P': {
				if (Pause(threadNewGame.native_handle()) == BACK_TO_MENU_CODE) {
					this->exitThread(&threadNewGame);
					return;
				}
			}
			}
		}
		else {
			if (this->isReset()) {
				this->resetData();
				this->startMap();
			}
			else {
				this->exitThread(&threadNewGame);
				return;
			}
		}
	}
}
void CGAME::startMap() {
	//for (int i = 0; i < BOARD_HEIGHT; i++)
	//	this->aLanes[i]->DrawLane(BgdLayer);
	this->cPlayer->drawCharacter(ObjLayer);
	this->displayBgd();
	this->displayObj();
}

void CGAME::resetData() {
	this->cPlayer->set(BOARD_WIDTH / 2, 0, true, 0);
	while (!this->aLanes.empty()) {
		CLANE* pointer = this->aLanes.back();
		if (pointer != NULL)
			delete pointer;
		pointer = NULL;
		this->aLanes.pop_back();
	}
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
void CGAME::saveData(string fileName) {
	ofstream file(fileName, ios::out);
	
	if(file.is_open()){
		// <x> <y> <score> <isRight> //Thông tin người chơi
		file << cPlayer->getX() << " " << cPlayer->getY() << " " << cPlayer->getScore() << endl;
		//file << level;
		for(int i=0;i<BOARD_HEIGHT;i++){
			file << ((this->cPlayer->setIsRight()) ? "r" : "l") << " ";
			for(int j=0;j<BOARD_WIDTH;j++){
				file<<(aLanes[i]->checkPos(j)?1:0);
			}
			file<<endl;
		}
		file << endl;
		file.close();
	}else{
		cout << "Cant open file." << endl;
	}
}
void CGAME::loadData(string fileName) {

}
string CGAME::inputUserTxt() {
	string fileName;
	cout << "Enter the file name: ";
	getline(cin, fileName);
	return fileName;
}
int CGAME::inputUserNumber() {
	int n{};
	cout << "Enter the number: ";
	cin >> n;
	return n;
}
void CGAME::saveFileNameList() {
	fstream outFile("file_name_list.txt", fstream::out);
	if (outFile.fail())
		return;
	int size = (int)fileNameList.size();
	outFile << size << endl;
	for (int i = 0; i < size; i++)
		outFile << fileNameList[i] << endl;
	outFile.close();
}
void CGAME::loadFileNameList() {
	fstream inFile("file_name_list.txt", fstream::in);
	if (inFile.fail())
		return;
	fileNameList.clear();
	int size{};
	inFile >> size;
	string fileName;
	for (int i = 0; i < size; i++) {
		inFile >> fileName;
		fileNameList.push_front(fileName);
	}
	inFile.close();
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
	this->resetData();
	this->playGame();
}
void CGAME::LoadGame() {
	//drawLoadGame
	//input user
	this->loadData();	//cap nhat bien
	this->playGame();
}
void CGAME::SaveGame() {
	drawSaveGame();
	string fileName=inputUserTxt();

	if(fileNameList.size()>10){
		fileNameList.pop_back();
	}
	fileNameList.push_back(fileName);
	saveFileNameList();
	saveData(fileName);
}
void CGAME::Setting() {

}
void CGAME::Help() {

}
void CGAME::About() {

}

void CGAME::SubThreadNewGame() {
	while (isThreadRunning) {
		if (!this->cPlayer->isDead()) {
			this->cPlayer->eraseCharacter(ObjLayer);
			this->cPlayer->moveCharacter();
		}
		this->cPlayer->setMove(0);
		for (int i = 1; i < BOARD_HEIGHT - 1; i++) //ignore the first and the last lanes
			this->aLanes[i]->Move();
		//Xu ly va cham
		if (this->isInjured()) {
			this->cPlayer->setAlive(false);
			//Hieu ung va cham
		}
		//Xy ly finish
		if (this->cPlayer->isFinish()) {
			this->cPlayer->increaseScore();
			this->cPlayer->set(-1, 0);
			this->cPlayer->setFinish(false);

			//Change direction of a line
			this->aLanes[rand() % BOARD_HEIGHT]->changeDirection();
		}
		//lock.unlock();
		this->drawMap();
		this->displayObj();
		Sleep(10);
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
	SuspendThread(t);
	//setup tmpLayers
	system("cls");
	this->drawPause();
	int key = toupper(_getch());
	switch (key) {
	case '1': {
		this->resumeThread(t);
		break;
	}
	case'6': {
		this->resumeThread(t);
		return BACK_TO_MENU_CODE;
	}
	default:
		this->resumeThread(t);
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
	//system("cls");
	//for (int i = 0; i < BOARD_HEIGHT; i++) {
	//	for (int j = 0; j < BOARD_WIDTH; j++)
	//		if (this->aLanes[i]->checkPos(j))
	//			this->aLanes[i]->DrawObject(ObjLayer, j);
	//}
	this->cPlayer->drawCharacter(ObjLayer);

	//for (int i = 0; i < BOARD_HEIGHT; i++) {
	//	for (int j = 0; j < BOARD_WIDTH; j++) {
	//		if (i == 0 && (j == 0 || j == BOARD_WIDTH - 1))
	//			cout << "S";
	//		if (i == BOARD_HEIGHT - 1 && (j == 0 || j == BOARD_WIDTH - 1))
	//			cout << "F";
	//		if (this->aLanes[i]->checkPos(j) && i != 0 && i != BOARD_HEIGHT - 1)    //no car in the first and the last lines
	//			cout << "#";
	//		else if (this->cPlayer->getX() == j && this->cPlayer->getY() == i)
	//			cout << "V";
	//		else
	//			cout << " ";
	//	}
	//	cout << endl;
	//}
	//cout << "Score: " << this->cPlayer->getScore() << endl;
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
void drawSaveGame();
void drawLoadGame();
void drawInputUserTxt();
void drawInputUserNumber();

void CGAME::displayBgd() {
	BgdLayer.display();
}
void CGAME::displayObj() {
	for (int i = 0; i < SCREEN_WIDTH; i++)
		for (int j = 0; j < SCREEN_HEIGHT; j++)
			if (ObjLayer.screen[i][j].bgdColor == -1)
				ObjLayer.screen[i][j].bgdColor = BgdLayer.screen[i][j].bgdColor;
	ObjLayer.display();
}
void CGAME::displayScreen() {
	BgdLayer.display();
	ObjLayer.display();
}
