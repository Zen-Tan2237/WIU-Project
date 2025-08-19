#pragma once
#include <iostream>
#include <string>
#include "Upgrades.h"

class Virus
{
protected:
	std::string name;
	int speed;
	int complexity;
	int payload;
	int resilience;

public:
	void evolve(Upgrades& toUpgrade);

	Virus();
	~Virus();

	//GETTERS SETTERS
	int getSpeed() const;
	int getComplexity() const;
	int getPayload() const;
	int getResilience() const;
	std::string getName() const;

	void setSpeed(int s);
	void setComplexity(int st);
	void setPayload(int payload);
	void setResilience(int resilience);
	void setName(std::string name);

};

