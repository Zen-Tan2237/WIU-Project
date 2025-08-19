#pragma once

#include <iostream>
#include <string>
#include "Virus.h"

class Player
{
private:
	int hackingPoints; // Points for the virus
	Virus* playerVirus; // Virus that the player has
	int companyChoice;

public:
	Player();
	~Player();

	void earnPoints(int points);
	bool spendPoints(int points);

	void setInitials(Company* companyList[]);
	void update();

	// Getters and Setters
	int getHackingPoints() const;
	int getCompanyChoice() const;
	void setCompanyChoice(int choice);	
	Virus* getPlayerVirus() const;
	
	void setHackingPoints(int hackingPoints);



};

