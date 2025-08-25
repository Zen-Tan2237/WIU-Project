#pragma once
#include "Virus.h"
class Ransomware :
    public Virus
{

public:
    Ransomware();
    ~Ransomware();

    void evolve(Upgrades*) override;
    void miniGame(int hackingPoints);
};

