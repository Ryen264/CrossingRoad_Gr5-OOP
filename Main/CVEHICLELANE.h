#pragma once
#include "CLANE.h"
#include "CCAR.h"
#include "CTRUCK.h"
class CVEHICLELANE : public CLANE {
	int delayTime;
	bool isStop = false;
	const vector <wstring> FRAME = {
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"                ",
L"                ",
L"▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀ ",
L"                ",
L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",
	};
public:
	CVEHICLELANE(int x = 0, int y = 0, int delayTime = 0);
	void Move();
	void pushObj(int x, int ID);

	void setIsMoveRight(bool isMoveRight);
	void setStop(bool isStop);

	bool getIsMoveRight();
	int getDelayTime();
	int getTimeCount();
	bool getIsStop();
};