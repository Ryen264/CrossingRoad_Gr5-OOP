#pragma once
#include "CGRAPHIC.h"
#include "COBJECT.h"
class CLANE {
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
	//const vector<int> OBJECT_ID_LIST = { PERRY_ID, CAPYBARA_ID };
protected:
	int x, y, numberOfBlock = 1, numberOfHeight = 1, numberOfWidth = 1;
	PIXEL** block;
public:
	CLANE(int x = 0, int y = 0, int delayTime = 0, bool haveLand = true);
	~CLANE();
	void DrawBlock(CGRAPHIC& layer);
};