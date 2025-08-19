#pragma once
#include <iostream>
#include "Worm.h"
class Company
{
private:
	std::string companyName;
	int networkSize; // how big the company is
	float securityLevel; // defence against virus
	int infectionLevel; // % of company infection (0-100%)
	int infectedStatus; // 0 = not infected, 1 = partially infected, 2 = fully infected/company dead
	Virus* virus;

public:
	Company();
	Company(std::string Name, int size); //overloaded
	~Company();

	void updateInfection();
	int getInfectedStatus() const;
	//Worm getVirus() const;
};

