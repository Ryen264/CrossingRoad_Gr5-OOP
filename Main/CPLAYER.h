#pragma once
#include "CDINOSAUR.h"
const int UP_LANE = BOARD_HEIGHT - 3;
const int DOWN_LANE = BOARD_HEIGHT - 2;
const int UP = 'W'; const int DOWN = 'S'; const int RIGHT = 'D'; const int LEFT = 'A';

class CPLAYER {
	int x, y, xBoard, yBoard;
	bool alive;
	int score;
	bool isRight = true; bool finish = false;
	int moving;
	int colorCharacter;
	
	COBJECT* dependObj;
	COBJECT* pCharacterR = NULL, * pCharacterL = NULL;
public:
	CPLAYER(int xBoard = 0, int yBoard = 0, int colorCharacter = DARK_GREEN);
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
	int getColorCharacter() const;
	string getNameCharacter() const;

    void set(int xBoard = 0, int yBoard = 0, bool alive = true, bool right = true, int score = -1);
    bool setIsRight();
    void setPos(int xBoard = 0, int yBoard = 0);
    void setxBoard(int xBoard = 0);
    void setyBoard(int yBoard = 0);
    void setFinish(bool finish);
    void setAlive(bool alive);
    void setMove(int moving);
    void setDependObj(COBJECT* obj = NULL);
	void setColorCharacter(int color);

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
