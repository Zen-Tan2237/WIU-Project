#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <iomanip>
#include <vector>
#include <random>
#include <fstream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <conio.h>
#include <cctype>

#include "algorithm"

#include "Game.h"
#include "SoundController.h"

Game::Game()
{
    currentTick = 0;
    tickInterval = 10; // 10 = 1 day
    isGameRunning = true;
    gameResult = 0;
    
    newZ = nullptr;
    companyA = NULL;
    companyB = NULL;

    for (int i = 0; i < maxCompany; i++) {
        companies[i] = nullptr;
    }

    std::cout << "Game instantiated" << std::endl;
    cyberSecurity = new CyberSecurity(maxCompany);

    screenIndex = 0;
    previousScreenIndex = -1;
    character = -1;
    selectedUIButton = 0;
    maxSelectedUIButtonOffset = 0;
    minSelectedUIButtonOffset = 0;
    navigationType = 0;
    isNamingVirus = false;
    isChoosingVirusType = false;
    isChoosingCompanyStart = false;
    virusName = "";
    virusTypeIndex = 0;
    gameplayButtonChosenIndex = 0;
    companyStartIndex = 0;
    refreshNow = false;
    consoleWidth = 0;
    previousConsoleWidth = 0;
    completedNews = 0;
    oldUniqueCompaniesInfected = 0;
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
        

    /*element_barFilled = "\xE2\x96\x84";
    element_barUnfilled = "-";*/

    emptyChickenFrames = loadFrames("emptyChickenFrames.txt");

    frame_Logo = loadFrames("Logo.txt");
    frame_LogoInteractToStart1 = loadFrames("LogoInteractToStart1.txt");
    frame_LogoInteractToStart2 = loadFrames("LogoInteractToStart2.txt");

    frame_Screen2DialoguePt1 = loadFrames("Screen2DialoguePt1.txt");
    frame_Screen2DialoguePt2 = loadFrames("Screen2DialoguePt2.txt");
    frame_Screen2DialoguePt3 = loadFrames("Screen2DialoguePt3.txt");
    frame_Screen7DialogueNews = loadFrames("Screen7DialogueNews.txt");

    frame_Screen3Welcome = loadFrames("Screen3Welcome.txt");

    frame_Screen3NameVirus = loadFrames("Screen3NameVirus.txt");

    frame_Screen3VirusType = loadFrames("Screen3VirusType.txt");
    frame_Screen3VirusType1 = loadFrames("Screen3VirusType1.txt");
    frame_Screen3VirusType2 = loadFrames("Screen3VirusType2.txt");

    frame_Screen3CompanyStart = loadFrames("Screen3CompanyStart.txt");
    frame_Screen3CompanyStart1 = loadFrames("Screen3CompanyStart1.txt");
    frame_Screen3CompanyStart2 = loadFrames("Screen3CompanyStart2.txt");

    frame_Screen4GameplayUI1 = loadFrames("Screen4GameplayUI1.txt");
    frame_Screen4GameplayUI2 = loadFrames("Screen4GameplayUI2.txt");
    frame_Screen4GameplayUI3 = loadFrames("Screen4GameplayUI3.txt");
    frame_Screen4GameplayUI4 = loadFrames("Screen4GameplayUI4.txt");
    frame_Screen4GameplayUIEnd = loadFrames("Screen4GameplayUIEnd.txt");

    frame_Screen5BuildingBottom = loadFrames("Screen5BuildingBottom.txt");
    frame_Screen5BuildingCenterClone = loadFrames("Screen5BuildingCenterClone.txt");
    frame_Screen5BuildingTop = loadFrames("Screen5BuildingTop.txt");
}

int Game::getCurrentTick() const
{
    return this->currentTick;
}

void Game::setCurrentTick(int tickInterval)
{
    this->currentTick += tickInterval;
}

int Game::getCurrentScreen() const
{
    return screenIndex;
}

void Game::doTurn()
{
    while (isGameRunning) {
        if (screenIndex == 4) {
            // starting
            if (currentTick == 0) {
                player.setMaxCompany(maxCompany);
                // player.setInitials(companies);
                newZ = new News(player.getPlayerVirus()->getName());
                for (int j = 0; j < maxCompany; j++) {
                    companies[j]->setVirus(player.getPlayerVirus());
                }
            }

            // update company infectivity
            for (int i = 0; i < tickInterval; i++) {
                for (int j = 0; j < maxCompany; j++) {
                    companies[j]->update(companies);
                }
                cyberSecurity->advanceCure(companies, *(player.getPlayerVirus()));
                cyberSecurity->triggerEvent(companies, *(player.getPlayerVirus()));

                currentTick++;
            }

            // all the news stuff
            if (currentTick % 400 == 0)
            {
                int eventTrigger = rand() % 100;
                if (eventTrigger >= 60)
                {
                    randomCollabGenerator();
                }
            }

            CheckCompanyDead();

            for (int i = 0; i < maxCompany + 4; i++) {
                if (cyberSecurity->getNewsDetectDone_bool(i) && i < maxCompany) {
                    newZ->virusFoundNews(cyberSecurity->getNewsIndex(i), companies[cyberSecurity->getNewsDetectDone_int(i)]->getName(), player.getPlayerVirus()->getName());
                    cyberSecurity->setNewsDetectDone(0, i);
                    newsInADay_Head.push_back(newZ->getHEAD());
                    newsInADay_Body.push_back(newZ->getBODY());
                    newsInADay_Effects.push_back(newZ->getEFFECTS());
                }
                else if (i == maxCompany) {
                    newZ->cybersecurityWinningNews(cyberSecurity->getNewsIndex(i), player.getPlayerVirus()->getName());
                    newsInADay_Head.push_back(newZ->getHEAD());
                    newsInADay_Body.push_back(newZ->getBODY());
                    newsInADay_Effects.push_back(newZ->getEFFECTS());
                }
                else if (i == maxCompany + 1) {
                    newZ->cyberSecurityLosingNews(cyberSecurity->getNewsIndex(i), player.getPlayerVirus()->getName());
                    newsInADay_Head.push_back(newZ->getHEAD());
                    newsInADay_Body.push_back(newZ->getBODY());
                    newsInADay_Effects.push_back(newZ->getEFFECTS());
                }
                else if (i == maxCompany + 2) {
                    newZ->PlayerWinNews(cyberSecurity->getNewsIndex(i));
                    newsInADay_Head.push_back(newZ->getHEAD());
                    newsInADay_Body.push_back(newZ->getBODY());
                    newsInADay_Effects.push_back(newZ->getEFFECTS());
                }
                else if (i == maxCompany + 3) {
                    newZ->PlayerLoseNews(cyberSecurity->getNewsIndex(i));
                    newsInADay_Head.push_back(newZ->getHEAD());
                    newsInADay_Body.push_back(newZ->getBODY());
                    newsInADay_Effects.push_back(newZ->getEFFECTS());
                }
            }

            //for (int i = 0; i < maxCompany + 4; i++) {
            //    int idx = cyberSecurity->getNewsIndex(i);
            //    if (idx == -1) continue; // no news for this slot

            //    if (i < maxCompany) {
            //        // virus found for company i
            //        newZ->virusFoundNews(idx, companies[i]->getName(), virusName);
            //    }
            //    else if (i == maxCompany) {
            //        // cyber-security milestone (cure progress)
            //        newZ->cybersecurityWinningNews(idx, virusName);
            //    }
            //    else if (i == maxCompany + 1) {
            //        // cyber-security losing milestone (infection thresholds)
            //        newZ->cyberSecurityLosingNews(idx, virusName);
            //    }
            //    else if (i == maxCompany + 2) {
            //        // player win (all bricked was used as push condition in CyberSecurity)
            //        newZ->PlayerWinNews(idx);
            //    }
            //    else { //i == maxCompany + 3
            //        // player lose
            //        newZ->PlayerLoseNews(idx);
            //    }

            //    newsInADay_Head.push_back(newZ->getHEAD());
            //    newsInADay_Body.push_back(newZ->getBODY());
            //    newsInADay_Effects.push_back(newZ->getEFFECTS());
            //}

            // ok

            // update player chioces
            player.update(Company::getTotalNoOfInfectedComputers(), Company::getTotalNetworkSize(), Company::getTotalNoOfBrickedComputers());

            // results
            if (cyberSecurity->isCureComplete()) {
                int temp = rand() % 2;
                newZ->PlayerLoseNews(temp);
                newsInADay_Head.push_back(newZ->getHEAD());
                newsInADay_Body.push_back(newZ->getBODY());
                newsInADay_Effects.push_back(newZ->getEFFECTS());

                gameResult = 1; // lost (cure found)
                screenIndex = 8; 
            }
            else if (Company::getTotalUniqueCompanyInfections() != oldUniqueCompaniesInfected) {
                screenIndex = 9;
            }
            else if (Company::getTotalNoOfBrickedComputers() == Company::getTotalNetworkSize()) {
                int temp = rand() % 2;
                newZ->PlayerWinNews(temp);
                newsInADay_Head.push_back(newZ->getHEAD());
                newsInADay_Body.push_back(newZ->getBODY());
                newsInADay_Effects.push_back(newZ->getEFFECTS());

                gameResult = 2; // won (yes)
                screenIndex = 8;
            }

            else if (newsInADay_Head.size() - completedNews > 0) {
                screenIndex = 7;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
}

void Game::printInterface()
{
    while (isGameRunning) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        //system("cls ");
        //for (int i = 0; i < maxCompany; i++) {
        //    std::cout << "-----------------------" << std::endl
        //        << i + 1 << ". " << companies[i]->getName() << std::endl
        //        << "Network Size: " << companies[i]->getNetworkSize() << std::endl
        //        << "Security Level: " << std::fixed << std::setprecision(1) << companies[i]->getSecurityLevel() << "/10" << std::endl
        //        << std::endl
        //        << "Infected: " << companies[i]->getNoOfInfectedComputers() << std::endl
        //        << "Bricked: " << companies[i]->getNoOfBrickedComputers() << std::endl
        //        << "Percentage Infected: " << std::fixed << std::setprecision(2) << companies[i]->getInfectedStatus() * 100.0f << "%" << std::endl
        //        << "Percentage Bricked: " << std::fixed << std::setprecision(2) << companies[i]->getBrickedStatus() * 100.0f << "%"
        //        << std::endl;
        //    std::cout << std::endl; 

        //    if (player.getPlayerVirus() != nullptr) {
        //        std::cout << "Debug (Advantage Count): " << companies[i]->getSecurityLevel() - player.getPlayerVirus()->getComplexity() << std::endl;
        //    }
        //}
        //cyberSecurity->displayStatus();
        //std::cout << "Total Bricked: " << Company::getTotalNoOfBrickedComputers() << std::endl;

        std::string screenIndex2_dialogues[3] = {
            "In a world dominated by towering corporations, one individual found themselves suffocated by the endless cycle of consumerism and corporate greed. Day after day, they toiled away in a job that felt more like servitude than work, watching as companies prioritized profit over people. The frustration grew, a quiet storm brewing inside, fueled by the injustice of a system that seemed designed to exploit rather than empower.",
            "One evening, overwhelmed by the weight of their dissatisfaction, they dreamed of a different kind of revolution, not one of destruction, but of transformation. Instead of fighting fire with fire, they envisioned a way to undermine the corporate giants through creativity and innovation, exposing the flaws in their systems and inspiring people to demand better. Their plan was to harness technology and art to awaken society to the power they held as consumers, turning frustration into a force for change.",
            "With renewed purpose, they set out to create tools and platforms that challenged the status quo, encouraging transparency and fairness. Their rebellion was not one of chaos, but a movement of hope that sought to rebuild a world where companies served the people, not the other way around."
        };

        int gap = 10;
        int typingInterval = 25;
        int longestCompanyValue = 0;
        int longestgetInfectedStatus = 0;
        int fraction;
        int iBricked;
        int iInfected;
        int resultingPoints;
        int yes;
        std::string interactToStartContent = "[ HOLD <SPACE> TO START ]";

        if (consoleWidth > 155) {
            resetUIButtonSelection();
            previousScreenIndex = screenIndex;

            switch (screenIndex) {
            case 0:
                SetConsoleOutputCP(CP_UTF8);

                // Title Screen
                renderAnimation(frame_Logo, 5, false, true, true);
                //virusName = "yes";
                //virusTypeIndex = 1;
                //companyStartIndex = 0;
                screenIndex = 1;
                //player.setInitials(companies, virusTypeIndex + 1, companyStartIndex + 1, virusName);

                break;

            case 1: // intro screen
                while (screenIndex == 1) {
                    if (interactToStartContent == "[ HOLD <SPACE> TO START ]") {
                        renderAnimation(frame_LogoInteractToStart1, 3, false, false, true);

                        if (155 - interactToStartContent.length() > 1) {
                            std::cout << std::string(floor((consoleWidth - 155) / 2), ' ') << std::string(floor((155 - interactToStartContent.length()) / 2), '.');
                            highlightSelectedUIButton(0, interactToStartContent, hConsole);
                            std::cout << std::string(ceil((155 - interactToStartContent.length()) / 2), '.') << std::endl;
                        }
                        else {
                            std::cout << std::string(floor((consoleWidth - 155) / 2), ' ') << std::string(floor((155 - interactToStartContent.length()) / 2), '.');
                            highlightSelectedUIButton(0, interactToStartContent, hConsole);
                            std::cout << std::string(ceil((155 - interactToStartContent.length()) / 2), '.') << std::endl;
                        }
                        renderAnimation(frame_LogoInteractToStart2, 0, true, true, true);
                        interactToStartContent = "";
                    }
                    else {
                        renderAnimation(frame_LogoInteractToStart1, 0, false, false, true);

                        std::cout << std::string(floor((consoleWidth - 155) / 2), ' ') << std::string(155, '.') << std::endl;

                        renderAnimation(frame_LogoInteractToStart2, 0, true, true, true);

                        interactToStartContent = "[ HOLD <SPACE> TO START ]";
                    }

                    for (int i = 0; i < 50; i++) {
                        if (screenIndex != 1) {
                            break;
                        }

                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    }
                }

                break;

            case 2: // dialogue screen
                while (screenIndex == 2) {
                    system("cls ");
                    for (int i = 0; i < sizeof(screenIndex2_dialogues) / sizeof(screenIndex2_dialogues[0]); i++) {
                        switch (i) {
                        case 0:
                            typingEntrance("BACKSTORY", screenIndex2_dialogues[i], "", typingInterval, true, frame_Screen2DialoguePt1);
                            break;

                        case 1:
                            typingEntrance("BACKSTORY", screenIndex2_dialogues[i], "", typingInterval, true, frame_Screen2DialoguePt2);
                            break;

                        case 2:
                            typingEntrance("BACKSTORY", screenIndex2_dialogues[i], "", typingInterval, true, frame_Screen2DialoguePt3);
                            break;

                        default:
                            typingEntrance("BACKSTORY", screenIndex2_dialogues[i], "", typingInterval, true, emptyChickenFrames);
                            break;
                        }

                        resetInputHandler();
                        while (character != ' ') {
                            continue;
                        }
                        resetInputHandler();
                    }

                    screenIndex = 3;
                }
                break;
            case 3: // selection and welcome screen
                while (screenIndex == 3) {
                    system("cls ");
                    renderAnimation(frame_Screen3Welcome, 0, false, true, true);

                    renderAnimation(frame_Screen3NameVirus, 2, false, true, true); // ask for name of virus
                    isNamingVirus = true;

                    while (isNamingVirus) {
                        if (virusName != "") { // wait until something is inputted
                            system("cls");
                            renderAnimation(emptyChickenFrames, 0, false, false, true);
                            std::cout << std::string(floor((consoleWidth - 155) / 2), ' ') << std::string(floor((155 - virusName.length()) / 2), '.');
                            highlightSelectedUIButton(0, virusName, hConsole);
                            std::cout << std::string(ceil((155 - virusName.length()) / 2), '.') << std::endl;
                            renderAnimation(emptyChickenFrames, 0, true, true, true);
                            resetInputHandler();
                        }

                        delayBeforeRefresh(previousScreenIndex);
                    }

                    system("cls ");
                    renderAnimation(frame_Screen3VirusType, 0, false, true, true);
                    isChoosingVirusType = true;

                    system("cls");
                    renderAnimation(frame_Screen3VirusType1, 0, false, false, true); // ask for type of virus
                    renderCenteringSpaces();
                    std::cout << std::string(floor((155 - 32) / 2), '.');
                    highlightSelectedUIButton(0, "[ WORM ]", hConsole);
                    highlightSelectedUIButton(1, "[ TROJAN ]", hConsole);
                    highlightSelectedUIButton(2, "[ RANSOMWARE ]", hConsole);
                    std::cout << std::string(ceil((155 - 32) / 2), '.');
                    std::cout << std::endl;
                    renderAnimation(frame_Screen3VirusType2, 0, true, true, true);
                    resetInputHandler();

                    while (isChoosingVirusType) {
                        if (character != -1) {
                            system("cls");
                            renderAnimation(frame_Screen3VirusType1, 0, false, false, true); // ask for type of virus
                            renderCenteringSpaces();
                            std::cout << std::string(floor((155 - 32) / 2), '.');
                            highlightSelectedUIButton(0, "[ WORM ]", hConsole);
                            highlightSelectedUIButton(1, "[ TROJAN ]", hConsole);
                            highlightSelectedUIButton(2, "[ RANSOMWARE ]", hConsole);
                            std::cout << std::string(ceil((155 - 32) / 2), '.');
                            std::cout << std::endl;
                            renderAnimation(frame_Screen3VirusType2, 0, true, true, true);
                            resetInputHandler();
                        }

                        delayBeforeRefresh(previousScreenIndex);
                    }

                    system("cls ");
                    renderAnimation(frame_Screen3CompanyStart, 0, false, true, true);
                    isChoosingCompanyStart = true;
                    maxSelectedUIButtonOffset = maxCompany - 1;

                    system("cls");
                    renderAnimation(frame_Screen3CompanyStart1, 2, false, false, true); // ask for type of virus
                    renderCenteringSpaces();

                    int temp = 0;
                    for (int i = 0; i < maxCompany; i++) {
                        temp += (4 + companies[i]->getName().length());
                    }

                    if (temp <= 155) {
                        std::cout << std::string(floor((155 - temp) / 2), '.');
                    }
                    else {
                        std::cout << std::string(1, '.');
                    }

                    for (int i = 0; i < maxCompany; i++) {
                        std::string yes = "[ " + companies[i]->getName() + " ]";
                        highlightSelectedUIButton(i, yes, hConsole);
                    }

                    if (temp <= 155) {
                        std::cout << std::string(floor((155 - temp) / 2), '.');
                    }
                    else {
                        std::cout << std::string(1, '.');
                    }

                    std::cout << std::endl;
                    renderAnimation(frame_Screen3CompanyStart2, 0, true, true, true);
                    resetInputHandler();

                    while (isChoosingCompanyStart) {
                        if (character != -1) {
                            system("cls");
                            renderAnimation(frame_Screen3CompanyStart1, 0, false, false, true); // ask for type of virus
                            renderCenteringSpaces();

                            int temp = 0;
                            for (int i = 0; i < maxCompany; i++) {
                                temp += (4 + companies[i]->getName().length());
                            }

                            if (temp <= 155) {
                                std::cout << std::string(floor((155 - temp) / 2), '.');
                            }
                            else {
                                std::cout << std::string(1, '.');
                            }

                            for (int i = 0; i < maxCompany; i++) {
                                std::string yes = "[ " + companies[i]->getName() + " ]";
                                highlightSelectedUIButton(i, yes, hConsole);
                            }

                            if (temp <= 155) {
                                std::cout << std::string(floor((155 - temp) / 2), '.');
                            }
                            else {
                                std::cout << std::string(1, '.');
                            }

                            std::cout << std::endl;
                            renderAnimation(frame_Screen3CompanyStart2, 0, true, true, true);
                            resetInputHandler();
                        }

                        delayBeforeRefresh(previousScreenIndex);
                    }

                    screenIndex = 4;
                }
                break;
            case 4:
                gameplayButtonChosenIndex = 0;

                while (screenIndex == 4) {
                    // pt1 (auto)
                    renderAnimation(frame_Screen4GameplayUI1, 0, false, false, true);

                    // pt2 (manual)
                    renderCenteringSpaces();
                    std::cout << ". Session : corporate_scan/001/" << player.getPlayerVirus()->getName()
                        << std::string(48 - player.getPlayerVirus()->getName().length(), ' ')
                        << ".                                                                          ."
                        << std::endl;

                    // pt3.1 (manual)
                    renderCenteringSpaces();
                    std::cout << ".                                                                              . Complexity : " << std::string(10 - 10, ' ');

                    for (int yes = 1; yes < 11; yes++) {
                        //renderAnimation(element_barFilled, 0, true, false, false);
                        if (yes == (int)player.getPlayerVirus()->getComplexity()) {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        }
                        else {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        }

                        if (abs((int)player.getPlayerVirus()->getComplexity() - yes) > 5) {
                            std::cout << element_bars[6];
                        }
                        else {
                            std::cout << element_bars[abs((int)player.getPlayerVirus()->getComplexity() - yes)];
                        }

                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    }

                    std::cout << " (" << player.getPlayerVirus()->getComplexity() << "/10)" << std::string(57 - (" (" + std::to_string(player.getPlayerVirus()->getComplexity()) + "/10)").length(), ' ') << "." << std::endl;

                    // pt3.2 (manual)
                    renderCenteringSpaces();

                    std::cout << ". Hacker Points : " << player.getHackingPoints()
                        << std::string(61 - std::to_string(player.getHackingPoints()).length(), ' ');

                    std::cout << ". Speed : " << std::string(10 - 5, ' ');

                    for (int yes = 1; yes < 11; yes++) {
                        //renderAnimation(element_barFilled, 0, true, false, false);
                        if (yes == (int)player.getPlayerVirus()->getSpeed()) {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        }
                        else {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        }

                        if (abs((int)player.getPlayerVirus()->getSpeed() - yes) > 5) {
                            std::cout << element_bars[6];
                        }
                        else {
                            std::cout << element_bars[abs((int)player.getPlayerVirus()->getSpeed() - yes)];
                        }

                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    }

                    std::cout << " (" << player.getPlayerVirus()->getSpeed() << "/10)" << std::string(57 - (" (" + std::to_string(player.getPlayerVirus()->getSpeed()) + "/10)").length(), ' ') << "." << std::endl;

                    // pt3.3 (manual)
                    renderCenteringSpaces();
                    std::cout << ".                                                                              . Payload : " << std::string(10 - 7, ' ');

                    for (int yes = 01; yes < 11; yes++) {
                        //renderAnimation(element_barFilled, 0, true, false, false);
                        if (yes == (int)player.getPlayerVirus()->getPayload()) {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        }
                        else {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        }

                        if (abs((int)player.getPlayerVirus()->getPayload() - yes) > 5) {
                            std::cout << element_bars[6];
                        }
                        else {
                            std::cout << element_bars[abs((int)player.getPlayerVirus()->getPayload() - yes)];
                        }

                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    }

                    std::cout << " (" << player.getPlayerVirus()->getPayload() << "/10)" << std::string(57 - (" (" + std::to_string(player.getPlayerVirus()->getPayload()) + "/10)").length(), ' ') << "." << std::endl;

                    // pt3.4 (manual)
                    renderCenteringSpaces();
                    std::cout << ".                                                                              . Resilience : " << std::string(10 - 10, ' ');

                    for (int yes = 1; yes < 11; yes++) {
                        //renderAnimation(element_barFilled, 0, true, false, false);
                        if (yes == (int)player.getPlayerVirus()->getResilience()) {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        }
                        else {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        }

                        if (abs((int)player.getPlayerVirus()->getResilience() - yes) > 5) {
                            std::cout << element_bars[6];
                        }
                        else {
                            std::cout << element_bars[abs((int)player.getPlayerVirus()->getResilience() - yes)];
                        }

                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    }

                    std::cout << " (" << player.getPlayerVirus()->getResilience() << "/10)" << std::string(57 - (" (" + std::to_string(player.getPlayerVirus()->getResilience()) + "/10)").length(), ' ') << "." << std::endl;

                    // upgrade button
                    renderCenteringSpaces();
                    std::cout << ".                                                                              .                                                                          ." << std::endl;
                    renderCenteringSpaces();
                    std::cout << ".                                                                              . ";
                    highlightSelectedUIButton(0, "[ EVOLVE ]", hConsole);
                    std::cout << "                                                               . " << std::endl;

                    // pt4 (auto)

                    renderAnimation(frame_Screen4GameplayUI2, 0, true, false, true);

                    // pt5 (manual)

                    int temp = 0;

                    for (int i = 0; i < maxCompany; i++) {
                        if (companies[i]->getName().length() > temp) {
                            temp = companies[i]->getName().length();
                        }
                    }

                    std::string tempWOW = ". Company" + std::string((temp + 2) - 7, ' ')
                        + "Status" + std::string((12 + 2) - 6, ' ')
                        + "No. Of Infected" + std::string(2 + 5, ' ')
                        + "No. Of Bricked" + std::string(2 + 5, ' ')
                        + "Network Size" + std::string(2 + 5, ' ');


                    renderCenteringSpaces();
                    std::cout << tempWOW << std::string(155 - (tempWOW.length() + 1), ' ') << "." << std::endl;

                    for (int i = 0; i < maxCompany; i++) {
                        std::string tempEvenMoreWOW = companies[i]->getName();
                        tempWOW = ". " + tempEvenMoreWOW + std::string((temp + 2) - tempEvenMoreWOW.length(), ' ');

                        // infected status
                        if (companies[i]->getInfectedStatus() == 0) {
                            tempEvenMoreWOW = "--SAFE--";

                        }
                        else if (companies[i]->getInfectedStatus() < 1) {
                            tempEvenMoreWOW = "~PARTIAL~";
                        }
                        else {
                            tempEvenMoreWOW = "!!INFECTED!!";
                        }
                        tempWOW = tempWOW + tempEvenMoreWOW + std::string((12 + 2) - tempEvenMoreWOW.length(), ' ');

                        // no of infected
                        int value = companies[i]->getInfectedStatus() * 100;
                        tempEvenMoreWOW = std::to_string(companies[i]->getNoOfInfectedComputers()) + " (" + std::to_string(value) + "%)";
                        tempWOW = tempWOW + tempEvenMoreWOW + std::string((2 + 5 + 15) - tempEvenMoreWOW.length(), ' ');

                        // no of bricked
                        value = companies[i]->getBrickedStatus() * 100;
                        tempEvenMoreWOW = std::to_string(companies[i]->getNoOfBrickedComputers()) + " (" + std::to_string(value) + "%)";
                        tempWOW = tempWOW + tempEvenMoreWOW + std::string((2 + 5 + 14) - tempEvenMoreWOW.length(), ' ');

                        // network size
                        tempEvenMoreWOW = std::to_string(companies[i]->getNetworkSize());
                        tempWOW = tempWOW + tempEvenMoreWOW + std::string((2 + 5 + 12) - tempEvenMoreWOW.length(), ' ');

                        renderCenteringSpaces();
                        std::cout << std::setprecision(2) << tempWOW;
                        highlightSelectedUIButton(i + 1, "[ VIEW ]", hConsole);
                        std::cout << std::string(155 - (tempWOW.length() + 1) - (8), ' ') << "." << std::endl;
                    }

                    // pt6 (auto)

                    renderAnimation(frame_Screen4GameplayUI3, 0, true, false, true);

                    // pt7 (manual)

                    tempWOW = ". Global" + std::string((temp + 2) - 6, ' ')
                        + "Status" + std::string((12 + 2) - 6, ' ')
                        + "No. Of Infected" + std::string(2 + 5, ' ')
                        + "No. Of Bricked" + std::string(2 + 5, ' ')
                        + "Network Size" + std::string(2 + 5, ' ');


                    renderCenteringSpaces();
                    std::cout << tempWOW << std::string(155 - (tempWOW.length() + 1), ' ') << "." << std::endl;

                    // gloabl status
                    std::string tempEvenMoreWOW = " ";
                    tempWOW = ". " + tempEvenMoreWOW + std::string((temp + 2) - tempEvenMoreWOW.length(), ' ');

                    // infected status
                    if (Company::getTotalNoOfInfectedComputers() == 0) {
                        tempEvenMoreWOW = "--SAFE--";

                    }
                    else if (Company::getTotalNoOfInfectedComputers() < Company::getTotalNetworkSize()) {
                        tempEvenMoreWOW = "~PARTIAL~";
                    }
                    else {
                        tempEvenMoreWOW = "!!INFECTED!!";
                    }
                    tempWOW = tempWOW + tempEvenMoreWOW + std::string((12 + 2) - tempEvenMoreWOW.length(), ' ');

                    // no of infected
                    int value = ((float)Company::getTotalNoOfInfectedComputers() / (float)Company::getTotalNetworkSize()) * 100;
                    tempEvenMoreWOW = std::to_string(Company::getTotalNoOfInfectedComputers()) + " (" + std::to_string(value) + "%)";
                    tempWOW = tempWOW + tempEvenMoreWOW + std::string((2 + 5 + 15) - tempEvenMoreWOW.length(), ' ');

                    // no of bricked
                    value = ((float)Company::getTotalNoOfBrickedComputers() / (float)Company::getTotalNetworkSize()) * 100;
                    tempEvenMoreWOW = std::to_string(Company::getTotalNoOfBrickedComputers()) + " (" + std::to_string(value) + "%)";
                    tempWOW = tempWOW + tempEvenMoreWOW + std::string((2 + 5 + 14) - tempEvenMoreWOW.length(), ' ');

                    // network size
                    tempEvenMoreWOW = std::to_string(Company::getTotalNetworkSize());
                    tempWOW = tempWOW + tempEvenMoreWOW + std::string((2 + 5 + 12) - tempEvenMoreWOW.length(), ' ');

                    renderCenteringSpaces();
                    std::cout << std::setprecision(2) << tempWOW;
                    std::cout << std::string(155 - (tempWOW.length() + 1), ' ') << "." << std::endl;

                    // pt 8 (auto)
                    renderAnimation(frame_Screen4GameplayUI4, 0, true, false, true);

                    // pt 9 (manual)
                    renderCenteringSpaces();
                    std::cout << ". ";
                    for (int yes = 1; yes < 101; yes++) {
                        //renderAnimation(element_barFilled, 0, true, false, false);
                        if (yes == (int)CyberSecurity::getGlobalCureProgress()) {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        }
                        else {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        }

                        if (abs((int)CyberSecurity::getGlobalCureProgress() - yes) > 5) {
                            std::cout << element_bars[6];
                        }
                        else {
                            std::cout << element_bars[abs((int)CyberSecurity::getGlobalCureProgress() - yes)];
                        }

                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    }

                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    std::cout << " (" << (int)CyberSecurity::getGlobalCureProgress() << "%)";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    std::cout << std::string(155 - (2 + 100 + 1 + (" (" + std::to_string((int)CyberSecurity::getGlobalCureProgress()) + "%)").length()), ' ') << "." << std::endl;

                    // pt end (auto)
                    renderAnimation(frame_Screen4GameplayUIEnd, 0, true, true, true);


                    //renderAnimation(frame_Screen4GameplayUI3, 0, true, false, true);

                    //renderCenteringSpaces();
                    //std::cout << ". " << newZ->getHEAD() << std::string(155 - (newZ->getHEAD().length() + 3), ' ') << "." << std::endl;
                    //std::cout << "." << std::string(155 - 2, ' ') << "." << std::endl;

                    //renderCenteringSpaces();

                    //for (int eachline = 0; eachline < ceil(newZ->getBODY().length() / (155 - 3)); eachline++) {
                    //    std::cout << ". " << newZ->getBODY() << std::string(155 - (newZ->getBODY().length() + 3), ' ') << "." << std::endl;
                    //}

                    delayBeforeRefresh(previousScreenIndex);
                }
                break;
            case 5:
                while (screenIndex == 5) {
                    system("cls");
                    yes = std::round(companies[gameplayButtonChosenIndex - 1]->getSecurityLevel()) + 2;
                    fraction = companies[gameplayButtonChosenIndex - 1]->getNetworkSize() / yes;
                    iBricked = 0;
                    iInfected = 0;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                    for (int i = yes; i > 0; i--) {
                        if (companies[gameplayButtonChosenIndex - 1]->getNoOfInfectedComputers() >= fraction * i) {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

                            if (iInfected == 0) {
                                iInfected = i;
                            }
                        }

                        if (companies[gameplayButtonChosenIndex - 1]->getNoOfBrickedComputers() >= fraction * i) {
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

                            if (iBricked == 0) {
                                iBricked = i;
                            }

                        }

                        if (i == yes) { // top
                            renderAnimation(frame_Screen5BuildingTop, 0, false, false, true);
                        }
                        else if (i > 1) { // center
                            renderAnimation(frame_Screen5BuildingCenterClone, 0, true, false, true);
                        }
                        else { // bottom
                            renderAnimation(frame_Screen5BuildingBottom, 0, true, false, true);
                        }

                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }

                    std::string title[7] = { "COMPANY", "NETWORK SIZE", "SECURITY LEVEL", "INFECTION STATUS", "VIRUS PLANTED", "AMOUNT INFECTED DATA", "AMOUNT BRICKED DATA" };
                    std::string content[7] = { companies[gameplayButtonChosenIndex - 1]->getName(),
                        std::to_string(companies[gameplayButtonChosenIndex - 1]->getNetworkSize()),
                        std::to_string(companies[gameplayButtonChosenIndex - 1]->getSecurityLevel()),
                        std::to_string(companies[gameplayButtonChosenIndex - 1]->getInfectedStatus()),
                        player.getPlayerVirus()->getName() + "[" + std::to_string(player.getPlayerVirus()->getComplexity()) + std::to_string(player.getPlayerVirus()->getSpeed()) + std::to_string(player.getPlayerVirus()->getPayload()) + std::to_string(player.getPlayerVirus()->getResilience()) + "]",
                        std::to_string(companies[gameplayButtonChosenIndex - 1]->getNoOfInfectedComputers()) + " (" + std::to_string(companies[gameplayButtonChosenIndex - 1]->getInfectedStatus() * 100) + "%)",
                        std::to_string(companies[gameplayButtonChosenIndex - 1]->getNoOfBrickedComputers()) + " (" + std::to_string(companies[gameplayButtonChosenIndex - 1]->getBrickedStatus() * 100) + "%)"
                    };

                    std::cout << std::endl;

                    for (int k = 0; k < 7; k++) {
                        renderCenteringSpaces();
                        //std::cout << std::string((155 - (title[k].length() + 3 + content[k].length())) / 2, ' ');
                        std::cout << title[k] << " | " << content[k] << std::endl << std::endl;
                    }

                    std::cout << std::endl << std::endl;

                    renderCenteringSpaces();
                    highlightSelectedUIButton(0, "[ RETURN ]", hConsole);

                    //std::this_thread::sleep_for(std::chrono::milliseconds(100));

                    while (companies[gameplayButtonChosenIndex - 1]->getNoOfBrickedComputers() < fraction * (iBricked + 1) && companies[gameplayButtonChosenIndex - 1]->getNoOfInfectedComputers() < fraction * (iInfected + 1) && screenIndex == 5) {
                        // yes
                    }
                }

                break;
            case 6: // upgrade
            {
                while (screenIndex == 6) {
                    system("cls ");

                    Upgrades* upgradesArray[20] = {nullptr};
                    int* currentUpgradesIndices = player.getCurrentUpgradeIndices();

                    for (int i = 0; i < 20; i++) {
                        if (player.getUpgradesArray()[i] != nullptr) {
                            upgradesArray[i] = player.getUpgradesArray()[i];
                        }
                    }
                    for (int i = 0; i < maxSelectedUIButtonOffset + 1 - 1; i++) {
                        if (upgradesArray[currentUpgradesIndices[i]] != nullptr && currentUpgradesIndices[i] != -1) {
                            renderCenteringSpaces();
                            highlightSelectedUIButton(i, "[ " + upgradesArray[currentUpgradesIndices[i]]->getName() + " ]", hConsole);
                            std::cout << std::endl;

                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                            renderCenteringSpaces();
                            std::cout << upgradesArray[currentUpgradesIndices[i]]->getDesc() << std::endl;
                            renderCenteringSpaces();
                            std::cout << "Cost: " << upgradesArray[currentUpgradesIndices[i]]->getCost() << " Hacker Point/s" << std::endl << std::endl;
                            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        }
                        else {
                            renderCenteringSpaces();
                            highlightSelectedUIButton(i, "[ LOCKED ]", hConsole);
                            std::cout << std::endl;

                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                            renderCenteringSpaces();
                            std::cout << "This upgrade tree is locked" << std::endl;
                            renderCenteringSpaces();
                            std::cout << "Cost: Nil" << std::endl << std::endl;
                            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        }
                    }

                    renderCenteringSpaces();
                    std::string temp = "Hacker Points : " + std::to_string(player.getHackingPoints());
                    std::cout << temp << std::string(155 - (temp.length() + 10), ' ');
                    highlightSelectedUIButton(maxSelectedUIButtonOffset, "[ RETURN ]", hConsole);
                    std::cout << std::endl << std::endl;

                    renderCenteringSpaces();
                    displayUIControls(0);

                    delayBeforeRefresh(previousScreenIndex);
                }
            }
                break;
                
            case 7: // news screen
                system("cls ");
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                resetInputHandler();

                SoundController::playSoundMP3("resources\\cartoon-phone-voice-88637.mp3", false);

                for (int i = completedNews; i < newsInADay_Head.size(); i++) {
                    system("cls ");
                    SoundController::playSound(L"resources\\cartoon-phone-voice-88637.mp3");
                    typingEntrance("TODAY'S HEADLINES: " + newsInADay_Head[i], newsInADay_Body[i], newsInADay_Effects[i], typingInterval, true, frame_Screen7DialogueNews);

                    resetInputHandler();
                    while (character != ' ') {
                        continue;
                    }
                    resetInputHandler();
                }
                
                completedNews += (newsInADay_Head.size() - completedNews);

                News::setHEAD("");
                News::setBODY("");
                News::setEFFECTS("");

                std::cout << "alert " << screenIndex << " " << newsInADay_Head.size() << " " << completedNews << std::endl;

                screenIndex = 4;

                
                break;
            case 8: // ending screen
                system("cls ");
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                resetInputHandler();

                for (int i = completedNews; i < newsInADay_Head.size(); i++) {
                    system("cls ");
                    typingEntrance("TODAY'S HEADLINES: " + newsInADay_Head[i], newsInADay_Body[i], newsInADay_Effects[i], typingInterval, true, frame_Screen7DialogueNews);

                    resetInputHandler();
                    while (character != ' ') {
                        continue;
                    }
                    resetInputHandler();
                }

                completedNews += newsInADay_Head.size();

                News::setHEAD("");
                News::setBODY("");
                News::setEFFECTS("");

                isGameRunning = false;
                break;
            case 9: // minigame   
                system("cls");
                resultingPoints = player.getPlayerVirus()->miniGame();
                player.setHackingPoints(player.getHackingPoints() + resultingPoints);
                system("cls");
                renderAnimation(emptyChickenFrames, 0, false, false, true);

                renderCenteringSpaces();
                std::cout << std::string(floor(155 - ("You Obtained " + std::to_string(resultingPoints) + " Hacker Point/s!").length()), '.') << "You Obtained " << resultingPoints << " Hacker Point/s!" << std::string(ceil(155 - ("You Obtained " + std::to_string(resultingPoints) + " Hacker Point/s!").length()), '.') << std::endl;

                renderAnimation(emptyChickenFrames, 0, false, false, true);
                
                std::this_thread::sleep_for(std::chrono::milliseconds(3000));

                oldUniqueCompaniesInfected = Company::getTotalUniqueCompanyInfections();
                screenIndex = 4;

                break;
            default:
                break;
            } 
        }
    }
    
}

void Game::typingEntrance(std::string head, std::string content, std::string end, int delayMs, bool startingChar, std::vector<std::vector<std::string>> graphicsToRender)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    std::string typedContent = "";
    std::string instantContent = "";
    int noOfLines = 0;
    int perLine = 100;
    int iteration = 0;
    int index = 0;
    int savedIndex = 0;
    bool isSkip = false;

    // image
    renderAnimation(graphicsToRender, delayMs, false, false, true);

    // line
    renderCenteringSpaces();
    std::cout << head << std::endl;
    renderCenteringSpaces();
    std::cout << std::string(155, '.') << std::endl;

    // buttons
    renderCenteringSpaces();
    highlightSelectedUIButton(0, "[ SKIP ]", hConsole);
    displayUIControls(8);

    // ui controls
    renderCenteringSpaces();

    std::cout << std::endl;

    while (index < content.length()) {
        std::string line = "";
        while (savedIndex <= perLine + (iteration * perLine)) { // each line
            line = line + content[index];
            if (content[index] == ' ') {
                if (index > perLine + (iteration * perLine)) {
                    savedIndex = index - 1; // remove the space
                    break;
                }
            }
            if (index + 1 > content.length()) {
                break;
            }
            else {
                index++;
            }
        }

        typedContent = typedContent + "\n" + std::string(floor((consoleWidth - line.length()) / 2), ' ');
        instantContent = instantContent + "\n" + std::string(floor((consoleWidth - line.length()) / 2), ' ') + line;
        noOfLines++;

        std::cout << std::endl << std::string(floor((consoleWidth - line.length()) / 2), ' ');

        for (int i = 0; i < line.length(); i++) {

            if (character == ' ' && selectedUIButton == 0) {
                isSkip = true;
                resetInputHandler();
            }

            if (isSkip) {
                typedContent = instantContent;
                break;
            }
            else {
                typedContent = typedContent + line[i];

                std::cout << line[i];
                std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
            }
        }

        index++; // dont add space in the next line
        iteration++;

        if (index > content.length()) {
            break;
        }
    }

    system("cls");

    // image
    renderAnimation(graphicsToRender, delayMs, false, false, true);

    // line
    renderCenteringSpaces();
    std::cout << head << std::endl;
    renderCenteringSpaces();
    std::cout << std::string(155, '.') << std::endl;

    // buttons
    renderCenteringSpaces();
    highlightSelectedUIButton(0, "[ CONTINUE ]", hConsole);

    // controls
    displayUIControls(12);
    std::cout << std::endl;

    if (end != "") {
        std::cout << typedContent << std::endl << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        std::cout << std::string(floor((consoleWidth - ("[ " + end + " ]").length()) / 2), ' ') << "[ " << end << " ]" << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    }
    else {
        std::cout << typedContent << std::endl;
    }
    

    /*for (int i = 0; i < content.length(); i++) {
        system("cls ");
        if (startingChar) {
            std::cout << std::string(floor((consoleWidthHandler() - 155) / 2), ' ');
        }

        if (i % 155 == 0 && i != 0) {
            typedContent = typedContent + "\n" + std::string(floor((consoleWidthHandler() - 155) / 2), ' ');
        }
        typedContent = typedContent + content[i];
        std::cout << typedContent << std::endl;

        if (character != ' ') {
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
        }
    }
    resetInputHandler();*/
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
        //std::shuffle(eligibleCompanies.begin(), eligibleCompanies.end(), std::default_random_engine(static_cast<unsigned>(std::time(0))));

        int randint = rand() % eligibleCompanies.size();
        int temp = randint;
        int companyA = eligibleCompanies[randint];
        do {
            randint = rand() % eligibleCompanies.size();
        } while (randint == temp);
        int companyB = eligibleCompanies[randint];

        // print out and set the finalised companies collabing spread
        temp = rand() % 5;
        newZ->companyCollabNews(temp, companies[companyA]->getName(), companies[companyB]->getName());

        temp = rand() % 3 + 2;
        companies[companyA]->setCollabSpreadWeightIndex(temp, companyB);
        companies[companyB]->setCollabSpreadWeightIndex(temp, companyA);

        newsInADay_Head.push_back(newZ->getHEAD());
        newsInADay_Body.push_back(newZ->getBODY());
        newsInADay_Effects.push_back(newZ->getEFFECTS());
    }
}

void Game::CheckCompanyDead()
{
    int temp;

    for (int i = 0; i < maxCompany; i++)
    {
        if (companies[i]->getBrickedStatus() == 1 && companies[i]->getIsFallen() == false)
        { 
            temp = rand() % 5;
            companies[i]->setIsFallen(true);
            newZ->companyDeadNews(temp, companies[i]->getName(), virusName);
            newsInADay_Head.push_back(newZ->getHEAD());
            newsInADay_Body.push_back(newZ->getBODY());
            newsInADay_Effects.push_back(newZ->getEFFECTS());
        }
    }
}

void Game::highlightSelectedUIButton(int thisUIButton, std::string content, HANDLE yes)
{
    if (thisUIButton == selectedUIButton) {
        SetConsoleTextAttribute(yes, BACKGROUND_RED | BACKGROUND_INTENSITY);
        std::cout << content;
    }
    else {
        SetConsoleTextAttribute(yes, FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << content;
    }
    SetConsoleTextAttribute(yes, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void Game::displayUIControls(int previousSpaceUsed)
{
    std::string uiControlsContent;

    if (navigationType == 0) {
        uiControlsContent = "[W] Previous  |  [S] Next  |  [SPACE] Select";
    }
    else {
        uiControlsContent = "[A] Previous  |  [D] Next  |  [SPACE] Select";
    }

    if (isNamingVirus) {
        uiControlsContent = "[ENTER] Enter";
    }
    
    std::cout << std::string(155 - previousSpaceUsed - uiControlsContent.length(), ' ') << uiControlsContent;
}

void Game::renderCenteringSpaces()
{
    std::cout << std::string(floor((consoleWidth - 155) / 2), ' ');
}

void Game::delayBeforeRefresh(int previousScreenIndex)
{
    if (screenIndex == previousScreenIndex) {
        for (int i = 0; i < 50; i++) {
            if (refreshNow || (newsInADay_Body.size() - completedNews) > 0) {
                refreshNow = false;
                break;
            }

            if (screenIndex != previousScreenIndex) {
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}

void Game::inputHandler()
{
    while (isGameRunning) {
        if (screenIndex != 9) {
            char characterInput = _getch();
            //SoundController::playSound(L"resources\hacking-sfx.wav");

            refreshNow = true;

            if (character != characterInput) {
                character = characterInput;
            }

            if (isNamingVirus) {
                if (character == '\r' && virusName.length() > 0) {
                    isNamingVirus = false;
                }
                else if (character == '\b') {
                    if (virusName.length() > 0) {
                        virusName.pop_back();
                    }
                }
                else if (virusName.length() < 20) {
                    virusName = virusName + character;
                }
            }
            else {
                switch (character) {
                case ' ':
                    if (screenIndex == 1) { // screen 1 selected button
                        if (selectedUIButton == 0) {
                            screenIndex = 2;
                            resetInputHandler();
                        }
                    }
                    else if (screenIndex == 3) { // screen 3 selected button
                        if (isChoosingVirusType) {
                            virusTypeIndex = selectedUIButton;
                            isChoosingVirusType = false;
                            resetInputHandler();
                        }
                        else if (isChoosingCompanyStart) { // screen 3.5 selected button
                            companyStartIndex = selectedUIButton;
                            isChoosingCompanyStart = false;
                            player.setInitials(companies, virusTypeIndex + 1, companyStartIndex + 1, virusName);
                            resetInputHandler();
                        }
                    }
                    else if (screenIndex == 4) { // screen 4 selected button
                        gameplayButtonChosenIndex = selectedUIButton;

                        if (gameplayButtonChosenIndex == 0) {
                            screenIndex = 6;
                        }
                        else {
                            screenIndex = 5;
                        }
                    }
                    else if (screenIndex == 5) { // screen 5 selected button
                        if (selectedUIButton == 0) {
                            screenIndex = 4;
                        }
                    }
                    else if (screenIndex == 6) {
                        if (selectedUIButton == maxSelectedUIButtonOffset) {
                            screenIndex = 4;
                        }
                        else {
                            int* currentUpgradesIndices = player.getCurrentUpgradeIndices();

                            if (currentUpgradesIndices[selectedUIButton] != -1) {
                                float cost = player.getUpgradesArray()[selectedUIButton]->getCost();

                                if (player.getHackingPoints() >= cost) {
                                    player.applyUpgrade(currentUpgradesIndices[selectedUIButton]);
                                    player.blockUpgrade();

                                    screenIndex = 4;
                                }
                            }
                        }
                    }

                    break;

                case 'w':
                case 'W':
                    if (navigationType == 0) {
                        if (selectedUIButton - 1 >= minSelectedUIButtonOffset) selectedUIButton--;
                    }
                    break;

                case 'a':
                case 'A':
                    if (navigationType == 1) {
                        if (selectedUIButton - 1 >= minSelectedUIButtonOffset) selectedUIButton--;
                    }
                    break;

                case 's':
                case 'S':
                    if (navigationType == 0) {
                        if (selectedUIButton + 1 <= maxSelectedUIButtonOffset) selectedUIButton++;
                    }
                    break;

                case 'd':
                case 'D':
                    if (navigationType == 1) {
                        if (selectedUIButton + 1 <= maxSelectedUIButtonOffset) selectedUIButton++;
                    }
                    break;

                default:
                    std::cout << "[ Input issue. Please retry ]" << std::endl;
                    break;
                }
            }
        }
    }
}

void Game::resetInputHandler()
{
    character = -1;
}

void Game::resetUIButtonSelection()
{
    switch (screenIndex) {
    case 0:
    case 1:
    case 4:
    case 6:
        navigationType = 0; // 0 means up down
        break;

    case 2:
    case 3:
    case 5:
        navigationType = 1; // 1 means sideways
        break;

    default:
        navigationType = 0;
        break;
    }

    int screenTotalButtons[8] = {0, 1, 1, 3, 6, 1, 8, 1};

    selectedUIButton = 0;
    minSelectedUIButtonOffset = 0;

    maxSelectedUIButtonOffset = minSelectedUIButtonOffset + screenTotalButtons[screenIndex] - 1;
}

// Load frames from a text file separated by "---FRAME---"
std::vector<std::vector<std::string>> Game::loadFrames(const std::string & filename) {
    std::ifstream file(filename);
    std::vector<std::vector<std::string>> frames;
    std::vector<std::string> currentFrame;
    std::string line;

    while (std::getline(file, line)) {
        if (line == "---FRAME---") {
            if (!currentFrame.empty()) {
                frames.push_back(currentFrame);
                currentFrame.clear();
            }
        }
        else {
            currentFrame.push_back(line);
        }
    }

    if (!currentFrame.empty()) {
        frames.push_back(currentFrame);
    }

    return frames;
}

std::string Game::loadChar(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary); // open as binary
    if (!file) {
        std::cerr << "Cannot open file\n";
        return "";
    }

    std::string utf8Char;
    char c;
    int bytesRead = 0;

    // Read the first UTF-8 character (1 to 4 bytes)
    file.get(c);
    if (file) {
        unsigned char first = static_cast<unsigned char>(c);
        int numBytes = 1;

        // Determine number of bytes for this UTF-8 character
        if ((first & 0x80) == 0x00) numBytes = 1;          // ASCII
        else if ((first & 0xE0) == 0xC0) numBytes = 2;     // 2-byte UTF-8
        else if ((first & 0xF0) == 0xE0) numBytes = 3;     // 3-byte UTF-8
        else if ((first & 0xF8) == 0xF0) numBytes = 4;     // 4-byte UTF-8

        utf8Char += c;
        for (int i = 1; i < numBytes; ++i) {
            file.get(c);
            if (file) utf8Char += c;
        }

        return utf8Char;
    }
}

// Render one loop of animation frames
void Game::renderAnimation(const std::vector<std::vector<std::string>>&frames, int delayMs, bool isContinued, bool haveControlsUI, bool hasEnd) {
    std::string totalRender = "";

    for (const auto& frame : frames) {
        
        totalRender = "";
        bool firstLine = true;

        if (firstLine == true && isContinued) {
            
        }
        else {
            system("cls ");
        }

        for (auto line : frame) {
            // Remove BOM if present on first line
            if (firstLine) {
                if (!line.empty() && (unsigned char)line[0] == 0xEF) {
                    line = line.substr(3); // skip BOM bytes
                }
                firstLine = false;
            }

            if (consoleWidth - line.length() > 1) {
                totalRender = totalRender + std::string(floor((consoleWidth - line.length()) / 2), ' ') + line + std::string(ceil((consoleWidth - line.length()) / 2), ' ') + "\n";
            }
            else {
                totalRender = totalRender + std::string(1, ' ') + line + std::string(1, ' ') + "\n";
            }
        }
        
        if (!hasEnd) {
            totalRender.erase(totalRender.begin());
            totalRender.pop_back();
        }

        std::cout << totalRender;
        if (haveControlsUI) {
            renderCenteringSpaces();
            displayUIControls(0);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

void Game::consoleWidthHandler() {
    while (isGameRunning) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int consoleWidthTemp = 0;

        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            consoleWidthTemp = csbi.dwSize.X;
        }
        else {
            std::cerr << "Error: Could not get console screen buffer info." << std::endl;
        }

        if (consoleWidthTemp > 155) {
            consoleWidth = consoleWidthTemp;
        }
        else {
            consoleWidth = 155;
        }

        if (previousConsoleWidth != consoleWidth) {
            previousConsoleWidth = consoleWidth;
            refreshNow = true;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
}