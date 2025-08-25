#pragma once
#include "Virus.h"
class Worm : public Virus
{
public:

	Worm();
	~Worm();

	void mutate(int);

};

