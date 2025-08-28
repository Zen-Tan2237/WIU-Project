#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <windows.h>

#include "Company.h"
#include "Player.h"
#include "CyberSecurity.h"
#include "News.h"

class Game
{
private:
	int currentTick;
	int tickInterval;
	bool isGameRunning;
    int gameResult;
	const static int maxCompany = 5;
    int companyA;
    int companyB;
    int screenIndex;
    int previousScreenIndex;
    int selectedUIButton;
    int maxSelectedUIButtonOffset;
    int minSelectedUIButtonOffset;
    int navigationType;
    bool isNamingVirus;
    bool isChoosingVirusType;
    bool isChoosingCompanyStart;
    std::string virusName;
    int virusTypeIndex;
    int companyStartIndex;
    int gameplayButtonChosenIndex;
    int consoleWidth;
    int previousConsoleWidth;
    bool refreshNow;
    int completedNews;
    char character;
    int oldUniqueCompaniesInfected;

    std::vector<std::string> newsInADay_Head;
    std::vector<std::string> newsInADay_Body;
    std::vector<std::string> newsInADay_Effects;

	std::string companyNames[50] = {
        // Tech
        "Dihhard", "Pear", "Googly", "Amazin", "FaceLock",
        "Twaddler", "Netflicks", "SnapChan", "TockTock", "DisCunt",

        // Hardware / Electronics
        "Samflung", "Sonai", "Dellusional", "Lenova", "Asuspect",
        "HPee", "Acers", "Intell", "AMDazed", "Nvidiugh",

        // Food & Beverage
        "WacDonalds", "Bugger King", "PieHut", "KFG", "Starbucksie",
        "Dunkin Dullnuts", "Substandard", "Taco Heaven", "Dominosh", "Wendeez",

        // Auto / Transport
        "Tomoya", "Ascurra", "Mustung", "Teslow", "BMDoubleU",
        "Merceduhs", "Volkswagooned", "Hyundae", "Uberrr", "Lyfted",

        // Finance / Retail
        "Walmutt", "Targeted", "Coscaw", "Pay After 10Months", "Vaesa",
        "MasturdCard", "Amexed", "Chased", "CitiNot", "Aliboba"
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
        6, 4, 3, 2, 2
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
        10, 8, 5, 8, 1
    };



	Player player; // the hacker/player
    CyberSecurity* cyberSecurity;
	Company* companies[maxCompany]; // list of all target companies
    News* newZ;

    /*std::string element_barFilled;
    std::string element_barUnfilled;*/
    const std::string element_bars[7] = {
        "\xE2\x96\x87", // 7/8
        "\xE2\x96\x86", // 6/8
        "\xE2\x96\x85", // 5/8
        "\xE2\x96\x84", // 4/8
        "\xE2\x96\x83", // 3/8
        "\xE2\x96\x82", // 2/8
        "\xE2\x96\x81"  // 1/8
    };

    std::vector<std::vector<std::string>> emptyChickenFrames;

    std::vector<std::vector<std::string>> frame_Logo;
    std::vector<std::vector<std::string>> frame_LogoInteractToStart1;
    std::vector<std::vector<std::string>> frame_LogoInteractToStart2;

    std::vector<std::vector<std::string>> frame_Screen2DialoguePt1;
    std::vector<std::vector<std::string>> frame_Screen2DialoguePt2;
    std::vector<std::vector<std::string>> frame_Screen2DialoguePt3;
    std::vector<std::vector<std::string>> frame_Screen7DialogueNews;

    std::vector<std::vector<std::string>> frame_Screen3Welcome;

    std::vector<std::vector<std::string>> frame_Screen3NameVirus;

    std::vector<std::vector<std::string>> frame_Screen3VirusType;
    std::vector<std::vector<std::string>> frame_Screen3VirusType1;
    std::vector<std::vector<std::string>> frame_Screen3VirusType2;

    std::vector<std::vector<std::string>> frame_Screen3CompanyStart;
    std::vector<std::vector<std::string>> frame_Screen3CompanyStart1;
    std::vector<std::vector<std::string>> frame_Screen3CompanyStart2;

    std::vector<std::vector<std::string>> frame_Screen4GameplayUI1;
    std::vector<std::vector<std::string>> frame_Screen4GameplayUI2;
    std::vector<std::vector<std::string>> frame_Screen4GameplayUI3;
    std::vector<std::vector<std::string>> frame_Screen4GameplayUI4;
    std::vector<std::vector<std::string>> frame_Screen4GameplayUIEnd;

    std::vector<std::vector<std::string>> frame_Screen5BuildingBottom;
    std::vector<std::vector<std::string>> frame_Screen5BuildingCenterClone;
    std::vector<std::vector<std::string>> frame_Screen5BuildingTop;

public:
	Game();
	~Game();

	void initGame();

    int getCurrentTick() const; // Getter
    void setCurrentTick(int tickInterval); // Setter
    int getCurrentScreen() const;

    void consoleWidthHandler();

    void doTurn();
    void printInterface();
    void typingEntrance(std::string head, std::string content, std::string end, int delayMs, bool startingChar, std::vector<std::vector<std::string>> graphicsToRender);
    void randomCollabGenerator();
    void CheckCompanyDead();
    void highlightSelectedUIButton(int thisUIButton, std::string content, HANDLE yes);
    void displayUIControls(int previousSpaceUsed);
    void renderCenteringSpaces();

    void delayBeforeRefresh(int previousScreenIndex);

    void inputHandler();
    void resetInputHandler();
    void resetUIButtonSelection();

    std::vector<std::vector<std::string>> loadFrames(const std::string& filename);
    std::string loadChar(const std::string& filename);
    void renderAnimation(const std::vector<std::vector<std::string>>& frames, int delayMs, bool isContinued, bool haveControlsUI, bool hasEnd);
};

