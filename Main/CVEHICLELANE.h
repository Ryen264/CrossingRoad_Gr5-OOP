#pragma once
#include "CLANE.h"
#include "CCAR.h"
#include "CTRUCK.h"
class CVEHICLELANE : public CLANE {
	int delayTime;
	const vector <wstring> FRAME = {
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"                ",
L"                ",
L"▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀ ",
L"                ",
L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",
	};
public:
	CVEHICLELANE(int x = 0, int y = 0, int delayTime = 0);
	void Move();
	void setStop(bool isStop);
};