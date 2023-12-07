#pragma once
#include "CGRAPHIC.h"
#include "COBJECT.h"
class CFLOPPYDISC: public COBJECT
{
	bool isRight;
	const vector<wstring> FLOPPY_DISC = {
		L"██████████████████████████████████████████████████    ",
		L"██          █                            █        ██  ",
		L"██          █                   █████    █          ██",
		L"██          █                   █████    █          ██",
		L"██          █                   █████    █          ██",
		L"██          █                   █████    █          ██",
		L"██          █                   █████    █          ██",
		L"██          █                   █████    █          ██",
		L"██          █                   █████    █          ██",
		L"██          █                   █████    █          ██",
		L"██                                                  ██",
		L"██      █████                            █████      ██",
		L"██   ███                                      ███   ██",
		L"██   █                                          █   ██",
		L"██   █                                          █   ██",
		L"██   █                                          █   ██",
		L"██   █                                          █   ██",
		L"██   █                                          █   ██",
		L"██   █                                          █   ██",
		L"██   █                                          █   ██",
		L"██   █                                          █   ██",
		L"██   █                                          █   ██",
		L"██   █                      ████       ████     █   ██",
		L"██   █                    ██    ██   ██    ██   █   ██",
		L"██   █                    ██    ██   ██    ██   █   ██",
		L"██   █                      ████       ████     █   ██",
		L"██   █                                          █   ██",
		L"██   █                                          █   ██",
		L"██████████████████████████████████████████████████████"
	};
public:
	int x, y, numberOfBlock = 1, numberOfHeight = 1, numberOfWidth = 1;
	PIXEL block[22][11];
	PIXEL* blocks[22][11];
	CFLOPPYDISC(int x = 0, int y = 0, bool isRight = true);
};

