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

}

Company::Company(std::string Name, int size, int startingSecurityLevel)
{
	companyName = Name;
	networkSize = size;
	infectedStatus = 0;
	noOfInfectedComputers = 0;
	securityLevel = startingSecurityLevel;
	virus = nullptr;
}

Company::~Company()
{
}

void Company::update()
{
	if (infectedStatus < 2)
	{
		// logic for infection level in the company
		if (noOfInfectedComputers > 0 && noOfInfectedComputers < networkSize) {
			float speedMult = 1.0 + 0.25 * (virus->getSpeed() - 1);
			int advantage = virus->getComplexity() - securityLevel;
			float advMult = 1.0 + 0.10 * advantage;


			// probability calculation
			float infectedFrac = (float)noOfInfectedComputers / (float)networkSize;

			float probability = 0.05 * speedMult * advMult * (infectedFrac * 100.0);
			
			if (probability < 0.01f) probability = 0.01f; // always at least 1% chance
			if (probability > 0.8f) probability = 0.8f;  // cap at 90%

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

				noOfInfectedComputers += add;
			}
		}


		// get infection status
		if (noOfInfectedComputers == 0)
		{
			infectedStatus = 0;
		}
		else if (noOfInfectedComputers >= networkSize)
		{
			infectedStatus = 2;
		}
		else
		{
			infectedStatus = 1;
		}
	}
}

int Company::getInfectedStatus() const
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

