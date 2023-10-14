#pragma once
#include "CVEHICLE.h"
class CCAR : public CVEHICLE {
public:
	void draw(ostream& outDev);
	//void draw(int x, int y, int txtColor, int bgdColor, wchar_t*& pBuffer, WORD*& pColor);
	//void display(int x, int y, wchar_t*& pBuffer, WORD*& pColor);
};
