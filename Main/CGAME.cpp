#include "CGAME.h"
CGAME::CGAME(int numberOfLanes) {
	srand(time(0));
	this->isRunning = true;
	this->numberOfLanes = numberOfLanes;
	for (int i = 0; i < numberOfLanes; i++) {
		switch (rand() % TYPELANENUM) {
		case 0: {
			this->aLanes.push_back(new CVEHICLELANE(WIDTH));
			break;
		}
		}
	}
}
CGAME::~CGAME() {
	for (int i = 0; i < this->numberOfLanes; i++) {
		CLANE* pointer = this->aLanes.back();
		this->aLanes.pop_back();
		delete pointer;
	}
}
void CGAME::finishTell(ostream& outDev) {
	outDev << "\x07"; //Bell~
}
void CGAME::draw(ostream& outDev) {
	system("cls");
	//for (int i = 0; i < this->numberOfLanes; i++) {
	//	//no car in the first and the last lines
	//	this->aLanes[i]->draw(outDev);
	//	for (int j = 0; j < WIDTH; j++) {
	//		if (this->cPlayer.getX() == j && this->cPlayer.getY() == i)
	//			this->cPlayer.draw(outDev);
	//	}
	//}
	for (int i = 0; i < this->numberOfLanes; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (i == 0 && (j == 0 || j == WIDTH - 1))
				cout << "S";
			if (i == this->numberOfLanes - 1 && (j == 0 || j == WIDTH - 1))
				cout << "F";
			if (this->aLanes[i]->checkPos(j) && i != 0 && i != this->numberOfLanes - 1)    //no car in the first and the last lines
				cout << "#";
			else if (this->cPlayer.getX() == j && this->cPlayer.getY() == i)
				cout << "V";
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << "Score: " << this->cPlayer.getScore() << endl;
}
void CGAME::input() {
	if (_kbhit()) {
		switch (toupper(_getch())) {
		case 'W': {
			this->cPlayer.Up();
			break;
		}
		case 'S': {
			this->cPlayer.Down();
			break;
		}
		case 'A': {
			this->cPlayer.Left();
			break;
		}
		case 'D': {
			this->cPlayer.Right();
			break;
		}
		case 'Q': {
			this->isRunning = false;
			break;
		}
		}
	}
}
void CGAME::logic() {
	//ignore the first and the last lanes
	for (int i = 1; i < this->numberOfLanes - 1; i++) {
		//Random move a lane
		if (rand() % 10 == 1)
			this->aLanes[i]->Move();
		//Quit if player has an accident
		if (this->aLanes[i]->checkPos(this->cPlayer.getX()) && this->cPlayer.getY() == i)
			this->isRunning = false;
	}
	//Player qua được màn
	if (this->cPlayer.isFinish(FINISH_HEIGHT)) {
		//Tăng điểm và reset màn
		this->cPlayer.increaseScore();
		this->cPlayer.setXY(-1, START_HEIGHT);
		this->finishTell(cout);
		//Change direction of a line
		this->aLanes[rand() % this->numberOfLanes]->changeDirection();
	}
}
void CGAME::start() {
	while (this->isRunning) {
		this->input();
		this->draw(cout);
		this->logic();
	}
}
