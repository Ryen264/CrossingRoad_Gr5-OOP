#pragma once
#include "CGRAPHIC.h"
#include "CPLAYER.h"
#include "CVEHICLELANE.h"
#include <vector>
#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;
class CGAME {
    const int START_HEIGHT = 0;
    const int FINISH_HEIGHT = 10;
    const int NUMBER_OF_TYPE_LANE = 1;
    bool isRunning;
    CPLAYER* cPlayer;
    int numberOfLanes;
    vector<CLANE*> aLanes;

    CGRAPHIC ObjLayer, BgdLayer;
public:
    friend void ShowCur(bool CursorVisibility);

    CGAME(int numberOfLanes = 10);
    ~CGAME();
    void start();
    void input();
    void logic();
    bool isReset();
    void reset();
    void saveGame();

    void Menu();
    void NewGame();
    void LoadGame();
    void Setting();
    void Help();
    void About();
    void Quit();

    void intro();
    void drawMenu();
    void drawMap();
    void drawQuit();
    void drawIsReset();

    void displayScreen();
};
