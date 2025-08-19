#pragma once
#include <iostream>
#include "Worm.h"
class Company
{
private:
	std::string companyName;
	int networkSize; // how big the company is
	float securityLevel; // defence against virus
	int noOfInfectedComputers; // company infection based off networkSize
	int infectedStatus; // 0 = not infected, 1 = partially infected, 2 = fully infected/company dead
	Virus* virus;

public:
	Company();
	Company(std::string Name, int size, int securityLevelMulti); //overloaded
	~Company();

	void update();
	int getInfectedStatus() const;
	void setVirus(Virus* viruS);
	int getNoOfInfectedComputers() const;
	std::string getName() const;
	
};

