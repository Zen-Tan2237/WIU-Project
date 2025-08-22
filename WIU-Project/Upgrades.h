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
	float cost;
	std::string desc;

public:
	std::string getName() const;
	float getSpeed() const;
	float getComplexity() const;
	float getPayload() const;
	float getResilience() const;
	float getCost() const;
	std::string getDesc() const;

	Upgrades();
	Upgrades(std::string name, std::string desc, float speed, float stealth, float payload, float resilience, float cost);
	~Upgrades();
};

