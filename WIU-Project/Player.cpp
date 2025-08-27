#include "Player.h"

Player::Player() {
	parseUpgrades();
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

int** Player::getDependencyChain() {
	return dependencyChain;
}

Upgrades** Player::getUpgradesArray() {
	return upgradesArray;
}

int* Player::getCurrentUpgradeIndices() {
	return currentUpgradeIndices;
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

void Player::setInitials(Company* companyList[], int type, int companyChoice, std::string virusName){

	// Set virus types!
	switch (type) {
	case 1:
		playerVirus = new Worm;
		break;
	case 2:
		playerVirus = new Trojan;
		break;
	case 3:
		playerVirus = new Ransomware;
		break;
	default:
		// I hate this
		break;
	}

	if (!virusName.empty()) {
		playerVirus->setName(virusName);
	}

	// Set company choice to 1 infected computer
	companyList[companyChoice - 1]->setNoOfInfectedComputers(1);

	// Initalise all upgrades stuff
	parseUpgrades();
	parseDependencies();
}

//*******************************************
// Written by Zen
// Name: parseUpgrades
// Description: Parses the array of data in player.h
// Note: meant to be scalable to read an external file, but ig if no time I'll just leave it here lol
//*******************************************
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

int Player::getNoOfChains() {
	return noOfChains;
}

void Player::update(int noOfInfectedComputers, int networkSize, int noOfBrickedComputers) {
	std::string upgrade;
	if (noOfInfectedComputers - infectedComputersPrevious > 0 || noOfBrickedComputers - brickedComputersPrevious) {
		int probability = (rand() % 10 +(noOfInfectedComputers - infectedComputersPrevious)/2);

		if (probability > 4) {//60% base chance
			if (noOfBrickedComputers < networkSize/(maxCompany*500)) {
				// If bricked computers are less than 2% of the network size , play this set of rules
				if (noOfInfectedComputers - infectedComputersPrevious < networkSize/(maxCompany*100)) {
					// If infected computers are less than 10% of the network size, add 1 point
					hackingPoints += 1;
				}
				else if(noOfInfectedComputers - infectedComputersPrevious < networkSize / (maxCompany * 50)){
					// If infected computers are less than 50% of the network size, add 1-3 points
					hackingPoints += (rand() % 2) + 1;
				}
				else {
					// If infected computers are more than 50% of the network size, add 1-4 points
					hackingPoints += (rand() % 3) + 1;
				}
			}
			else if(noOfBrickedComputers < networkSize / (maxCompany * 100)) {
				// If bricked computers are less than 10% of the network size, add 2-4 points
				hackingPoints += (rand()% 3) + 1;
			}
			else {
				// If bricked computers are more than 10% of the network size, add 2-6 points
				hackingPoints += (rand() % 3) + 2;
			}
		}
	}

	infectedComputersPrevious = noOfInfectedComputers;
	brickedComputersPrevious = noOfBrickedComputers;
	bool menuing = true;

	//do {//upgrade menu
	//	std::cout << "Hacker Points: " << hackingPoints << std::endl;
	//	std::cout << "Enter to continue, U to open Upgrade Menu \n";
	//	do {
	//		getline(std::cin, upgrade);
	//	} while (!(upgrade == "" || upgrade == "U" || upgrade == "u"));
	//	if (upgrade == "U" || upgrade == "u") {
	//		displayUpgrades();

	//	}
	//	else if(upgrade == ""){
	//		menuing = false;
	//	}
	//} while (menuing == true);
	//std::cout << "exited";
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
}

void Player::displayUpgrades() {
	blockUpgrade(); // update current available upgrades
	std::string input;
	while (true) {
		std::cout << "\nAvailable Upgrades:\n";
		std::cout << "Hacker Points: " << hackingPoints << std::endl;
		for (int i = 0; i < noOfChains; i++) {
			if (currentUpgradeIndices[i] != -1) {
				int idx = currentUpgradeIndices[i];
				if (upgradesArray[idx] != nullptr) {
					std::cout << i + 1 << ". " << upgradesArray[idx]->getName() << " Costs: " << static_cast<int>(upgradesArray[idx]->getCost()) << std::endl;
				}
			}
		}
		std::cout << "Enter number to purchase, 'E' to exit:";
		std::getline(std::cin, input);

		if (input == "E" || input == "e") {
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
				applyUpgrade(upgradeIdx);
			}
		}
	}
}

void Player::applyUpgrade(int upgradeIndex) {
	// Apply upgrade
	playerVirus->evolve(upgradesArray[upgradeIndex]);
	spendPoints(upgradesArray[upgradeIndex]->getCost());
	std::cout << upgradesArray[upgradeIndex]->getName() << " has been upgraded with NO additional cost!" << std::endl;
	// Delete upgrade to mark as purchased
	delete upgradesArray[upgradeIndex];
	upgradesArray[upgradeIndex] = nullptr;

	// Update available upgrades
	blockUpgrade();
}