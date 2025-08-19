#include "Player.h"
Player::Player() {
	hackingPoints = 0;
	playerVirus = nullptr;
}
Player::~Player() {

}
void setHackingPoints(int hackingPoints) {
	this->hackingPoints = hackingPoints;
}
int getHackingPoints() {
	return hackingPoints;
}
void earnPoints(int points) {
	
}
bool Player::spendPoints(int points) {
	if (points <= hackingPoints) {
		hackingPoints -= points;
	} 
}
void Player::showMenu() {

}
void Player::setInitials()
{
	int temp;

	do {
		std::cout << "Enter your virus (1 - Worm): ";
		std::cin >> temp;
	} while (temp < 1 || temp > 1);
	

}
