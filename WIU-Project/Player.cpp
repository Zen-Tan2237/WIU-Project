#include "Player.h"

Player::Player() {
	for (int i = 0; i < NUM_UPGRADES; i++) {
		upgradesArray[i] = nullptr;
	}
	hackingPoints = 5;
	companyChoice = 0;
	maxCompany = 0;
	infectedComputersPrevious = 0;
	brickedComputersPrevious = 0;
	playerVirus = nullptr;
	noOfChains = 0;
	lengthOfArray = nullptr;
	dependencyChain = nullptr;
	currentUpgradeIndices = nullptr;
}
Player::~Player() {
	for (int i = 0; i < NUM_UPGRADES; i++) {
		delete upgradesArray[i];
		upgradesArray[i] = nullptr;
	}
	delete playerVirus;
	playerVirus = nullptr;

	for (int i = 0; i < 1; i++) {
		delete[] dependencyChain[i];
	}
	delete dependencyChain;
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
	this-> maxCompany = maxCompany;
}

Virus* Player::getPlayerVirus() const {
	return playerVirus;
}

void Player::spendPoints(float cost) {
	if (cost <= hackingPoints) {
		hackingPoints -= cost;
		std::cout << "You have spent " << cost << " hacking points." << std::endl;
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
	parseDependencies();
}

//**************241199A**************
// Written by Zen
// Name: parseUpgrades
// Description: Parses the array of data in player.h
// Coding is my passion ahh font :sob:
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

void Player::parseDependencies() {
	int numberOfElements = sizeof(dependentIndices) / sizeof(dependentIndices[0]);

	// Count chains first
	noOfChains = 0;
	for (int i = 0; i < numberOfElements; i++) {
		if (dependentIndices[i] == -1) {
			noOfChains++;
		}
	}

	dependencyChain = new int* [noOfChains];
	lengthOfArray = new int[noOfChains];
	currentUpgradeIndices = new int[noOfChains];

	// Filling the chains
	int chainIndex = 0;
	int start = 0;
	for (int i = 0; i < numberOfElements; i++) {
		if (dependentIndices[i] == -1) {
			int length = i - start;
			dependencyChain[chainIndex] = new int[length + 1];

			// Copy into 2D array
			for (int j = 0; j < length; j++) {
				dependencyChain[chainIndex][j] = dependentIndices[start + j];
			}

			dependencyChain[chainIndex][length] = -1; // stopper
			lengthOfArray[chainIndex] = length;
			chainIndex++;
			start = i + 1;
		}
	}
}

void Player::printArrays() {
	// Print chains
	for (int i = 0; i < noOfChains; i++) {
		std::cout << "Chain " << i + 1 << ": ";
		for (int j = 0; dependencyChain[i][j] != -1; j++) {
			std::cout << dependencyChain[i][j] << " ";
		}
		std::cout << std::endl;


	}
	for (int i = 0; i < noOfChains; i++) {
		std::cout << "Length of array " << i + 1 << ": " << lengthOfArray[i] << std::endl;
	}
	blockUpgrade();
	for (int i = 0; i < noOfChains; i++) {
		std::cout << "Current index in array: " << i + 1 << ": " << currentUpgradeIndices[i] << std::endl;
	}
}

void Player::update(int noOfInfectedComputers, int networkSize, int noOfBrickedComputers) {
	std::string upgrade;
	if (noOfInfectedComputers - infectedComputersPrevious > 0 || noOfBrickedComputers - brickedComputersPrevious) {
		int probability = (rand() % 10);
		if (probability > 1) {
			if (noOfBrickedComputers < networkSize/(maxCompany*500)) {
				if (noOfInfectedComputers - infectedComputersPrevious < networkSize/(maxCompany*100)) {
					hackingPoints += 1;
				}
				else if(noOfInfectedComputers - infectedComputersPrevious < networkSize / (maxCompany * 50)){
					hackingPoints += (rand() % 2) + 1;
				}
				else {
					hackingPoints += (rand() % 4) + 1;
				}
			}
			else if(noOfBrickedComputers < networkSize / (maxCompany * 100)) {
				hackingPoints += (rand()% 3) + 2;
			}
			else {
				hackingPoints += (rand() % 5) + 2;
			}
		}
	}
	infectedComputersPrevious = noOfInfectedComputers;
	brickedComputersPrevious = noOfBrickedComputers;
	std::cout << "Hacker Points: " << hackingPoints << std::endl;
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

void Player::blockUpgrade() {
	for (int i = 0; i < noOfChains; i++) {
		currentUpgradeIndices[i] = dependencyChain[i][0];
		for (int j = 0; dependencyChain[i][j] != -1; j++) {

			if (upgradesArray[dependencyChain[i][j]] == nullptr) {
				if (j + 1 < lengthOfArray[i]) {
					currentUpgradeIndices[i] = dependencyChain[i][j + 1];
				}
				else {
					currentUpgradeIndices[i] = -1;
				}
			}
		}
	}
	for (int i = 0; i < noOfChains; i++) {
		std::cout << "Current Array Index " << i + 1 << ": " << currentUpgradeIndices[i] << std::endl;
	}
}
void Player::displayUpgrades(bool& menuing) {
	blockUpgrade(); // update current available upgrades
	std::string input;
	while (menuing) {
		std::cout << "\nAvailable Upgrades:\n";
		for (int i = 0; i < noOfChains; i++) {
			if (currentUpgradeIndices[i] != -1) {
				int idx = currentUpgradeIndices[i];
				if (upgradesArray[idx] != nullptr) {
					std::cout << i + 1 << ". " << upgradesArray[idx]->getName() << " Costs: " << static_cast<int>(upgradesArray[idx]->getCost()) << std::endl;
				}
			}
		}
		std::cout << "Enter number to purchase, 'E' to exit:";
		std::cin >> input;

		if (input == "E" || input == "e") {
			menuing = false;
			return;
		}
		else if (input == "S" || input == "s") {
			playerVirus->displayStats();
		}
		else if (input == "P" || input == "p") {
			playerVirus->setAll10();
		}
		else {
			// Try to parse number
			int choice = -1;
			std::istringstream iss(input);
			if (!(iss >> choice) || choice <= 0 || choice > noOfChains) {
				std::cout << "Invalid input. Try again.\n";
				continue;
			}
			// Map user input to actual upgrade index
			int upgradeIdx = currentUpgradeIndices[choice - 1];

			if ((upgradeIdx == -1 || upgradesArray[upgradeIdx] == nullptr)) {
				std::cout << "Upgrade unavailable. Try again.\n";
			}
			else if (upgradesArray[upgradeIdx]->getCost() > hackingPoints) {
				std::cout << "Not enough hacking points to purchase this upgrade.\n";
			}
			else{
				// Apply upgrade
				playerVirus->evolve(upgradesArray[upgradeIdx]);
				spendPoints(upgradesArray[upgradeIdx]->getCost());
				std::cout << "Purchased: " << upgradesArray[upgradeIdx]->getName() << std::endl;
				// Delete upgrade to mark as purchased
				delete upgradesArray[upgradeIdx];
				upgradesArray[upgradeIdx] = nullptr;

				// Update available upgrades
				blockUpgrade();
			}
		}
	}
}

