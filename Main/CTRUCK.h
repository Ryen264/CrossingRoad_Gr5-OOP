﻿#pragma once
#include "COBJECT.h"
class CTRUCK : public COBJECT {
	bool isRight;
	const vector <wstring> FRAME_RIGHT =
	{
L"                ",
L" ▄▄▄▄▄▄▄███▄▄▄▄ ",
L" █▄▄▄▄▄█▄▄▄████ ",
L" █▄▄▄▄▄█▄▄▄█▄▄▄ ",
L"   ▀▀      ▀▀   ",
L"                "
	};
	const vector<wstring> FRAME_LEFT =
	{
L"                ",
L" ▄▄▄▄███▄▄▄▄▄▄▄ ",
L" ████▄▄▄█▄▄▄▄▄█ ",
L" ▄▄▄█▄▄▄█▄▄▄▄▄█ ",
L"   ▀▀      ▀▀   ",
L"                "
	};
public:
	CTRUCK(int x = 0, int y = 0, bool isRight = true);
	bool getIsRight() const;

	void setIsRight(bool isRight);

};
