#include "Ransomware.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>  
#include <random>     
#include <chrono>    

Ransomware::Ransomware() {
    name = "no name lol";
    speed = 2.f;
    complexity = 2.f;
    payload = 4.f;
    resilience = 3.f;
}

Ransomware::~Ransomware() {

}

void Ransomware::evolve(Upgrades* toUpgrade) {
    std::cout << "Speed to upgrade: " << (toUpgrade->getSpeed() + 0.5f) << std::endl
        << " Complexity to upgrade: " << toUpgrade->getComplexity() << std::endl
        << " Payload to upgrade" << toUpgrade->getPayload() << std::endl
        << " Resilience to upgrade" << toUpgrade->getResilience() << std::endl;

    speed += (toUpgrade->getSpeed() + 0.5f);
    complexity += toUpgrade->getComplexity();
    payload += toUpgrade->getPayload();
    resilience += toUpgrade->getResilience();
}

void Ransomware::miniGame(int& hackingPoints)
{
    std::default_random_engine rng(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));

    for (int i = 0; i < 3; i++)
    {
        system("cls");
        std::cout << "Mini Game:\n"
            << "Create a Ransomware note to convince victims to actually pay you.\n\n";

        std::cout << NoteBuilderHeader[i];

        // Create and shuffle index array
        int indices[3] = { 0, 1, 2 };
        std::shuffle(indices, indices + 3, rng);

        // Display shuffled options
        for (int j = 0; j < 3; j++)
        {
            std::cout << j + 1 << ". " << NoteBuilder[i][indices[j]] << std::endl;
        }

        int input;
        std::cout << "Choose option (1-3): ";
        do
        {
            std::cin >> input;

            if (input < 1 || input > 3)
            {
                std::cout << "Invalid option, please choose again\n";
            }
            else
            {
                option[i] = indices[input - 1];
                break;
            }
        } while (true);
    }

    int Points = NoteBuilderPoints[0][option[0]] + NoteBuilderPoints[1][option[1]] + NoteBuilderPoints[2][option[2]];
    std::cout << "Minimum points to win: 5\n"
        << "Your points: " << Points << std::endl;
    if (Points > 4)
    {
        std::cout << "You Win the mini game\n";
        hackingPoints += 20;
    }
    else
    {
        std::cout << "You Lose the mini game\n";
    }
}