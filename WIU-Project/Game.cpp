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
    companyStartIndex = 0;
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

    emptyChickenFrames = loadFrames("emptyChickenFrames.txt");
    frame_Logo = loadFrames("Logo.txt");
    frame_LogoInteractToStart1 = loadFrames("LogoInteractToStart1.txt");
    frame_LogoInteractToStart2 = loadFrames("LogoInteractToStart2.txt");
    frame_Screen2DialoguePt1 = loadFrames("Screen2DialoguePt1.txt");
    frame_Screen2DialoguePt2 = loadFrames("Screen2DialoguePt2.txt");
    frame_Screen2DialoguePt3 = loadFrames("Screen2DialoguePt3.txt");
    frame_Screen3Welcome = loadFrames("Screen3Welcome.txt");
    frame_Screen3NameVirus = loadFrames("Screen3NameVirus.txt");
    frame_Screen3VirusType = loadFrames("Screen3VirusType.txt");
    frame_Screen3VirusType1 = loadFrames("Screen3VirusType1.txt");
    frame_Screen3VirusType2 = loadFrames("Screen3VirusType2.txt");
    frame_Screen3CompanyStart = loadFrames("Screen3CompanyStart.txt");
    frame_Screen3CompanyStart1 = loadFrames("Screen3CompanyStart1.txt");
    frame_Screen3CompanyStart2 = loadFrames("Screen3CompanyStart2.txt");
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

    if (currentTick % 10 == 0)
    {
        //randomMutation;
    }

    // update company infectivity
    for (int i = 0; i < tickInterval; i++) {
        for (int j = 0; j < maxCompany;  j++) {
            companies[j]->update(companies);
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
    std::cout << "Total Bricked: " << Company::getTotalNoOfBrickedComputers() << std::endl;*/

    std::string screenIndex2_dialogues[3] = {
        "In a world dominated by towering corporations, one individual found themselves suffocated by the endless cycle of consumerism and corporate greed. Day after day, they toiled away in a job that felt more like servitude than work, watching as companies prioritized profit over people. The frustration grew, a quiet storm brewing inside, fueled by the injustice of a system that seemed designed to exploit rather than empower.",
        "One evening, overwhelmed by the weight of their dissatisfaction, they dreamed of a different kind of revolution—not one of destruction, but of transformation. Instead of fighting fire with fire, they envisioned a way to undermine the corporate giants through creativity and innovation, exposing the flaws in their systems and inspiring people to demand better. Their plan was to harness technology and art to awaken society to the power they held as consumers, turning frustration into a force for change.",
        "With renewed purpose, they set out to create tools and platforms that challenged the status quo, encouraging transparency and fairness. Their rebellion was not one of chaos, but of hope—a movement that sought to rebuild a world where companies served the people, not the other way around."
    };

    int gap = 10;
    int typingInterval = 25;
    int longestCompanyValue = 0;
    int longestgetInfectedStatus = 0;
    std::string interactToStartContent = "Hold <Space> To Start";

    std::this_thread::sleep_for(std::chrono::milliseconds(750));

    if (screenIndex != previousScreenIndex && consoleWidthHandler() > 155) {
        resetUIButtonSelection();
        previousScreenIndex = screenIndex;

        switch (screenIndex) {
        case 0:
            SetConsoleOutputCP(CP_UTF8);

            // Title Screen
            renderAnimation(frame_Logo, 5, false, true);
            screenIndex = 1;

            break;

        case 1: // intro screen
            while (screenIndex == 1) {
                if (interactToStartContent == "Hold <Space> To Start") {
                    renderAnimation(frame_LogoInteractToStart1, 3, false, false);

                    if (155 - interactToStartContent.length() > 1) {
                        std::cout << std::string(floor((consoleWidthHandler() - 155) / 2), ' ') << std::string(floor((155 - interactToStartContent.length()) / 2), '.');
                        highlightSelectedUIButton(0, interactToStartContent, hConsole);
                        std::cout << std::string(ceil((155 - interactToStartContent.length()) / 2), '.') << std::endl;
                    }
                    else {
                        std::cout << std::string(floor((consoleWidthHandler() - 155) / 2), ' ') << std::string(floor((155 - interactToStartContent.length()) / 2), '.');
                        highlightSelectedUIButton(0, interactToStartContent, hConsole);
                        std::cout << std::string(ceil((155 - interactToStartContent.length()) / 2), '.') << std::endl;
                    }
                    renderAnimation(frame_LogoInteractToStart2, 5, true, true);
                    interactToStartContent = "";
                }
                else {
                    renderAnimation(frame_LogoInteractToStart1, 5, false, false);

                    std::cout << std::string(floor((consoleWidthHandler() - 155) / 2), ' ') << std::string(155, '.') << std::endl;
                    
                    renderAnimation(frame_LogoInteractToStart2, 5, true, true);

                    interactToStartContent = "Hold <Space> To Start";
                }

                if (screenIndex == 1) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(250));
                }
            }
            break;

        case 2: // dialogue screen
            while (screenIndex == 2) {
                system("cls ");
                for (int i = 0; i < sizeof(screenIndex2_dialogues) / sizeof(screenIndex2_dialogues[0]); i++) {
                    switch (i) {
                    case 0:
                        typingEntrance(screenIndex2_dialogues[i], typingInterval, true, frame_Screen2DialoguePt1);
                        break;

                    case 1:
                        typingEntrance(screenIndex2_dialogues[i], typingInterval, true, frame_Screen2DialoguePt2);
                        break;

                    case 2:
                        typingEntrance(screenIndex2_dialogues[i], typingInterval, true, frame_Screen2DialoguePt3);
                        break;

                    default:
                        typingEntrance(screenIndex2_dialogues[i], typingInterval, true, emptyChickenFrames);
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
                renderAnimation(frame_Screen3Welcome, 0, false, true);

                std::this_thread::sleep_for(std::chrono::milliseconds(1500));

                renderAnimation(frame_Screen3NameVirus, 2, false, true); // ask for name of virus
                isNamingVirus = true;

                while (isNamingVirus) {
                    if (virusName != "") {
                        if (character != -1) {
                            system("cls");
                            renderAnimation(emptyChickenFrames, 2, false, false);
                            std::cout << std::string(floor((consoleWidthHandler() - 155) / 2), ' ') << std::string(floor((155 - virusName.length()) / 2), '.');
                            highlightSelectedUIButton(0, virusName, hConsole);
                            std::cout << std::string(ceil((155 - virusName.length()) / 2), '.') << std::endl;
                            renderAnimation(emptyChickenFrames, 2, true, true);
                            resetInputHandler();
                        }
                    }
                }

                system("cls ");
                renderAnimation(frame_Screen3VirusType, 0, false, true);
                isChoosingVirusType = true;

                system("cls");
                renderAnimation(frame_Screen3VirusType1, 2, false, false); // ask for type of virus
                renderCenteringSpaces();
                std::cout << std::string(floor((155 - 26) / 2), '.');
                highlightSelectedUIButton(0, "[Worm]", hConsole);
                highlightSelectedUIButton(1, "[Trojan]", hConsole);
                highlightSelectedUIButton(2, "[Ransomware]", hConsole);
                std::cout << std::string(ceil((155 - 26) / 2), '.');
                std::cout << std::endl;
                renderAnimation(frame_Screen3VirusType2, 2, true, true);
                resetInputHandler();

                while (isChoosingVirusType) {
                    if (character != -1) {
                        system("cls");
                        renderAnimation(frame_Screen3VirusType1, 2, false, false); // ask for type of virus
                        renderCenteringSpaces();
                        std::cout << std::string(floor((155 - 26) / 2), '.');
                        highlightSelectedUIButton(0, "[Worm]", hConsole);
                        highlightSelectedUIButton(1, "[Trojan]", hConsole);
                        highlightSelectedUIButton(2, "[Ransomware]", hConsole);
                        std::cout << std::string(ceil((155 - 26) / 2), '.');
                        std::cout << std::endl;
                        renderAnimation(frame_Screen3VirusType2, 2, true, true);
                        resetInputHandler();
                    }
                }

                system("cls ");
                renderAnimation(frame_Screen3CompanyStart, 0, false, true);
                isChoosingCompanyStart = true;
                maxSelectedUIButtonOffset = maxCompany - 1;

                system("cls");
                renderAnimation(frame_Screen3CompanyStart1, 2, false, false); // ask for type of virus
                renderCenteringSpaces();

                int temp = 0;
                for (int i = 0; i < maxCompany; i++) {
                    temp += (2 + companies[i]->getName().length());
                }

                if (temp <= 155) {
                    std::cout << std::string(floor((155 - temp) / 2), '.');
                }
                else {
                    std::cout << std::string(1, '.');
                }

                for (int i = 0; i < maxCompany; i++) {
                    std::string yes = "[" + companies[i]->getName() + "]";
                    highlightSelectedUIButton(i, yes, hConsole);
                }

                if (temp <= 155) {
                    std::cout << std::string(floor((155 - temp) / 2), '.');
                }
                else {
                    std::cout << std::string(1, '.');
                }

                std::cout << std::endl;
                renderAnimation(frame_Screen3CompanyStart2, 2, true, true);
                resetInputHandler();

                while (isChoosingCompanyStart) {
                    if (character != -1) {
                        system("cls");
                        renderAnimation(frame_Screen3CompanyStart1, 2, false, false); // ask for type of virus
                        renderCenteringSpaces();
                        
                        int temp = 0;
                        for (int i = 0; i < maxCompany; i++) {
                            temp += (2 + companies[i]->getName().length());
                        }

                        if (temp <= 155) {
                            std::cout << std::string(floor((155 - temp) / 2), '.');
                        }
                        else {
                            std::cout << std::string(1, '.');
                        }

                        for (int i = 0; i < maxCompany; i++) {
                            std::string yes = "[" + companies[i]->getName() + "]";
                            highlightSelectedUIButton(i, yes, hConsole);
                        }
                        
                        if (temp <= 155) {
                            std::cout << std::string(floor((155 - temp) / 2), '.');
                        }
                        else {
                            std::cout << std::string(1, '.');
                        }

                        std::cout << std::endl;
                        renderAnimation(frame_Screen3CompanyStart2, 2, true, true);
                        resetInputHandler();
                    }
                }

                screenIndex = 12;
            }
            break;
        case 12:
            while (screenIndex == 12) {
                system("cls ");
                for (int i = 0; i < maxCompany; i++) {
                    if (companies[i]->getName().length() > longestCompanyValue) {
                        longestCompanyValue = companies[i]->getName().length();
                    }
                    if (std::to_string(companies[i]->getInfectedStatus()).length() > longestgetInfectedStatus) {
                        longestgetInfectedStatus = std::to_string(companies[i]->getInfectedStatus()).length();
                    }
                }

                std::cout << "Company" << std::string(longestCompanyValue - 7 + gap, ' ') << "Status" << std::endl;
                std::cout << std::string((longestCompanyValue + gap) + (longestgetInfectedStatus + gap), '-') << std::endl;
                for (int i = 0; i < maxCompany; i++) {
                    std::cout << companies[i]->getName() << std::string(longestCompanyValue - (companies[i]->getName().length()) + gap, ' ')
                        << companies[i]->getInfectedStatus() << std::string(longestgetInfectedStatus - (std::to_string(companies[i]->getInfectedStatus()).length()) + gap, ' ')
                        << std::endl;
                }
                doTurn();

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            break;

        default:
            break;

        }
    }
}

void Game::typingEntrance(std::string content, int delayMs, bool startingChar, std::vector<std::vector<std::string>> graphicsToRender)
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
    renderAnimation(graphicsToRender, 5, false, false);

    // line
    renderCenteringSpaces();
    std::cout << "Backstory" << std::endl;
    renderCenteringSpaces();
    std::cout << std::string(155, '.') << std::endl;

    // buttons
    renderCenteringSpaces();
    highlightSelectedUIButton(0, "[Skip]", hConsole);
    displayUIControls(6);

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

        typedContent = typedContent + "\n" + std::string(floor((consoleWidthHandler() - line.length()) / 2), ' ');
        instantContent = instantContent + "\n" + std::string(floor((consoleWidthHandler() - line.length()) / 2), ' ') + line;
        noOfLines++;

        std::cout << std::endl << std::string(floor((consoleWidthHandler() - line.length()) / 2), ' ');

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
    renderAnimation(graphicsToRender, 5, false, false);

    // line
    renderCenteringSpaces();
    std::cout << "Backstory" << std::endl;
    renderCenteringSpaces();
    std::cout << std::string(155, '.') << std::endl;

    // buttons
    renderCenteringSpaces();
    highlightSelectedUIButton(0, "[Continue]", hConsole);

    // controls
    displayUIControls(10);
    std::cout << std::endl;

    std::cout << instantContent << std::endl;

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
    if (thisUIButton == selectedUIButton) {
        SetConsoleTextAttribute(yes, BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << content;
        SetConsoleTextAttribute(yes, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else {
        std::cout << content;
    }
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
    
    std::cout << std::string(155 - previousSpaceUsed - uiControlsContent.length(), ' ') << uiControlsContent;
}

void Game::renderCenteringSpaces()
{
    std::cout << std::string(floor((consoleWidthHandler() - 155) / 2), ' ');
}

void Game::inputHandler()
{
    while (true) {
        switch (screenIndex) {
        case 0:
        case 1:
            navigationType = 0; // 0 means up down
            break;

        case 2:
        case 3:
            navigationType = 1; // 1 means sideways
            break;

        default:
            navigationType = 0;
            break;
        }

        char characterInput = _getch();
        if (character != characterInput) {
            character = characterInput;
        }
        if (isNamingVirus) {
            if (character == ' ' && virusName.length() > 0) {
                isNamingVirus = false;
            }
            else if (character == 8) {
                if (virusName.length() > 0) {
                    virusName.pop_back();
                }
            }
            else {
                virusName = virusName + character;
            }
        }
        else {
            switch (character) {
            case ' ':
                if (screenIndex == 1) {
                    if (selectedUIButton == 0) {
                        screenIndex = 2;
                        resetInputHandler();
                    }
                }
                else if (screenIndex == 3) {
                    if (isChoosingVirusType) {
                        virusTypeIndex = selectedUIButton;
                        isChoosingVirusType = false;
                        resetInputHandler();
                    }
                    else if (isChoosingCompanyStart) {
                        companyStartIndex = selectedUIButton;
                        isChoosingCompanyStart = false;
                        player.setInitials(companies, virusName, virusTypeIndex + 1, companyStartIndex + 1);
                        resetInputHandler();
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
                std::cout << "yes" << std::endl;
                break;
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
    int screenTotalButtons[5] = {0, 1, 1, 3};

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

// Render one loop of animation frames
void Game::renderAnimation(const std::vector<std::vector<std::string>>&frames, int delayMs, bool isContinued, bool haveControlsUI) {
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

            if (consoleWidthHandler() - line.length() > 1) {
                totalRender = totalRender + std::string(floor((consoleWidthHandler() - line.length()) / 2), ' ') + line + std::string(ceil((consoleWidthHandler() - line.length()) / 2), ' ') + "\n";
            }
            else {
                totalRender = totalRender + std::string(1, ' ') + line + std::string(1, ' ') + "\n";
            }
        }

        std::cout << totalRender;
        if (haveControlsUI) {
            renderCenteringSpaces();
            displayUIControls(0);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

int Game::consoleWidthHandler() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int consoleWidth = 0;

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        consoleWidth = csbi.dwSize.X;
    }
    else {
        std::cerr << "Error: Could not get console screen buffer info." << std::endl;
    }

    if (consoleWidth > 155) {
        return consoleWidth;
    }
    else {
        return 155;
    }
}