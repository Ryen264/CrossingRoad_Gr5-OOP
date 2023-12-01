#pragma once
#include "CLANE.h"
#include "CEGG.h"
#include "CTREE.h"
const int MAX_NUMBER_OF_TREE = 3;
const vector<int> FULL_TREE_TYPELANE = { TREE_ID, TREE_ID, TREE_ID, TREE_ID, TREE_ID, TREE_ID, TREE_ID, TREE_ID, TREE_ID, TREE_ID, TREE_ID, TREE_ID, TREE_ID };
const vector<int> SURROUND_TREE_TYPELANE = { TREE_ID, TREE_ID, 0, TREE_ID, 0, 0, 0, 0, 0, TREE_ID, 0, TREE_ID, TREE_ID };
const vector<int> AROUND_TREE_TYPELANE = { TREE_ID, 0, TREE_ID, 0, 0, 0, 0, 0, 0, 0, TREE_ID, 0, TREE_ID };

class CGRASSLANE : public CLANE {
	const vector <wstring> FRAME =
	{
L"                ",
L"                ",
L"        ▄▀       ",
L"     ▀▄ ▀        ",
L"                ",
L"                "
//L"████████████████",
//L"████████████████",
//L"████████████████",
//L"████████████████",
//L"████████████████",
//L"████████████████"
	};
	const vector<int> OBJECT_ID_LIST = { EGG_ID,TREE_ID,0,0,0,0,0,0,0 };
public:
	CGRASSLANE(int x = 0, int y = 0, vector<int> typeLane = {});
    void injuredPlayer(CPLAYER& player);
	void push_frontObject(int ID = 0);
};