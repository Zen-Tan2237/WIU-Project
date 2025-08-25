#include "Ransomware.h"
#include <iostream>
#include <cstdlib>

Ransomware::Ransomware() {

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
    std::cout << "Minimum points to win: 4\n"
        << "Your points: " << Points << std::endl;
    if (Points > 3)
    {
        std::cout << "You Win the mini game\n";
    }
    else
    {
        std::cout << "You Lose the minigame\n";
    }
}