#include "CGAME.h"
//Friend functions
CGAME::CGAME() {
	this->Configure();
	this->cPlayer = new CPLAYER;
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
void CGAME::Configure()
{
	//Disable Button
	HWND hWnd = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hWnd, false);
	DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	ShowScrollbar(false);
	DisableResizeWindow();
	ShowCur(false);
	SetConsoleTitle(L"CROSSY-ROAD-Project_Group-5_22CLC01_HCMUS");
	//

	//Setup zoom
	CONSOLE_FONT_INFOEX cfiex;
	cfiex.cbSize = sizeof(CONSOLE_FONT_INFOEX);

	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hConsoleOutput, 0, &cfiex);
	cfiex.dwFontSize.Y = 14;
	SetCurrentConsoleFontEx(hConsoleOutput, 0, &cfiex);
	//

	//Setup WindowSize & ScreenBufferSize
	RECT rectClient, rectWindow;
	GetClientRect(hWnd, &rectClient);
	GetWindowRect(hWnd, &rectWindow);

	MoveWindow(hWnd, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TRUE);

	string sysStr = "mode " + to_string(SCREEN_WIDTH) + ", " + to_string(SCREEN_HEIGHT );
	char* sysMode = new char[sysStr.size() + 1];
	for (int i = 0; i < (int)sysStr.size(); i++) sysMode[i] = sysStr[i];
	sysMode[sysStr.size()] = '\0';
	system(sysMode);
	system("color 20");
	//
	srand(time(0));
	SetupTheme();
	BgdLayer.clear(BLACK, WHITE);
	ObjLayer.clear(BLACK, -1);
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
	resetData();
	startMap();
	isThreadRunning = true;
	thread threadNewGame(&CGAME::SubThreadNewGame, this);
	while (1) {
		if (!cPlayer->isDead()) {
			int temp = toupper(_getch());
			switch (temp) {
			case 'W': case 'S': case 'A': case 'D': {
				cPlayer->setMove(temp);
				break;
			}
			case 'P': {
				if (Pause(threadNewGame.native_handle()) == BACK_TO_MENU_CODE) {
					exitThread(&threadNewGame);
					return;
				}
			}
			}
		}
		else if (cPlayer->isDead()) {
			if (isReset()) {
				resetData();
				startMap();
				cPlayer->setMove(0);
				cPlayer->set(BOARD_WIDTH / 2, 0, true,true, 0);
			}
			else {
				exitThread(&threadNewGame);
				return;
			}
		}
	}
}
void CGAME::startMap() {
	system("cls");
	for (int i = 0; i < BOARD_HEIGHT; i++)
		aLanes[i]->DrawLane(BgdLayer);
}

void CGAME::resetData() {
	while (!aLanes.empty()) {
		CLANE* pointer = aLanes.back();
		aLanes.pop_back();
		if (pointer != NULL)
			delete pointer;
		pointer = NULL;
	}
	aLanes.push_back(new CGRASSLANE(0, START_HEIGHT));

	int condition = 0, laneCase{};
	for (int i = 1; i < BOARD_HEIGHT - 1; i++) {
		laneCase = random(LANE_ID_LIST);

		switch (laneCase) {
		case VEHICLELANE_ID: {
			aLanes.push_back(new CVEHICLELANE(0, i * BLOCK_HEIGHT + START_HEIGHT, rand() % 3));
			condition = 0;
			break;
		}
		case GRASSLANE_ID: {
			aLanes.push_back(new CGRASSLANE(0, i * BLOCK_HEIGHT + START_HEIGHT));
			condition = 0;
			break;
		}
		case TRAINLANE_ID: {
			aLanes.push_back(new CTRAINLANE(0, i * BLOCK_HEIGHT + START_HEIGHT, rand() % 3, 10, 5));
			condition = 0;
			break;
		}
		case RIVERLANE_LAND_ID: {
			if (condition == 0) {
				aLanes.push_back(new CRIVERLANE(0, i * BLOCK_HEIGHT + START_HEIGHT, rand() % 3, true));
				condition = RIVERLANE_NOLAND_ID;
			}
			else
				aLanes.push_back(new CRIVERLANE(0, i * BLOCK_HEIGHT + START_HEIGHT, rand() % 3, false));
			break;
		}
		default:
			aLanes.push_back(new CGRASSLANE(0, i * BLOCK_HEIGHT + START_HEIGHT));
			condition = 0;
		}
	}
	aLanes.push_back(new CGRASSLANE(0, (BOARD_HEIGHT - 1) * BLOCK_HEIGHT + START_HEIGHT));
}
void CGAME::saveData(string fileName) {
	ofstream file(fileName, ios::out);

	if (file.is_open()) {
		// <x> <y> <score> <isRight> //Thông tin người chơi
		file << cPlayer->getX() << " " << cPlayer->getY() << " " << cPlayer->getScore() << " " <<cPlayer->getIsAlive() <<" "<<cPlayer->getIsRight() << endl;
		file << this->level << endl;
		// <type lane ID> <isMoveRight> <timeCount> <isStop> <delayTime> [<object ID>/0]
		for (int i = 0; i < BOARD_HEIGHT; i++) {
			file << aLanes[i]->getID() << " " << aLanes[i]->getIsMoveRight() << " " << aLanes[i]->getTimeCount() << " " << aLanes[i]->getDelayTime() << " ";
			for (int j = 0; j < BOARD_WIDTH; j++) {
				file << aLanes[i]->PosID(j) << " ";
			}
			file << endl;
		}
		file << endl;
		file.close();
	}
	else {
		cout << "Can't open file." << endl;
	}
}
void CGAME::loadData(string fileName) {
	ifstream file(fileName, ios::in);
	if (file.is_open()) {
		int x, y, score;
		bool isRight,isAlive;//player
		// Doc thong tin nguoi choi
		file >> x >> y >> score >>isAlive >>isRight;
		cPlayer->set(x, y, isAlive,isRight, score);
		file >> level;
		for (int i = 0; i < BOARD_HEIGHT; i++) {
			bool direction;
			int laneID;
			int timeCount, delayTime;
			file >> laneID >> direction >> timeCount >> delayTime;
			switch (laneID) {
			case VEHICLELANE_ID: {
				aLanes.push_back(new CVEHICLELANE(0, i * BLOCK_HEIGHT, delayTime));
				break;
			}
			case GRASSLANE_ID: {
				aLanes.push_back(new CGRASSLANE(0, i * BLOCK_HEIGHT));
				break;
			}
			case RIVERLANE_LAND_ID: {
				aLanes.push_back(new CRIVERLANE(0, i * BLOCK_HEIGHT, delayTime, 1));
				break;
			}
			case RIVERLANE_NOLAND_ID: {
				aLanes.push_back(new CRIVERLANE(0, i * BLOCK_HEIGHT, delayTime, 0));
				break;
			}
			case TRAINLANE_ID: {
				aLanes.push_back(new CTRAINLANE(0, i * BLOCK_HEIGHT, delayTime, 0,0));
				break;
			}
			default:
				aLanes.push_back(NULL);
			}
			aLanes[i]->setIsMoveRight(direction);
			aLanes[i]->setTimeCount(timeCount);
			// Doc trang thai tung o
			for (int j = 0; j < BOARD_WIDTH; j++) {
				int posID;
				file >> posID;
				aLanes[i]->pushObj(j, posID);
			}
		}
		file.close();
	}
	else {
		cout << "Can't open file." << endl;
	}
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
bool CGAME::checkFileName(string fileName) {
	if (fileName.size() > 20 && fileName.size() <= 0) {
		cout << "Error over 20 characters." << endl;
		return false;
	}
	if (find(fileNameList.begin(), fileNameList.end(), fileName) != fileNameList.end())
	{
		cout << "Name has been existed." << endl;
		return false;
	}
	return true;
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
void CGAME::deleteFileName(int index)
{
	if (index >= 0 && index < fileNameList.size()) {
		fileNameList.erase(fileNameList.begin() + index);
		saveFileNameList();
		cout << "File name at index " << index << " has been deleted." << endl;
	}
	else {
		cout << "Invalid index. Cannot delete file name." << endl;
	}
}
void CGAME::changeFileName(int index) {
	if (index >= 0 && index < fileNameList.size()) {
		string newName;
		cout << "Enter the new file name: ";
		cin >> newName;

		if (find(fileNameList.begin(), fileNameList.end(), newName) != fileNameList.end()) {
			cout << "Name already exists. Cannot change file name." << endl;
			return;
		}

		fileNameList[index] = newName;
		saveFileNameList();
		cout << "File name at index " << index << " has been changed to " << newName << endl;
	}
	else {
		cout << "Invalid index. Cannot change file name." << endl;
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
	cPlayer->set(BOARD_WIDTH / 2, BOARD_HEIGHT - 1, true, 0);
	resetData();
	playGame();
}
void CGAME::LoadGame() {
	drawLoadGame();
	while (1) {
		int choice = inputUserNumber();
		if (choice == 11) {
			return;
		}
		else if (choice >= 1 && choice <= fileNameList.size()) {
			string selectedFileName = fileNameList[choice - 1];
			// draw options
			cout << "1. Load game" << endl;
			cout << "2. Delete name" << endl;
			cout << "3. Change name" << endl;
			cout << "4. Back" << endl;
			int choice1 = inputUserNumber();
			switch (choice1) {
			case 1:
				this->loadData(selectedFileName);
				this->playGame();
				break;
			case 2:
				this->deleteFileName(choice - 1);
				break;
			case 3:
				this->changeFileName(choice - 1);
				break;
			case 4:
				break;
			default:
				cout << "Invalid choice. Please enter a valid number" << endl;
				break;
			}
			break;
		}
		else {
			cout << "Invalid choice. Please enter a valid number" << endl;
		}
	}
}
string CGAME::SaveGame() {
	drawSaveGame();
	string fileName;
	if (!isSaved) {
		do {
			fileName = inputUserTxt();
		} while (!checkFileName(fileName));

		if (fileNameList.size() > 10) {
			fileNameList.pop_back();
		}
		fileNameList.push_front(fileName);
		saveFileNameList();
		saveData(fileName);
	}
	else {
		fileName = this->savename;
		ofstream file(fileName, ofstream::trunc);
		saveData(fileName);
	}
	isSaved = true;
	return fileName;
}
void CGAME::Setting() {

}
void CGAME::Help() {

}
void CGAME::About() {

}

void CGAME::SubThreadNewGame() {
	while (isThreadRunning) {
		{
			if (!cPlayer->isDead())
			{
				if (cPlayer->isMoving()) {
					cPlayer->eraseCharacter(ObjLayer);
					cPlayer->moveCharacter();
				}
				cPlayer->setMove(0);
				for (int i = 1; i < BOARD_HEIGHT - 1; i++) //ignore the first and the last lanes
					aLanes[i]->Move();
				//Xu ly va cham
				if (isInjured()) {
					cPlayer->setAlive(false);
					//Hieu ung va cham
					cout << cPlayer->getScore();
					continue;
				}
				//Xy ly finish
				if (cPlayer->isFinish()) {
					cPlayer->increaseScore();
					cPlayer->set(-1, BOARD_HEIGHT - 1);
					cPlayer->setFinish(false);
					resetData();
					startMap();
					displayBgd();
				}
				drawMap();
				displayObj();
			}
		}
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
	case '2': {
		this->savename = this->SaveGame();
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
bool CGAME::isInjured() const {
	return this->aLanes[this->cPlayer->getY()]->checkPos(this->cPlayer->getX());
}
bool CGAME::isReset() {
	do 	{
		this->drawPlayAgain();
		int temp = toupper(_getch());
		if (temp == 'Y') return true;
		else if (temp == 'N') return false;
	} while (1);
}

//Drawing functions
void CGAME::intro() {
	cout << "START!!!" << endl;
}
void CGAME::outtro() {
	cout << "End game" << endl;
}
void CGAME::drawMap() {
	for (int i = 0; i < BOARD_HEIGHT; i++)
		this->aLanes[i]->DrawObjects(ObjLayer);
	cPlayer->drawCharacter(ObjLayer);
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
void CGAME::drawSaveGame()
{
}

void CGAME::drawLoadGame()
{
	cout << "===== Load Game =====" << endl;
	if (fileNameList.empty()) {
		cout << "No saved games available." << endl;
	}
	else {
		for (int i = 0; i < fileNameList.size(); i++) {
			cout << i + 1 << ". " << fileNameList[i] << endl;
		}
	}
	cout << "11. Back to Main Menu" << endl;
	cout << "========================" << endl;
	cout << "Enter the number of the game: ";
}


void CGAME::drawInputUserTxt()
{
}

void CGAME::drawInputUserNumber()
{
}

void CGAME::displayBgd() {
	BgdLayer.display();
}
void CGAME::displayObj() {
	for (int i = 0; i < SCREEN_WIDTH; i++)
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			if (ObjLayer.screen[i][j].bgdColor == -1)
				ObjLayer.screen[i][j].bgdColor = BgdLayer.screen[i][j].bgdColor;
			if (ObjLayer.screen[i][j].txtColor == -1)
				ObjLayer.screen[i][j].txtColor = BgdLayer.screen[i][j].txtColor;
			if (ObjLayer.screen[i][j].buffer == L' ')
				ObjLayer.screen[i][j].buffer = BgdLayer.screen[i][j].buffer;
		}
	ObjLayer.display();
}
void CGAME::displayScreen() {
	BgdLayer.display();
	ObjLayer.display();
}


void ShowCur(bool CursorVisibility) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}
void DisableResizeWindow()
{
	HWND hWnd = GetConsoleWindow();
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}
void ShowScrollbar(BOOL Show)
{
	HWND hWnd = GetConsoleWindow();
	ShowScrollBar(hWnd, SB_BOTH, Show);
}
