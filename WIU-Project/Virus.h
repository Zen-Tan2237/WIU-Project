#pragma once // guys remember to pragma twice bro
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

	virtual void evolve(Upgrades* toUpgrade); // I forgot why I even made this virtual... haiz lazy to change la.
	void setAll10();
	virtual void miniGame(int& hackingPoints) = 0; // pure virtual (make Mr Izan proud realll)
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


	virtual const std::string* getNameUpgrade() const = 0;	// WOW VERY POLYMORPHISM
	virtual const float* getStatsUpgrades() const = 0;	// MANY PURE VIRTUAL
	virtual const int* getDependentIndices() const = 0;	// SUCH ABSTRACT
	virtual const int getNumUpgrades() const = 0;	// VERY INHERITANCE

	// Anyways in all seriousness, this just to get the arrays from each derived class...

};

//p.s. ONLY I can do polymporhism like this! :D