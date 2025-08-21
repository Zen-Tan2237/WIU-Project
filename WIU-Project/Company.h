// V1.1.5
#pragma once
#include <iostream>
#include "Virus.h"
class Company
{
private:
	static int totalNetworkSize;
	static int totalNoOfInfectedComputers;

	std::string companyName;
	int networkSize; // how big the company is 
	float securityLevel; // defence against virus
	float noOfInfectedComputers; // company infection based off networkSize
	float infectedStatus; // 0 = not infected, 0-1 = partially infected, 1 = fully infected/company dead
	Virus* virus;
	bool isEmailTransmissionEnabled;
	int maxCompany;
	float* collabSpreadWeight;

	int companyIndex;

public:
	// Cons and Dest
	Company();
	Company(std::string Name, int size, float startingSecurityLevel, int maxCompany, int companyIndex); //overloaded
	~Company();

	// Getters and Setters
	float getInfectedStatus() const;
	int getNoOfInfectedComputers() const;
	std::string getName() const;
	int getNetworkSize() const;
	float getSecurityLevel() const;
	static void getTotalStuff();
	static int getTotalNetworkSize();
	static int getTotalNoOfInfectedComputers();

	void setVirus(Virus* Virus);
	void setNoOfInfectedComputers(int noOfInfectedComputers);
	void setCollabSpreadWeightIndex(int spreadWeight, int companyIndex);

	// Functions
	void update(Company* companies[]);
	int calculateInfected();
	void calculateSpread(Company* companies[]);
};

