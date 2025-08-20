#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>

#include "Company.h"
#include "Virus.h"

Company::Company()
{
	infectedStatus = 0;
	companyName = "We sell 100% halalpork";
	securityLevel = 1;
	noOfInfectedComputers = 0;
	networkSize = 1;
	virus = nullptr;
	isEmailTransmissionEnabled = true;
	maxCompany = 1;
}

Company::Company(std::string Name, int size, float startingSecurityLevel, int maxCompany)
{
	companyName = Name;
	networkSize = size;
	infectedStatus = 0;
	noOfInfectedComputers = 0;
	securityLevel = startingSecurityLevel;
	virus = nullptr;
	isEmailTransmissionEnabled = true;
	this->maxCompany = maxCompany;
}

Company::~Company()
{
}

void Company::update(Company* companies[])
{
	if (infectedStatus < 1) {
		// logic for infection level in the company
		if (noOfInfectedComputers > 0 && noOfInfectedComputers < networkSize) {
			noOfInfectedComputers += calculateInfected();
		}

		// logic for spreading between companies
		if (isEmailTransmissionEnabled) {
			calculateSpread(companies);
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
}

int Company::calculateInfected()
{
	float speedMult = 1.0 + 0.25 * (virus->getSpeed() - 1);
	float advantage = virus->getComplexity() - securityLevel;
	float advMult = 1.0 + 0.10 * advantage;


	// probability calculation
	float infectedFrac = (float)noOfInfectedComputers / (float)networkSize;

	float probability = 0.05 * speedMult * advMult * (infectedFrac * 100.0);

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

	if (probability < 0.0f) probability = 0.0f; // always at least 1% chance
	if (probability > 0.02f) probability = 0.02f;  // cap at 1%

	// roll probability with rand()
	bool triggers = (rand() % 1000) < (int)(probability * 1000.0);

	if (triggers) {
		int temp;
		int attempts = 0;

		do {
			temp = rand() % maxCompany;
			attempts++;
		} while (companies[temp]->getInfectedStatus() != 0 && attempts < 100);

		

		if (companies[temp]->getNoOfInfectedComputers() == 0) {
			float advantage = companies[temp]->getSecurityLevel() - virus->getComplexity();
			std::cout << "ALERT: " << advantage << std::endl;

			float probability = 0.0f;

			if (advantage < -2) {
				probability = 1.0f; // guaranteed
			}
			else {
				probability = 1.0f / std::pow(1.5f, advantage + 2);
			}

			triggers = (rand() % 100) < (int)(probability * 100.0);

			if (triggers) {
				std::cout << "Virus managed to spread to " << companies[temp]->getName() << ", with a chance of " << probability * 100 << "%" << std::endl;
				companies[temp]->setNoOfInfectedComputers(1);
			}
		}
		else {
			int spreadAmount = 1 + (rand() % 3); // infect 1–3 new computers
			int current = companies[temp]->getNoOfInfectedComputers();
			int maxSize = companies[temp]->getNetworkSize();

			companies[temp]->setNoOfInfectedComputers(
				std::min(current + spreadAmount, maxSize)
			);
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
	this->noOfInfectedComputers = noOfInfectedComputers;
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

