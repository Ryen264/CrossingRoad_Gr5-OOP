#pragma once
#include "CGRAPHIC.h"
#include "CPLAYER.h"
#include "CVEHICLELANE.h"
#include "CGRASSLANE.h"
#include "CTRAINLANE.h"
#include "CRIVERLANE.h"

#include <vector>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <deque>
#include <queue>
#include <thread>
#include <fstream>
#include <string>
using namespace std;
class CGAME {
    const int NUMBER_OF_TYPE_LANE = 3;

    CPLAYER* cPlayer;
    vector<CLANE*> aLanes;
    deque<string> fileNameList;

    //Thread variables
    bool isThreadRunning = true;

    //Screen layers
    CGRAPHIC ObjLayer, BgdLayer;
public:
    CGAME();
    ~CGAME();
    void Configure();

    void start();
    void playGame();
    void startMap();

    void resetData();
    void saveData(string fileName);
    void loadData(string fileName);
    string inputUserTxt();
    int inputUserNumber();
    void saveFileNameList();
    void loadFileNameList();
    
    int Menu();
    void NewGame();
    void LoadGame();
    void SaveGame();
    void Setting();
    void Help();
    void About();

    void SubThreadNewGame();
    void exitThread(thread* t);
    void resumeThread(HANDLE t);
    int Pause(HANDLE t);

    bool isInjured() const;
    bool isReset();

    void intro();
    void outtro();
    void drawMap();
    void drawMenu();
    void drawPause();
    void drawPlayAgain();
    void drawSaveGame();
    void drawLoadGame();
	void drawInputUserTxt();
    void drawInputUserNumber();

    void displayBgd();
    void displayObj();
    void displayScreen();
};
//Return codes
const int QUIT_CODE = -1000;
const int BACK_TO_MENU_CODE = -1001;

//Lane IDs
const int VEHICLELANE_ID = 20001;
const int GRASSLANE_ID = 20002;
const int RIVERLANE_LAND_ID = 20003;
const int RIVERLANE_NOLAND_ID = 21003;
const int TRAINLANE_ID = 20004;
const vector<int> LANE_ID_LIST = { VEHICLELANE_ID, GRASSLANE_ID, RIVERLANE_LAND_ID, TRAINLANE_ID };

void ShowCur(bool CursorVisibility);
void DisableResizeWindow();
void ShowScrollbar(BOOL Show);

