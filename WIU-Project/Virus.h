#pragma once
#include <iostream>
#include "Company.h"
#include <string>
#include "Upgrades.h"
class Virus
{
	// THIS CLASS IS ABSTRACT! INSTANTIATE CHILD OBJECT INSTEAD!
protected:
	std::string name;
	int speed;
	int stealth;
	int payload;
	int resilience;

public:
	void evolve(Upgrades toUpgrade);
	virtual void applyEffect(Company& company) = 0;

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

