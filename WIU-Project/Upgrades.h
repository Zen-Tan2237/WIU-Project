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
	std::string desc;

public:
	std::string getName();
	float getSpeed();
	float getComplexity();
	float getPayload();
	float getResilience();
	std::string getDesc();

	Upgrades();
	Upgrades(std::string name, std::string desc, float speed, float stealth, float payload, float resilience);
	~Upgrades();
};

