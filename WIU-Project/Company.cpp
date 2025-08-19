#include "Company.h"
#include "stdlib.h"
#include "time.h"
#include "Worm.h"

Company::Company()
{
	infectedStatus = 0;
	companyName = "halalpork";
	securityLevel = 1;
	infectionLevel = 0;
	networkSize = 1;
	virusType = nullptr;

}

Company::Company(std::string Name, int size)
{
	companyName = Name;
	networkSize = size;
	infectedStatus = 0;
	infectionLevel = 0;
	securityLevel = networkSize * 350;
	virusType = nullptr;
}

Company::~Company()
{
}

void Company::updateInfection(int virusStrength)
{
	if (infectedStatus < 2)
	{
		// logic for infection level in the company
		infectionLevel += securityLevel - virusStrength;

		if (infectionLevel = 0)
		{
			infectedStatus = 0;
		}
		else if (infectionLevel = 100)
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

//Worm Company::getVirus() const
//{
//	return;
//}
