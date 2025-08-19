#include "Company.h"
#include "stdlib.h"
#include "time.h"
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

Company::Company(std::string Name, int size)
{
	companyName = Name;
	networkSize = size;
	infectedStatus = 0;
	noOfInfectedComputers = 0;
	securityLevel = networkSize ;
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
		noOfInfectedComputers += securityLevel - virus->getSpeed();

		if (noOfInfectedComputers = 0)
		{
			infectedStatus = 0;
		}
		else if (noOfInfectedComputers == networkSize)
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

int Company::getNoOfInfectedComputers() const
{
	return noOfInfectedComputers;
}

std::string Company::getName() const
{
	return companyName;
}

