#pragma once
#include "Virus.h"
class Ransomware :
    public Virus
{

public:
    void evolve(Upgrades*) override;
    void mutate(int);
    void miniGame();
};

