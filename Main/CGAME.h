#pragma once
#include "CGRAPHIC.h"
#include "CPLAYER.h"
#include "CVEHICLELANE.h"
#include "CGRASSLANE.h"
#include "CTRAINLANE.h"
#include "CRIVERLANE.h"
#include "CFINISHLANE.h"
#include "CUFO.h"
#include "CDINOSAUR.h"

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
    string savedName;

    int level = 1, countLane = 0, numberOfLane = 0;
    int conditionLane = 0, countConditionLane = 0, numberOfConditionLane = 0;

    //Thread variables
    bool isThreadRunning = true;

    //Screen layers
    CGRAPHIC ObjLayer, BgdLayer;

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwBytesWritten = 0;
public:
    CGAME();
    ~CGAME();
    void Configure();

    void start();
    void playGame();

    void resetData();
    void saveData(string fileName);
    void loadData(string fileName);

    string inputUserTxt(CGRAPHIC& ObjLayer, CGRAPHIC& BgdLayer, int fromX, int fromY, int maxSize, int txtColor, int bgdColor, bool(*checkFunction)(char) = NULL, deque<string> strArr = {});

    void saveFileNameList();
    void loadFileNameList();
    void deleteFileName(int);
    void changeFileName(int);

    int Menu();
    void NewGame();
    void LoadGame();
    void SaveGame();
    void Setting();
    void Help();
    void About();

    int Pause(HANDLE t);
    void ChooseCharacter();

    bool isReset();

    void exitThread(thread* t);
    void resumeThread(HANDLE t);

    void updateYLane();
    void pushRandomLane();
    void push_frontLane(int ID);
    void pop_backLane();
    void moveNewLane();

    void SubThreadNewGame();

    void startMap();
    void drawMap();

    void intro();
    void outtro();
    void drawPlayAgain();
    void drawWiningScreen(int COLOR = DARK_GREEN);

    void displayScreen(int fromX = 0, int fromY = 0, int toX = -1, int toY = -1);
    void displayScreen(CGRAPHIC& ObjLayer, const CGRAPHIC& BgdLayer, int fromX = 0, int fromY = 0, int toX = -1, int toY = -1);
};
//Return codes
const int QUIT_CODE = -1000;
const int BACK_TO_MENU_CODE = -1001;

const vector<int> LANE_ID_LIST = { VEHICLELANE_ID, TRAINLANE_ID, RIVERLANE_ID };

bool isUpButton(int button);
bool isDownButton(int button);
bool isRightButton(int button);
bool isLeftButton(int button);
bool isEnterButton(int button);
bool isDeleteButton(int button);
bool isBackspaceButton(int button);

bool isNumber(char ch);
bool isLetter(char ch);
bool isNumberOrLetter(char ch);
bool isExist(string str, deque<string> strArr);

int getiMatrix(int val, vector<vector<int>>& matrix);
int getjMatrix(int val, vector<vector<int>>& matrix);

void ShowCur(bool CursorVisibility);
void DisableResizeWindow();
void ShowScrollbar(BOOL Show);

