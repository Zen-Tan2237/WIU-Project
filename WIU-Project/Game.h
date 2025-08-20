#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

#include "Company.h"
#include "Player.h"

class Game
{
private:
	int currentTick;
	int tickInterval;
	bool isGameRunning;
	int maxCompany = 5;
    int companyA;
    int companyB;

	std::string companyNames[50] = {
        // Tech
        "Dihhard", "Pear", "Googly", "Amazin", "FaceLock",
        "Twaddler", "Netflicks", "SnapChan", "TockTock", "DisCunt",

        // Hardware / Electronics
        "Samflung", "Sonii", "Dellusional", "Lenova", "Asuspect",
        "HPee", "Acern’t", "Intell", "AMDazed", "Nvidiugh",

        // Food & Beverage
        "MacRonalds", "Bugger King", "PieHut", "KFG", "Starbucksie",
        "Dunkin’ Dullnuts", "Substandard", "Taco Hell", "Dominosh", "Wendooz",

        // Auto / Transport
        "Totoya", "Hondumb", "Forrrd", "Teslow", "BMDoubleU",
        "Merceduhs", "Volkswagoned", "Hyundie", "Uberrr", "Lyfted",

        // Finance / Retail
        "Walmutt", "Targeted", "CosLow", "PayBuddy", "Veesa",
        "MasturdCard", "Amexed", "Chased", "CitiNot", "AliBlaba"
    };

    int networkSize[50] = {
        // Tech
        10, 10, 10, 9, 7,
        6, 4, 5, 3, 3,

        // Hardware / Electronics
        9, 8, 6, 7, 7,
        7, 4, 3, 3, 2,

        // Food & Beverage
        10, 8, 7, 9, 9,
        8, 7, 5, 3, 1,

        // Auto / Transport
        9, 8, 8, 9, 7,
        6, 6, 5, 3, 3,

        // Finance / Retail
        10, 10, 9, 7, 6,
        6, 4, 3, 2, 5
    };

    float securityLevel[50] = {
        // Tech
        10, 10, 10, 8, 7,
        4, 2, 5, 7, 1,

        // Hardware / Electronics
        9, 9, 1, 5, 7,
        3, 3, 6, 8, 9,

        // Food & Beverage
        6, 6, 5, 7, 1,
        5, 6, 7, 3, 1,

        // Auto / Transport
        8, 7, 4, 7, 4,
        7, 5, 7, 1, 1,

        // Finance / Retail
        5, 5 ,3, 7, 10,
        10, 8, 5, 8,
    };

    //std::string randomEvents[5]{
    //    "is having a international collaboration to learn from each other",

    //};

	Player player;                      // the hacker/player
	Company* companies[5];     // list of all target companies

public:
	Game();
	~Game();

	void initGame();

	int getCurrentTick() const; // Getter
	void setCurrentTick(int tickInterval); // Setter

    void doTurn();
    void printInterface();
    void randomEvent();
    void randomEventCompanyGenerator();
};

