#pragma once
#include "CLANE.h"
#include "CPERRY.h"
#include "CCAPYBARA.h"
class CRIVERLANE : public CLANE {
	int timeCount = 0, delayTime = 0;
	int condition = 0, countObject = 0, numberOfConditionObj = 0;

	const vector <wstring> FRAME =
	{
L"██▄█████▄███▄███",
L"▄█▄▄▄▄▄▄▄▄▄▄▄▄█▄",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"██▄▄▄█▄███▄▄▄█▄█",
L"████████▄▄▄█▄███",
L"██▄▄▄█▄█████████"
	};
	const vector<int> OBJECT_ID_LIST = { PERRY_ID, CAPYBARA_ID,PERRY_ID,PERRY_ID,  0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0 };
public:
	CRIVERLANE(int x = 0, int y = 0, int delayTime = 0);
	void pushObject(int ID = 0);
	void push_backObject(int ID = 0);
	void Move();
	void injuredPlayer(CPLAYER& player);

	int getCondition() const;
	int getCountObject() const;
	int getNumberOfConditionObj() const;
	int getTimeCount() const;
	int getDelayTime() const;

	void setCondition(int condition);
	void setCountObject(int countObject);
	void setNumberOfConditionObj(int numberOfConditionObj);
	void setTimeCount(int timeCount);
	void setDelayTime(int delayTime);

};
static bool checkinList(int val, vector<int> list);