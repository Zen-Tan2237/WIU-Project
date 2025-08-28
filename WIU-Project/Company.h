// V1.1.5
#pragma once
#include <iostream>
#include "Virus.h"
class Company
{
private:
	static int totalNetworkSize;
	static int totalNoOfInfectedComputers;
	static int totalNoOfBrickedComputers;
	static int totalUniqueCompanyInfections;

	std::string companyName;
	int networkSize; // how big the company is 
	float securityLevel; // defence against virus
	int noOfInfectedComputers; // company infection based off networkSize
	int noOfBrickedComputers;
	float infectedStatus; // 0 = not infected, 0-1 = partially infected, 1 = fully infected/company dead
	float brickedStatus;
	Virus* virus;
	bool isEmailTransmissionEnabled;
	int maxCompany;
	int* collabSpreadWeight;
	bool isFallen;

	int companyIndex;

public:
	// Cons and Dest
	Company();
	Company(std::string Name, int size, float startingSecurityLevel, int maxCompany, int companyIndex); //overloaded
	~Company();

	// Getters and Setters
	float getInfectedStatus() const;
	float getBrickedStatus() const;
	int getNoOfInfectedComputers() const;
	int getNoOfBrickedComputers() const;
	std::string getName() const;
	int getNetworkSize() const;
	float getSecurityLevel() const;
	static void getTotalStuff();
	static int getTotalNetworkSize();
	static int getTotalNoOfInfectedComputers();
	static int getTotalNoOfBrickedComputers();
	static int getTotalUniqueCompanyInfections();

	bool getIsFallen() const;
	void setIsFallen(bool isFallen);

	void setVirus(Virus* Virus);
	void setNoOfInfectedComputers(int noOfInfectedComputers);
	void setCollabSpreadWeightIndex(int spreadWeight, int companyIndex);

	// Functions
	void update(Company* companies[]);
	int calculateInfected();
	int calculateBricked();
	void calculateSpread(Company* companies[]);
};

