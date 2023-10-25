#include "CGRAPHIC.h"
#include "CLANE.h"
#include "COBJECT.h"
#include <conio.h>

int main() {
	CGRAPHIC BgdLayer, ObjLayer;
	BgdLayer.clear(BLACK, WHITE);
	ObjLayer.clear(BLACK, -1);
	SetupTheme();

	CLANE testlane(WIDTH);
	COBJECT testobject;
	testlane.DrawBlock(BgdLayer);
	testobject.DrawBlock(ObjLayer);

	BgdLayer.display();
	ObjLayer.display();
	_getch();
	return 0;
}