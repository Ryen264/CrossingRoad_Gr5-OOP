#pragma once
#include "CLANE.h"
#include "CPERRY.h"
#include "CCAPYBARA.h"
class CRIVERLANE : public CLANE {
	int condition = 0, countObject = 0;
	int numberOfCapybara = 0;
	const vector <wstring> FRAME =
	{
L"██▄█████▄███▄███",
L"▄█▄▄▄▄▄▄▄▄▄▄▄▄█▄",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"██▄▄▄█▄███▄▄▄█▄█",
L"████████▄▄▄█▄███",
L"██▄▄▄█▄█████████"
	};
	const vector<int> OBJECT_ID_LIST = { PERRY_ID, CAPYBARA_ID,PERRY_ID,PERRY_ID,  0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0};
public:
	CRIVERLANE(int x = 0, int y = 0, int delayTime = 0);
	void push_frontObject(int ID = 0);
	void Move();
	void injuredPlayer(CPLAYER& player);
};