#pragma once
#include "COBJECT.h"
class CTRAFFICLIGHT : public COBJECT {
	bool isRight;
	int lightColor = 0; //0: red, 1: yellow, 2: green
	const vector <wstring> FRAME =
	{
L"                ",
L"            █▀█ ",
L"            █▀█ ",
L"            █▀█ ",
L"            ▀█▀ ",
L"             █ "
	};
public:
	CTRAFFICLIGHT(int x = 0, int y = 0);
	void setLightColor(int lightColor);
};
