#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

#include "Game.h"

Game::Game()
{
    currentTick = 0;
    tickInterval = 10; // 10 = 1 day
    isGameRunning = true;

    for (int i = 0; i < maxCompany; i++) {
        companies[i] = nullptr;
    }

    std::cout << "Game instantiated" << std::endl;
}

Game::~Game()
{
    std::cout << "Game destroyed" << std::endl;
}

void Game::initGame()
{
    
    int temp;
    for (int i = 0; i < maxCompany; i++) {
        do {
            temp = rand() % 50;
        } while (companyNames[temp] == "none");
        
        companies[i] = new Company(companyNames[temp], (networkSize[temp] * 1000) + ((rand() % 501) - 250), securityLevel[temp] + (rand() % 11) / 10 - 0.5f);
        companyNames[temp] = "none";
        std::cout << "yes" << std::endl;
    }
}

int Game::getCurrentTick() const
{
    return this->currentTick;
}

void Game::setCurrentTick(int tickInterval)
{
    this->currentTick += tickInterval;
}

void Game::doTurn()
{
    // starting
    if (currentTick == 0) {
        player.setMaxCompany(maxCompany);
        player.setInitials(companies);

        for (int j = 0; j < maxCompany; j++) {
            companies[j]->setVirus(player.getPlayerVirus());
        }
    }

    // update company infectivity
    for (int i = 0; i < tickInterval; i++) {
        for (int j = 0; j < maxCompany;  j++) {
            companies[j]->update();
        }
        currentTick++;
    }

    // update player chioces
    player.update();
}

void Game::printInterface()
{
    for (int i = 0; i < maxCompany; i++) {
        std::cout << i + 1 << ". " << companies[i]->getName() << std::endl
            << "Network Size: " << companies[i]->getNetworkSize() << std::endl
            << "Infected: " << companies[i]->getNoOfInfectedComputers() << std::endl
            << std::endl;
        std::cout << std::endl;
    }
}

void Game::randomEvent()
{
        
}
