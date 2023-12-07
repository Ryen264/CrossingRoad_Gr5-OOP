#pragma once
#include "COBJECT.h"
class CCAR : public COBJECT {
	bool isRight;
	const vector <wstring> FRAME_RIGHT =
	{
L"                ",
L"   ▄▄████▄▄▄▄   ",
L"   ██▄▄▄▄████   ",
L"   ██▄▄▄▄█▄▄▄   ",
L"    ▀▀   ▀▀     ",
L"                ",
	};
	const vector<wstring> FRAME_LEFT =
	{
L"                ",
L"   ▄▄▄▄████▄▄   ",
L"   ████▄▄▄▄██   ",
L"   ▄▄▄█▄▄▄▄██   ",
L"     ▀▀   ▀▀    ",
L"                "
	};
public:
	CCAR(int x = 0, int y = 0, bool isRight = true);
	bool getIsRight() const;

	void setIsRight(bool isRight);

};
