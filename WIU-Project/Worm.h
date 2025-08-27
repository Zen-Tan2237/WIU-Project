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
public:

	Worm();
	~Worm();

	void evolve(Upgrades*) override;
	void miniGame(int &hackingPoints);
	void makeboard();
	void printboard();
	void update();
	void getInput();

};

