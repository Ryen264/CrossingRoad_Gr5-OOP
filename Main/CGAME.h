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
public:
	CGAME(int numberOfLanes = 10);
	~CGAME();
    void input();
    void logic();
    void start();
    void quit();
    bool isReset();
    void reset();

    void finishTell(ostream& outDev);
    void drawMap(ostream& outDev);
    void drawStart(ostream& outDev);
    void drawQuit(ostream& outDev);
    void drawIsReset(ostream& outDev);
    void drawDemo();
    void drawlane();
    void drawPerry();

    friend void ShowCur(bool CursorVisibility);
    /*
    void loadGame(istream); //Tải trò chơi đã lưu
    void saveGame(istream); //Lưu trò chơi
    void pauseGame(HANDLE); //Tạm dừng thread
    void resumeGame(HANDLE); //Quay lại thread
    */
};

