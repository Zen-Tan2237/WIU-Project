#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>

#include "Company.h"
#include "Virus.h"

int Company::totalNetworkSize = 0;
int Company::totalNoOfInfectedComputers = 0;

Company::Company()
{
	this->companyIndex = 0;

	infectedStatus = 0;
	companyName = "We sell 100% halalpork";
	securityLevel = 1;
	noOfInfectedComputers = 0;
	networkSize = 1;
	virus = nullptr;
	isEmailTransmissionEnabled = true;
	maxCompany = 1;
	collabSpreadWeight = new int[maxCompany];

	totalNetworkSize += networkSize;

	for (int i = 0; i < maxCompany; i++) {
		if (i == this->companyIndex) {
			collabSpreadWeight[i] = 0;
		}
		else {
			collabSpreadWeight[i] = 1;
		}
	}
}

Company::Company(std::string Name, int size, float startingSecurityLevel, int maxCompany, int companyIndex)
{
	this->companyIndex = companyIndex;

	companyName = Name;
	networkSize = size;
	infectedStatus = 0;
	noOfInfectedComputers = 0;
	securityLevel = startingSecurityLevel;
	virus = nullptr;
	isEmailTransmissionEnabled = true;
	this->maxCompany = maxCompany;
	collabSpreadWeight = new int[maxCompany];

	totalNetworkSize += networkSize;

	for (int i = 0; i < maxCompany; i++) {
		if (i == this->companyIndex) {
			collabSpreadWeight[i] = 0;
		}
		else {
			collabSpreadWeight[i] = 1;
		}
	}
}

Company::~Company()
{
	delete[] collabSpreadWeight;
}

void Company::update(Company* companies[])
{
	if (infectedStatus < 1) {
		// logic for infection level in the company
		if (noOfInfectedComputers > 0 && noOfInfectedComputers < networkSize) {
			int temp = calculateInfected();
			noOfInfectedComputers += temp;
			totalNoOfInfectedComputers += temp;
		}

		// get infection status
		if (noOfInfectedComputers == 0) {
			infectedStatus = 0;
		}
		else if (noOfInfectedComputers < networkSize) {
			infectedStatus = (float)noOfInfectedComputers / (float)networkSize;
		}
		else {
			infectedStatus = 1;
			noOfInfectedComputers = networkSize;
		}
	}

	// logic for spreading between companies
	if (isEmailTransmissionEnabled) {
		calculateSpread(companies);
	}
}

int Company::calculateInfected()
{
	float speedMult = 1.0 + 0.25 * (virus->getSpeed() - 1);
	float advantage = virus->getComplexity() - securityLevel;
	float advMult = 1.0 + 0.10 * advantage;


	// probability calculation
	float infectedFrac = (float)noOfInfectedComputers / (float)networkSize;

	float probability = 0.05 * speedMult * advMult * (infectedFrac * 1000.0);

	if (probability < 0.01f) probability = 0.01f; // always at least 1% chance
	if (probability > 0.1f) probability = 0.1f;  // cap at 10%

	// roll probability with rand()
	bool triggers = (rand() % 1000) < (int)(probability * 1000.0);

	if (triggers) {
		int add = (int)std::floor(noOfInfectedComputers * 0.10 * speedMult * advMult * (1.0 - infectedFrac));
		if (add < 1) {
			add = 1;
		}
		if (add > (networkSize - noOfInfectedComputers)) {
			add = networkSize - noOfInfectedComputers;
		}

		return add;
	}

	return 0;
}

void Company::calculateSpread(Company* companies[])
{
	float speedMult = 1.0 + 0.01 * (virus->getSpeed() - 1);
	float advantage = virus->getComplexity() - securityLevel;
	float advMult = 1.0 + 0.01 * advantage;
	float networkSizeMult = 1.0 + 0.01 * networkSize;


	// probability calculation
	float infectedFrac = (float)noOfInfectedComputers / (float)networkSize;

	float probability = 0.01 * speedMult * advMult * infectedFrac * networkSizeMult;

	if (probability < 0.001f) probability = 0.001f; // always at least 0.1% chance
	if (probability > 0.03f) probability = 0.03f;  // cap at 3%

	// roll probability with rand()
	bool triggers = (rand() % 1000) < (int)(probability * 1000.0);
	int chosenSpreadCompany = -1;

	if (triggers) {
		//int attempts = 0;

		//new choose company spread code

		int total = 0;
		for (int i = 0; i < maxCompany; i++) {
			total += collabSpreadWeight[i];
		}

		if (total > 0) { // has valid target
			int r = rand() % total;
			std::cout << "Chosen Weight: " << r << std::endl;

			// find which company gets picked
			int cumulative = 0;
			for (int i = 0; i < maxCompany; i++) {
				cumulative += collabSpreadWeight[i];
				if (r < cumulative) {
					chosenSpreadCompany = i;
					break;
				}
			}
		}
		else {
			chosenSpreadCompany = -1;
		}

		for (int i = 0; i < maxCompany; i++) {
			std::cout << collabSpreadWeight[i] << ", ";
		}
		std::cout << std::endl;

		/*do {
			chosenSpreadCompany = rand() % maxCompany;
			attempts++;
		} while (companies[chosenSpreadCompany]->getInfectedStatus() != 0 && attempts < 100);*/

		
		if (chosenSpreadCompany != -1) {
			if (companies[chosenSpreadCompany]->getNoOfInfectedComputers() == 0) {
				float advantage = companies[chosenSpreadCompany]->getSecurityLevel() - virus->getComplexity();

				float probability = 0.0f;

				if (advantage < -2) {
					probability = 1.0f; // guaranteed
				}
				else {
					probability = 1.0f / std::pow(1.5f, advantage + 2);
				}

				triggers = (rand() % 100) < (int)(probability * 100.0);

				if (triggers) {
					std::cout << "Virus managed to spread to " << companies[chosenSpreadCompany]->getName() << ", with a chance of " << probability * 100 << "%" << std::endl;
					companies[chosenSpreadCompany]->setNoOfInfectedComputers(1);
				}
			}
			else {
				int spreadAmount = 1 + (rand() % 3); // infect 1–3 new computers if already infected there
				int current = companies[chosenSpreadCompany]->getNoOfInfectedComputers();
				int maxSize = companies[chosenSpreadCompany]->getNetworkSize();

				companies[chosenSpreadCompany]->setNoOfInfectedComputers(
					std::min(current + spreadAmount, maxSize)
				);
			}
		}
	}
}

float Company::getInfectedStatus() const
{	
	return infectedStatus;
}

void Company::setVirus(Virus* Virus)
{
	virus = Virus;
}

void Company::setNoOfInfectedComputers(int noOfInfectedComputers)
{
	totalNoOfInfectedComputers -= this->noOfInfectedComputers;
	this->noOfInfectedComputers = noOfInfectedComputers;
	totalNoOfInfectedComputers += this->noOfInfectedComputers;
}

void Company::setCollabSpreadWeightIndex(int spreadWeight, int companyIndex)
{
	collabSpreadWeight[companyIndex] = spreadWeight;
}

int Company::getNoOfInfectedComputers() const
{
	return noOfInfectedComputers;
}

std::string Company::getName() const
{
	return companyName;
}

int Company::getNetworkSize() const
{
	return networkSize;
}

float Company::getSecurityLevel() const
{
	return securityLevel;
}

void Company::getTotalStuff()
{
	std::cout << "Total Network Size: " << totalNetworkSize << std::endl
		<< "Total Number Of Infected Computers: " << totalNoOfInfectedComputers << std::endl;
}

int Company::getTotalNetworkSize()
{
	return totalNetworkSize;
}

int Company::getTotalNoOfInfectedComputers()
{
	return totalNoOfInfectedComputers;
}



