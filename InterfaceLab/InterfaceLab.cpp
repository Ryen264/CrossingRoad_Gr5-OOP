#include "CGRAPHIC.h"
#include "CLANE.h"
#include "COBJECT.h"
#include <conio.h>
int main() {
	SetupTheme();
	CGRAPHIC BgdLayer;
	BgdLayer.clear(BLACK, WHITE);
	BgdLayer.display();
	//CLANE testlane1(0, 0), testlane2(0, BLOCK_HEIGHT);
	////draw background
	//testlane1.DrawBlock(BgdLayer);
	//testlane2.DrawBlock(BgdLayer);
	BgdLayer.display();

	CGRAPHIC ObjLayer = BgdLayer;
	COBJECT testobject;
	//draw object
	//ObjLayer.drawClipBoard(0,0,46,20);
	testobject.DrawBlock(ObjLayer);
	//ObjLayer.drawTag(0, 0, RED);
	ObjLayer.display();
	_getch();
	return 0;
}