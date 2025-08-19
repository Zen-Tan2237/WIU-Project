#include "Player.h"
#include "Worm.h"

Player::Player() {
	hackingPoints = 0;
	companyChoice = 0;
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

int Player::getCompanyChoice() const
{
	return companyChoice;
}

void Player::setCompanyChoice(int choice)
{
	this->companyChoice = choice;
}

void Player::setMaxCompany(int maxCompany)
{
	this->maxCompany = maxCompany;
}

Virus* Player::getPlayerVirus() const {
	return playerVirus;
}


void Player :: earnPoints(int points) {
	hackingPoints += points;
}
void Player::spendPoints(int cost) {
	if (cost <= hackingPoints) {
		hackingPoints -= cost;
	} 

}

void Player::setInitials(Company* companyList[])
{
	int type;
	do {
		std::cout << "Enter your virus (1 - Worm): ";
		std::cin >> type;
	} while (type < 1 || type > 1);

	if (type == 1) {
		playerVirus = new Worm;
	}


	do {
		std::cout << "Enter the company you want to start at: ";
		for (int i = 0; i < maxCompany; i++) {
			std::cout << i + 1 << "." << companyList[i]->getName() << std::endl;
		}
		std::cin >> companyChoice;
	} while (companyChoice < 1 || companyChoice > maxCompany);

	

}
void Player::update(){
	int upgrade;
	std::cout << "Do you want to spend points upgrading? (1 - Yes, 0 - skip to next day): ";
	std::cin >> upgrade;

	if (upgrade == 1) {
	}
}

