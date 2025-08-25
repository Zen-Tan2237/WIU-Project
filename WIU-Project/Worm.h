#pragma once
#include "Virus.h"
#include "Upgrades.h"

class Worm : public Virus
{
public:

	Worm();
	~Worm();

	void evolve(Upgrades*) override;
	void miniGame(int &hackingPoints);

};

