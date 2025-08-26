#pragma once
#include "Virus.h"
#include <vector>

class Trojan : public Virus {
private:
    bool companyOperation(int, std::string*);
    bool companyFinancial(int, std::string*);
    bool companySales(int, std::string*);
    bool companyAccounting(int, std::string*);
    bool companyInfoTech(int, std::string*);
    bool companyHumanResource(int, std::string*);

    std::string itemsOps();
    std::string itemsfin();
    std::string itemsSales();
    std::string itemsAcct();
    std::string itemsIT();
    std::string itemsHR();
    bool miniGameBody();


    int* winConditions(int, int, int, int*);
    int conditionOffset(int, int&);
    void printDialog(std::string, std::string&, std::string&, std::string&, std::string&, std::string&);
    void printSynSectNm(int);
    void minigameOptions_2d(int, int, int&, std::string [][4], std::vector<std::string> []);
    void minigameOptions_1d(int, int, int&, std::string*, std::vector<std::string> []);
    bool playerInput(char*);

public:
    Trojan();
    ~Trojan();

    void evolve(Upgrades*);
    void miniGame(int& hackingPoints);
};