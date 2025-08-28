#include "Ransomware.h"
#include <iostream>
#include <cstdlib>

Ransomware::Ransomware() {
    speed = 2; // 1 for slow 5 max
    complexity = 4; // 1 to 10
    payload = 5; // 1 to 10
    resilience = 3; //1 to 10
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

int Ransomware::miniGame()
{
    for (int i = 0; i < 3; i++)
    {
        system("cls");
        std::cout << "Mini Game:\n"
            << "Create a Randsomeware note to convince victims to actually pay you.\n\n";

        std::cout << NoteBuilderHeader[i]
            << "1. " << NoteBuilder[i][0] << std::endl
            << "2. " << NoteBuilder[i][1] << std::endl
            << "3. " << NoteBuilder[i][2] << std::endl
            << "Choose options (1-3): ";
        do
        {
            std::cin >> option[i];

            if (option[i] < 1 || option[i] > 3)
            {
                std::cout << "invalid option, please choose again)\n";
            }
            else
            {
                option[i] -= 1;
                break;
            }
        } while (true);
    }

    //points
    int Points = NoteBuilderPoints[0][option[0]] + NoteBuilderPoints[1][option[1]] + NoteBuilderPoints[2][option[2]];
    std::cout << "Minimum points to win: 5\n"
        << "Your points: " << Points << std::endl;
    if (Points > 4)
    {
        std::cout << "You Win the mini game\n";
        Points += 20;
    }
    else
    {
        std::cout << "You Lose the minigame\n";
    }
    return Points;
}

const std::string* Ransomware::getNameUpgrade() const {
    return nameUpgrade;                                                     // Wait just wondering, why need pointer?? I cannot run away from pointers :(
}

const float* Ransomware::getStatsUpgrades() const {
    return statsUpgrade;
}

const int* Ransomware::getDependentIndices() const {
    return dependentIndices;
}

const int Ransomware::getNumUpgrades() const {
    return NUM_UPGRADES;
}