#include "CGRAPHIC.h"
#include "CLANE.h"
#include "COBJECT.h"
#include <conio.h>
int main() {
	SetupTheme();
	CGRAPHIC BgdLayer;
	BgdLayer.clear(BLACK, BLUE);

	//CLANE testlane1(0, 0), testlane2(0, BLOCK_HEIGHT);
	////draw background
	//testlane1.DrawBlock(BgdLayer);
	//testlane2.DrawBlock(BgdLayer);
	//BgdLayer.display();


	CGRAPHIC ObjLayer;
	ObjLayer.clear(-1, -1);

	COBJECT testobject(0, 0, true);
	//draw object
	testobject.DrawBlock(ObjLayer);
	ObjLayer.display();
	_getch();
	return 0;
}