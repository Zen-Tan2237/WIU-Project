#pragma once
#include "Virus.h"
class Worm : public Virus
{
public:

	Worm();
	Worm(int speed, int stealth, int payload, int resilience);
	~Worm();
};

