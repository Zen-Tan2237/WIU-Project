#pragma once
#include "Virus.h"
class Trojan :
    public Virus
{
public:
    void evolve(Upgrades*);
    void mutate(int);
    void miniGame();
};

