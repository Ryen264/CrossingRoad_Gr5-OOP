#pragma once
#include "CLANE.h"
#include "CPERRY.h"
#include "CCAPYBARA.h"
class CRIVERLANE : public CLANE {
	int delayTime;
	bool haveLand;
	const vector<wstring> FRAME_LAND =
	{
L"██▄█████▄███▄███",
L"▄█▄▄▄▄▄▄▄▄▄▄▄▄█▄",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"██▄▄▄█▄███▄▄▄█▄█",
L"████████▄▄▄█▄███",
L"██▄▄▄█▄█████████"
	};
	const vector<wstring> FRAME_NOLAND =
	{
L"██▄█████▄███▄███",
L"█▄▄▄█▄████▄▄▄█▄█",
L"██████▄▄▄█▄█████",
L"██▄▄▄█▄███▄▄▄█▄█",
L"████████▄▄▄█▄███",
L"██▄▄▄█▄█████████"
	};
public:
	CRIVERLANE(int x = 0, int y = 0, int delayTime = 0, bool haveLand = true);
	void Move();
	void setStop(bool isStop);
	bool checkPos(int pos);
};