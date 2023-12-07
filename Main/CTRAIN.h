#pragma once
#include "COBJECT.h"
class CTRAIN : public COBJECT {
	bool isRight, isHead;
	const vector <wstring> FRAME_HEAD_RIGHT =
	{
L"▀▀▀▀▀▀▀▀▀▄▄▄    ",
L"▄▄▄▄▄▄▄▄▄▄ ███▄ ",
L"  █▄▄█▄▄█▄▀▄███ ",
L"▄▄███████████▄▄ ",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▀▀ ",
L"▀▀▀▀▀▀▀▀▀▀▀▀▀   ",
	};
	const vector <wstring> FRAME_BODY_RIGHT =
	{
L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L" █▄▄ █▄▄  ▄ █▄▄ ",
L"▄▄▄▄▄▄▄▄▄ █▄▄▄▄▄",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
	};
	const vector <wstring> FRAME_HEAD_LEFT =
	{
L"    ▄▄▄▀▀▀▀▀▀▀▀▀",
L" ▄███ ▄▄▄▄▄▄▄▄▄▄",
L" ███▄▀▄█▄▄█▄▄█  ",
L" ▄▄███████████▄▄",
L" ▀▀▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"   ▀▀▀▀▀▀▀▀▀▀▀▀▀",
	};
	const vector <wstring> FRAME_BODY_LEFT =
	{
L"▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L" ▄▄█ ▄  ▄▄█ ▄▄█ ",
L"▄▄▄▄▄██▄▄▄▄▄▄▄▄▄",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
L"▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄",
	};
public:
	CTRAIN(int x = 0, int y = 0, bool isRight = true, bool isHead = true);
	bool getIsRight() const;
	bool getIsHead() const;

	void setIsRight(bool isRight);
	void setIsHead(bool isHead);
};
