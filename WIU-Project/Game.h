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

	std::string companyNames[50] = {
        // Tech
        "Microhard", "Pear", "Googol", "Amazin", "FaceLook",
        "Twiddler", "Netflicks", "SnapCat", "TickTock", "DisCorded",

        // Hardware / Electronics
        "Samflung", "Sonii", "Dellusional", "Lenova", "Asuspect",
        "HPee", "Acern’t", "Intell", "AMDazed", "Nvidiugh",

        // Food & Drink
        "MacRonalds", "Bugger King", "PizzHut", "KFG", "Starbucksie",
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
        9, 9, 10, 10, 10,
        8, 8, 7, 7, 7,

        // Hardware / Electronics
        9, 8, 6, 7, 7,
        7, 6, 9, 8, 9,

        // Food & Drink
        10, 8, 7, 9, 9,
        8, 7, 7, 8, 7,

        // Auto / Transport
        9, 8, 8, 9, 9,
        9, 8, 8, 7, 7,

        // Finance / Retail
        10, 9, 8, 9, 9,
        9, 9, 8, 8, 9
    };

	Player player;                      // the hacker/player
	Company* companies[5];     // list of all target companies

	Game();
	~Game();

	void initGame();

	int getCurrentTick() const; // Getter
	void setCurrentTick(int tickInterval); // Setter

    void doTurn();
    void printInterface();
};

