#include "Player.h"
#include "Worm.h"

Player::Player() {
	for (int i = 0; i < NUM_UPGRADES; i++) {
		upgradesArray[i] = nullptr;
	}
	hackingPoints = 0;
	companyChoice = 0;
	playerVirus = nullptr;
}
Player::~Player() {
	for (int i = 0; i < NUM_UPGRADES; i++) {
		delete upgradesArray[i];
		upgradesArray[i] = nullptr;
	}
	delete playerVirus;
	playerVirus = nullptr;
}

void Player::setHackingPoints(int hackingPoints) {
	this->hackingPoints = hackingPoints;
}

int Player::getHackingPoints() const {
	return hackingPoints;
}

int Player::getCompanyChoice() const {
	return companyChoice;
}

void Player::setCompanyChoice(int choice){
	this->companyChoice = choice;
}

void Player::setMaxCompany(int maxCompany){
	this->maxCompany = maxCompany;
}

Virus* Player::getPlayerVirus() const {
	return playerVirus;
}


void Player::earnPoints(int points) {
	hackingPoints += points;
}
void Player::spendPoints(int cost) {
	if (cost <= hackingPoints) {
		hackingPoints -= cost;
	} 

}

void Player::setInitials(Company* companyList[]){
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
// obama have dih 
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
				statsUpgrade[parserIndex2 + 3],
				statsUpgrade[parserIndex2 + 4]
		);
		parserIndex1 += 2;
		parserIndex2 += 5;
	}
}
void Player::update() {
	std::string upgrade;
	std::cout << "Enter to continue, U to open Upgrade Menu \n";
	do {
		getline(std::cin, upgrade);
	} while (!(upgrade == "" || upgrade == "U" || upgrade == "u"));
	bool menuing = true;
	while (menuing == true) {
		if (upgrade == "U" || upgrade == "u") {
			displayUpgrades(menuing);
		}
		else {
			menuing = false;
		}
	}
}
void Player::displayUpgrades(bool& menuing) {
	std::cout << "Available Upgrades: " << std::endl;
	std::string input = "";
	int choice = -1;
	do {
		std::cout << "Enter the number of the upgrade you want to purchase(or E to exit): \n" << std::endl;
		for (int i = 0; i < NUM_UPGRADES; i++) {
			if (upgradesArray[i] != nullptr) {
				std::cout << i + 1 << ". " << upgradesArray[i]->getName() << std::endl;
			}
		}
		std::cin >> input;
		if (input == "E" || input == "e") {
			menuing = false;
			return;
		}
		else {
			std::istringstream iss(input);
			if (!(iss >> choice)) {
				std::cout << "Invalid input. Please enter a number or 'E' to exit." << std::endl;
				choice = -1;
			}
			else {
				choice -= 1;
			}
		}
	} while (choice < 0 || choice >= NUM_UPGRADES || upgradesArray[choice] == nullptr);

	playerVirus->evolve(upgradesArray[choice]);
	std::cout << "You have purchased the upgrade:\n "
		<< upgradesArray[choice]->getName() << std::endl;

	delete upgradesArray[choice];
	upgradesArray[choice] = nullptr;
}

