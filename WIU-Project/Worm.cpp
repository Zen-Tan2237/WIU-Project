#include "Worm.h"

Worm::Worm() {
	speed = 2; // 1 for slow 5 max
	complexity = 3; // 1 to 10
	payload = 1; // 1 to 10
	resilience = 4; //1 to 10
}

Worm::~Worm() {

}
void Worm::evolve(Upgrades* toUpgrade) {
	std::cout << "Speed to upgrade: " << (toUpgrade->getSpeed() + 0.5f) << std::endl
		<< " Complexity to upgrade: " << toUpgrade->getComplexity() << std::endl
		<< " Payload to upgrade" << toUpgrade->getPayload() << std::endl
		<< " Resilience to upgrade" << toUpgrade->getResilience() << std::endl;

	speed += (toUpgrade->getSpeed() + 0.5f);
	complexity += toUpgrade->getComplexity();
	payload += toUpgrade->getPayload();
	resilience += toUpgrade->getResilience();
}

void Worm::miniGame(int &hackingPoints) {
	srand(static_cast<unsigned int>(time(0)));
	int points = 0;
	for (int i = 0; i < row; i++) {
		board[i] = new char[col];
	}
	std::cout << "Minigame: move the worm deeper into the companies defences using WSD\n";
	makeboard();
	board[wormRow][wormCol] = 'W';
	printboard();
	while (!lose) {
		update();
		if (wormCol % 6 == 2 && wormColPrevious % 6 != 2) {
			points++;
		}
	}
	std::cout << "you crashed. You get " << points << " points";
	hackingPoints += points;
	Sleep(5000);
	for (int i = 0; i < row; i++)
	{
		delete[] board[i];
	}
	delete[] board;
}
void Worm::makeboard() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (j % 6 == 2) {
				board[i][j] = '#';
			}
			else {
				board[i][j] = ' ';
			}
		}
	}
	for (int j = 0; j < col; j++) {
		if (j % 6 == 2) {
			board[rand() % 10][j] = ' ';
		}
	}
}

void Worm::printboard() {
	std::cout << "======================================================================"
		"===========================================================================\n";
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
		{
			std::cout << '|' << board[i][j];
		}
		std::cout << '|' << std::endl;
	}
	std::cout << "======================================================================"
		"===========================================================================\n";
}

void Worm::update() {
	wormRowPrevious = wormRow;
	wormColPrevious = wormCol;
	getInput();
	board[wormRow][wormCol] = 'W';
	board[wormRowPrevious][wormColPrevious] = ' ';
	Sleep(500);
	system("cls");
	printboard();
}

void Worm::getInput() {
	std::cout << "enter a direction:\n";
	if (_kbhit()) {
		char input = _getch();
		switch (input) {
		case 'w':
		case 'W':
			dir = 'w';
			break;
		case 's':
		case 'S':
			dir = 's';
			break;
		case 'd':
		case 'D':
			dir = 'd';
			break;
		default:
			std::cout << "invalid input\n";
			break;
		}
	}
	switch (dir) {
	case 'w':
		if (wormRow != 0) {
			if (board[wormRow - 1][wormCol] == ' ') {
				wormRow--;
			}
			else {
				lose = true;
			}
		}
		else {
			lose = true;
		}
		break;
	case 's':
		if (wormRow < row - 1) {
			if (board[wormRow + 1][wormCol] == ' ') {
				wormRow++;
			}
			else {
				lose = true;
			}
		}
		else {
			lose = true;
		}
		break;
	case 'd':
		if (wormCol < col - 1) {
			if (board[wormRow][wormCol + 1] == ' ') {
				wormCol++;
			}
			else {
				lose = true;
			}
		}
		else {
			lose = true;
		}
		break;
	default:
		std::cout << "halalalal\n"; //halal indeed. #include <quran.h>, inshallah.
		break;
	}
}

const std::string* Worm::getNameUpgrade() const{
	return nameUpgrade;
}

const float* Worm::getStatsUpgrades() const{
	return statsUpgrade;
}

const int* Worm::getDependentIndices() const{
	return dependentIndices;
}

const int Worm::getNumUpgrades() const{
	return NUM_UPGRADES;
}