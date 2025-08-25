#pragma once
#include "Virus.h"
class Trojan :
    public Virus
{
public:
    Trojan();
    ~Trojan();

    void evolve(Upgrades*);
    void miniGame(int hackingPoints);
};

