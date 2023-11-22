#pragma once
#include "CLANE.h"
#include "CPERRY.h"
#include "CCAPYBARA.h"
class CRIVERLANE : public CLANE {
	int delayTime;
	bool haveLand;
	const vector <wstring> FRAME_LAND =
	{
L"██▄█████▄███▄███",
L"▄█▄▄▄▄▄▄▄▄▄▄▄▄█▄",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"██▄▄▄█▄███▄▄▄█▄█",
L"████████▄▄▄█▄███",
L"██▄▄▄█▄█████████"
	};
	const vector <wstring> FRAME_NOLAND =
	{
L"██▄█████▄███▄███",
L"█▄▄▄█▄████▄▄▄█▄█",
L"██████▄▄▄█▄█████",
L"██▄▄▄█▄███▄▄▄█▄█",
L"████████▄▄▄█▄███",
L"██▄▄▄█▄█████████"
	};
	const vector<int> OBJECT_ID_LIST = { PERRY_ID, CAPYBARA_ID, 0 };
public:
	CRIVERLANE(int x = 0, int y = 0, int delayTime = 0, bool haveLand = true);
	void pushDeque();
	void Move();
};