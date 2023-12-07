#pragma once
#include "CDINOSAUR.h"
const int UP_LANE = BOARD_HEIGHT - 3;
const int DOWN_LANE = BOARD_HEIGHT - 2;
const int UP = 'W'; const int DOWN = 'S'; const int RIGHT = 'D'; const int LEFT = 'A';

class CPLAYER {
	int x, y, xBoard, yBoard;
	bool alive;
	int score;
	bool isRight = true;
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
	int getColorCharacter() const;
	string getNameCharacter() const;
	bool getIsRight() const;
	bool getAlive() const;
	int getScore() const;
	int getMoving() const;
	COBJECT* getDependObj() const;

	void set(int xBoard = 0, int yBoard = 0, bool alive = true, bool right = true, int score = -1);
	void setPos(int xBoard = 0, int yBoard = 0);
	void setXBoard(int xBoard = 0);
	void setYBoard(int yBoard = 0);
	void setColorCharacter(int colorCharacter);
	void setIsRight(bool isRight);
	void setAlive(bool alive);
	void setScore(int score);
	void setMoving(int moving);
	void setDependObj(COBJECT* dependObj = NULL);

	//is deleting depend obj
	int updateDepend();

	//return: is push new lane
	bool moveCharacter();
	void increaseScore(int point = 1);
	void decreaseScore(int point = 1);
	bool isDead() const;
	bool isMoving() const;
	void drawCharacter(CGRAPHIC& layer);
	void displayCharacter(CGRAPHIC& layer);
};
