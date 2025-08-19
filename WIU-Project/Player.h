#pragma once

#include <iostream>
#include <string>
#include "Virus.h"

class Player
{
private:
	int hackingPoints; // Points for the virus
	Virus* playerVirus; // Virus that the player has

public:
	Player();
	~Player();

	void earnPoints(int points);
	bool spendPoints(int points);

	void showMenu();
	void setInitials();

	// Getters and Setters
	int getHackingPoints() const;

	void setHackingPoints(int hackingPoints);
};

