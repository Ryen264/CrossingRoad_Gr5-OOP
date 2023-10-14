#include "CGAME.h"
#include <Windows.h>

void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}
int main()
{
	ShowCur(false);
    CGAME CrossingGame;
    CrossingGame.start();
    cout << "Game Over!" << endl;
	ShowCur(true);
}
APPCOMMAND_HELP
//Endur was here
// hi

