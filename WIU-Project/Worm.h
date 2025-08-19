#pragma once
#include "Virus.h"
class Worm :public Virus
{
public:
	void evolve(std::string upgrade) override;
	void applyEffect(Company& company);
	void displayStats() const override;

	Worm();
	Worm(int speed, int stealth, int payload, int resilience);
	~Worm();
};

