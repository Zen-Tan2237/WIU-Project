#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <iomanip>
#include <vector>
#include <random>
#include "algorithm"

#include "Game.h"

Game::Game()
{
    currentTick = 0;
    tickInterval = 10; // 10 = 1 day
    isGameRunning = true;
    
    newZ = nullptr;
    companyA = NULL;
    companyB = NULL;

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
        
        companies[i] = new Company(companyNames[temp], (networkSize[temp] * 1000) + ((rand() % 500 + 1) - 250), securityLevel[temp] - ((rand() % 5 + 1) / 10.0f), maxCompany, i);
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
        newZ = new News(player.getPlayerVirus()->getName());
        for (int j = 0; j < maxCompany; j++) {
            companies[j]->setVirus(player.getPlayerVirus());
        }
    }

    if (currentTick % 50 == 0)
    {
        int eventTrigger = rand() % 100;
        if (eventTrigger >= 80)
        {
            randomCollabGenerator();
        }
    }

    // update company infectivity
    for (int i = 0; i < tickInterval; i++) {
        for (int j = 0; j < maxCompany;  j++) {
            companies[j]->update(companies);
            player.getPlayerVirus()->mutate(player.getDependencyChain(), player.getCurrentUpgradeIndices());
        }
        cyberSecurity->advanceCure(companies, *(player.getPlayerVirus()));
        currentTick++;
    }

    Company::getTotalStuff();

    // update player chioces
    player.update(Company::getTotalNoOfInfectedComputers(), Company::getTotalNetworkSize(), Company::getTotalNoOfBrickedComputers());

    CheckCompanyDead();
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
            << "Bricked: " << companies[i]->getNoOfBrickedComputers() << std::endl
            << "Percentage Infected: " << std::fixed << std::setprecision(2) << companies[i]->getInfectedStatus() * 100.0f << "%" << std::endl
            << "Percentage Bricked: " << std::fixed << std::setprecision(2) << companies[i]->getBrickedStatus() * 100.0f << "%"
            << std::endl;
        std::cout << std::endl; 

        if (player.getPlayerVirus() != nullptr) {
            std::cout << "Debug (Advantage Count): " << companies[i]->getSecurityLevel() - player.getPlayerVirus()->getComplexity() << std::endl;
        }
    }
    cyberSecurity->displayStatus();
    std::cout << "Total Bricked: " << Company::getTotalNoOfBrickedComputers() << std::endl;
}

void Game::randomCollabGenerator()
{
    // check how many companies can collab
    std::vector<int> eligibleCompanies;
    for (int i = 0; i < 5; ++i)
    {
        if (companies[i]->getInfectedStatus() < 0.7f)
        {
           eligibleCompanies.push_back(i);
        }
    }

    // collabing only runs if 2 or more companies can collab
    if (eligibleCompanies.size() >= 2)
    {
        std::shuffle(eligibleCompanies.begin(), eligibleCompanies.end(), std::default_random_engine(static_cast<unsigned>(std::time(0))));
        int companyA = eligibleCompanies[0];
        int companyB = eligibleCompanies[1];

        // print out and set the finalised companies collabing spread
        newZ->companyCollabNews(companies[companyA]->getName(), companies[companyB]->getName());
        companies[companyA]->setCollabSpreadWeightIndex(rand() % 4 + 1, companyB);
        companies[companyB]->setCollabSpreadWeightIndex(rand() % 4 + 1, companyA);
    }
}

void Game::CheckCompanyDead()
{
    for (int i = 0; i < 5; i++)
    {
        if (companies[i]->getBrickedStatus() == 1)
        { 
            newZ->companyDeadNews(companies[i]->getName());
        }
    }
}

void Game::randomMutation()
{
    //player.getPlayerVirus()->mutate(rand() % 10);
}
