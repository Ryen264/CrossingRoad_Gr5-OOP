#pragma once
#include "CLANE.h"
#include "CCAR.h"
#include "CTRUCK.h"
#include "CBUS.h"
const int TRAFFICLIGHT_DELAY = 20;
const int TRAFFICLIGHT_WAIT = 20;
class CVEHICLELANE : public CLANE {
	int delayTime, condition = 0;
	bool isStop = false;
	const vector <wstring> FRAME =
	{
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"                ",
L"                ",
L"▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀ ",
L"                ",
L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀"
	};
	const vector<int> OBJECT_ID_LIST = {0,0,0,0,0,0,0, CAR_ID, TRUCK_ID, BUS_HEAD_ID, 0, 0, 0, 0, 0, 0, 0, 0};

	//trafic light
	int lightPos, timeLight = 0;
public:
	CVEHICLELANE(int x = 0, int y = 0, int delayTime = 0);
	void pushDeque(int redPoint = -1);
	void pushObj(int x, int ID);
	void Move();
	void lightWork();

	void setStop(bool isStop);
	bool getStop() const;
};