#pragma once
#include "Virus.h"
class Trojan : public Virus {
private:
    void companyOperation();
    void companyFinancial();
    void companySales();
    void companyAccounting();
    void companyInfoTech();
    void companyHumanResource();

    void printDialog(std::string, std::string);

public:
    Trojan();
    ~Trojan();

    void evolve(Upgrades*);
    void miniGame(int hackingPoints);
};

