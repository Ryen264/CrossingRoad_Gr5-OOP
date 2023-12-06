#include "CGAME.h"
CGAME::CGAME() {
	this->Configure();
	this->cPlayer = new CPLAYER(0, 0);
}
CGAME::~CGAME() {
	delete this->cPlayer;
	this->cPlayer = NULL;
	while (!aLanes.empty()) {
		CLANE* pointer = this->aLanes.back();
		this->aLanes.pop_back();
		if (pointer != NULL) delete pointer;
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
	ObjLayer.clear(-1, -1);
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
	system("cls");
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
		else {
			if (isReset()) {
				resetData();
				startMap();
				cPlayer->setMove(0);
				cPlayer->set(BOARD_WIDTH / 2, UP_LANE, true, 0);
			}
			else {
				exitThread(&threadNewGame);
				return;
			}
		}
	}
}

void CGAME::resetData() {
	if (level == 1) this->numberOfLane = 5;
	else this->numberOfLane += (1 + (rand() % 3));
	numberOfLane = 10;

	while (!aLanes.empty()) pop_backLane();
	aLanes.clear();

	push_frontLane(RIVERLANE_ID);
	push_frontLane(GRASSLANE_SURROUND_ID);
	push_frontLane(GRASSLANE_AROUND_ID);
	int numberOfRandomLane = (numberOfLane < BOARD_HEIGHT - 3) ? numberOfLane : BOARD_HEIGHT - 3;
	for (int i = 0; i < numberOfRandomLane; i++) pushRandomLane();
	for (int i = 0; i < BOARD_HEIGHT - 3 - numberOfRandomLane; i++) {
		if (i == 0) push_frontLane(FINISHLANE_ID);
		else if (i == 1) push_frontLane(GRASSLANE_FULL_ID);
		else push_frontLane(GRASSLANE_ID);
	}
}
void CGAME::saveData(string fileName) {
	ofstream file(fileName, ios::trunc);
	if (file.is_open()) {
		//CGAME: cPlayer: new, aLanes: new, fileNamelist: load, isSave = true, savedName = file name, <level>, <numberOfLane>, <conditionLane>, <countLane>, <numberOfConditionLane>, isThreadRunning = true, ObjLayer, bgdLayer: draw
		file << this->level << " " << this->numberOfLane << " " << this->conditionLane << " " << this->countLane << " " << this->numberOfConditionLane << endl;
		// <xBoard>(x) <yBoard>(y) (alive = 1) <score> <isRight> (finish = false) (moving = 0) <colorCharacter> (depend: get from lane[yBoard][xBoard]) (pCharacterR/L = new CDINOSAUR(x, y, true/left, colorCharacter) //Thông tin người chơi
		file << cPlayer->getXBoard() << " " << cPlayer->getYBoard() << " " << cPlayer->getIsAlive() << " " << cPlayer->getScore() << " " << cPlayer->getIsRight()
			<< " " << cPlayer->isFinish() << " " << 0 << " " << cPlayer->getColorCharacter() << endl;
		
		// (lane: push with ID) <isMoveRight> <timeCount> <isStop> <delayTime> (x, y: update) <ID> (block: new with ID) [<object ID>/0]
			//VEHICLE: ... <condition> <countObject> <numberOfCar*> <numberOfTruck*> <lightPos> <timeLight> (pTrafficLight = new with lightPos > 0) [<object ID>/0]
			//TRAIN: ... <numberOfTrain*> <countTrain> [<object ID>/0]
			//RIVER: ... <condition> <countObj> <numberOfCapybara*> [<object>/0]
			//GRASS: ... [<object>/0]
			//FINISH: ...
			//
			//TREE: isDouble*

		for (int i = 0; i < BOARD_HEIGHT; i++) {
			file << aLanes[i]->getID() << " " 
				 << aLanes[i]->getIsMoveRight()  << " " 
				 << aLanes[i]->getTimeCount() << " " 
				 << aLanes[i]->getDelayTime() << " ";
			switch (aLanes[i]->getID()) {
			case VEHICLELANE_ID:
{}
				
			}
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
			
			push_frontLane(laneID);
			aLanes.front()->setIsMoveRight(direction);
			aLanes.front()->setTimeCount(timeCount);
			// Doc trang thai tung o
			for (int j = 0; j < BOARD_WIDTH; j++) {
				int posID;
				file >> posID;
				aLanes[i]->pop_backObject();
				aLanes[i]->push_frontObject(posID);
			}
		}
		file.close();
	}
	else {
		cout << "Can't open file." << endl;
	}
}

string CGAME::inputUserTxt(CGRAPHIC& ObjLayer, CGRAPHIC& BgdLayer, int fromX, int fromY, int maxSize, int txtColor, int bgdColor, bool(*checkFunction)(char), deque<string> strArr) {
	string fileName = "";
	int size = (int)fileName.size();

	//draw current step
	ObjLayer.DrawInputPos(fromX, fromY, txtColor, bgdColor);
	if (size < maxSize) displayScreen(ObjLayer, BgdLayer, fromX, fromY, fromX + (size + 1) * 4, fromY + 2);
	else displayScreen(ObjLayer, BgdLayer, fromX, fromY, fromX + maxSize * 3 + maxSize - 1, fromY + 2);

	while (1) {
		char ch = _getch(); int temp = toupper(ch);
		//erase the last step
		if (size > 0)
		{
			if (size < maxSize) ObjLayer.erasePixel(fromX, fromY, fromX + size * 4 + 3, fromY + 2);
			else ObjLayer.erasePixel(fromX, fromY, fromX + maxSize * 4 - 1, fromY + 2);
			if (isDeleteButton(temp) || isBackspaceButton(temp)) {
				fileName.pop_back();
				size--;
			}
		}
		if (isEnterButton(temp) || isDownButton(temp)) return fileName;

		if (checkFunction(ch) && size < maxSize)
		{
			fileName.push_back(ch);
			size++;
		}

		//draw new string
		ObjLayer.drawString(fileName, fromX, fromY, txtColor, bgdColor);

		//draw new step
		ObjLayer.DrawInputPos(fromX + size * 4 + 1, fromY, txtColor, bgdColor);
		if (size < maxSize) displayScreen(ObjLayer, BgdLayer, fromX, fromY, fromX + size * 4 + 3, fromY + 2);
		else displayScreen(ObjLayer, BgdLayer, fromX, fromY, fromX + maxSize * 3 + maxSize - 1, fromY + 2);
	}
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
	const int fromX = 5, fromY = 18,
		toX = fromX + 40 - 1, toY = fromY + 27 - 1;
	const int xfromTalk = (160 - 41) / 2, yfromTalk = 38 - 10, xfromMessage = xfromTalk + 4, yfromMessage = yfromTalk + 3;

	const int xdrawerStart = 7 + fromX, ydrawerStart = fromY;
	const int NEW_GAME = ydrawerStart;
	const int LOAD_GAME = ydrawerStart + 4;
	const int SETTING = ydrawerStart + 4 * 2;
	const int HELP = ydrawerStart + 4 * 3;
	const int ABOUT = ydrawerStart + 4 * 4;
	const int QUIT = ydrawerStart + 4 * 5;
	//NewGame - LoadGame - Setting - Help - About - Quit
	vector<int> colorArr = { LIGHT_GREEN, BLUE, LIGHT_GRAY, BRIGHT_YELLOW, SADDLE_BROWN, RED };
	vector<string> messageArr = { "NEW GAME", "LOAD GAME", "SETTING", "HELP", "ABOUT", "QUIT" };
	int xOption = xdrawerStart, yOption = ydrawerStart;
	int iCur = 0, curColor = colorArr[iCur]; string curMessage = messageArr[iCur];

	//setup tmp layers
	CGRAPHIC tmpBgdLayer(BgdLayer), tmpObjLayer({ L' ', -1, -1 });

	//draw menu
	tmpBgdLayer.DrawDrawer(fromX, fromY + 3);

	//draw current step
	tmpObjLayer.DrawSmallDrawer(xOption, yOption, curColor);
	tmpObjLayer.DrawPerryTalk(curMessage, xfromTalk, yfromTalk, curColor, -1);
	displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
	displayScreen(tmpObjLayer, tmpBgdLayer, xfromTalk, yfromTalk, xfromTalk + 63 - 1, yfromTalk + 19 - 1);
	while (1) {
		int temp = toupper(_getch());

		//erase the last step
		tmpObjLayer.erasePixel(xOption, yOption, xOption + 32 - 1, yOption + 7 - 1);
		tmpObjLayer.erasePixel(xfromMessage, yfromMessage, xfromMessage + 33 - 1, yfromMessage + 3 - 1);
		if (isEnterButton(temp)) {
			//draw choice
			tmpObjLayer.DrawSmallDrawer(xOption, yOption, DARK_GREEN);
			tmpObjLayer.DrawPerryTalk(curMessage, xfromTalk, yfromTalk, curColor, -1);
			if (iCur != 0) tmpObjLayer.screen[xOption + 14][yOption].bgdColor = LIGHT_BROWN;
			displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
			displayScreen(tmpObjLayer, tmpBgdLayer, xfromTalk, yfromTalk, xfromTalk + 63 - 1, yfromTalk + 19 - 1);

			Sleep(500);
			switch (yOption) {
			case NEW_GAME:
				this->NewGame();
				break;
			case LOAD_GAME:
				this->LoadGame();
				break;
			case SETTING:
				this->Setting();
				break;
			case HELP:
				this->Help();
				break;
			case ABOUT:
				this->About();
				break;
			case QUIT:
				return QUIT_CODE;
			}
		}
		else {
			if (isUpButton(temp) && iCur > 0) {
				iCur--;
				yOption -= 4;
			}
			if (isDownButton(temp) && iCur < 5) {
				iCur++;
				yOption += 4;
			}
			//update new step
			curColor = colorArr[iCur];
			curMessage = messageArr[iCur];
		}
		tmpObjLayer.DrawSmallDrawer(xOption, yOption, curColor);
		tmpObjLayer.DrawPerryTalk(curMessage, xfromTalk, yfromTalk, curColor, -1);
		if (iCur != 0) tmpObjLayer.screen[xOption + 14][yOption].bgdColor = LIGHT_BROWN;
		displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
		displayScreen(tmpObjLayer, tmpBgdLayer, xfromTalk, yfromTalk, xfromTalk + 63 - 1, yfromTalk + 19 - 1);
	}
	return 0;
}

void CGAME::NewGame() {
	cPlayer->set(BOARD_WIDTH / 2, UP_LANE, true, 0);
	resetData();
	playGame();
}
void CGAME::LoadGame() {
    loadFileNameList();
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
void CGAME::SaveGame() {
	const int fromX = (SCREEN_WIDTH - 54) / 2, fromY = (SCREEN_HEIGHT - 30) / 2,
		toX = fromX + 54 - 1, toY = fromY + 30 - 1;

	const int INPUT_OPTION = 11 + fromX;
	const int OK_OPTION = 26 + fromX;
	const int BACK_OPTION = 37 + fromX;
	const int yFirstLine = 14 + fromY, ySecondLine = 23 + fromY;
	const int MAX_INPUT_SIZE = 8;

	int xOption = INPUT_OPTION, yOption = yFirstLine;
	string fileName{};
	int curSize = (int)fileName.size();

	//setup tmpLayers
	CGRAPHIC tmpBgdLayer(BgdLayer), tmpObjLayer({ L' ', -1, -1 });
	//draw menu
	tmpBgdLayer.DrawSaveScreen(fromX, fromY);
	tmpBgdLayer.screen[fromX + 50][fromY] = BgdLayer.screen[fromX + 50][fromY];
	tmpBgdLayer.screen[fromX + 51][fromY] = BgdLayer.screen[fromX + 51][fromY];
	tmpBgdLayer.screen[fromX + 52][fromY] = BgdLayer.screen[fromX + 52][fromY];
	tmpBgdLayer.screen[fromX + 53][fromY] = BgdLayer.screen[fromX + 53][fromY];
	tmpBgdLayer.screen[fromX + 52][fromY + 1] = BgdLayer.screen[fromX + 52][fromY + 1];
	tmpBgdLayer.screen[fromX + 53][fromY + 1] = BgdLayer.screen[fromX + 53][fromY + 1];

	//draw current pos
	switch (xOption) {
	case INPUT_OPTION:
		tmpObjLayer.drawRegtangle(xOption, yOption, MAX_INPUT_SIZE * 4, 3, LIGHT_GREEN);
		tmpObjLayer.drawString(fileName, xOption, yOption, BLACK, -1);
		break;
	case OK_OPTION:
		tmpObjLayer.drawButton(xOption, yOption, DARK_GREEN, LIGHT_GREEN);
		break;
	case BACK_OPTION:
		tmpObjLayer.drawButton(xOption, yOption, DARK_RED, RED);
		break;
	}
	displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
	while (1) {
		int temp = toupper(_getch());

		//erase the last step
		switch (xOption) {
		case INPUT_OPTION:
			tmpObjLayer.erasePixel(xOption, yOption, xOption + MAX_INPUT_SIZE * 4 - 1, yOption + 2);
			break;
		case OK_OPTION: case BACK_OPTION:
			tmpObjLayer.erasePixel(xOption, yOption, xOption + 8 - 1, yOption + 4 - 1);
			break;
		}

		if (!isEnterButton(temp)) {
			if (isUpButton(temp)) {
				switch (xOption) {
				case OK_OPTION: case BACK_OPTION:
					xOption = INPUT_OPTION;
					yOption = yFirstLine;
					break;
				}
			}
			if (isDownButton(temp)) {
				switch (xOption) {
				case INPUT_OPTION:
					xOption = OK_OPTION;
					yOption = ySecondLine;
					break;
				}
				if (isRightButton(temp) || isLeftButton(temp)) {
					switch (xOption) {
					case OK_OPTION:
						xOption = BACK_OPTION;
						break;
					case BACK_OPTION:
						xOption = OK_OPTION;
						break;
					}
				}

				//draw new step
				switch (xOption) {
				case INPUT_OPTION:
					tmpObjLayer.drawRegtangle(xOption, yOption, MAX_INPUT_SIZE * 4, 3, LIGHT_GREEN);
					tmpObjLayer.drawString(fileName, xOption, yOption, BLACK, -1);
					break;
				case OK_OPTION:
					tmpObjLayer.drawButton(xOption, yOption, DARK_GREEN, LIGHT_GREEN);
					break;
				case BACK_OPTION:
					tmpObjLayer.drawButton(xOption, yOption, DARK_RED, LIGHT_GREEN);
					break;
				}
				displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
			}
			else {
				//draw choice
				switch (xOption) {
				case INPUT_OPTION:
					tmpObjLayer.drawRegtangle(xOption, yOption, MAX_INPUT_SIZE * 4, 3, DARK_GREEN);
					tmpObjLayer.drawString(fileName, xOption, yOption, BLACK, -1);
					break;
				case OK_OPTION:
					tmpObjLayer.drawButton(xOption, yOption, DARK_GREEN, DARK_GREEN);
					break;
				case BACK_OPTION:
					tmpObjLayer.drawButton(xOption, yOption, DARK_RED, DARK_RED);
					break;
				}
				displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);

				Sleep(500);
				switch (xOption) {
				case OK_OPTION:
					isSaved = true;
					savedName = fileName;
					if ((int)fileNameList.size() >= 10) fileNameList.pop_back();
					fileNameList.push_front(fileName);
					saveFileNameList();
					saveData(fileName);
					return;
				case BACK_OPTION:
					return;
				case INPUT_OPTION:
					fileName = inputUserTxt(ObjLayer, BgdLayer, xOption, yOption, MAX_INPUT_SIZE, DARK_GREEN, LIGHT_GREEN, isNumberOrLetter, fileNameList);
					if (fileName != "") {
						xOption = OK_OPTION;
						yOption = ySecondLine;
					}
					break;
				}
			}
			switch (xOption) {
			case INPUT_OPTION:
				tmpObjLayer.drawRegtangle(xOption, yOption, xOption + MAX_INPUT_SIZE * 4 - 1, yOption + 2, LIGHT_GREEN);
				tmpObjLayer.drawString(fileName, xOption, yOption, BLACK, -1);
				break;
			case OK_OPTION:
				tmpObjLayer.drawButton(xOption, yOption, DARK_GREEN, LIGHT_GREEN);
				break;
			case BACK_OPTION:
				tmpObjLayer.drawButton(xOption, yOption, DARK_RED, LIGHT_GREEN);
				break;
			}
			displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
		}
	}
}
void CGAME::Setting() {
	const int fromX = (SCREEN_WIDTH - 53) / 2, fromY = (SCREEN_HEIGHT - 30) / 2,
		toX = fromX + 53 - 1, toY = fromY + 30 - 1;

	const int BACKGROUND_YSOUND = 13 + fromY;
	const int EFFECT_YSOUND = 17 + fromY;
	const int OK_XOPTION = 26 + fromX;
	const int BACK_XOPTION = 37 + fromX;

	const int XSOUND = 10 + fromX;
	const int YOPTION = 22 + fromY;

	int xOption = XSOUND, yOption = BACKGROUND_YSOUND;
	int curBgdSound = bgdSoundLevel, curEffectSound = effectSoundLevel;

	// setup tmpLayers
	CGRAPHIC tmpBgdLayer(BgdLayer), tmpObjLayer({ L' ',-1,-1 });

	// draw menu
	tmpBgdLayer.DrawSettingScreen(fromX, fromY);
	tmpBgdLayer.screen[fromX + 50][fromY] = BgdLayer.screen[fromX + 50][fromY];
	tmpBgdLayer.screen[fromX + 51][fromY] = BgdLayer.screen[fromX + 51][fromY];
	tmpBgdLayer.screen[fromX + 52][fromY] = BgdLayer.screen[fromX + 52][fromY];
	tmpBgdLayer.screen[fromX + 53][fromY] = BgdLayer.screen[fromX + 53][fromY];
	tmpBgdLayer.screen[fromX + 52][fromY + 1] = BgdLayer.screen[fromX + 52][fromY + 1];
	tmpBgdLayer.screen[fromX + 53][fromY + 1] = BgdLayer.screen[fromX + 53][fromY + 1];

	//draw the last sound levels
	tmpObjLayer.drawRegtangle(XSOUND, BACKGROUND_YSOUND, (curBgdSound / 25) * 8.75, 3, LIGHT_GRAY,true);
	tmpObjLayer.drawRegtangle(XSOUND, EFFECT_YSOUND, (curEffectSound / 25) * 8.75, 3, LIGHT_GRAY,true);
	//if (xOption == XSOUND) {
	//	//draw the last sound levels
	//	if (yOption == BACKGROUND_YSOUND) tmpObjLayer.drawRegtangle(XSOUND, BACKGROUND_YSOUND, (curBgdSound / 25) * 8.75, 3, LIGHT_GREEN,true);
	//	else tmpObjLayer.drawRegtangle(XSOUND, EFFECT_YSOUND, (curEffectSound / 25) * 8.75, 3, LIGHT_BROWN,true);
	//}
	//else {
	//	tmpObjLayer.drawButton(xOption, yOption, WHITE,BLACK);
	//}

	// draw current pos
	if (xOption == XSOUND) {
		if (yOption == BACKGROUND_YSOUND) tmpObjLayer.drawRegtangle(xOption, yOption, (curBgdSound / 25) * 8.75, 3, LIGHT_GREEN, true);
		else tmpObjLayer.drawRegtangle(xOption, yOption, (curEffectSound / 25) * 8.75, 3, LIGHT_BROWN , true);
	}
	else {
		if (xOption == OK_XOPTION) tmpObjLayer.drawButton(xOption, yOption, DARK_GREEN, LIGHT_GREEN);
		else tmpObjLayer.drawButton(xOption, yOption, DARK_RED, RED);
	}

	displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
	while (1) {
		int temp = toupper(_getch());

		// erase the last step
		if (xOption == XSOUND) { 
			//if (yOption == BACKGROUND_YSOUND) {
			//	tmpObjLayer.drawRegtangle(XSOUND, BACKGROUND_YSOUND, (curBgdSound / 25) * 8.75, 3, LIGHT_GRAY, true);
			//}
			//else { 
			//	tmpObjLayer.drawRegtangle(XSOUND, EFFECT_YSOUND, (curEffectSound / 25) * 8.75, 3, LIGHT_GRAY, true); 
			//}
			tmpObjLayer.erasePixel(xOption, yOption, xOption + 35 - 1, yOption + 3 - 1);
		}
		else {
			tmpObjLayer.erasePixel(xOption, yOption, xOption + 8 - 1, yOption + 4 - 1);
			//if (yOption == OK_XOPTION) {
			//	tmpObjLayer.drawRegtangle(XSOUND,EFFECT_YSOUND, (curEffectSound / 25) * 8.75, 3, LIGHT_GRAY, true);
			//	tmpObjLayer.drawButton(xOption, yOption, WHITE, BLACK);
			//}
			//tmpObjLayer.drawButton(xOption, yOption, WHITE, BLACK);
		}

		if (!isEnterButton(temp)) {
			if (isUpButton(temp)) {
				if (xOption == XSOUND) {
					if (yOption == EFFECT_YSOUND) yOption = BACKGROUND_YSOUND;
				}
				else {
					xOption = XSOUND;
					yOption = EFFECT_YSOUND;
				}
			}
			if (isDownButton(temp)) {
				if (xOption == XSOUND) {
					if (yOption == BACKGROUND_YSOUND) yOption = EFFECT_YSOUND;
					else {
						xOption = OK_XOPTION;
						yOption = YOPTION;
					}
				}
			}
			if (isRightButton(temp)) {
				if (xOption == XSOUND) {
					if (yOption == BACKGROUND_YSOUND)
					{
						if (curBgdSound < 100) curBgdSound += 25;
					}
					else if (curEffectSound < 100) curEffectSound += 25;
				}
				else {
					if (xOption == OK_XOPTION) xOption = BACK_XOPTION;
					else xOption = OK_XOPTION;
				}
			}
			if (isLeftButton(temp)) {
				if (xOption == XSOUND) {
					if (yOption == BACKGROUND_YSOUND)
					{
						if (curBgdSound > 0) curBgdSound -= 25;
					}
					else if (curEffectSound > 0) curEffectSound -= 25;
				}
				else {
					if (xOption == OK_XOPTION) xOption = BACK_XOPTION;
					else xOption = OK_XOPTION;
				}
			}
			// draw new step
		}
		else {
			//draw choice
			if (xOption == XSOUND) {
				if (yOption == BACKGROUND_YSOUND) {
					tmpObjLayer.drawRegtangle(xOption, yOption, (curBgdSound / 25) * 8.75, 3, DARK_GREEN, true);
				}
				else tmpObjLayer.drawRegtangle(xOption, yOption, (curEffectSound / 25) * 8.75, 3, DARK_GREEN, true);
			}
			else {
				if (xOption == OK_XOPTION) tmpObjLayer.drawButton(xOption, yOption, DARK_GREEN, DARK_GREEN);
				else tmpObjLayer.drawButton(xOption, yOption, DARK_RED, DARK_RED);
			}
			displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);

			Sleep(500);
			if (xOption == XSOUND) {
				
				if (yOption == BACKGROUND_YSOUND) {
					yOption = EFFECT_YSOUND;
				}
				else if (yOption == EFFECT_YSOUND) {
					xOption = OK_XOPTION;
					yOption = YOPTION;
				}
			}
			else {
				if (xOption == OK_XOPTION) {
					bgdSoundLevel = curBgdSound;
					effectSoundLevel = curEffectSound;
					//playSound again
					return;
				}
				else return;
			}
			//reset the choice
		}
		tmpObjLayer.drawRegtangle(XSOUND, BACKGROUND_YSOUND, (curBgdSound / 25) * 8.75, 3, LIGHT_GRAY, true);
		tmpObjLayer.drawRegtangle(XSOUND, EFFECT_YSOUND, (curEffectSound / 25) * 8.75, 3, LIGHT_GRAY, true);
		if (xOption == XSOUND) {
			if (yOption == BACKGROUND_YSOUND) { 
				tmpObjLayer.drawRegtangle(xOption, yOption, (curBgdSound / 25) * 8.75, 3, LIGHT_GREEN, true);
			}
			else tmpObjLayer.drawRegtangle(xOption, yOption, (curEffectSound / 25) * 8.75, 3, LIGHT_GREEN, true);
		}
		else {
			if (xOption == OK_XOPTION) tmpObjLayer.drawButton(xOption, yOption, DARK_GREEN, LIGHT_GREEN);
			else tmpObjLayer.drawButton(xOption, yOption, DARK_RED, RED);
		}
		displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
	}
}

void CGAME::Help() {
	CGRAPHIC tmpBgdLayer(BgdLayer);

	vector<string> bodycontent = {
		"- KEYS:                             ",
		"  + W - UPWARD ARROW              UP",
		"  + S - DOWN ARROW              DOWN",
		"  + A - LEFT ARROW              LEFT",
		"  + D - RIGHT ARROW            RIGHT",
		"  + ENTER - SPACE               MARK",
		"  + P							PAUSE",
		"- RULE:                             ",
		"  TRY TO SURVICE AND COLLECT EGGS!!!"
	};

	int maxWidth = 0;
	for (const string& line : bodycontent) {
		if (line.length() > maxWidth) {
			maxWidth = line.length();
		}
	}
	int width = maxWidth+18; 
	int height = bodycontent.size()*2+10; 
	
	const int fromX = (SCREEN_WIDTH - width) / 2, fromY = (SCREEN_HEIGHT - height) / 2,
		toX = fromX + width - 1, toY = fromY + height - 1;
	
	tmpBgdLayer.DrawTextBoard("HELP", BRIGHT_YELLOW, bodycontent, fromX, fromY, width, height, BLACK, SAND);
	
	displayScreen(tmpBgdLayer, tmpBgdLayer, fromX, fromY, toX, toY);
	_getch();

	tmpBgdLayer.DrawTextBoard("HELP", DARK_RED, bodycontent, fromX, fromY, 53, 29, BLACK, WHITE);
	displayScreen(tmpBgdLayer, tmpBgdLayer, fromX, fromY, toX, toY);
	_getch();
}

void CGAME::About() {
	CGRAPHIC tmpBgdLayer(BgdLayer);

	vector<string> bodycontent = {
		"              <<TEACHER>>           ",
		"            Truong Toan Thinh       ",
		"									 ",			
		"           <<GROUP'S MEMBER>>      ",
		"      22127029 - Le Nguyen Gia Bao  ",
		"      22127445 - Nguyen Lam Nha Uyen",
		"      22127385 - Nguyen Quoc Thang  ",
		"      22127301 - Nguyen Gia Nguyen  ",
	};

	int maxWidth = 0;
	for (const string& line : bodycontent) {
		if (line.length() > maxWidth) {
			maxWidth = line.length();
		}
	}
	int width = maxWidth + 18;
	int height = bodycontent.size() + 20;

	const int fromX = (SCREEN_WIDTH - width) / 2, fromY = (SCREEN_HEIGHT - height) / 2,
		toX = fromX + width - 1, toY = fromY + height - 1;

	tmpBgdLayer.DrawTextBoard("ABOUT", DARK_RED, bodycontent, fromX, fromY, width, height, BLACK, SAND);


	displayScreen(tmpBgdLayer, tmpBgdLayer, fromX, fromY, toX, toY);
	_getch();
}

int CGAME::Pause(HANDLE t) {
	SuspendThread(t);
	const int fromX = (SCREEN_WIDTH - 53) / 2, fromY = (SCREEN_HEIGHT - 30) / 2,
		toX = fromX + 53 - 1, toY = fromY + 30 - 1;

	const int SETTING_OPTION = 7 + fromX;
	const int RESUME_OPTION = 23 + fromX;
	const int HELP_OPTION = 39 + fromX;
	const int SAVE_OPTION = 15 + fromX;
	const int EXIT_OPTION = 31 + fromX;
	const int CHARACTER_OPTION = 5 + fromX;
	const int yFirstLine = 15 + fromY, ySecondLine = 24 + fromY;

	int xOption = RESUME_OPTION, yOption = yFirstLine;

	//setup tmpLayers
	CGRAPHIC tmpBgdLayer(BgdLayer), tmpObjLayer({ L' ', -1, -1 });
	//draw menu
	tmpBgdLayer.DrawPauseMenu(fromX, fromY);
	displayScreen(tmpBgdLayer, tmpBgdLayer, fromX, fromY, toX, toY);

	//draw character name
	tmpObjLayer.drawString(cPlayer->getNameCharacter(), 24 + fromX, 4 + fromY, cPlayer->getColorCharacter(), SAND);
	//draw character
	CDINOSAUR characterSample(fromX + 5, fromY + 3, true, cPlayer->getColorCharacter());
	characterSample.DrawBlock(tmpObjLayer);
	//draw current cell
	tmpObjLayer.drawCell(xOption, yOption, LIGHT_GREEN);

	displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
	while (1) {
		int temp = toupper(_getch());

		//erase the last step
		if (xOption != CHARACTER_OPTION)
			tmpObjLayer.erasePixel(xOption, yOption, xOption + 7, yOption + 4);
		else {
			tmpObjLayer.erasePixel(xOption, yOption, xOption + 17, yOption + 8);
			characterSample.DrawBlock(tmpObjLayer);
		}

		if (!isEnterButton(temp)) {
			if (isUpButton(temp)) {
				switch (xOption) {
				case SAVE_OPTION:
					xOption = RESUME_OPTION;
					yOption = yFirstLine;
					break;
				case EXIT_OPTION:
					xOption = HELP_OPTION;
					yOption = yFirstLine;
					break;
				case SETTING_OPTION: case RESUME_OPTION: case HELP_OPTION:
					xOption = CHARACTER_OPTION;
					yOption = 2 + fromY;
					break;
				}
			}
			if (isDownButton(temp)) {
				switch (xOption) {
				case SETTING_OPTION:
					xOption = SAVE_OPTION;
					yOption = ySecondLine;
					break;
				case RESUME_OPTION: case HELP_OPTION:
					xOption = EXIT_OPTION;
					yOption = ySecondLine;
					break;
				case CHARACTER_OPTION:
					xOption = SETTING_OPTION;
					yOption = yFirstLine;
					break;
				}
			}
			if (isRightButton(temp)) {
				switch (xOption) {
				case SETTING_OPTION:
					xOption = RESUME_OPTION;
					break;
				case RESUME_OPTION:
					xOption = HELP_OPTION;
					break;
				case SAVE_OPTION:
					xOption = EXIT_OPTION;
					break;
				case CHARACTER_OPTION:
					xOption = RESUME_OPTION;
					yOption = yFirstLine;
					break;
				}
			}
			if (isLeftButton(temp)) {
				switch (xOption) {
				case HELP_OPTION:
					xOption = RESUME_OPTION;
					break;
				case RESUME_OPTION:
					xOption = SETTING_OPTION;
					break;
				case EXIT_OPTION:
					xOption = SAVE_OPTION;
					break;
				case CHARACTER_OPTION:
					xOption = SETTING_OPTION;
					yOption = yFirstLine;
					break;
				}
			}

			//draw new step
			if (xOption != CHARACTER_OPTION) tmpObjLayer.drawCell(xOption, yOption, LIGHT_GREEN);
			else tmpObjLayer.drawCharacterFrame(xOption, yOption, LIGHT_GREEN);
			displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
		}
		else {
			//draw choice
			if (xOption != CHARACTER_OPTION) tmpObjLayer.drawCheck(xOption, yOption);
			else tmpObjLayer.drawCharacterFrame(xOption, yOption, DARK_GREEN);
			displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);

			Sleep(500);
			switch (xOption) {
			case CHARACTER_OPTION:
				ChooseCharacter();
				//update new character name
				tmpObjLayer.erasePixel(24 + fromX, 4 + fromY, 24 + fromX + 23, 4 + fromY + 3);
				tmpObjLayer.drawString(cPlayer->getNameCharacter(), 24 + fromX, 4 + fromY, cPlayer->getColorCharacter(), SAND);
				//update new character color
				characterSample.setColor(cPlayer->getColorCharacter());
				tmpObjLayer.erasePixel(xOption, yOption, xOption + 17, yOption + 8);
				characterSample.DrawBlock(tmpObjLayer);
				break;
			case SETTING_OPTION:
				//setting
				break;
			case RESUME_OPTION:
				resumeThread(t);
				return 0;
			case HELP_OPTION:
				//help
				break;
			case SAVE_OPTION:
				if (isSaved) saveData(savedName);
				else SaveGame();
				resumeThread(t);
				return 0;
			case EXIT_OPTION:
				resumeThread(t);
				savedName = "";
				isSaved = false;
				return BACK_TO_MENU_CODE;
			}
			//reset choice
			tmpObjLayer.drawCharacterFrame(xOption, yOption, LIGHT_GREEN);
			displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
		}
	}
	return 0;
}
void CGAME::ChooseCharacter() {
	const int fromX = (SCREEN_WIDTH - 53) / 2, fromY = (SCREEN_HEIGHT - 30) / 2,
		toX = fromX + 53 - 1, toY = fromY + 30 - 1;

	vector<vector<int>> colorArr = { {RED, BLUE, DARK_GREEN}, {BRIGHT_YELLOW, ORANGE, SADDLE_BROWN}, {DARK_GRAY, DARK_RED, DARK_BLUE} };

	const int xcellStart = 6 + fromX, ycellStart = 11 + fromY;

	int curColor = cPlayer->getColorCharacter(); string curName = cPlayer->getNameCharacter();
	int iCur = getiMatrix(curColor, colorArr), jCur = getjMatrix(curColor, colorArr);
	int xOption = xcellStart + jCur * 14, yOption = ycellStart + iCur * 6;

	//setup tmpLayers
	CGRAPHIC tmpBgdLayer(BgdLayer), tmpObjLayer({ L' ', -1, -1 });
	//draw menu
	tmpBgdLayer.DrawChooseCharacterMenu(fromX, fromY);

	//draw character name
	tmpObjLayer.drawString(curName, 24 + fromX, 4 + fromY, curColor, SAND);
	//draw character
	CDINOSAUR characterSample(fromX + 5, fromY + 3, true, curColor);
	characterSample.DrawBlock(tmpObjLayer);
	//draw current cell
	tmpObjLayer.drawCell(xOption, yOption, LIGHT_GREEN);
	
	displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
	while (1) {
		int temp = toupper(_getch());

		//erase the last step
		tmpObjLayer.erasePixel(xOption, yOption, xOption + 7, yOption + 4);
		if (!isEnterButton(temp)) {
			if (isUpButton(temp))
				if (iCur > 0)
				{
					yOption -= 6;
					iCur--;
				}
			if (isDownButton(temp))
				if (iCur < 2)
				{
					yOption += 6;
					iCur++;
				}
			if (isRightButton(temp))
				if (jCur < 2)
				{
					xOption += 14;
					jCur++;
				}
			if (isLeftButton(temp))
				if (jCur > 0)
				{
					xOption -= 14;
					jCur--;
				}
			//update new color
			curColor = colorArr[iCur][jCur];
			//draw new step
			tmpObjLayer.drawCell(xOption, yOption, LIGHT_GREEN);
			//draw new model color
			characterSample.setColor(curColor);
			characterSample.DrawBlock(tmpObjLayer);

			displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
		}
		else {
			//draw choice
			tmpObjLayer.drawCheck(xOption, yOption);
			//set new character color
			cPlayer->setColorCharacter(curColor);
			//draw new name
			tmpObjLayer.erasePixel(24 + fromX, 4 + fromY, 24 + fromX + 23, 4 + fromY + 3);
			curName = cPlayer->getNameCharacter();
			tmpObjLayer.drawString(curName, 24 + fromX, 4 + fromY, curColor, SAND);

			displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
			Sleep(500);
			return;
		}
	}
}

bool CGAME::isReset() {
	do {
		this->drawPlayAgain();
		int temp = toupper(_getch());
		if (temp == 'Y') return true;
		else if (temp == 'N') return false;
	} while (1);
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

bool CGAME::isInjured() const {
    return this->aLanes[this->cPlayer->getYBoard()]->checkPos(this->cPlayer->getXBoard());
}
void CGAME::updateYLane() {
	for (int i = 0; i < (int)aLanes.size(); i++)
		if (aLanes[i] != NULL) aLanes[i]->setyBoard(i);
}
void CGAME::pushRandomLane()
{
	//Random push a river/trainlane or 1-2 vehiclelane and a grasslane after 3 others
	if (conditionLane == 0) {
		int ID = random(LANE_ID_LIST);
		push_frontLane(ID);
		switch (ID) {
		case VEHICLELANE_ID: case TRAINLANE_ID: {
			countLane = 1;
			numberOfConditionLane = 1 + rand() % 2;
			if (numberOfConditionLane > 1) conditionLane = ID;
			else conditionLane = GRASSLANE_ID;
			break;
		}
		case RIVERLANE_ID: {
			conditionLane = GRASSLANE_ID;
			break;
		}
		default:
			conditionLane = 0;
		}
	}
	else {
		push_frontLane(conditionLane);
		switch (conditionLane) {
		case GRASSLANE_ID: {
			countLane = 0;
			numberOfConditionLane = 0;
			conditionLane = 0;
			break;
		}
		case VEHICLELANE_ID: case TRAINLANE_ID: {
			countLane++;
			if (countLane >= numberOfConditionLane) conditionLane = GRASSLANE_ID;
			break;
		}
		default:
			conditionLane = 0;
		}
	}
}
void CGAME::push_frontLane(int ID) {
	if (ID == 0) ID = GRASSLANE_ID;
    for (int i = 0; i < (int)aLanes.size(); i++)
        if (aLanes[i] != NULL) aLanes[i]->setyBoard(i + 1);

    // delay time cang nho thi push cang nhanh , delaytime ti le ngich vs level
	// level 1-3 : speed rand() %4 ; level 4-7 : rand() % 3 ; level >=8 : rand() %2
	
	switch (ID) {
	case VEHICLELANE_ID: {
		aLanes.push_front(new CVEHICLELANE(0, 0, rand() % 3));
		break;
	}
	case GRASSLANE_ID: {
		aLanes.push_front(new CGRASSLANE(0, 0));
		break;
	}
	case TRAINLANE_ID: {
		aLanes.push_front(new CTRAINLANE(0, 0, rand() % 2, 10 + rand() % 5));
		break;
	}
	case RIVERLANE_ID: {
		aLanes.push_front(new CRIVERLANE(0, 0, rand() % 3));
		break;
	}
	case FINISHLANE_ID: {
		aLanes.push_front(new CFINISHLANE(0, 0));
		break;
	}
	case GRASSLANE_FULL_ID: {
		aLanes.push_front(new CGRASSLANE(0, 0, FULL_TREE_TYPELANE));
		break;
	}
	case GRASSLANE_SURROUND_ID: {
		aLanes.push_front(new CGRASSLANE(0, 0, SURROUND_TREE_TYPELANE));
		break;
	}
	case GRASSLANE_AROUND_ID: {
		aLanes.push_front(new CGRASSLANE(0, 0, AROUND_TREE_TYPELANE));
		break;
	}
	default:
		aLanes.push_front(new CGRASSLANE(0, 0));
	}
	updateYLane();
}
void CGAME::pop_backLane() {
	CLANE* tmp = aLanes.back();
	aLanes.pop_back();
	if (tmp != NULL) delete tmp;
	tmp = NULL;
}
void CGAME::moveNewLane() {
	if (numberOfLane > BOARD_HEIGHT - 3) pushRandomLane();
	else if (numberOfLane == BOARD_HEIGHT - 3) push_frontLane(FINISHLANE_ID);
	else if (numberOfLane == BOARD_HEIGHT - 4) push_frontLane(GRASSLANE_FULL_ID);
	else push_frontLane(GRASSLANE_ID);
	pop_backLane();
	numberOfLane--;
}

void CGAME::SubThreadNewGame() {
    while (isThreadRunning) {
        if (!cPlayer->isDead()) {
            //Lane move
            for (int i = 0; i < BOARD_HEIGHT; i++) aLanes[i]->Move();

            int xBoard = cPlayer->getXBoard(), yBoard = cPlayer->getYBoard();
            int xBoardNext{}, yBoardNext{};
            switch (cPlayer->getMoving()) {
            case UP:
                xBoardNext = xBoard; yBoardNext = yBoard - 1;
                break;
            case DOWN:
                xBoardNext = xBoard; yBoardNext = yBoard + 1;
                break;
            case LEFT:
                xBoardNext = xBoard - 1; yBoardNext = yBoard;
                break;
            case RIGHT:
                xBoardNext = xBoard + 1; yBoardNext = yBoard;
                break;
            default:
                xBoardNext = xBoard; yBoardNext = yBoard;
            }
            COBJECT* nextObj = aLanes[yBoardNext]->getPos(xBoardNext);
			
			aLanes[yBoard]->injuredPlayer(*cPlayer);
            
			//Update player's pos with depend obj and delete depend obj if the func returns true
            switch (cPlayer->updateDepend()) {
            case EGG_ID: {
                COBJECT* cur = aLanes[yBoard]->getPos(xBoard);
                if (cur != NULL) delete cur;
                cur = NULL;
                aLanes[yBoard]->setPos(xBoard, NULL);
                cPlayer->setDependObj(NULL);
                break;
            }
            case PERRY_ID: {
				COBJECT* cur = aLanes[yBoard]->getPos(xBoard);
				aLanes[yBoard]->setPos(xBoard, NULL);
				if (cur != NULL) delete cur;
				cur = NULL;
                if (!(nextObj->getID() == TREE_ID)) cPlayer->setPos(xBoard, yBoard - 1);
				cPlayer->setDependObj(NULL);
                break;
            }
            }

			if (cPlayer->isMoving() && !(nextObj->getID() == TREE_ID)) {
				if (cPlayer->moveCharacter()) {
					moveNewLane();
					startMap();
				};
				//Reset moving
				cPlayer->setMove(0);
				//Update depend obj 
				cPlayer->setDependObj(nextObj);
			}
			
            drawMap();
            displayScreen();

            if (cPlayer->isDead()) {
                //Hieu ung va cham
				cout << cPlayer->getScore() << " " << this->level << endl;
                continue;
            }
            //Xy ly finish
            if (cPlayer->isFinish() || numberOfLane == -1) {
                cPlayer->increaseScore();
                cPlayer->set(BOARD_WIDTH / 2, UP_LANE);
                cPlayer->setFinish(false);
                resetData();
                startMap();
				this->level++;
            }
			Sleep(100);
        }
    }
}

// Time
void CGAME::updateTime() {
	endTime = clock();
	if (endTime - startTime > 0) {
		curTime += (endTime - startTime);
		startTime = endTime;
		ObjLayer.drawTime(curTime, SCREEN_WIDTH - 17, 0, BLACK, -1);
		//ObjLayer.display(0, 0, SCREEN_WIDTH, 2);
	}
}
string CGAME::getTime(clock_t curTime) {
	ostringstream oss;
	oss << curTime;
	return oss.str();
}
clock_t CGAME::setTime(string& time) {
	istringstream iss(time);
	clock_t result;
	iss >> result;
	return result;
}



//Drawing functions
void CGAME::startMap() {
	BgdLayer.clear(BLACK, WHITE);
	for (int i = 0; i < BOARD_HEIGHT; i++)
		aLanes[i]->DrawLane(BgdLayer);
}
void CGAME::drawMap() {
	ObjLayer.clear(-1, -1);
	for (int i = 0; i < BOARD_HEIGHT; i++)
		this->aLanes[i]->DrawObjects(ObjLayer);
	cPlayer->drawCharacter(ObjLayer);
}

void CGAME::intro() {
	cout << "START!!!" << endl;
}
void CGAME::outtro() {
	cout << "End game" << endl;
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

void CGAME::displayScreen(int fromX, int fromY, int toX, int toY) {
	if (toX < 0 || toX > SCREEN_WIDTH - 1) toX = SCREEN_WIDTH - 1;
	if (toY < 0 || toY > SCREEN_HEIGHT - 1) toY = SCREEN_HEIGHT - 1;
	for (int x = fromX; x <= toX; x++)
		for (int y = fromY; y <= toY; y++) {
			PIXEL& objPixel = ObjLayer.screen[x][y], bgdPixel = BgdLayer.screen[x][y];
			if (objPixel.txtColor < 0 && objPixel.bgdColor < 0) objPixel = bgdPixel;
			else if (objPixel.bgdColor < 0) objPixel.bgdColor = bgdPixel.bgdColor;
		}
	ObjLayer.display(hStdout, dwBytesWritten, fromX, fromY, toX, toY);
}
void CGAME::displayScreen(CGRAPHIC& ObjLayer, const CGRAPHIC& BgdLayer, int fromX, int fromY, int toX, int toY) {
	if (toX < 0 || toX > SCREEN_WIDTH - 1) toX = SCREEN_WIDTH - 1;
	if (toY < 0 || toY > SCREEN_HEIGHT - 1) toY = SCREEN_HEIGHT - 1;
	for (int x = fromX; x <= toX; x++)
		for (int y = fromY; y <= toY; y++) {
			PIXEL& objPixel = ObjLayer.screen[x][y], bgdPixel = BgdLayer.screen[x][y];
			if (objPixel.txtColor < 0 && objPixel.bgdColor < 0) objPixel = bgdPixel;
			else if (objPixel.bgdColor < 0) objPixel.bgdColor = bgdPixel.bgdColor;
		}
	ObjLayer.display(hStdout, dwBytesWritten, fromX, fromY, toX, toY);
}

bool isUpButton(int button) {
	return button == 'W' || button == 38;
}
bool isDownButton(int button) {
	return button == 'S' || button == 40;
}
bool isRightButton(int button) {
	return button == 'D' || button == 39;
}
bool isLeftButton(int button) {
	return button == 'A' || button == 37;
}
bool isEnterButton(int button) {
	return button == 13 || button == 32;
}
bool isDeleteButton(int button) {
	return button == 224;
}
bool isBackspaceButton(int button) {
	return button == 8;
}

bool isNumber(char ch) {
	return ch >= '0' && ch <= '9';
}
bool isLetter(char ch) {
	return toupper(ch) >= 'A' && toupper(ch) <= 'Z';
}
bool isNumberOrLetter(char ch) {
	return isNumber(ch) || isLetter(ch);
}
bool isExist(string str, deque<string> strArr) {
	return find(strArr.begin(), strArr.end(), str) != strArr.end();
}

int getiMatrix(int val, vector<vector<int>>& matrix) {
	for (int i = 0; i < (int)matrix.size(); i++)
		for (int j = 0; j < (int)matrix[i].size(); j++)
			if (matrix[i][j] == val) return i;
	return -1;
}
int getjMatrix(int val, vector<vector<int>>& matrix) {
	for (int i = 0; i < (int)matrix.size(); i++)
		for (int j = 0; j < (int)matrix[i].size(); j++)
			if (matrix[i][j] == val) return j;
	return -1;
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

