#pragma once
#include "CLANE.h"
#include "CVEHICLE.h"
#include "CCAR.h"
class CVEHICLELANE : public CLANE {
public:
	CVEHICLELANE(int width);
	~CVEHICLELANE();
	void Move();
	bool checkPos(int pos);
	void draw(ostream& outDev);
};