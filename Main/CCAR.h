#pragma once
#include "CVEHICLE.h"
class CCAR : public CVEHICLE {
    int x, y;
    bool isRight;
    PIXEL block[16][16];
    const vector<wstring> FRAME_RIGHT = {
L"                ",
L"   ▄▄████▄▄▄▄   ",
L"   ██▄▄▄▄████   ",
L"   ██▄▄▄▄█▄▄▄   ",
L"    ▀▀   ▀▀     ",
L"                " };
    const vector<wstring> FRAME_LEFT = {
L"                ",
L"   ▄▄████▄▄▄▄   ",
L"   ██▄▄▄▄████   ",
L"   ██▄▄▄▄█▄▄▄   ",
L"    ▀▀   ▀▀     ",
L"                " };
public:
    CCAR(int x = 0, int y = 0, int isRight = true);
};
