#pragma once
#include "CGRAPHIC.h"
#include "CPLAYER.h"
#include "CVEHICLELANE.h"
#include "CGRASSLANE.h"
#include "CTRAINLANE.h"
#include "CRIVERLANE.h"
#include "CFINISHLANE.h"

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
    CPLAYER* cPlayer;
    deque<CLANE*> aLanes;
    deque<string> fileNameList;
    bool isSaved = false;
    string savename;
    bool isNextTree = false;

    int level = 1, numberOfLane = 0;
    int conditionLane = 0, countLane = 0, numberOfConditionLane = 0;

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

    void resetData();
    void saveData(string fileName);
    void loadData(string fileName);

    string inputUserTxt();
    int inputUserNumber();
    bool checkFileName(string fileName);
    void saveFileNameList();
    void loadFileNameList();
    void deleteFileName(int);
    void changeFileName(int);

    int Menu();
    void NewGame();
    void LoadGame();
    string SaveGame();
    void Setting();
    void Help();
    void About();


    int Pause(HANDLE t);
    bool isReset();

    void exitThread(thread* t);
    void resumeThread(HANDLE t);

    bool isInjured() const;
    void updateYLane();
    void pushRandomLane();
    void push_frontLane(int ID);
    void pop_backLane();


    void SubThreadNewGame();

    void startMap();
    void drawMap();

    void intro();
    void outtro();

    void drawMenu();
    void drawPause();
    void drawPlayAgain();
    void drawSaveGame();
    void drawLoadGame();
	void drawInputUserTxt();
    void drawInputUserNumber();

    void displayScreen(int fromX = 0, int fromY = 0, int toX = -1, int toY = -1);
};
//Return codes
const int QUIT_CODE = -1000;
const int BACK_TO_MENU_CODE = -1001;

const vector<int> LANE_ID_LIST = { VEHICLELANE_ID, TRAINLANE_ID, RIVERLANE_ID};

void ShowCur(bool CursorVisibility);
void DisableResizeWindow();
void ShowScrollbar(BOOL Show);

