#pragma once
#include "Virus.h"
#include "Upgrades.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
class Worm : public Virus
{
public:

	Worm();
	~Worm();

	void evolve(Upgrades*) override;
	void miniGame(int &hackingPoints);

};

