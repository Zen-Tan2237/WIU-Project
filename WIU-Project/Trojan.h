#pragma once
#include "Virus.h"
class Trojan :
    public Virus
{
public:
    Trojan();
    ~Trojan();

    void evolve(Upgrades*);
    void mutate(int** upgradesArray, int* currentUpgradesIndexs);
    void miniGame(int hackingPoints);
};

