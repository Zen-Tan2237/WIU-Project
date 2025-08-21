#include "Player.h"

Player::Player() {
	for (int i = 0; i < NUM_UPGRADES; i++) {
		upgradesArray[i] = nullptr;
	}
	hackingPoints = 5;
	companyChoice = 0;
	maxCompany = 0;
	infectedComputersPrevious = 0;
	playerVirus = nullptr;
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
	parseDependencies();
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

void Player::parseDependencies() {
	int numberOfElements = sizeof(dependentIndices) / sizeof(dependentIndices[0]);

	// Count chains first
	noOfChains = 0;
	for (int i = 0; i < numberOfElements; i++)
		if (dependentIndices[i] == -1) noOfChains++;

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

void Player::update(int noOfInfectedComputers, int networkSize) {
	std::string upgrade;
	if (noOfInfectedComputers - infectedComputersPrevious > 0) {
			int probability = (rand() % 10);
			if (probability > 4) {
				if (noOfInfectedComputers < networkSize/(maxCompany*100)) {
					hackingPoints += rand() % 2;
				}
				else if(noOfInfectedComputers < networkSize / (maxCompany * 10)) {
					hackingPoints += rand()% 2 + 1 ;
				}
				else {
					hackingPoints += rand() % 4 + 1;
				}

			}
	}
	infectedComputersPrevious = noOfInfectedComputers;
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


//void Player::displayUpgrades(bool& menuing) {
//	std::cout << "Available Upgrades: " << std::endl;
//	std::string input = "";
//	int choice = -1;
//	do {
//		std::cout << "Enter the number of the upgrade you want to purchase(or E to exit): \n" << std::endl;
//		for (int i = 0; i < NUM_UPGRADES; i++) {
//			if (upgradesArray[i] != nullptr) {
//				std::cout << i + 1 << ". " << upgradesArray[i]->getName() << std::endl;
//			}
//		}
//		std::cin >> input;
//		if (input == "E" || input == "e") {
//			menuing = false;
//			return;
//		}
//		else if (input == "P" || input == "p") {
//			playerVirus->setAll10();
//		}
//		else if (input == "S" || input == "s") {
//			playerVirus->displayStats();
//		}
//		else {
//			std::istringstream iss(input);
//			if (!(iss >> choice)) {
//				std::cout << "Invalid input. Please enter a number or 'E' to exit." << std::endl;
//				choice = -1;
//			}
//			else {
//				choice -= 1;
//			}
//		}
//	} while (choice < 0 || choice >= NUM_UPGRADES || upgradesArray[choice] == nullptr);
//
//	playerVirus->evolve(upgradesArray[choice]);
//	std::cout << "You have purchased the upgrade:\n "
//		<< upgradesArray[choice]->getName() << std::endl;
//
//	delete upgradesArray[choice];
//	upgradesArray[choice] = nullptr;
//}


void Player::displayUpgrades(bool& menuing) {
	blockUpgrade(); // update current available upgrades
	std::string input;
	bool ignoreTryingParseNo = false;
	bool ignoreApplyUpgrade = false;
	while (menuing) {
		std::cout << "\nAvailable Upgrades:\n";
		for (int i = 0; i < noOfChains; i++) {
			if (currentUpgradeIndices[i] != -1) {
				int idx = currentUpgradeIndices[i];
				std::cout << i + 1 << ". " << upgradesArray[idx]->getName() << std::endl;
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
			ignoreTryingParseNo = true;
		}
		else if (input == "P" || input == "p") {
			playerVirus->setAll10();
			ignoreTryingParseNo = true;
		}

		if (ignoreTryingParseNo == false) {
			// Try to parse number
			int choice = -1;
			std::istringstream iss(input);
			if (!(iss >> choice) || choice <= 0 || choice > noOfChains) {
				std::cout << "Invalid input. Try again.\n";
				ignoreApplyUpgrade = true;
			}

			// Map user input to actual upgrade index
			int upgradeIdx = currentUpgradeIndices[choice - 1];
			if (upgradeIdx == -1 || upgradesArray[upgradeIdx] == nullptr) {
				std::cout << "Upgrade unavailable. Try again.\n";
				ignoreApplyUpgrade = true;
			}
			if (ignoreApplyUpgrade == false) {
				// Apply upgrade
				playerVirus->evolve(upgradesArray[upgradeIdx]);
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

