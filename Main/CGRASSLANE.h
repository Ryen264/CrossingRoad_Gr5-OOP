#pragma once
#include "CLANE.h"
#include "CEGG.h"
#include "CTREE.h"
const int MAX_NUMBER_OF_TREE = 3;
class CGRASSLANE : public CLANE {
	const vector <wstring> FRAME =
	{
L"         ▄▄▄    ",
L"       ▄██      ",
L"   ▀█▄ █▀       ",
L"     ▀▀       █ ",
L"        ▀█▄ ▄█▀ ",
L"          ▀ ▀   "
 
//L"████████████████",
//L"████████████████",
//L"████████████████",
//L"████████████████",
//L"████████████████",
//L"████████████████"
	};
	const vector<int> OBJECT_ID_LIST = { EGG_ID,TREE_ID,0,0,0,0,0,0,0 };
public:
	CGRASSLANE(int x = 0, int y = 0);
    void injuredPlayer(CPLAYER& player);
};