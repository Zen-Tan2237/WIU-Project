#pragma once
#include "Virus.h"
#include "Upgrades.h"
#include <iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
class Worm : public Virus
{
private:
	const int row = 10;
	const int col = 72;
	bool lose = false;
	int wormRow = 0;
	int wormCol = 0;
	int wormRowPrevious = wormRow;
	int wormColPrevious = wormCol;
	char dir = 's';
	char** board = new char* [row];



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

	int dependentIndices[NUM_UPGRADES + 6]{
		//Dependency chain 1
		0, 1, 2, 4, -1,
		//Depenency Chain 2
		0, 3, 5, -1,
		//Dependency Chain 3
		6, 8, 11, -1,
		//Dependency Chain 4
		7, 10, 9, -1,
		//Dependency Chain 5
		14, 15, 16, 18, -1,
		//Dependency Chain 6
		17, -1,
		//Dependency Chain 7
		19, -1
	};

	int dependentIndicesLength = NUM_UPGRADES + 6;

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
		// Polymorphic Engine 0
		0.3f, 0.2f, 0, 0, 10,
		// LAN Scanner 1
		0.5f, 0.2f, 0, 0, 15,
		// SMB Exploit 2
		0.6f, 0, 0, 0, 18,
		// USB Propagation 3
		0.4f, 0, 0, 0, 14,
		// Botnet Boost 4
		0.7f, 0, 0, 0, 23,
		// Email Worm Boost 5
		0.8f, 0.1f, 0, 0, 27,
		// Encryption Layer 6
		0, 0.1f, 0, 0.3f, 9,
		// Keylogger Module 7
		0, 0.2f, 0.1f, 0, 14,
		// Rootkit Injection 8
		0, 0.5f, 0.6f, 0, 16,
		// Bricking Routine 9
		0, 0.6f, 2.f, 0, 18,
		// Data Wiper 10
		0, 0.7f, 3.f, 0, 40,
		// Antivirus Bypass 11
		0, 1.f, 0.3f, 0, 15,
		// Code Obfuscation I 12
		0, 0, 0, 0.5f, 10,
		// Code Obfuscation II 13
		0, 0, 0, 0.7f, 15,
		// Code Refactor I 14
		0, 0, 0, 0.5f, 13,
		// Code Refactor II 15
		0, 0, 0, 0.6f, 19,
		// Code Refactor III 16
		0, 0, 0, 0.7f, 25,
		// Kill Switch 17
		-0.5f, -1.f, 0, 1.5f, 24,
		// Signature Mutation 18
		0, 1.f, 1.f, 2.8f, 60,
		// Virtual Machine Detection 19
		0, 0, 0.5f, 1.4f, 25
	};

public:


	Worm();
	~Worm();

	void evolve(Upgrades*) override;
	void miniGame(int& hackingPoints);
	void makeboard();
	void printboard();
	void update();
	void getInput();

	const std::string* getNameUpgrade() const;
	const float* getStatsUpgrades() const;
	const int* getDependentIndices() const;
	const int getNumUpgrades() const;
	const int getDependentIndicesLength() const { return dependentIndicesLength; };
};

