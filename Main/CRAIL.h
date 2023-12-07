#pragma once
#include "CGRAPHIC.h"

class CRAIL
{
	const vector <wstring> FRAME = {
L"████████████████",
L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"▄█▄█▄█▄▄▄█▄▄▄█▄▄",
L"▀█▀▀▀█▀▀██▀▀▀█▀█",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
	};

public:
	int x, y, numberOfBlock = 1, numberOfHeight = 1, numberOfWidth = 1;
	PIXEL** block;
	CRAIL(int x = 0, int y = 0);
	~CRAIL();
};

