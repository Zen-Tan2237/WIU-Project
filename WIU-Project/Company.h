// V1.1.4
#pragma once
#include <iostream>
#include "Virus.h"
class Company
{
private:
	std::string companyName;
	int networkSize; // how big the company is 
	int securityLevel; // defence against virus
	float noOfInfectedComputers; // company infection based off networkSize
	int infectedStatus; // 0 = not infected, 1 = partially infected, 2 = fully infected/company dead
	Virus* virus;

public:
	Company();
	Company(std::string Name, int size, int startingSecurityLevel); //overloaded
	~Company();

	void update();
	int getInfectedStatus() const;
	void setVirus(Virus* Virus);
	void setNoOfInfectedComputers(int noOfInfectedComputers);
	int getNoOfInfectedComputers() const;
	std::string getName() const;
	int getNetworkSize() const;
};

