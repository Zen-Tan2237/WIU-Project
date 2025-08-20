#pragma once

#include <iostream>
#include <string>
#include<sstream>
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
		LAN_SCANNER,
		SMB_EXPLOIT,
		USB_PROPAGATION,
		BOTNET_BOOST,
		EMAIL_WORM_BOOST,
		//COMPLEXITY/PAYLOAD UPGRADES
		ENCRYPTION_LAYER,
		KEYLOGGER_MODULE,
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
		KILL_SWITCH,
		SIGNATURE_MUTATION,
		VIRTUAL_MACHINE_DETECTION,
		NUM_UPGRADES,
	};

	std::string nameUpgrade[NUM_UPGRADES * 2] = { // First string is Name, After that is the description
		// SPEED UPGRADES
		"Polymorphic Engine", "The virus rewrites its code everytime it spreads to a new computer, harder to detect. Speed and complexity increase slightly",
		"LAN Scanner", "The virus auto-scans local networks for vulnerable devices. Speed increases slighty",
		"SMB Exploit", "The virus exploits the Windows file sharing vulnerability. Speed increases slighty",
		"USB Propagation", "The virus copies itself when infected device is connected to a USB Drive. Speed increases slighty",
		"Botnet Boost", "Virus hijacks more infected PCs to spread faster. Speed increases slightly",
		"Email Worm Boost", "Adds auto-email propagation. Speed increases significantly",

		//COMPLEXITY/PAYLOAD UPGRADES
		"Encryption Layer", "Adds obfuscation, making it harder to analyze. Increases complexity and resilience", 
		"Keylogger Module", "The virus drops a keylogger to steal credentials. Increases complexity and slightly to payload",
		"Rootkit Injection", "Gains stealth and deeper system access. Increases complexity and payload", 
		"Bricking Routine", "Aggressive payload: corrupts boot sector. Significantly increase payload",
		"Data Wiper", "Destroys company files on infection. Significantly increases complexity and payload",
		"Antivirus Bypass", "Mimics normal system processes, increases complexity",

		//RESILIENCE UPGRADES
		"Code Obfuscation I", "Obfuscates the code. Harder to cure",
		"Code Obfuscation II", "Further obfuscation, slows down cure significantly",
		"Code Refactor I", "The code was rewritten. Sets cures progress back",
		"Code Refactor II", "The code was rewritten. Sets cures progress back",
		"Code Refactor III", "The code was rewritten. Sets cures progress back",
		"Kill Switch", "The virus has a kill switch, removing itself when it detects it's being analysed. Increases resilience and slows down cure progress.",
		"Signature Mutation", "The virus changes it's digital signature, confusing analysts. Sets cure progress back.",
		"Virtual Machine Detection", "The virus does not run in Virtual Machines, mutually exclusive to Virtual Machine Leak",
	};

	float statsUpgrade[NUM_UPGRADES * 5]{
		// Polymorphic Engine
		0.5f, 0.3f, 0, 0, 0,
		// Botnet Boost
		0.3f, 0, 0, 0, 0,
		// Email Worm Boost
		1.f, 0, 0, 0, 0,
		// Encryption Layer
		0, 0.3f, 0, 0.5f, 0,
		// Rootkit Injection
		0, 0.5f, 0.6f, 0, 0,
		// Bricking Routine
		0, 0.6f, 2.f, 0, 0,
		// Data Wiper
		0, 0.7f, 4.f, 0, 0,
		// Antivirus Bypass
		0, 1.f, 0.2f, 0, 0,
		// Code Obfuscation I
		0, 0, 0, 1.f, 0,
		// Code Obfuscation II
		0, 0, 0, 2.f, 0,
		// Code Refactor I
		0, 0, 0, 2.f, 0,
		// Code Refactor II
		0, 0, 0, 2.5f, 0,
		// Code Refactor III
		0, 0, 0, 3.f, 0,
	};

public:
	Player();
	~Player();

	void earnPoints(int points);
	void spendPoints(int cost);

	void setInitials(Company* companyList[]);
	void update();
	void displayUpgrades(bool& menuing);

	void parseUpgrades();

	// Getters and Setters
	int getHackingPoints() const;
	int getCompanyChoice() const;
	void setCompanyChoice(int choice);	
	void setMaxCompany(int maxCompany);
	Virus* getPlayerVirus() const;

	Upgrades* upgradesArray[NUM_UPGRADES];
	
	void setHackingPoints(int hackingPoints);



};

