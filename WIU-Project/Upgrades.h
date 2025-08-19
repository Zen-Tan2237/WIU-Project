#pragma once
#include <iostream>
#include <string>

class Upgrades
{
private:
	std::string name;
	int speed;
	int stealth;
	int payload;
	int resilience;
public:
	std::string getName();
	int getSpeed();
	int getStealth();
	int getPayload();
	int getResilience();

	Upgrades();
	Upgrades(std::string name, int speed, int stealth, int payload, int resilience);
	~Upgrades();
};

