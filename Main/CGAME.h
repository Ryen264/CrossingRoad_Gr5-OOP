#pragma once
#include "CGRAPHIC.h"
#include "CPLAYER.h"
#include "CVEHICLELANE.h"
#include "CGRASSLANE.h"

#include <vector>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <mutex>
#include <condition_variable>
using namespace std;
class CGAME {
    const int NUMBER_OF_TYPE_LANE = 2;

    CPLAYER* cPlayer;
    vector<CLANE*> aLanes;

    //Return codes
    const int QUIT_CODE = -1000;
    const int BACK_TO_MENU_CODE = -1001;

    //Thread variables
    bool isThreadRunning = true;
    mutex mtx;
    condition_variable cv;

    //Screen layers
    CGRAPHIC ObjLayer, BgdLayer;
public:
    friend void ShowCur(bool CursorVisibility);

    CGAME();
    ~CGAME();
    void start();
    void resetData();
    void resetMap();
    //void saveData();

    int Menu();
    void NewGame();
    void LoadGame();
    void Setting();
    void Help();
    void About();

    void SubThreadNewGame();
    void exitThread(thread* t);
    void resumeThread(HANDLE t);
    int Pause(HANDLE t);

    bool isInjured();
    bool isReset();

    void intro();
    void outtro();
    void drawMap();
    void drawMenu();
    void drawPause();
    void drawPlayAgain();

    void displayBgd();
    void displayObj();
    void displayScreen();
};
