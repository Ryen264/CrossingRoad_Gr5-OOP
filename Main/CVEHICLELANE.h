#pragma once
#include "CLANE.h"
#include "CCAR.h"
#include "CTRUCK.h"
#include "CBUS.h"
#include "CTRAFFICLIGHT.h"
const int TRAFFICLIGHT_DELAY = 20;
const int TRAFFICLIGHT_WAIT = 20;
class CVEHICLELANE : public CLANE {
	int timeCount = 0, delayTime = 0;
	bool isStop = false;
	int condition = 0, countObject = 0, numberOfConditionObj = 0;
	int lightPos, timeLight = 0;
	CTRAFFICLIGHT* ptrafficLight = NULL;

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
	const vector<int> OBJECT_ID_LIST = { CAR_ID, TRUCK_ID, BUS_HEAD_ID, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
public:
	CVEHICLELANE(int x = 0, int y = 0, int delayTime = 0);
	~CVEHICLELANE();
	void push_frontObject(int ID = 0);
	void push_backObject(int ID = 0);
	void pushNormally();
	void lightWork();
	void Move();

	void setyBoard(int yBoard);
	void updateYObj();

	int getCondition() const;
	int getCountObject() const;
	int getNumberOfConditionObj() const;
	int getLightPos() const;
	int getTimeLight() const;
	bool getIsStop() const;
	int getTimeCount() const;
	int getDelayTime() const;

	void setCondition(int condition);
	void setCountObject(int countObject);
	void setNumberOfConditionObj(int numberOfConditionObj);
	void setLightPos(int lightPos);
	void setTimeLight(int timeLight);
	void setIsStop(bool isStop);
	void setTimeCount(int timeCount);
	void setDelayTime(int delayTime);

	void DrawObjects(CGRAPHIC& layer);
	void DrawLane(CGRAPHIC& layer);
};
static bool checkinList(int val, vector<int> list);