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
	Virus* playerVirus; 

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
	Virus* getPlayerVirus() const;
	
	void setHackingPoints(int hackingPoints);



};

