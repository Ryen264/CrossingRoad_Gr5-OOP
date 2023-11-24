#pragma once
#include "CLANE.h"
#include "CTRAIN.h"
const int TRAIN_BEFORE = 5;
class CTRAINLANE : public CLANE {
	int delayTime, timeTrain = 0, trainDelay, trainWait;
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
	CTRAINLANE(int x = 0, int y = 0, int delayTime = 0, int trainDelay = 0, int trainWait = 0);
	void fillDeque(int ID = 0);
	void Move();

	void setStop(bool isStop);
	bool getStop() const;
};