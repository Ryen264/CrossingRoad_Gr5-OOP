#pragma once
#include "CDINOSAUR.h"
#include "COBJECT.h"
#include <iostream>
const int UP_LANE = BOARD_HEIGHT - 3;
const int DOWN_LANE = BOARD_HEIGHT - 2;
const int UP = 'W'; const int DOWN = 'S'; const int RIGHT = 'D'; const int LEFT = 'A';

const vector<int> GREEN_CHARACTER = { DARK_GREEN, LIGHT_GREEN };
const vector<int> RED_CHARACTER = { DARK_RED, RED };
const vector<int> BLUE_CHARACTER = { BLUE, SKY_BLUE };
const vector<int> GRAY_CHARACTER = { DARK_GRAY, LIGHT_GRAY };
const vector<int> BROWN_CHARACTER = { SADDLE_BROWN, LIGHT_BROWN };
const vector<int> YELLOW_CHARACTER = { BRIGHT_YELLOW, WHITE };
const vector<int> SAND_CHARACTER = { SAND, BRIGHT_YELLOW };

using namespace std;
class CPLAYER {
	int x, y, xBoard, yBoard;
	bool alive;
	int score;
	bool isRight = true; bool finish = false;
	int moving;
	vector<int> color;
	
	COBJECT* dependObj;
	COBJECT* pCharacterR = NULL, * pCharacterL = NULL;
public:
	CPLAYER(int xBoard = 0, int yBoard = 0, vector<int> color = GREEN_CHARACTER);
	~CPLAYER();

	int getX() const;
	int getY() const;
    int getXBoard() const;
    int getYBoard() const;
	int getScore() const;
	bool getIsRight() const;
	bool getIsAlive() const;
    COBJECT* getDependObj() const;
    int getMoving() const;
	vector<int> getColorCharacter() const;


    void set(int xBoard = 0, int yBoard = 0, bool alive = true, bool right = true, int score = -1);
    bool setIsRight();
    void setPos(int xBoard = 0, int yBoard = 0);
    void setxBoard(int xBoard = 0);
    void setyBoard(int yBoard = 0);
    void setFinish(bool finish);
    void setAlive(bool alive);
    void setMove(int moving);
    void setDependObj(COBJECT* obj = NULL);
	void setColorCharacter(vector<int> color);

    //is deleting depend obj
    int updateDepend();

	//return: is push new lane
	bool moveCharacter();
	void increaseScore(int point = 1);
	void decreaseScore(int point = 1);
	bool isFinish() const;
	bool isDead() const;
	bool isMoving() const;
	void drawCharacter(CGRAPHIC& layer);
	void displayCharacter(CGRAPHIC& layer);
};
