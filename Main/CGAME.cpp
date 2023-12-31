﻿#include "CGAME.h"
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
	ShowScrollbar(true);
	system("mode 1000, 500");
	system("color 67");
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

	system("mode 208, 51");
	system("color 20");
	//
	srand(time(0));
	SetupTheme(THEME_BASIC, hStdout);
	BgdLayer.clear(BLACK, WHITE);
	ObjLayer.clear(-1, -1);
}

void CGAME::start() {
	ShowCur(false);
	system("cls");
	this->intro();
	_getch();
	while (this->Menu() != QUIT_CODE);
	system("cls");
	system("color 67");
	this->outtro();
	_getch();
}
void CGAME::playGame() {
	playBackgroundSound(GAME_THEME);
	system("cls");
	startMap();
	isThreadRunning = true;
	thread threadNewGame(&CGAME::SubThreadNewGame, this);
	while (1) {
		if (level == MAX_LEVEL) {
			SuspendThread(threadNewGame.native_handle());
			drawWiningScreen();
			if (_getch()) {
				resumeThread(threadNewGame.native_handle());
				exitThread(&threadNewGame);
				return;
			}
		}
		if (!cPlayer->isDead()) {
			int temp = toupper(_getch());
			switch (temp) {
			case 'W': case 'S': case 'A': case 'D': {
				playEffectSound(GAME_MOVE);
				cPlayer->setMoving(temp);
				break;
			}
			case 'P': {
				playEffectSound(GAME_PAUSE);
				if (Pause(threadNewGame.native_handle()) == BACK_TO_MENU_CODE) {
					exitThread(&threadNewGame);
					return;
				}
			}
			}
		}
		else {
			if (isReset()) {
				playBackgroundSound(OFF_SOUND);
				playBackgroundSound(GAME_THEME);
				cPlayer->setScore(0);
				level = 1;
				startTime = clock(), endTime = 0, curTime = 0;
				resetData();
				startMap();
				cPlayer->setMoving(0);
				cPlayer->set(BOARD_WIDTH / 2, UP_LANE, true, 0);
			}
			else {
				playEffectSound(MENU_QUIT);
				exitThread(&threadNewGame);
				return;
			}
		}
	}
}

void CGAME::resetData() {
	if (level == 1) numberOfLane = 5;
	for (int i = 1; i < level; i++ , numberOfLane += 3) {
		numberOfLane += (rand() % 3);
	}

	while (!aLanes.empty()) pop_backLane();
	aLanes.clear();

	push_frontLane(RIVERLANE_ID);
	push_frontLane(GRASSLANE_SURROUND_ID);
	push_frontLane(GRASSLANE_AROUND_ID);
	int numberOfRandomLane = (numberOfLane < BOARD_HEIGHT - 3) ? numberOfLane : BOARD_HEIGHT - 3;
	for (int i = 0; i < numberOfRandomLane; i++, countLane++) pushRandomLane();
	for (int i = 0; i < BOARD_HEIGHT - 3 - numberOfRandomLane; i++) {
		if (i == 0) push_frontLane(FINISHLANE_ID);
		else if (i == 1) push_frontLane(GRASSLANE_FULL_ID);
		else push_frontLane(GRASSLANE_ID);
	}
}
void CGAME::saveData(string fileName) {
	ofstream file(fileName + ".bin", ios::trunc | ios::binary);
	if (file.is_open()) {
		//CGAME: cPlayer: new, aLanes: new, fileNamelist: load, isSave = true, savedName = file name, <level>, <numberOfLane>, <conditionLane>, <countLane>, <numberOfConditionLane>, isThreadRunning = true, ObjLayer, bgdLayer: draw, <startTime>, <endTime>, <curTime>
		file << this->level << " " << this->numberOfLane << " " << this->conditionLane << " " << this->countLane << " " << this->numberOfConditionLane << " " << this->startTime << " " << this->endTime << " " << this->curTime << endl;
		file << endl;
		//CPLAYER: <xBoard>(x) <yBoard>(y) (alive = 1) <score> <isRight> (moving = 0) <colorCharacter> (depend: get from lane[yBoard][xBoard]) (pCharacterR/L = new CDINOSAUR(x, y, true/left, colorCharacter)
		file << cPlayer->getXBoard() << " " << cPlayer->getYBoard() << " " << cPlayer->getScore() << " " << cPlayer->getIsRight() << " " << cPlayer->getColorCharacter() << endl;
		file << endl;
		for (int i = 0; i < BOARD_HEIGHT; i++) {
			//CLANE: <isMoveRight> <ID> (lane: push with ID) (block: new with ID) [<object ID>/0]
				//VEHICLE:	...	<timeCount> <delayTime> (x, y: update)	<isStop>	<condition> <countObject>	<numberOfConditionObj>	<lightPos>	<timeLight> (pTrafficLight = new with lightPos > 0) [<object ID>/0]
				//TRAIN:		<timeCount> <delayTime> (x, y: update)	0			0			<countObject>	<numberOfConditionObj>	-1			0			[<object ID>/0]
				//RIVER:		<timeCount> <delayTime> (x, y: update)	0			<condition> <countObject>	<numberOfConditionObj>	-1			0			[<object>/0]
				//GRASS:		0			0							0			0			0				0						-1			0			[<object>/0]
				//FINISH:		0			0							0			0			0				0						-1			0			[<object>/0]
			file << aLanes[i]->getIsMoveRight() << " " << aLanes[i]->getID() << " ";
			file << aLanes[i]->getTimeCount() << " " << aLanes[i]->getDelayTime() << " " << aLanes[i]->getIsStop() << " " << aLanes[i]->getCondition() << " " << aLanes[i]->getCountObject() << " " << aLanes[i]->getNumberOfConditionObj() << " " << aLanes[i]->getLightPos() << " " << aLanes[i]->getTimeLight() << endl;
			file << endl;
			for (int j = 0; j < BOARD_WIDTH; j++) {
				//COBJECT: <ID> (object: push with ID)
					//CAR	...		isRight		0
					//TRUCK			isRight		0
					//BUS			isRight		isHead
					//CAPY			isRight		0
					//EGG			0			0
					//PERRY			isRight		0
					//TRAIN			isRight		isHead
					//TREE			0			0
					//NULL	0		0			0
				COBJECT* obj = aLanes[i]->getPos(j);
				if (obj == NULL) file << 0 << " " << 0 << " " << 0 << endl;
				else {
					file << obj->getID() << " ";
					file << obj->getIsRight() << " " << obj->getIsHead() << endl;
				}
			}
			file << endl;
		}
		file.close();
	}
}
void CGAME::loadData(string fileName) {
	ifstream file(fileName + ".bin", ios::in | ios::binary);
	if (file.is_open()) {
		//CGAME: <level>, <numberOfLane>, <conditionLane>, <countLane>, <numberOfConditionLane>, <startTime>, <endTime>, <curTime>
		int level{}, numberOfLane{}, conditionLane{}, countLane{}, numberOfConditionLane{}; clock_t startTime{}, endTime{}, curTime{};
		file >> level >> numberOfLane >> conditionLane >> countLane >> numberOfConditionLane >> startTime >> endTime >> curTime;
		file.ignore(1);

		//CGAME: aLanes: new, isSave = true, savedName = file name, <level>, <numberOfLane>, <conditionLane>, <countLane>, <numberOfConditionLane>, isThreadRunning = true, ObjLayer, bgdLayer: draw
		isSaved = true; savedName = fileName; isThreadRunning = true;
		this->level = level; this->numberOfLane = numberOfLane; this->conditionLane = conditionLane; this->countLane = countLane; this->numberOfConditionLane = numberOfConditionLane;
		this->startTime = startTime; this->endTime = endTime; this->curTime = curTime;

		//CPLAYER: <xBoard> <yBoard> <score> <isRight> <colorCharacter>
		int xBoard{}, yBoard{}, score{}; bool isRightCharacter{}; int colorCharacter{};
		file >> xBoard >> yBoard >> score >> isRightCharacter >> colorCharacter;
		file.ignore(1);

		//CPLAYER: <xBoard> <yBoard> <score> <isRight> <colorCharacter> (depend: get from lane[yBoard][xBoard])
		cPlayer = new CPLAYER(xBoard, yBoard, colorCharacter);
		cPlayer->setScore(score);
		cPlayer->setIsRight(isRightCharacter);

		//clear the last aLanes
		while (!aLanes.empty()) {
			CLANE* cur = aLanes.back();
			aLanes.pop_back();
			if (cur != NULL) delete cur;
			cur = NULL;
		}
		aLanes.clear();

		for (int i = 0; i < BOARD_HEIGHT; i++) {
			//CLANE: <isMoveRight> <ID>
			//...	<timeCount> <delayTime> <isStop> <condition> <countObject> <numberOfConditionObj> <lightPos> <timeLight>
			bool isMoveRight{}; int laneID{};
			int timeCount{}, delayTime{}; bool isStop{}; int condition{}, countObject{}, numberOfConditionObj{}, lightPos{}, timeLight{};
			file >> isMoveRight >> laneID;
			file >> timeCount >> delayTime >> isStop >> condition >> countObject >> numberOfConditionObj >> lightPos >> timeLight;
			file.ignore(1);

			//CLANE: <isMoveRight> <ID>
				//...	<timeCount> <delayTime>	<isStop> <condition> <countObject>	<numberOfConditionObj>	<lightPos>	<timeLight>
			push_backLane(laneID);
			CLANE* lane = aLanes.back();
			lane->setIsMoveRight(isMoveRight); lane->setTimeCount(timeCount); lane->setDelayTime(delayTime); lane->setIsStop(isStop);
			lane->setCondition(condition); lane->setCountObject(countObject); lane->setNumberOfConditionObj(numberOfConditionObj); lane->setLightPos(lightPos); lane->setTimeLight(timeLight);

			//clear the last aLanes
			while (!lane->emptyObject()) lane->popObject();
			lane->clearObject();

			for (int j = 0; j < BOARD_WIDTH; j++) {
				//COBJECT: <ID>
				//...	<isRight> <isHead>
				int objID{};
				bool isRight{}, isHead{};
				file >> objID;
				file >> isRight >> isHead;

				//COBJECT: <ID> (object: push with ID)
				//...	<isRight>	<isHead>
				lane->push_backObject(objID);
				if (objID != 0) {
					COBJECT* back = lane->backObject();
					back->setIsRight(isRight); back->setIsHead(isHead);
				}
			}
			file.ignore(1);
		}
		file.close();
		cPlayer->setDependObj(aLanes[yBoard]->getPos(xBoard));
		startMap();
		drawMap();
	}
}

string CGAME::inputUserTxt(const CGRAPHIC& BgdLayer) {
	const int fromX = (SCREEN_WIDTH - 54) / 2, fromY = (SCREEN_HEIGHT - 29) / 2 - 1,
		toX = fromX + 53, toY = fromY + 28;

	const int INPUT_OPTION = 10 + fromX;
	const int OK_OPTION = 26 + fromX;
	const int BACK_OPTION = 37 + fromX;
	const int yFirstLine = 13 + fromY, ySecondLine = 22 + fromY;

	int xOption = INPUT_OPTION, yOption = yFirstLine;
	string text{}; int size = (int)text.size();

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

	displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);

	//draw current pos
	if (xOption == INPUT_OPTION) {
		//draw current pos
		if (size < MAX_INPUT_SIZE) tmpObjLayer.DrawInputPos(xOption + size * 4 + 1, yOption, LIGHT_GREEN, BLACK);
		displayScreen(tmpObjLayer, tmpBgdLayer, xOption, yOption, xOption + MAX_INPUT_SIZE * 3 + (MAX_INPUT_SIZE - 1), yOption + 2);

		char ch{};
		do {
			//draw current pos
			tmpObjLayer.erasePixel(xOption, yOption, xOption + MAX_INPUT_SIZE * 4 - 1, yOption + 2);
			tmpObjLayer.drawString(text, xOption, yOption, LIGHT_GREEN, BLACK);
			if (size < MAX_INPUT_SIZE) tmpObjLayer.DrawInputPos(xOption + size * 4 + 1, yOption, LIGHT_GREEN, BLACK);
			displayScreen(tmpObjLayer, tmpBgdLayer, xOption, yOption, xOption + MAX_INPUT_SIZE * 3 + (MAX_INPUT_SIZE - 1), yOption + 2);

			ch = toupper(_getch());
			//erase the last pos
			if (size < MAX_INPUT_SIZE) tmpObjLayer.erasePixel(xOption + size * 4, yOption, xOption + size * 4 + 3, yOption + 2);

			if (isBackspaceButton((int)ch) && size > 0) {
				text.pop_back();
				size--;
			}
			if (isLetter(ch)&& size < MAX_INPUT_SIZE) {
				text.push_back(ch);
				size++;
			}
		} while (!isEnterButton((int)ch));

		//draw OK
		tmpObjLayer.drawString(text, xOption, yOption, DARK_GREEN, BLACK);
		displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);

		Sleep(500);
		xOption = OK_OPTION;
		yOption = ySecondLine;

		tmpObjLayer.drawButton(xOption, yOption, DARK_GREEN, LIGHT_GREEN);
		displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
	}

	while (1) {
		int temp = toupper(_getch());

		//erase the last step
		switch (xOption) {
		case INPUT_OPTION:
			tmpObjLayer.erasePixel(xOption, yOption, xOption + MAX_INPUT_SIZE * 4 - 1, yOption + 2);
			tmpObjLayer.drawString(text, xOption, yOption, LIGHT_GRAY, -1);
			break;
		case OK_OPTION: case BACK_OPTION:
			tmpObjLayer.erasePixel(xOption, yOption, xOption + 8 - 1, yOption + 4 - 1);
			break;
		}

		if (!isEnterButton(temp)) {
			if (isUpButton(temp)) {
				switch (xOption) {
				case OK_OPTION: case BACK_OPTION:
					displayScreen(tmpObjLayer, tmpBgdLayer, xOption, yOption, xOption + 8 - 1, yOption + 4 - 1);
					xOption = INPUT_OPTION;
					yOption = yFirstLine;
					break;
				}
			}
			if (isDownButton(temp)) {
				if (xOption == INPUT_OPTION) {
					xOption = OK_OPTION;
					yOption = ySecondLine;
				}
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
			if (xOption == INPUT_OPTION) {
				char ch{};
				do {
					//draw current pos
					tmpObjLayer.erasePixel(xOption, yOption, xOption + MAX_INPUT_SIZE * 4 - 1, yOption + 2);
					tmpObjLayer.drawString(text, xOption, yOption, LIGHT_GREEN, BLACK);
					if (size < MAX_INPUT_SIZE) tmpObjLayer.DrawInputPos(xOption + size * 4 + 1, yOption, LIGHT_GREEN, BLACK);
					displayScreen(tmpObjLayer, tmpBgdLayer, xOption, yOption, xOption + MAX_INPUT_SIZE * 3 + (MAX_INPUT_SIZE - 1), yOption + 2);

					ch = toupper(_getch());
					//erase the last pos
					if (size < MAX_INPUT_SIZE) tmpObjLayer.erasePixel(xOption + size * 4, yOption, xOption + size * 4 + 3, yOption + 2);

					if (isBackspaceButton((int)ch) && size > 0) {
						text.pop_back();
						size--;
					}
					if (isNumberOrLetter(ch) && size < MAX_INPUT_SIZE) {
						text.push_back(ch);
						size++;
					}
				} while (!isEnterButton((int)ch));

				//draw OK
				tmpObjLayer.drawString(text, xOption, yOption, DARK_GREEN, BLACK);
				displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);

				Sleep(500);
				xOption = OK_OPTION;
				yOption = ySecondLine;
			} 
		} 
		else {
			//draw choice
			switch (xOption) {
			case INPUT_OPTION:
				tmpObjLayer.drawString(text, xOption, yOption, DARK_GREEN, BLACK);
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
				return text;
			case BACK_OPTION:
				return "";
			case INPUT_OPTION:
				xOption = OK_OPTION;
				yOption = ySecondLine;
				break;
			}
			//reset choice
		}
		switch (xOption) {
		case INPUT_OPTION:
			tmpObjLayer.drawString(text, xOption, yOption, LIGHT_GREEN, BLACK);
			break;
		case OK_OPTION:
			tmpObjLayer.drawButton(xOption, yOption, DARK_GREEN, LIGHT_GREEN);
			break;
		case BACK_OPTION:
			tmpObjLayer.drawButton(xOption, yOption, DARK_RED, RED);
			break;
		}
		displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
	}
}
void CGAME::saveFileNameList() {
	fstream outFile("file_name_list.bin", fstream::out | fstream::trunc | fstream::binary);
	if (outFile.fail()) return;
	int size = (int)fileNameList.size();
	outFile << size << endl;
	for (int i = 0; i < size; i++)
		outFile << fileNameList[i] << endl;
	outFile.close();
}
void CGAME::loadFileNameList() {
	fstream inFile("file_name_list.bin", fstream::in | fstream::binary);
	if (inFile.fail()) return;
	fileNameList.clear();
	int size{};
	inFile >> size;
	string fileName{};
	for (int i = 0; i < size; i++) {
		inFile >> fileName;
		fileNameList.push_front(fileName);
	}
	inFile.close();
}
void CGAME::deleteFile(int index)
{
	if (fileNameList.empty() || index < 0 || index >(int)fileNameList.size() - 1) return;

	char fileName[8 + 4]{};
	for (int i = 0; i < (int)fileNameList[index].size(); i++)
		fileName[i] = fileNameList[index][i];
	strcat_s(fileName, ".bin");
	remove(fileName);

	fileNameList.erase(fileNameList.begin() + index);
	saveFileNameList();
}
void CGAME::renameFile(int index, const CGRAPHIC& BgdLayer) {
	if (fileNameList.empty() || index < 0 || index >(int)fileNameList.size() - 1) return;

	string str{};
	do {
		str = inputUserTxt(BgdLayer);
		if (str == "") return;
	} while (str.size() > 8 || checkinList(str, fileNameList));

	char oldName[8 + 4]{}, newName[8 + 4]{};
	for (int i = 0; i < (int)fileNameList[index].size(); i++)
		oldName[i] = fileNameList[index][i];
	strcat_s(oldName, ".bin");
	for (int i = 0; i < (int)str.size(); i++)
		newName[i] = str[i];
	strcat_s(newName, ".bin");

	rename(oldName, newName);

	fileNameList[index] = str;
	saveFileNameList();
}

int CGAME::Menu() {
	playBackgroundSound(MENU_THEME);
	system("cls");
	SetupTheme(MAIN_MENU_THEME, hStdout);
	const int fromX = 5, fromY = 18,
		toX = fromX + 40 - 1, toY = fromY + 27 - 1;
	const int xfromTalk = 105, yfromTalk = 38 - 10, xfromMessage = xfromTalk + 4, yfromMessage = yfromTalk + 3;

	const int xdrawerStart = 7 + fromX, ydrawerStart = fromY;
	const int NEW_GAME = ydrawerStart;
	const int LOAD_GAME = ydrawerStart + 4;
	const int SETTING = ydrawerStart + 4 * 2;
	const int HELP = ydrawerStart + 4 * 3;
	const int ABOUT = ydrawerStart + 4 * 4;
	const int QUIT = ydrawerStart + 4 * 5;
	//NewGame - LoadGame - Setting - Help - About - Quit
	vector<int> colorArr = { LIGHT_GREEN, TEAL, LIGHT_GRAY, CREAMY_AVOCADO, PURPLE, DARK_ORANGE };
	vector<string> messageArr = { "NEW GAME", "LOAD GAME", "SETTING", "HELP", "ABOUT", "QUIT" };
	int xOption = xdrawerStart, yOption = ydrawerStart;
	int iCur = 0, curColor = colorArr[iCur]; string curMessage = messageArr[iCur];

	//setup tmp layers
	CGRAPHIC tmpBgdLayer(BgdLayer), tmpObjLayer({ L' ', -1, -1 });

	//draw menu
	tmpBgdLayer.DrawMainMenu();
	tmpObjLayer.DrawDoofCorp(176, 16);
	displayScreen(tmpObjLayer, tmpBgdLayer, 0, 0, -1, -1);

	bool isSkip = false;
	takeArest(isSkip);

	tmpObjLayer.DrawDinasourPicture(10, 2);
	displayScreen(tmpObjLayer, tmpBgdLayer, 0, 0, -1, -1);

	takeArest(isSkip);

	tmpObjLayer.DrawHeader(98, 3);
	tmpObjLayer.DrawHat(190, 44, DARK_BROWN);
	displayScreen(tmpObjLayer, tmpBgdLayer, 0, 0, -1, -1);

	takeArest(isSkip);

	tmpObjLayer.DrawBigDinoSaur(53, 17);
	displayScreen(tmpObjLayer, tmpBgdLayer, 0, 0, -1, -1);

	takeArest(isSkip);

	tmpBgdLayer.DrawDrawer(fromX, fromY + 3);
	tmpObjLayer.DrawDrawer(fromX, fromY + 3);
	//draw current step
	tmpObjLayer.DrawSmallDrawer(xOption, yOption, curColor);
	tmpObjLayer.DrawPerryTalk(curMessage, xfromTalk, yfromTalk, curColor, WHITE);
	displayScreen(tmpObjLayer, tmpBgdLayer, 0, 0, -1, -1);
	while (1) {
		playEffectSound(MENU_MOVE);
		int temp = toupper(_getch());

		//erase the last step
		tmpObjLayer.erasePixel(xOption, yOption, xOption + 32, yOption + 7 - 1);
		tmpObjLayer.erasePixel(xfromMessage, yfromMessage, xfromMessage + 33 - 1, yfromMessage + 3 - 1);
		if (isEnterButton(temp)) {
			//draw choice
			tmpObjLayer.DrawSmallDrawer(xOption , yOption, DARK_GREEN);
			tmpObjLayer.DrawPerryTalk(curMessage, xfromTalk, yfromTalk, curColor, WHITE);
			if (iCur != 0) tmpObjLayer.screen[xOption + 14][yOption].bgdColor = LIGHT_BROWN;
			displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
			displayScreen(tmpObjLayer, tmpBgdLayer, xfromTalk, yfromTalk, xfromTalk + 63 - 1, yfromTalk + 19 - 1);
			Sleep(500);
			switch (yOption) {
			case NEW_GAME:
				playEffectSound(MENU_ENTER);
				SetupTheme(THEME_BASIC, hStdout);
				NewGame();
				playBackgroundSound("");
				playBackgroundSound(MENU_THEME);
				SetupTheme(MAIN_MENU_THEME, hStdout);
				break;
			case LOAD_GAME:
				playEffectSound(MENU_ENTER);
				SetupTheme(THEME_BASIC, hStdout);
				LoadGame();
				SetupTheme(MAIN_MENU_THEME, hStdout);
				break;
			case SETTING:
				playEffectSound(MENU_ENTER);
				SetupTheme(THEME_BASIC, hStdout);
				Setting();
				SetupTheme(MAIN_MENU_THEME, hStdout);
				playBackgroundSound("");
				playBackgroundSound(MENU_THEME);
				break;
			case HELP:
				playEffectSound(MENU_ENTER);
				this->Help(CREAMY_AVOCADO, BLACK, WHITE, DARK_BROWN, WHITE);
				break;
			case ABOUT:
				playEffectSound(MENU_ENTER);
				this->About();
				break;
			case QUIT:
				playEffectSound(MENU_QUIT);
				return QUIT_CODE;
			}
			displayScreen(tmpObjLayer, tmpBgdLayer);
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
		tmpObjLayer.DrawSmallDrawer(xOption , yOption, curColor);
		tmpObjLayer.DrawPerryTalk(curMessage, xfromTalk, yfromTalk, curColor, WHITE);
		if (iCur != 0) tmpObjLayer.screen[xOption + 14][yOption].bgdColor = LIGHT_BROWN;
		displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
		displayScreen(tmpObjLayer, tmpBgdLayer, xfromTalk, yfromTalk, xfromTalk + 63 - 1, yfromTalk + 19 - 1);
	}
	return 0;
}
void CGAME::NewGame() {
	BgdLayer.clear(WHITE, WHITE);
	ObjLayer.clear(WHITE, WHITE);
	displayScreen(ObjLayer, BgdLayer);
	ChooseCharacter(BgdLayer);
	cPlayer->setScore(0);
	cPlayer->set(BOARD_WIDTH / 2, UP_LANE, true, 0);
	isSaved = false;
	this->level = 1;
	startTime = clock(), endTime = 0, curTime = 0;
	resetData();
	playGame();
}
void CGAME::LoadGame() {
	const int fromX = 50, fromY = 10,
		toX = fromX + 90 + 40 - 1, toY = fromY + 30 + 7 - 1;

	const int LOAD_YOPTION = fromY;
	const int RENAME_YOPTION = 5 + fromY;
	const int DELETE_YOPTION = 10 + fromY;
	const int CANCEL_YOPTION = 15 + fromY;
	const int BACK_YOPTION = 20 + fromY;

	const vector<string> optionList = { "LOAD", "RENAME", "DELETE", "CANCEL", "BACK" };
	const int MAX_FILE_IN_TAB = 5;
	loadFileNameList();

	const int XOPTION = 52 + fromX;
	const int XCHOOSE = fromX + 11, YCHOOSE_FIRST = fromY + 6;

	bool isRight = false;
	int xOption = XCHOOSE, yOption = YCHOOSE_FIRST;
	int idFile = 0, idOption = 0, numberOfFile = ((int)fileNameList.size() < MAX_FILE_IN_TAB) ? (int)fileNameList.size() : MAX_FILE_IN_TAB;

	//setup tmpLayers
	CGRAPHIC tmpback;
	tmpback.clear(WHITE, WHITE);
	CGRAPHIC tmpBgdLayer(BgdLayer), tmpObjLayer({ L' ', -1, -1 });
	tmpBgdLayer.clear(WHITE, WHITE);
	//draw menu
	tmpBgdLayer.DrawLoadGame(fromX, fromY, fileNameList);

	//draw current step
	if (!isRight) {
		if (!fileNameList.empty()) {
			tmpObjLayer.DrawNumber1pixel(xOption, yOption, idFile + 1, LIGHT_GREEN, SAND);
			tmpObjLayer.DrawString1pixel(xOption + 4, yOption, fileNameList[idFile], LIGHT_GREEN, SAND);
		}
	}
	else tmpObjLayer.drawTag(xOption, yOption, optionList[idOption], LIGHT_GREEN);

	displayScreen(tmpBgdLayer, tmpback, 0, 0, -1, -1);
	displayScreen(tmpObjLayer, tmpBgdLayer, 0, 0, -1, -1);
	while (1) {
		int temp = toupper(_getch());

		//erase the last step
		if (!isRight) {
			if (!fileNameList.empty()) tmpObjLayer.erasePixel(xOption, yOption, xOption + 12, yOption);
		}
		else tmpObjLayer.erasePixel(xOption, yOption, xOption + 40 - 1, yOption + 5 - 1);

		if (!isEnterButton(temp)) {
			if (!isRight) {
				if (!fileNameList.empty()) {
					if (isUpButton(temp)) {
						if (idFile > 0) {
							idFile--;
							yOption -= 2;
						}
					}
					if (isDownButton(temp)) {
						if (idFile < numberOfFile - 1) {
							idFile++;
							yOption += 2;
						}
					}
					if (isRightButton(temp) || isLeftButton(temp)) {
						isRight = true;
						idOption = 0;
						xOption = XOPTION;
						yOption = LOAD_YOPTION;
					}
				}
			}
			else {
				if (isUpButton(temp)) {
					if (idOption > 0) {
						idOption--;
						yOption -= 5;
					}
				}
				if (isDownButton(temp)) {
					if (idOption < 5 - 1) {
						idOption++;
						yOption += 5;
					}
				}
				if (isRightButton(temp) || isLeftButton(temp)) {
					isRight = false;
					xOption = XCHOOSE;
					yOption = YCHOOSE_FIRST + idFile * 2;
				}
			}
			//draw new step
		}
		else {
			//draw choice
			if (!isRight) {
				if (!fileNameList.empty()) {
					tmpObjLayer.DrawNumber1pixel(xOption, yOption, idFile + 1, DARK_GREEN, SAND);
					tmpObjLayer.DrawString1pixel(xOption + 4, yOption, fileNameList[idFile], DARK_GREEN, SAND);
				}
			}
			else tmpObjLayer.drawTag(xOption, yOption, optionList[idOption], DARK_GREEN);
			displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);

			Sleep(500);
			if (!isRight) {
				isRight = true;
				idOption = 0;
				xOption = XOPTION;
				yOption = LOAD_YOPTION;
			}
			else {
				switch (yOption) {
				case LOAD_YOPTION:
					if (!fileNameList.empty()) {
						loadData(fileNameList[idFile]);
						playGame();
						return;
					}
				case RENAME_YOPTION:
					if (!fileNameList.empty()) {
						renameFile(idFile, tmpBgdLayer);

						//update fileNameList and bgd
						loadFileNameList();
						tmpObjLayer.erasePixel(XCHOOSE, YCHOOSE_FIRST, XCHOOSE + 10, YCHOOSE_FIRST + 10 * 2);
						tmpBgdLayer.DrawLoadGame(fromX, fromY, fileNameList);
						displayScreen(tmpBgdLayer, tmpback, 0, 0, -1, -1);
						displayScreen(tmpObjLayer, tmpBgdLayer, 0, 0, -1, -1);
					}
					break;
				case DELETE_YOPTION:
					if (!fileNameList.empty()) {
						deleteFile(idFile);
						if (idFile > 0) idFile--;

						//update fileNameList and bgd
						loadFileNameList();
						tmpObjLayer.erasePixel(XCHOOSE, YCHOOSE_FIRST, XCHOOSE + 10, YCHOOSE_FIRST + 10 * 2);
						tmpBgdLayer.DrawLoadGame(fromX, fromY, fileNameList);
						displayScreen(tmpBgdLayer, tmpback, 0, 0, -1, -1);
						displayScreen(tmpObjLayer, tmpBgdLayer, 0, 0, -1, -1);
					}
					break;
				case CANCEL_YOPTION:
					tmpObjLayer.drawTag(xOption, yOption, optionList[idOption], BLACK);
					isRight = false;
					xOption = XCHOOSE;
					yOption = YCHOOSE_FIRST + idFile * 2;
					break;
				case BACK_YOPTION:
					return;
				}
			}
			//reset choice
		}
		if (!isRight) {
			if (!fileNameList.empty()) {
				tmpObjLayer.DrawNumber1pixel(xOption, yOption, idFile + 1, LIGHT_GREEN, SAND);
				tmpObjLayer.DrawString1pixel(xOption + 4, yOption, fileNameList[idFile], LIGHT_GREEN, SAND);
			}
		}
		else tmpObjLayer.drawTag(xOption, yOption, optionList[idOption], LIGHT_GREEN);
		displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
	}
}
void CGAME::SaveGame(const CGRAPHIC& BgdLayer) {
	if (!isSaved) {
		string fileName{};
		do {
			fileName = inputUserTxt(BgdLayer);
			if (fileName == "") return;
		} while (fileName.size() > MAX_INPUT_SIZE || checkinList(fileName, fileNameList));

		//update save variables
		isSaved = true;
		savedName = fileName;

		//update file name list
		if (fileNameList.size() >= MAX_NUMBER_OF_SAVED_FILE) fileNameList.pop_back();
		fileNameList.push_front(fileName);
		saveFileNameList();
	}
	saveData(savedName);
}
void CGAME::Setting() {
	const int fromX = (SCREEN_WIDTH - 53) / 2, fromY = (SCREEN_HEIGHT - 30) / 2,
		toX = fromX + 53, toY = fromY + 28;

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
	tmpBgdLayer.clear(WHITE, WHITE);
	displayScreen(0, 0, -1, -1);
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
		playEffectSound(MENU_MOVE);
		int temp = toupper(_getch());

		// erase the last step
		if (xOption == XSOUND)
			tmpObjLayer.erasePixel(xOption, yOption, xOption + 35 - 1, yOption + 3 - 1);
		else
			tmpObjLayer.erasePixel(xOption, yOption, xOption + 8 - 1, yOption + 4 - 1);

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
			playEffectSound(MENU_ENTER);
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
void CGAME::Help(int header, int txt, int bgd, int clipboard, int paper) {
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
		"  TRY TO SURVIVE AND COLLECT EGGS!!!"
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
		toX = fromX + width - 1, toY = fromY + height + 1;
	

	tmpBgdLayer.DrawTextBoard("HELP", header, bodycontent, fromX, fromY, 53, 29, txt, bgd, clipboard, paper);
	displayScreen(tmpBgdLayer, tmpBgdLayer, fromX, fromY, toX, toY);
	_getch();
}
void CGAME::About() {
	CGRAPHIC tmpBgdLayer(BgdLayer);

	vector<string> bodycontent = {
		"              <<TEACHER>>           ",
		"            Truong Toan Thinh       ",
		"									 ",			
		"           <<GROUP'S MEMBER>>       ",
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
		toX = fromX + width, toY = fromY + height;

	tmpBgdLayer.DrawTextBoard("ABOUT", LAVENDER, bodycontent, fromX, fromY, width, height, BLACK, WHITE, DARK_BROWN,WHITE);


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

	//draw character name
	tmpObjLayer.drawString(cPlayer->getNameCharacter(), 24 + fromX, 4 + fromY, cPlayer->getColorCharacter(), SAND);
	//draw character
	CDINOSAUR characterSample(fromX + 5, fromY + 3, true, cPlayer->getColorCharacter());
	characterSample.DrawBlock(tmpObjLayer);
	//draw current cell
	tmpObjLayer.drawCell(xOption, yOption, LIGHT_GREEN);

	displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
	while (1) {
		playEffectSound(MENU_MOVE);
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
		}
		else {
			//draw choice
			if (xOption != CHARACTER_OPTION) tmpObjLayer.drawCheck(xOption, yOption);
			else tmpObjLayer.drawCharacterFrame(xOption, yOption, DARK_GREEN);
			displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);

			Sleep(500);
			switch (xOption) {
			case CHARACTER_OPTION:
				ChooseCharacter(tmpBgdLayer);
				//update new character name
				tmpObjLayer.erasePixel(24 + fromX, 4 + fromY, 24 + fromX + 23, 4 + fromY + 3);
				tmpObjLayer.drawString(cPlayer->getNameCharacter(), 24 + fromX, 4 + fromY, cPlayer->getColorCharacter(), SAND);
				//update new character color
				characterSample.setColor(cPlayer->getColorCharacter());
				tmpObjLayer.erasePixel(xOption, yOption, xOption + 17, yOption + 8);
				characterSample.DrawBlock(tmpObjLayer);
				tmpObjLayer.drawCharacterFrame(xOption, yOption, LIGHT_GREEN);
				break;
			case SETTING_OPTION:
				playEffectSound(MENU_ENTER);
				Setting();
				playBackgroundSound("");
				playBackgroundSound(GAME_THEME);
				break;
			case RESUME_OPTION:
				playEffectSound(MENU_ENTER);
				drawCountDown();
				resumeThread(t);
				curTime += endTime - startTime;
				return 0;
			case HELP_OPTION:
				playEffectSound(MENU_ENTER);
				Help(BRIGHT_YELLOW, BLACK, SAND, DARK_BLUE, SAND);
				break;
			case SAVE_OPTION:
				playEffectSound(MENU_ENTER);
				SaveGame(tmpBgdLayer);
				drawCountDown();
				resumeThread(t);
				return 0;
			case EXIT_OPTION:
				playEffectSound(MENU_QUIT);
				resumeThread(t);
				savedName = "";
				isSaved = false;
				return BACK_TO_MENU_CODE;
			}
			//reset choice
		}
		displayScreen(tmpObjLayer, tmpBgdLayer, fromX, fromY, toX, toY);
	}
	return 0;
}
void CGAME::ChooseCharacter(const CGRAPHIC& BgdLayer) {
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
		playEffectSound(MENU_MOVE);
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
	return drawLosingScreen(cPlayer->getColorCharacter());
}

void CGAME::exitThread(thread* t) {
	system("cls");
	isThreadRunning = false;
	t->join();
}
void CGAME::resumeThread(HANDLE t) {
	if (t != NULL) ResumeThread(t);
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
			countConditionLane = 1;
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
			countConditionLane = 0;
			numberOfConditionLane = 0;
			conditionLane = 0;
			break;
		}
		case VEHICLELANE_ID: case TRAINLANE_ID: {
			countConditionLane++;
			if (countConditionLane >= numberOfConditionLane) conditionLane = GRASSLANE_ID;
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
		aLanes.push_front(new CVEHICLELANE(0, 0, 2 + rand() % 5));
		break;
	}
	case GRASSLANE_ID: {
		aLanes.push_front(new CGRASSLANE(0, 0));
		break;
	}
	case TRAINLANE_ID: {
		aLanes.push_front(new CTRAINLANE(0, 0, 1 + rand() % 2, 10 + (rand() % 10)));
		break;
	}
	case RIVERLANE_ID: {
		aLanes.push_front(new CRIVERLANE(0, 0, 2 + rand() % 5));
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
void CGAME::push_backLane(int ID) {
	if (ID == 0) ID = GRASSLANE_ID;
	int yLane = (int)aLanes.size();

	// delay time cang nho thi push cang nhanh , delaytime ti le ngich vs level
	// level 1-3 : speed rand() %4 ; level 4-7 : rand() % 3 ; level >=8 : rand() %2

	switch (ID) {
	case VEHICLELANE_ID: {
		aLanes.push_back(new CVEHICLELANE(0, yLane, 2 + rand() % 5));
		break;
	}
	case GRASSLANE_ID: {
		aLanes.push_back(new CGRASSLANE(0, yLane));
		break;
	}
	case TRAINLANE_ID: {
		aLanes.push_back(new CTRAINLANE(0, yLane, 1 + rand() % 2, 10 + (rand() % 10)));
		break;
	}
	case RIVERLANE_ID: {
		aLanes.push_back(new CRIVERLANE(0, yLane, 2 + rand() % 5));
		break;
	}
	case FINISHLANE_ID: {
		aLanes.push_back(new CFINISHLANE(0, yLane));
		break;
	}
	case GRASSLANE_FULL_ID: {
		aLanes.push_back(new CGRASSLANE(0, yLane, FULL_TREE_TYPELANE));
		break;
	}
	case GRASSLANE_SURROUND_ID: {
		aLanes.push_back(new CGRASSLANE(0, yLane, SURROUND_TREE_TYPELANE));
		break;
	}
	case GRASSLANE_AROUND_ID: {
		aLanes.push_back(new CGRASSLANE(0, yLane, AROUND_TREE_TYPELANE));
		break;
	}
	default:
		aLanes.push_back(new CGRASSLANE(0, yLane));
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
	if (countLane < numberOfLane) pushRandomLane();
	else if (countLane == numberOfLane) push_frontLane(FINISHLANE_ID);
	else if (countLane == numberOfLane + 1) push_frontLane(GRASSLANE_FULL_ID);
	else push_frontLane(GRASSLANE_ID);
	pop_backLane();
	countLane++;
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
				cPlayer->increaseScore(1);
				break;
			}
			case PERRY_ID: {
				COBJECT* cur = aLanes[yBoard]->getPos(xBoard);
				if (cur != NULL) delete cur;
				cur = NULL;
				aLanes[yBoard]->setPos(xBoard, NULL);
				cPlayer->setDependObj(NULL);

				if (!(nextObj->getID() == TREE_DOUBLE_ID || nextObj->getID() == TREE_SINGLE_ID)) {
					if (cPlayer->getYBoard() == UP_LANE)
					{
						moveNewLane();
						startMap();
					}
					else cPlayer->setPos(xBoard, yBoard - 1);
				}
				break;
			}
			case CAR_ID: case TRUCK_ID:
				playEffectSound(GAME_CARHIT);
				break;
			case TRAIN_HEAD_ID: case TRAIN_BODY_ID:
				playEffectSound(GAME_TRAIN);
				break;
			}

			if (cPlayer->isMoving() && !(nextObj->getID() == TREE_DOUBLE_ID || nextObj->getID() == TREE_SINGLE_ID)) {
				if (cPlayer->moveCharacter()) {
					moveNewLane();
					startMap();
				};
				//Reset moving
				cPlayer->setMoving(0);
				//Update depend obj 
				cPlayer->setDependObj(nextObj);
			}
			drawTaskBar();
			drawMap();
			displayScreen(0, START_BOARD_HEIGHT, -1, -1);

			if (cPlayer->isDead()) {
				level = 1;
				countLane = 0;
				continue;
			}
			//Xy ly finish
			if (countLane == numberOfLane + 6) {
				cPlayer->increaseScore(5);
				level++;
				countLane = 0;
				cPlayer->set(BOARD_WIDTH / 2, UP_LANE);
				resetData();
				startMap();
			}
			//Win
			if (level == MAX_LEVEL) continue;
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
		ObjLayer.drawString("TIME", SCREEN_WIDTH - 44, 0, BLACK, LIGHT_GRAY);
		ObjLayer.DrawObject(COLON, SCREEN_WIDTH - 27, 0,BLACK, LIGHT_GRAY);
		ObjLayer.drawTime(curTime, SCREEN_WIDTH- 22, 0, BLACK, LIGHT_GRAY);
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
// task bar
void CGAME::updateScore() {
	ObjLayer.DrawEgg(114, 0);
	ObjLayer.DrawNumber(cPlayer->getScore()+1, 127, 0, BLACK, LIGHT_GRAY);
}
void CGAME::updateLevel() {
	ObjLayer.drawString("LEVEL", 74, 0, BLACK, LIGHT_GRAY);
	ObjLayer.DrawObject(COLON, 95, 0, BLACK, LIGHT_GRAY);
	ObjLayer.DrawNumber(this->level, 100, 0, BLACK, LIGHT_GRAY);
}

//Drawing functions
void CGAME::startMap() {
	BgdLayer.clear(BLACK, LIGHT_GRAY);
	for (int i = 0; i < BOARD_HEIGHT; i++)
		aLanes[i]->DrawLane(BgdLayer);
}
void CGAME::drawMap() {
	ObjLayer.clear(-1, -1);
	for (int i = 0; i < BOARD_HEIGHT; i++)
		this->aLanes[i]->DrawObjects(ObjLayer);
	if (!cPlayer->isDead()) cPlayer->drawCharacter(ObjLayer);
}
void CGAME::drawTaskBar() {
	// draw pause
	ObjLayer.drawString("P", 3, 0, BLACK, LIGHT_GRAY);
	ObjLayer.DrawObject(COLON,8, 0, BLACK, LIGHT_GRAY);
	ObjLayer.drawString("PAUSE", 12, 0, BLACK, LIGHT_GRAY);

	updateLevel();
	updateTime();
	updateScore();
	displayScreen(0, 0, SCREEN_WIDTH, 2);
}
void CGAME::intro() {
	cout << "LET'S START IT!" << endl;
}
void CGAME::outtro() {
	cout << "END GAME..." << endl;
}
void CGAME::drawCountDown() {
	//cout down
	CGRAPHIC tmpBgdLayer(BgdLayer), tmpObjLayer({ L' ', -1, -1 });
	displayScreen(tmpObjLayer, tmpBgdLayer);

	int x = (SCREEN_WIDTH - 35) / 2, y = (SCREEN_HEIGHT - 17) / 2;
	tmpObjLayer.DrawBigNumber(3, x, y, DARK_RED, WHITE);
	displayScreen(tmpObjLayer, BgdLayer, 0, 0, -1, -1);

	bool isSkip = false;
	takeArest(isSkip, 1000);

	tmpObjLayer.clear(-1, -1);
	tmpObjLayer.DrawBigNumber(2, x, y, BRIGHT_YELLOW, WHITE);
	displayScreen(tmpObjLayer, BgdLayer, 0, 0, -1, -1);

	takeArest(isSkip, 1000);

	tmpObjLayer.clear(-1, -1);
	tmpObjLayer.DrawBigNumber(1, x, y, DARK_GREEN, WHITE);
	displayScreen(tmpObjLayer, BgdLayer, 0, 0, -1, -1);

	takeArest(isSkip, 1000);
}

bool CGAME::drawLosingScreen(int COLOR) {
	playBackgroundSound(OFF_SOUND);
	playEffectSound(MENU_LOSING);
	// draw
	CGRAPHIC Tmpback;
	Tmpback.clear(SKY_BLUE, SKY_BLUE);
	for (int i = 0; i < 208; i++) {
		Tmpback.screen[i][34].bgdColor = DARK_GREEN;
		Tmpback.screen[i][34].txtColor = DARK_GREEN;
	}
	for (int i = 0; i < 208; i++)
		for (int j = 34; j < 51; j++) {
			Tmpback.screen[i][j].bgdColor = LIGHT_GREEN;
			Tmpback.screen[i][j].txtColor = LIGHT_GREEN;
		}
	CGRAPHIC TmpBgdLayer(BgdLayer), TmpObjLayer({ L' ', -1, -1 });
	TmpBgdLayer.clear(SKY_BLUE, SKY_BLUE);
	for (int i = 0; i < 208; i++) {
		TmpBgdLayer.screen[i][34].bgdColor = DARK_GREEN;
		TmpBgdLayer.screen[i][34].txtColor = DARK_GREEN;
	}
	for (int i = 0; i < 208; i++)
		for (int j = 35; j < 51; j++) {
			TmpBgdLayer.screen[i][j].bgdColor = LIGHT_GREEN;
		}
	int UFO_x = 81, UFO_y = 10;
	int Dino_x = UFO_x + 15, Dino_y = UFO_y + 20;
	CUFO UFO(UFO_x, UFO_y);
	UFO.DrawObject(TmpBgdLayer, 47, 28);
	CDINOSAUR DINO(Dino_x, Dino_y, true, COLOR);
	DINO.DrawBlock(TmpObjLayer);
	for (int i = 0; i < 208; i++) {
		Tmpback.screen[i][34].bgdColor = DARK_GREEN;
		Tmpback.screen[i][34].txtColor = DARK_GREEN;
	}
	for (int i = 0; i < 208; i++) {
		TmpBgdLayer.screen[i][34].bgdColor = DARK_GREEN;
		TmpBgdLayer.screen[i][34].txtColor = DARK_GREEN;
		TmpBgdLayer.screen[i][34].txtColor = BLACK;
	}
	displayScreen(TmpBgdLayer, Tmpback, 0, 0, -1, -1);
	displayScreen(TmpObjLayer, TmpBgdLayer, 0, 0, -1, -1);

	bool isSkip = false;
	takeArest(isSkip);

	TmpObjLayer.erasePixel(Dino_x, Dino_y, Dino_x + 16, Dino_y + 6);
	DINO.setY(Dino_y -= 3);
	DINO.DrawBlock(TmpObjLayer);
	displayScreen(TmpObjLayer, TmpBgdLayer, Dino_x, Dino_y, Dino_x + 16, Dino_y + 9);

	takeArest(isSkip);

	TmpObjLayer.erasePixel(Dino_x, Dino_y, Dino_x + 16, Dino_y + 6);
	DINO.setY(Dino_y -= 3);
	DINO.DrawBlock(TmpObjLayer);
	displayScreen(TmpObjLayer, TmpBgdLayer, Dino_x, Dino_y, Dino_x + 16, Dino_y + 9);

	takeArest(isSkip);

	TmpObjLayer.erasePixel(Dino_x, Dino_y, Dino_x + 16, Dino_y + 6);
	DINO.setY(Dino_y -= 3);
	DINO.DrawBlock(TmpObjLayer);
	displayScreen(TmpObjLayer, TmpBgdLayer, Dino_x, Dino_y, Dino_x + 16, Dino_y + 9);

	takeArest(isSkip);

	TmpObjLayer.erasePixel(Dino_x, Dino_y, Dino_x + 16, Dino_y + 6);
	DINO.setY(Dino_y -= 3);
	DINO.DrawBlock(TmpObjLayer);
	displayScreen(TmpObjLayer, TmpBgdLayer, Dino_x, Dino_y, Dino_x + 16, Dino_y + 9);

	takeArest(isSkip);

	TmpObjLayer.erasePixel(Dino_x, Dino_y, Dino_x + 16, Dino_y + 6);
	DINO.setY(Dino_y -= 1);
	DINO.DrawBlock(TmpObjLayer);
	displayScreen(TmpObjLayer, TmpBgdLayer, Dino_x, Dino_y, Dino_x + 16, Dino_y + 6);
	TmpObjLayer.erasePixel(Dino_x, Dino_y, Dino_x + 16, Dino_y + 6);
	TmpBgdLayer.erasePixel(UFO_x, UFO_y + 7, UFO_x + 47, UFO_y + 28);
	for (int i = 0; i < 208; i++) {
		Tmpback.screen[i][34].bgdColor = DARK_GREEN;
		Tmpback.screen[i][34].txtColor = DARK_GREEN;
	}
	for (int i = 0; i < 208; i++) {
		TmpBgdLayer.screen[i][34].bgdColor = DARK_GREEN;
		TmpBgdLayer.screen[i][34].txtColor = DARK_GREEN;
	}
	displayScreen(TmpObjLayer, TmpBgdLayer, UFO_x, UFO_y + 7, UFO_x + 47, UFO_y + 28);
	displayScreen(TmpBgdLayer, Tmpback, UFO_x, UFO_y + 7, UFO_x + 47, UFO_y + 28);

	takeArest(isSkip);

	TmpBgdLayer.DrawMissonFailed(54, 2, DARK_RED, SKY_BLUE);
	TmpBgdLayer.drawString("SCORE", UFO_x, UFO_y + 8, BLACK, SKY_BLUE);
	TmpBgdLayer.DrawObject(COLON, UFO_x + 21, UFO_y + 8, BLACK, SKY_BLUE);
	if (cPlayer->getScore() == 0) cPlayer->setScore(1);
	TmpBgdLayer.DrawNumber(cPlayer->getScore(), UFO_x + 25, UFO_y + 8, BLACK, SKY_BLUE);
	TmpBgdLayer.drawString("LEVEL", UFO_x, UFO_y + 13, BLACK, SKY_BLUE);
	TmpBgdLayer.DrawObject(COLON, UFO_x + 21, UFO_y + 13, BLACK, SKY_BLUE);
	TmpBgdLayer.DrawNumber(level, UFO_x + 25, UFO_y + 13, BLACK, SKY_BLUE);
	displayScreen(TmpBgdLayer, Tmpback, 0, 0, -1, -1);

	takeArest(isSkip);

	TmpBgdLayer.drawString("PLAY AGAIN", 34, 40, LIGHT_GRAY, LIGHT_GREEN);
	TmpBgdLayer.drawString("EXIT TO MENU", 134, 40, LIGHT_GRAY, LIGHT_GREEN);
	displayScreen(TmpBgdLayer, Tmpback, 0, 0, -1, -1);

	// option
	const int fromX = 34, fromY = 40,
		toX = fromX + 11 * 4 + 7, toY = fromY + 4;

	const int PLAY_AGAIN = fromX;
	const int EXIT_TO_MENU = fromX + 100;

	int xOption = PLAY_AGAIN, yOption = fromY;

	// draw current choice
	if (xOption == PLAY_AGAIN) {
		TmpObjLayer.drawString("PLAY AGAIN", PLAY_AGAIN, fromY, DARK_GREEN, LIGHT_GREEN);
		TmpObjLayer.drawString("EXIT TO MENU", EXIT_TO_MENU, fromY, LIGHT_GRAY, LIGHT_GREEN);
	}
	else {
		TmpObjLayer.drawString("EXIT TO MENU", xOption, 40, DARK_RED, LIGHT_GREEN);
		TmpObjLayer.drawString("PLAY AGAIN", 34, 40, LIGHT_GRAY, LIGHT_GREEN);
	}
	displayScreen(TmpObjLayer, TmpBgdLayer, 0, 40, SCREEN_WIDTH - 1, 42);

	while (1) {
		// erase the last step
		if (xOption == PLAY_AGAIN)TmpObjLayer.erasePixel(34, 40, 34 + 60, 42);
		else TmpObjLayer.erasePixel(134, 40, 134 + 60, 42);

		int temp = toupper(_getch());
		if (xOption == PLAY_AGAIN) {
			if (!isEnterButton(temp)) {
				if (isUpButton(temp) == true || isDownButton(temp) == true || isLeftButton(temp) == true || isRightButton(temp) == true) {
					xOption = EXIT_TO_MENU;

					TmpObjLayer.drawString("PLAY AGAIN", 34, 40, LIGHT_GRAY, LIGHT_GREEN);
					displayScreen(TmpObjLayer, TmpBgdLayer, 34, 40, 34 + 60, 42);
					TmpObjLayer.drawString("EXIT TO MENU", 134, 40, DARK_RED, LIGHT_GREEN);
					displayScreen(TmpObjLayer, TmpBgdLayer, 134, 40, 134 + 60, 42);
				}
			}
			else {
				return true;
			}
		}
		else {
			if (!isEnterButton(temp)) {
				if (isUpButton(temp) == true || isDownButton(temp) == true || isLeftButton(temp) == true || isRightButton(temp) == true) {
					xOption = PLAY_AGAIN;
					TmpObjLayer.drawString("PLAY AGAIN", 34, 40, DARK_GREEN, LIGHT_GREEN);
					displayScreen(TmpObjLayer, TmpBgdLayer, 34, 40, 34 + 60, 42);
					TmpObjLayer.drawString("EXIT TO MENU", 134, 40, LIGHT_GRAY, LIGHT_GREEN);
					displayScreen(TmpObjLayer, TmpBgdLayer, 134, 40, 134 + 60, 42);

				}
			}
			else {
				return false;
			}
		}
	}

}
void CGAME::drawWiningScreen(int COLOR) {
	playBackgroundSound(OFF_SOUND);
	playEffectSound(MENU_WINING);
	CGRAPHIC Tmpback;
	Tmpback.clear(SKY_BLUE, SKY_BLUE);
	for (int i = 0; i < 208; i++) {
		Tmpback.screen[i][34].bgdColor = DARK_GREEN;
		Tmpback.screen[i][34].txtColor = DARK_GREEN;
	}
	for (int i = 0; i < 208; i++)
		for (int j = 34; j < 51; j++) {
			Tmpback.screen[i][j].bgdColor = LIGHT_GREEN;
			Tmpback.screen[i][j].txtColor = LIGHT_GREEN;
		}
	CGRAPHIC TmpBgdLayer(BgdLayer), TmpObjLayer({ L' ', -1, -1 });
	TmpBgdLayer.clear(SKY_BLUE, SKY_BLUE);
	for (int i = 0; i < 208; i++) {
		TmpBgdLayer.screen[i][34].bgdColor = DARK_GREEN;
		TmpBgdLayer.screen[i][34].txtColor = DARK_GREEN;
	}
	for (int i = 0; i < 208; i++)
		for (int j = 35; j < 51; j++) {
			TmpBgdLayer.screen[i][j].bgdColor = LIGHT_GREEN;
		}
	int UFO_x = 81, UFO_y = 10;
	int Dino_x = UFO_x + 15, Dino_y = UFO_y + 20;
	int Fedora_x = Dino_x + 1, Fedora_y = Dino_y - 12;
	CUFO UFO(UFO_x, UFO_y);
	for (int i = UFO_x + 13; i <= UFO_x + 31; i++)
		for (int j = UFO_y + 17; j <= UFO_y + 23; j++) {
			Tmpback.screen[i][j].txtColor = BRIGHT_YELLOW;
			Tmpback.screen[i][j].bgdColor = BRIGHT_YELLOW;
		}
	UFO.DrawObject(TmpBgdLayer, 47, 28);
	CDINOSAUR DINO(Dino_x, Dino_y, false, COLOR);
	DINO.DrawBlock(TmpBgdLayer);
	for (int i = 0; i < 208; i++) {
		Tmpback.screen[i][34].bgdColor = DARK_GREEN;
		Tmpback.screen[i][34].txtColor = DARK_GREEN;
	}
	for (int i = 0; i < 208; i++) {
		TmpBgdLayer.screen[i][34].bgdColor = DARK_GREEN;
		TmpBgdLayer.screen[i][34].txtColor = DARK_GREEN;
		TmpBgdLayer.screen[i][34].txtColor = BLACK;
	}
	TmpBgdLayer.screen[Dino_x + 7][Dino_y + 4].bgdColor = LIGHT_GREEN;
	TmpBgdLayer.screen[Dino_x + 8][Dino_y + 4].bgdColor = LIGHT_GREEN;
	TmpBgdLayer.screen[Dino_x + 9][Dino_y + 4].bgdColor = LIGHT_GREEN;
	TmpObjLayer.DrawHat(Fedora_x, Fedora_y, SADDLE_BROWN);
	displayScreen(TmpBgdLayer, Tmpback, 0, 0, -1, -1);
	displayScreen(TmpObjLayer, TmpBgdLayer, 0, 0, -1, -1);

	bool isSkip = false;
	takeArest(isSkip, 300);

	TmpObjLayer.erasePixel(Fedora_x, Fedora_y, Fedora_x + 15, Fedora_y + 5);
	TmpObjLayer.DrawHat(Fedora_x, Fedora_y += 2, SADDLE_BROWN);
	displayScreen(TmpObjLayer, TmpBgdLayer, Fedora_x, Fedora_y - 2, Fedora_x + 15, Fedora_y + 5);

	takeArest(isSkip, 300);

	TmpObjLayer.erasePixel(Fedora_x, Fedora_y, Fedora_x + 15, Fedora_y + 5);
	TmpObjLayer.DrawHat(Fedora_x, Fedora_y += 2, SADDLE_BROWN);
	displayScreen(TmpObjLayer, TmpBgdLayer, Fedora_x, Fedora_y - 2, Fedora_x + 15, Fedora_y + 5);

	takeArest(isSkip, 300);

	TmpObjLayer.erasePixel(Fedora_x, Fedora_y, Fedora_x + 15, Fedora_y + 5);
	TmpObjLayer.DrawHat(Fedora_x, Fedora_y += 2, SADDLE_BROWN);
	displayScreen(TmpObjLayer, TmpBgdLayer, Fedora_x, Fedora_y - 2, Fedora_x + 15, Fedora_y + 5);

	takeArest(isSkip, 300);

	TmpObjLayer.erasePixel(Fedora_x, Fedora_y, Fedora_x + 15, Fedora_y + 5);
	TmpObjLayer.DrawHat(Fedora_x, Fedora_y += 2, SADDLE_BROWN);
	displayScreen(TmpObjLayer, TmpBgdLayer, Fedora_x, Fedora_y - 2, Fedora_x + 15, Fedora_y + 5);
	TmpBgdLayer.erasePixel(UFO_x, UFO_y + 7, UFO_x + 47, UFO_y + 28);
	TmpObjLayer.erasePixel(UFO_x, UFO_y + 7, UFO_x + 47, UFO_y + 28);
	for (int i = UFO_x + 13; i <= UFO_x + 31; i++)
		for (int j = UFO_y + 17; j <= UFO_y + 23; j++) {
			Tmpback.screen[i][j].txtColor = SKY_BLUE;
			Tmpback.screen[i][j].bgdColor = SKY_BLUE;
		}
	DINO.DrawBlock(TmpBgdLayer);
	TmpObjLayer.DrawHat(Fedora_x, Fedora_y, SADDLE_BROWN);
	TmpObjLayer.DrawMissonMissonCompleted(40, 2, DARK_GREEN, SKY_BLUE);
	displayScreen(TmpBgdLayer, Tmpback, UFO_x, UFO_y + 7, UFO_x + 47, UFO_y + 28);
	displayScreen(TmpObjLayer, TmpBgdLayer, 0, 0, -1, -1);
	TmpObjLayer.drawString("SCORE", UFO_x, UFO_y + 8, BLACK, SKY_BLUE);
	TmpObjLayer.DrawObject(COLON, UFO_x + 21, UFO_y + 8, BLACK, SKY_BLUE);
	if (cPlayer->getScore() == 0) cPlayer->setScore(1);
	TmpObjLayer.DrawNumber(cPlayer->getScore(), UFO_x + 25, UFO_y + 8, BLACK, SKY_BLUE);
	TmpObjLayer.drawString("TIME", UFO_x, UFO_y + 13, BLACK, SKY_BLUE);
	TmpObjLayer.DrawObject(COLON, UFO_x + 21, UFO_y + 13, BLACK, SKY_BLUE);
	TmpObjLayer.drawTime(curTime, UFO_x + 25, UFO_y + 13, BLACK, SKY_BLUE);

	takeArest(isSkip, 300);

	displayScreen(TmpObjLayer, TmpBgdLayer, 0, 0, -1, -1);
	TmpObjLayer.drawString("PRESS ANY KEY TO RETURN", 60, UFO_y + 30, DARK_GREEN, LIGHT_GREEN);

	takeArest(isSkip, 300);

	displayScreen(TmpObjLayer, TmpBgdLayer, 0, 0, -1, -1);
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

void CGAME::playEffectSound(string soundName) {
	mciSendString(L"close wav", NULL, 0, NULL);
	if (soundName != OFF_SOUND) {
		string fileName = "open " + soundName + int_to_string(effectSoundLevel) + ".wav" + " type mpegvideo alias wav";
		wstring wfileName(fileName.begin(), fileName.end());
		LPCWSTR swfileName = wfileName.c_str();
		mciSendString(swfileName, NULL, 0, NULL);

		mciSendString(L"play wav", NULL, 0, NULL);
	}
}
void CGAME::playBackgroundSound(string soundName) {
	if (soundName == OFF_SOUND) PlaySound(NULL, NULL, 0);
	else {
		string fileName = soundName + int_to_string(bgdSoundLevel) + ".wav";
		wstring wfileName(fileName.begin(), fileName.end());
		LPCWSTR swfileName = wfileName.c_str();
		PlaySound(swfileName, NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	}
}
void CGAME::takeArest(bool& isSkip, int wait) {
	if (!isSkip) {
		isSkip = _kbhit();
		if (isSkip) _getch();
	}
	if (!isSkip) Sleep(500);
}

bool isUpButton(int button) {
	return button == 'W' || button == 72;
}
bool isDownButton(int button) {
	return button == 'S' || button == 80;
}
bool isRightButton(int button) {
	return button == 'D' || button == 77;
}
bool isLeftButton(int button) {
	return button == 'A' || button == 75;
}
bool isEnterButton(int button) {
	return button == 13 || button == 32;
}
bool isDeleteButton(int button) {
	return button == 83;
}
bool isBackspaceButton(int button) {
	return button == 8;
}

bool isNumber(char ch) {
	return tolower(ch) >= '0' && tolower(ch) <= '9';
}
bool isLetter(char ch) {
	return toupper(ch) >= 'A' && toupper(ch) <= 'Z';
}
bool isNumberOrLetter(char ch) {
	return isNumber(ch) || isLetter(ch);
}
bool checkinList(string str, deque<string> strArr) {
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

string int_to_string(int num) {
	vector<int> arrNum{};
	for (; num != 0; num /= 10)
		arrNum.push_back(num % 10);
	string res{};
	for (int i = 0; i < (int)arrNum.size(); i++)
		res.push_back(arrNum[(int)arrNum.size() - 1 - i] + '0');
	return res;
}
