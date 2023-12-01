#pragma once
#include "CLANE.h"
#include "CTRAIN.h"
class CTRAINLANE : public CLANE {
	int delayTime, numberOfTrain, countTrain = 0;
	bool isStop = true;
    const vector <wstring> FRAME = {
L"████████████████",
L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"▄█▄█▄█▄▄▄█▄▄▄█▄▄",
L"▀█▀▀▀█▀▀██▀▀▀█▀█",
L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",
    };

public:
	CTRAINLANE(int x = 0, int y = 0, int delayTime = 0, int numberOfTrain = 0);
	void push_frontObject(int ID = 0);
	void Move();

	void setStop(bool isStop);
	bool getStop() const;
};