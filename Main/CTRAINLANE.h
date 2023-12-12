#pragma once
#include "CLANE.h"
#include "CTRAIN.h"
class CTRAINLANE : public CLANE {
	int timeCount = 0, delayTime = 0;
	int countObject = 0, numberOfConditionObj = 0;

	const vector <wstring> FRAME = {
L"████████████████",
L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"▄█▄█▄█▄▄▄█▄▄▄█▄▄",
L"▀█▀▀▀█▀▀██▀▀▀█▀█",
L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",
	};

public:
	CTRAINLANE(int x = 0, int y = 0, int delayTime = 0, int numberOfConditionObj = 0);
	void pushObject(int ID = 0);
	void push_backObject(int ID = 0);
	void Move();

	int getCountTrain() const;
	int getNumberOfConditionObj() const;
	int getTimeCount() const;
	int getDelayTime() const;

	void setNumberOfConditionObj(int numberOfConditionObj);
	void setCountObject(int countObject);
	void setTimeCount(int timeCount);
	void setDelayTime(int delayTime);

};