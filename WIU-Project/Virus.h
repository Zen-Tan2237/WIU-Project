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
	int mutationProbability;

public:
	virtual void evolve(Upgrades* toUpgrade);
	void setAll10();
	void displayStats();
	virtual void mutate(int** upgradesArray, int* currentUpgradesIndex) = 0;
	virtual void miniGame(int hackingPoints) = 0;

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

};

