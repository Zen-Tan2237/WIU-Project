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
		std::cout << "Enter the company you want to start at: " << std::endl;
		for (int i = 0; i < maxCompany; i++) {
			std::cout << i + 1 << "." << companyList[i]->getName() << std::endl;
		}
		std::cin >> companyChoice;
	} while (companyChoice < 1 || companyChoice > maxCompany);

	companyList[companyChoice - 1]->setNoOfInfectedComputers(1);

	parseUpgrades();
}

//**************241199A**************
// Written by Zen
// Name: parseUpgrades
// Description: Parses the array of data in player.h
// 
//**************241199A**************
void Player::parseUpgrades() {
	int parserIndex1 = 0;
	int parserIndex2 = 0;
	for (int i = 0; i < NUM_UPGRADES; i++) {
		upgradesArray[i] = new Upgrades(nameUpgrade[parserIndex1], 
				nameUpgrade[parserIndex1 + 1], 
				statsUpgrade[parserIndex2], 
				statsUpgrade[parserIndex2 + 1], 
				statsUpgrade[parserIndex2 + 2], 
				statsUpgrade[parserIndex2 + 3]
		);
		parserIndex1 += 2;
		parserIndex2 += 4;
	}
}
void Player::update(){
	std::string upgrade;
	std::cout << "Enter to continue, U to open Upgrade Menu";
	do {
		getline(std::cin, upgrade);
	} while (!(upgrade == "" || upgrade == "U"));
}

