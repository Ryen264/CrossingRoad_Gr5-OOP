#pragma once
#include "CLANE.h"
#include"CEGG.h"
class CGRASSLANE : public CLANE {
	const vector <wstring> FRAME =
	{
//L"    ▄    ▄▄▄    ",
//L"   ▀▀▀ ▄██  ▄   ",
//L"   ▀█▄ █▀  ▀▀▀  ",
//L"   ▄ ▀▀       █ ",
//L"  ▀▀▀   ▀█▄ ▄█▀ ",
//L"          ▀ ▀   "
 
L"████████████████",
L"████████████████",
L"████████████████",
L"████████████████",
L"████████████████",
L"████████████████",
	};

public:
	CGRASSLANE(int x = 0, int y = 0);
	void injuredPlayer(CPLAYER& player);
};