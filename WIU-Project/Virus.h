#pragma once
#include <iostream>
#include <string>
#include "Upgrades.h"

class Virus
{
protected:
	std::string name;
	float speed;
	float complexity;
	float payload;
	float resilience;

public:

	virtual void evolve(Upgrades* toUpgrade);
	void setAll10();
	virtual void miniGame(int& hackingPoints) = 0;
	void displayStats();

	Virus();
	virtual ~Virus();

	//GETTERS SETTERS
	float getSpeed() const;
	float getComplexity() const;
	float getPayload() const;
	float getResilience() const;
	std::string getName() const;

	void setSpeed(float s);
	void setComplexity(float st);
	void setPayload(float payload);
	void setResilience(float resilience);
	void setName(std::string name);

	virtual const std::string* getNameUpgrade() const = 0;
	virtual const float* getStatsUpgrades() const = 0;
	virtual const int* getDependentIndices() const = 0;
	virtual const int getNumUpgrades() const = 0;

};

