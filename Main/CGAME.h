#pragma once
#include "CGRAPHIC.h"
#include "CPLAYER.h"
#include "CVEHICLELANE.h"
#include "CGRASSLANE.h"

#include <vector>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <deque>
#include <queue>
#include <thread>
#include <fstream>
#include<string>
using namespace std;
class CGAME {
    const int NUMBER_OF_TYPE_LANE = 2;

    CPLAYER* cPlayer;
    vector<CLANE*> aLanes;
    deque<string> fileNameList;

    //Return codes
    const int QUIT_CODE = -1000;
    const int BACK_TO_MENU_CODE = -1001;

    //Lane IDs
    const int VEHICLELANE_ID = 20001;
    const int GRASSLANE_ID = 20002;
    const int RIVERLANE_ID = 20003;

    //Object IDs
    const int CAR_ID = 30001;
    const int TRUCK_ID = 30002;
    const int DINOSAUR_ID = 30003;

    //Thread variables
    bool isThreadRunning = true;

    //Screen layers
    CGRAPHIC ObjLayer, BgdLayer;
public:
    friend void ShowCur(bool CursorVisibility);

    CGAME();
    ~CGAME();
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
