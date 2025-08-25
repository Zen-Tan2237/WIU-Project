#pragma once
#include "Virus.h"
class Trojan :
    public Virus
{
public:
    void evolve(Upgrades*);
    void mutate(int** upgradesArray, int* currentUpgradesIndexs);
    void miniGame(int hackingPoints);
};

