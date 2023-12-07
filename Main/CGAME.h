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

#include <xaudio2.h>
#include <windows.h>
#include <iostream>
#include <sstream>
#include <conio.h>
#include <time.h>
#include <deque>
#include <queue>
#include <thread>
#include <fstream>
#include <string>
using namespace std;

#pragma comment(lib, "xaudio2.lib")

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

    // Time
    clock_t startTime = 0, endTime = 0, curTime = 0;
    bool isPaused = false;

    // Sound
    int bgdSoundLevel = 100;
    int effectSoundLevel = 100;

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

    string inputUserTxt(const CGRAPHIC& BgdLayer);
    void saveFileNameList();
    void loadFileNameList();
    void deleteFile(int index);
    void renameFile(int index, const CGRAPHIC& BgdLayer);

    int Menu();
    void NewGame();
    void LoadGame();
    void SaveGame(const CGRAPHIC& BgdLayer);
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

    // Time
    void updateTime();
    string getTime(clock_t curTime);
    clock_t setTime(string& time);

    void startMap();
    void drawMap();

    void intro();
    void outtro();
    void drawCountDown();
    void drawPlayAgain();
    void drawWiningScreen(int COLOR = DARK_GREEN);
    void drawLosingScreen(int COLOR = DARK_GREEN);

    void displayScreen(int fromX = 0, int fromY = 0, int toX = -1, int toY = -1);
    void displayScreen(CGRAPHIC& ObjLayer, const CGRAPHIC& BgdLayer, int fromX = 0, int fromY = 0, int toX = -1, int toY = -1);

    void playEffectSound(string soundName);
    void playBackgroundSound(string soundName);
};
//Return codes
const int QUIT_CODE = -1000;
const int BACK_TO_MENU_CODE = -1001;


const int MAX_INPUT_SIZE = 8;
const int MUSIC = 4, SFX = 4;
//Sounds
const vector<string> Menu_move_sound =  {"", "Menu_Move_25.wav","Menu_Move_50.wav","Menu_Move_75.wav","Menu_Move_100.wav"};
const vector<string> Menu_enter_sound = { "", "Menu_Enter_25.wav","Menu_Enter_50.wav","Menu_Enter_75.wav","Menu_Enter_100.wav" };

//Sounds/Menu
const string MENU_ENTER = "Menu_Enter/Menu_Enter_";
const string MENU_MOVE = "Menu_Move/Menu_Move_";
const string MENU_THEME = "Menu_Theme/Menu_Theme_";
const string MENU_QUIT = "Menu_Quit/Menu_Quit_";
const string MENU_WINING = "Menu_Wining/Menu_Wining_";
const string MENU_LOSING = "Menu_Losing/Menu_Losing_";
//Sounds/Game
const string GAME_EGGCOLLECT = "Game_EggCollect/Game_EggCollect_";
const string GAME_THEME = "Game_Theme/Game_Theme_";
const string GAME_CARHIT = "Game_CarHit/Game_CarHit_";
const string GAME_TRAIN = "Game_Train/Game_Train_";
const string GAME_MOVE = "Game_Move/Game_Move_";
const string GAME_PERRYGROWL = "Game_PerryGrowl/Game_PerryGrowl_";
const string GAME_PAUSE = "Game_Pause/Game_Pause_";
const string GAME_WATERSPLASH = "Game_WaterSplash/Game_WaterSplash_";

const string OFF_SOUND = "OFF_SOUND";


const vector<int> LANE_ID_LIST = { VEHICLELANE_ID, TRAINLANE_ID, RIVERLANE_ID };

string int_to_string(int num);
bool isUpButton(int button);
bool isDownButton(int button);
bool isRightButton(int button);
bool isLeftButton(int button);
bool isEnterButton(int button);
bool isBackspaceButton(int button);

bool isNumber(char ch);
bool isLetter(char ch);
bool isNumberOrLetter(char ch);
bool checkinList(string str, deque<string> strArr);

int getiMatrix(int val, vector<vector<int>>& matrix);
int getjMatrix(int val, vector<vector<int>>& matrix);

void ShowCur(bool CursorVisibility);
void DisableResizeWindow();
void ShowScrollbar(BOOL Show);
