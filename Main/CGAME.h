#pragma once
#include "CGRAPHIC.h"
#include "CPLAYER.h"
#include "CLANE.h"
#include "CVEHICLELANE.h"
#include <vector>
#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;
class CGAME {
    const int WIDTH = 20;
    const int HEIGHT = 10;
    const int START_HEIGHT = 0;
    const int FINISH_HEIGHT = 10;
    const int TYPELANENUM = 1;
    bool isRunning;
	CPLAYER* cPlayer;
    int numberOfLanes;
	vector<CLANE*> aLanes;
    int BLACK, WHITE;
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

    void Configure();
    void SetupTheme(THEME theme = THEME_BASIC);

    void intro();
    void drawMenu();
    void drawMap();
    void drawQuit();
    void drawIsReset();
    void drawDemo();
    void drawlane();
    void drawTree(int, int);
    void drawCar(int, int);

    void finishTell();
    /*
    void pauseGame(HANDLE); //Tạm dừng thread
    void resumeGame(HANDLE); //Quay lại thread
    */
};

