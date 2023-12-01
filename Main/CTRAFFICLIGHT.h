#pragma once
#include "COBJECT.h"
const int RED_TRAFFICLIGHT = 0;
const int YELLOW_TRAFFICLIGHT = 1;
const int GREEN_TRAFFICLIGHT = 2;
class CTRAFFICLIGHT : public COBJECT {
	bool isRight;
	int lightColor = GREEN_TRAFFICLIGHT;
	const vector <wstring> FRAME =
	{
L"                ",
L"            █▀█ ",
L"            █▀█ ",
L"            █▀█ ",
L"            ▀█▀ ",
L"             █  "
	};
public:
	CTRAFFICLIGHT(int x = 0, int y = 0);
	void setLightColor(int lightColor = GREEN_TRAFFICLIGHT);
	PIXEL** getBlock() const;
};
