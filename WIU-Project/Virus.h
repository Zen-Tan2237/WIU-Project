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
	void evolve(Upgrades& toUpgrade);

	Virus();
	~Virus();

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

