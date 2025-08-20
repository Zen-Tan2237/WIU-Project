#pragma once
#include "Virus.h"
class Worm : public Virus
{
public:

	Worm();
	Worm(float speed, float stealth, float payload, float resilience);
	~Worm();
};

