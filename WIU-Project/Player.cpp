#include "Player.h"
Player::Player() {
	hackingPoints = 0;
	playerVirus = nullptr;
}
Player::~Player() {

}

void Player:: setHackingPoints(int hackingPoints) {
	this->hackingPoints = hackingPoints;
}

int Player :: getHackingPoints()const {
	return hackingPoints;
}

Virus* Player::getPlayerVirus() const {
	return playerVirus;
}

void Player :: earnPoints(int points) {
	hackingPoints += points;
}
bool Player::spendPoints(int points) {
	if (points <= hackingPoints) {
		hackingPoints -= points;
	} 
}

void Player::showMenu() {

}
void Player::setInitials(Company companyList[])
{
	int type;
	int companyChoice;
	do {
		std::cout << "Enter your virus (1 - Worm): ";
		std::cin >> type;
	} while (type < 1 || type > 1);
	do {
		std::cout << "Enter the company you want to start at: ";
		for (int i = 0; i < 50; i++) {
			std::cout << i + 1 << "." << companyList[i].getName() << std::endl;
		}
		std::cin >> companyChoice;
	} while (companyChoice < 1 || companyChoice > 50);

}
