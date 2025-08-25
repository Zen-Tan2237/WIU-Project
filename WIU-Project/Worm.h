#pragma once
#include "Virus.h"
#include "Upgrades.h"

class Worm : public Virus
{
public:

	Worm();
	~Worm();

	void mutate(int);
	void evolve(Upgrades*) override;
	void miniGame(int &hackingPoints);

};

