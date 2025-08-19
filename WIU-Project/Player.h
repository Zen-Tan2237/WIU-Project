#pragma once

#include <iostream>
#include <string>
#include "Virus.h"
#include "Company.h"

class Player
{
private:
	int hackingPoints;
	int companyChoice;
	int maxCompany;
	Virus* playerVirus; 

	enum UPGRADES {
		// SPEED UPGRADES
		POLYMORHPIC_ENGINE,
		BOTNET_BOOST,
		EMAIL_WORM_BOOST,
		//COMPLEXITY/PAYLOAD UPGRADES
		ENCRYPTION_LAYER,
		ROOTKIT_INJECTION,
		BRICKING_ROUTINE,
		DATA_WIPER,
		ANTIVIRUS_BYPASS,
		//RESILIENCE UPGRADES
		CODE_OBFUSCATION_I,
		CODE_OBFUSCATION_II,
		CODE_REFACTOR_I,
		CODE_REFACTOR_II,
		CODE_REFACTOR_III,
		NUM_UPGRADES,
	};

	std::string nameUpgrade[NUM_UPGRADES * 2] = { // First string is Name, After that is the description
		// SPEED UPGRADES
		"Polymorphic Engine", "The virus rewrites its code everytime it spreads to a new computer, harder to detect. Speed and complexity increase slightly",
		"Botnet Boost", "Virus hijacks more infected PCs to spread faster. Speed increases slightly",
		"Email Worm Boost", "Adds auto-email propagation. Speed increases significantly",

		//COMPLEXITY/PAYLOAD UPGRADES
		"Encryption Layer", "Adds obfuscation, making it harder to analyze. Increases complexity and resilience", 
		"Rootkit Injection", "Gains stealth and deeper system access. Increases complexity and payload", 
		"Bricking Routine", "Aggressive payload: corrupts boot sector. Significantly increase payload",
		"Data Wiper", "Destroys company files on infection. Significantly increases complexity and payload",
		"Antivirus Bypass", "Mimics normal system processes, increases complexity"

		//RESILIENCE UPGRADES
		"Code Obfuscation I", "Obfuscates the code. Harder to cure",
		"Code Obfuscation II", "Further obfuscation, slows down cure significantly",
		"Code Refactor I", "The code was rewritten. Sets cures progress back",
		"Code Refactor II", "The code was rewritten. Sets cures progress back",
		"Code Refactor III", "The code was rewritten. Sets cures progress back",
	};

	float statsUpgrade[NUM_UPGRADES * 4]{
		// Polymorphic Engine
		0.5, 0.3, 0, 0,
		// Botnet Boost
		0.3, 0, 0, 0,
		// Email Worm Boost
		1, 0, 0, 0,
		// Encryption Layer
		0, 0.3, 0, 0.5,
		// Rootkit Injection
		0, 0.5, 0.6, 0,
		// Bricking Routine
		0, 0.6, 2, 0,
		// Data Wiper
		0, 0.7, 4, 0,
		// Antivirus Bypass
		0, 1, 0.2, 0,
		// Code Obfuscation I
		0, 0, 0, 1,
		// Code Obfuscation II
		0, 0, 0, 2,
		// Code Refactor I
		0, 0, 0, 2,
		// Code Refactor II
		0, 0, 0, 2.5,
		// Code Refactor III
		0, 0, 0, 3
	};

public:
	Player();
	~Player();

	void earnPoints(int points);
	void spendPoints(int cost);

	void setInitials(Company* companyList[]);
	void update();

	// Getters and Setters
	int getHackingPoints() const;
	int getCompanyChoice() const;
	void setCompanyChoice(int choice);	
	void setMaxCompany(int maxCompany);
	Virus* getPlayerVirus() const;

	Upgrades* upgradesArray[NUM_UPGRADES];
	
	void setHackingPoints(int hackingPoints);



};

