#pragma once
#include <iostream>
#include <string>
#include "Upgrades.h"

class Virus
{
protected:
	std::string name;
	int speed;
	int stealth;
	int payload;
	int resilience;

public:
	void evolve(Upgrades& toUpgrade);

	Virus();
	~Virus();

	//GETTERS SETTERS
	int getSpeed() const;
	int getStealth() const;
	int getPayload() const;
	int getResilience() const;
	std::string getName() const;

	void setSpeed(int s);
	void setStealth(int st);
	void setPayload(int payload);
	void setResilience(int resilience);
	void setName(std::string name);

};

