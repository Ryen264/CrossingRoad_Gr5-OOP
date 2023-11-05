#pragma once
#include "CDINOSAUR.h"
#include <iostream>
using namespace std;
class CPLAYER {
	int x, y;
	bool alive;
	int score;
	bool isRight = true; bool finish = false;
	int moving = 0;
	const int UP = 'W'; const int DOWN = 'S'; const int RIGHT = 'D'; const int LEFT = 'A';
public:
	CPLAYER(int firstX = 0, int firstY = 0);
	~CPLAYER();
	int getX();
	int getY();
	int getScore();
	void set(int x = -1, int y = -1, bool alive = true, int score = -1);
	bool setIsRight();
	void setFinish(bool finish);
	void setAlive(bool alive);
	void setMove(int moving);
	void moveCharacter();
	void increaseScore(int point = 1);
	void decreaseScore(int point = 1);
	bool isFinish();
	bool isDead();
	void drawCharacter(CGRAPHIC& layer);
	void eraseCharacter(CGRAPHIC& layer);
};
