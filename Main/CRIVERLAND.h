#pragma once
#include "COBJECT.h"
class CRIVERLAND : public COBJECT {
	bool isRight;
	const vector<wstring> FRAME_LEFT =
	{
		L"██▄█████▄███▄███",
		L"▄█▄▄▄▄▄▄▄▄▄▄▄▄█▄",
		L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
		L"██▄▄▄█▄███▄▄▄█▄█",
		L"████████▄▄▄█▄███",
		L"██▄▄▄█▄█████████",
	};
	const vector<wstring> FRAME_RIGHT =
	{
		L"██▄█████▄███▄███",
		L"█▄▄▄█▄████▄▄▄█▄█",
		L"██████▄▄▄█▄█████",
		L"██▄▄▄█▄███▄▄▄█▄█",
		L"████████▄▄▄█▄███",
		L"██▄▄▄█▄█████████",
	};
public:
	CRIVERLAND(int x = 0, int y = 0, int isRight = true);
	~CRIVERLAND();
};