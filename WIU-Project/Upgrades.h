#pragma once
#include <iostream>
#include <string>

class Upgrades
{
private:
	std::string name;
	float speed;
	float complexity;
	float payload;
	float resilience;
public:
	std::string getName();
	float getSpeed();
	float getComplexity();
	float getPayload();
	float getResilience();

	Upgrades();
	Upgrades(std::string name, float speed, float stealth, float payload, float resilience);
	~Upgrades();
};

