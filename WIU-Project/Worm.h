#pragma once
#include "Virus.h"
class Worm :public Virus
{
public:
	void evolve(std::string upgrade) override;
	void applyEffect(Company& company);

	Worm();
	Worm(int speed, int stealth, int payload, int resilience);
	~Worm();
};

