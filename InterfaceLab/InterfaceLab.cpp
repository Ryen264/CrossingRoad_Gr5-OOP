#include "CGRAPHIC.h"
#include "CLANE.h"
#include "COBJECT.h"
#include <conio.h>
#include"CDINOSAUR.h"

const int BOARD_HEIGHT = 10;
const int BOARD_WIDTH = 20;

int main() {
	CGRAPHIC BgdLayer, ObjLayer;
	BgdLayer.clear(BLACK, WHITE);
	ObjLayer.clear(BLACK, -1);
	SetupTheme();

	CLANE testlane(BOARD_WIDTH);
	CDINOSAUR testobject(BOARD_WIDTH);

	testlane.DrawBlock(BgdLayer);
	testlane.DrawBlock(ObjLayer);

    testobject.DrawDinosaur(BgdLayer);
	testobject.DrawDinosaur(ObjLayer);

	BgdLayer.display();
	ObjLayer.display();
	_getch();
	return 0;
}