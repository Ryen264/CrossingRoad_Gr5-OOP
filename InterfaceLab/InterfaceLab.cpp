#include "CGRAPHIC.h"
#include "CLANE.h"
#include "COBJECT.h"
#include <conio.h>

const int BOARD_HEIGHT = 10;
const int BOARD_WIDTH = 20;

int main() {
	SetupTheme();
	CGRAPHIC BgdLayer;
	BgdLayer.clear(BLACK, WHITE);

	CLANE testlane1(0, 0), testlane2(BLOCK_WIDTH, 0), testlane3(BLOCK_WIDTH, BLOCK_HEIGHT), testlane4(0, BLOCK_HEIGHT);
	//draw background
	//testlane1.DrawBlock(BgdLayer); testlane2.DrawBlock(BgdLayer); testlane3.DrawBlock(BgdLayer); testlane4.DrawBlock(BgdLayer);
	BgdLayer.display();


	CGRAPHIC ObjLayer;
	ObjLayer.clear(BLACK, -1);

	COBJECT testobject;
	//draw object
	testobject.DrawBlock(ObjLayer);
	ObjLayer.display();
	_getch();
	return 0;
}