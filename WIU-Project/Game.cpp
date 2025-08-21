#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <iomanip>

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
    cyberSecurity = new CyberSecurity(maxCompany);
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
        
        companies[i] = new Company(companyNames[temp], (networkSize[temp] * 1000) + ((rand() % 500 + 1) - 250), securityLevel[temp] - ((rand() % 5 + 1) / 10.0f), maxCompany);
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
        //cyberSecurity->advanceCure(companies, *(player.getPlayerVirus()));
    }

    // update company infectivity
    int totalNoOfInfectedComputers = 0;
    int totalNetworkSize = 0;

    for (int i = 0; i < tickInterval; i++) {
        for (int j = 0; j < maxCompany;  j++) {
            companies[j]->update(companies);
            totalNoOfInfectedComputers += companies[j]->getNoOfInfectedComputers();
            totalNetworkSize += companies[j]->getNetworkSize();
        }
        currentTick++;
    }

    // update player chioces
    player.update(totalNoOfInfectedComputers, totalNetworkSize);
}

void Game::printInterface()
{
    system("cls ");
    for (int i = 0; i < maxCompany; i++) {
        std::cout << "-----------------------" << std::endl
            << i + 1 << ". " << companies[i]->getName() << std::endl
            << "Network Size: " << companies[i]->getNetworkSize() << std::endl
            << "Security Level: " << std::fixed << std::setprecision(1) << companies[i]->getSecurityLevel() << "/10" << std::endl
            << std::endl
            << "Infected: " << companies[i]->getNoOfInfectedComputers() << std::endl
            << "Percentage Infected: " << std::fixed << std::setprecision(2) << companies[i]->getInfectedStatus() * 100.0f << "%"
            << std::endl;
        std::cout << std::endl; 

        if (player.getPlayerVirus() != nullptr) {
            std::cout << "Debug (Advantage Count): " << companies[i]->getSecurityLevel() - player.getPlayerVirus()->getComplexity() << std::endl;
        }
    }
    cyberSecurity->displayStatus();
}

void Game::randomEventGenerator()
{
    eventTrigger = rand() % 100;
        if (eventTrigger >= 90)
        {
            //companyA = rand() % 50;
            //bool BNotA = false;
            //while (BNotA)
            //{
            //    companyB = rand() % 50;
            //    if (companyA != companyB)
            //    {
            //        BNotA = true;
            //    }
            //}
            
            // print out chosen companies chosen and their event
            //std::cout << companyNames[companyA] << " and " << companyNames[companyB] << randomEvents[rand() % 5] << std::endl;
            
            // add code to increase virus spread stuff here
        }
}
