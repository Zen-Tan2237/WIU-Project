#pragma once
#include "Virus.h"
class Ransomware :
    public Virus
{

public:
    void evolve(Upgrades*) override;
    void mutate(int** upgradesArray, int* currentUpgradesIndex);
    void miniGame(int hackingPoints);
};

