// V1.1.4
#pragma once
#include <iostream>
#include "Virus.h"
class Company
{
private:
	std::string companyName;
	int networkSize; // how big the company is 
	float securityLevel; // defence against virus
	float noOfInfectedComputers; // company infection based off networkSize
	float infectedStatus; // 0 = not infected, 0-1 = partially infected, 1 = fully infected/company dead
	Virus* virus;
	bool isEmailTransmissionEnabled;
	int maxCompany;

public:
	// Cons and Dest
	Company();
	Company(std::string Name, int size, int startingSecurityLevel); //overloaded
	~Company();

	// Getters and Setters
	int getInfectedStatus() const;
	int getNoOfInfectedComputers() const;
	std::string getName() const;
	int getNetworkSize() const;

	void setVirus(Virus* Virus);
	void setNoOfInfectedComputers(int noOfInfectedComputers);

	// Functions
	void update(Company* companies[]);
	int calculateInfected();
	float calculateSpread(Company* companies[]);
};

