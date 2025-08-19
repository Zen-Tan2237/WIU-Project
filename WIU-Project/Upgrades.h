#pragma once
#include <iostream>
#include <string>

class Upgrades
{
private:
	std::string name;
	int speed;
	int complexity;
	int payload;
	int resilience;
public:
	std::string getName();
	int getSpeed();
	int getComplexity();
	int getPayload();
	int getResilience();

	Upgrades();
	Upgrades(std::string name, int speed, int stealth, int payload, int resilience);
	~Upgrades();
};

