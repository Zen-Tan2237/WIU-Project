#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <limits>
#include <numbers>

#include "Company.h"
#include "Virus.h"

int Company::totalNetworkSize = 0;
int Company::totalNoOfInfectedComputers = 0;
int Company::totalNoOfBrickedComputers = 0;

Company::Company()
{
	this->companyIndex = 0;

	infectedStatus = 0;
	brickedStatus = 0;
	companyName = "We sell 100% halalpork";
	securityLevel = 1;
	noOfInfectedComputers = 0;
	noOfBrickedComputers = 0;
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
	brickedStatus = 0;
	noOfInfectedComputers = 0;
	noOfBrickedComputers = 0;
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
	}

	if (brickedStatus < 1) {
		// logic for bricked level in the company
		if (noOfInfectedComputers > 0 && noOfBrickedComputers < noOfInfectedComputers) {
			int temp2 = calculateBricked();
			noOfBrickedComputers += temp2;
			totalNoOfBrickedComputers += temp2;
		}
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

	// get bricked status
	if (noOfBrickedComputers == 0) {
		brickedStatus = 0;
	}
	else if (noOfBrickedComputers < networkSize) {
		brickedStatus = (float)noOfBrickedComputers / (float)networkSize;
	}
	else {
		brickedStatus = 1;
		noOfBrickedComputers = networkSize;
	}

	// logic for spreading between companies
	if (noOfInfectedComputers > 0 && isEmailTransmissionEnabled) {
		calculateSpread(companies);
	}
}

int Company::calculateInfected() // BALANCED
{
	float speedMult = 1.0 + 0.5 * (virus->getSpeed() - 1);
	if (virus->getSpeed() == 0) {
		speedMult = 0;
	}
	
	float advantage = virus->getComplexity() - securityLevel;
	if (advantage <= 0) {
		advantage = 0;
	}
	float advMult = 1.0 + (0.25 * advantage);


	// probability calculation
	float infectedFrac = (float)noOfInfectedComputers / (float)networkSize;

	float probability = 0.03f + 0.02f * speedMult * advMult * (1.0f + (infectedFrac * 100.0f) * 0.4f);

	if (probability < 0.05f) probability = 0.05f; // always at least 1% chance
	if (probability > 0.5f) probability = 0.5f;  // cap at 50%

	// roll probability with rand()
	bool triggers = (rand() % 1000) < (int)(probability * 1000.0f);

	if (triggers) {
		int add = (int)std::floor(noOfInfectedComputers * 0.02 * speedMult * advMult * (1.0 - infectedFrac));
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

int Company::calculateBricked() // BALANCED
{
	float payloadMult = 0 + 0.5 * (virus->getPayload() - 1);
	float advantage = virus->getComplexity() - securityLevel;
	if (advantage <= 0) {
		advantage = 0;
	}
	float advMult = 1.0 + (0.25 * advantage);


	// probability calculation
	float infectedFrac = (float)noOfInfectedComputers / (float)networkSize;
	float brickedFrac = (float)noOfBrickedComputers / (float)networkSize;

	float probability = 0.01f * payloadMult * advMult * (1.0f + (infectedFrac * 100.0f) * 0.4f);


	if (probability < 0.00f) probability = 0.00f; // yes 
	if (probability > 0.2f) probability = 0.2f;  // cap at 30%

	// roll probability with rand()
	bool triggers = (rand() % 1000) < (int)(probability * 1000.0);

	if (triggers) {
		int add = (int)std::floor(noOfBrickedComputers * 0.02 * payloadMult * advMult * (1.0 - brickedFrac));
		if (add < 1) {
			add = 1;
		}
		if (add > (noOfInfectedComputers - noOfBrickedComputers)) {
			add = noOfInfectedComputers - noOfBrickedComputers;
		}

		return add;
	}

	return 0;
}

void Company::calculateSpread(Company* companies[]) // BALANCED
{
	float speedMult = 1.0 + 0.01 * (virus->getSpeed() - 1);
	float advantage = virus->getComplexity() - securityLevel;
	float advMult = 1.0 + 0.01 * advantage;
	float networkSizeMult = 1.0 + 0.01 * networkSize;


	// probability calculation
	float infectedFrac = (float)noOfInfectedComputers / (float)networkSize;


	float probability = 0.01 * speedMult * advMult * infectedFrac * networkSizeMult;

	if (probability < 0.001f) probability = 0.001f; // always at least 0.1% chance
	if (probability > (0.05f + (0.05 * (virus->getSpeed() - 1)))) probability = 0.05f;  // cap at 5-20% (dynamically)

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

				triggers = (rand() % 1000) < (int)(probability * 1000.0);

				if (triggers) {
					//std::cout << "Virus managed to spread to " << companies[chosenSpreadCompany]->getName() << ", with a chance of " << probability * 100 << "%" << std::endl;
					companies[chosenSpreadCompany]->setNoOfInfectedComputers(1);
				}
				else {
					//std::cout << "Virus failed: Security Too High" << std::endl;
				}
			}
			else {
				companies[chosenSpreadCompany]->setNoOfInfectedComputers(companies[chosenSpreadCompany]->getNoOfInfectedComputers() + rand() % 3 + 1);
			}
		}
	}
}

float Company::getInfectedStatus() const
{	
	return infectedStatus;
}

float Company::getBrickedStatus() const
{
	return brickedStatus;
}

void Company::setVirus(Virus* Virus)
{
	virus = Virus;
}

void Company::setNoOfInfectedComputers(int noOfInfectedComputers)
{
	totalNoOfInfectedComputers -= this->noOfInfectedComputers;

	if (noOfInfectedComputers < networkSize) {
		this->noOfInfectedComputers = noOfInfectedComputers;
	}
	else {
		this->noOfInfectedComputers = networkSize;
	}

	totalNoOfInfectedComputers += this->noOfInfectedComputers;

	if (this->noOfInfectedComputers < networkSize) {
		infectedStatus = (float)this->noOfInfectedComputers / (float)networkSize;
	}
	else {
		infectedStatus = 1;
		this->noOfInfectedComputers = networkSize;
	}
}

void Company::setCollabSpreadWeightIndex(int spreadWeight, int companyIndex)
{
	collabSpreadWeight[companyIndex] = spreadWeight;
}

int Company::getNoOfInfectedComputers() const
{
	return noOfInfectedComputers;
}

int Company::getNoOfBrickedComputers() const
{
	return noOfBrickedComputers;
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

int Company::getTotalNoOfBrickedComputers()
{
	return totalNoOfBrickedComputers;
}



