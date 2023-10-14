#pragma once
#include <iostream>
using namespace std;
class CPLAYER {
	int x, y;
	bool alive;
	int score;
public:
	CPLAYER(int firstX = 20 / 2, int firstY = 0);
	int getX();
	int getY();
	int getScore();
	void setXY(int x = -1, int y = -1);
	void decreaseScore(int point = 1);
	void increaseScore(int point = 1);
	void Up(int step = 1);
	void Down(int step = 1);
	void Left(int step = 1);
	void Right(int step = 1);
	bool isFinish(int finishHeight);
	bool isDead();
	void draw(ostream& outDev);
};

