#pragma once
#include "Virus.h"
#include <vector>

class Trojan : public Virus {
private:
    void nMConvention_Ops(std::string**);
    void nMConvention_Fin(std::string**);
    void nMConvention_Sales(std::string**);
    void nMConvention_Acct(std::string**);
    void nMConvention_IT(std::string**);
    void nMConvention_HR(std::string**);

    void winConditions(int, int, int, int*);
    int conditionOffset(int, int&);
    void printDialog(std::string, std::string&, std::string&, std::string&, std::string&, std::string&);
    void printSynSectNm(int);
    void minigameOptions_2d(int, int, int, std::string**, std::vector<std::string>[]);
    void minigameOptions_1d(int, int, std::string*, std::vector<std::string>[]);
    bool playerInput(char*);

public:
    Trojan();
    ~Trojan();

    void evolve(Upgrades*);
    void miniGame(int& hackingPoints);
};