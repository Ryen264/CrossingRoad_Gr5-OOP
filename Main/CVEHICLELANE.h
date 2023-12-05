#pragma once
#include "CLANE.h"
#include "CCAR.h"
#include "CTRUCK.h"
#include "CBUS.h"
#include "CTRAFFICLIGHT.h"
const int TRAFFICLIGHT_DELAY = 20;
const int TRAFFICLIGHT_WAIT = 20;
class CVEHICLELANE : public CLANE {
	int condition = 0, countObject = 0, numberOfConditionalObject;
	const vector <wstring> FRAME =
	{
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"                ",
L"                ",
L"▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀ ",
L"                ",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄"
	};
	const vector <wstring> FRAME_MARKING =
	{
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"        ▄▄▄     ",
L"        ▄▄▄     ",
L"▀▀▀ ▀▀▀ ▄▄▄ ▀▀▀ ",
L"        ▄▄▄     ",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
	};
	const vector<int> OBJECT_ID_LIST = { CAR_ID, TRUCK_ID, BUS_HEAD_ID, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	//trafic light
	int lightPos, timeLight = 0;
	CTRAFFICLIGHT* ptrafficLight = NULL;
public:
	CVEHICLELANE(int x = 0, int y = 0, int delayTime = 0);
	~CVEHICLELANE();
	void push_frontObject(int ID = 0);
	void pushNormally();
	void lightWork();
	void Move();

	void setyBoard(int yBoard);
	void updateYObj();
	void setStop(bool isStop);
	bool getStop() const;

	void DrawObjects(CGRAPHIC& layer);
	void DrawLane(CGRAPHIC& layer);
};