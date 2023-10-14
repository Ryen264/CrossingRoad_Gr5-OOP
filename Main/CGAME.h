﻿#pragma once
#include "CPLAYER.h"
#include "CLANE.h"
#include "CVEHICLELANE.h"
#include <vector>
#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;
class CGAME {
    bool isRunning;
	CPLAYER cPlayer;

    int numberOfLanes;
	vector<CLANE*> aLanes;
    const int WIDTH = 20;
    const int HEIGHT = 10;
    const int START_HEIGHT = 0;
    const int FINISH_HEIGHT = 10;
    const int TYPELANENUM = 1;
public:
	CGAME(int numberOfLanes = 10);
	~CGAME();
    void finishTell(ostream& outDev);
    void draw(ostream& outDev);
    void input();
    void logic();
    void start();
    /*
    void resetGame(); //Thiếp lập lại dữ liệu
    void loadGame(istream); //Tải trò chơi đã lưu
    void saveGame(istream); //Lưu trò chơi
    void pauseGame(HANDLE); //Tạm dừng thread
    void resumeGame(HANDLE); //Quay lại thread
    */
};

