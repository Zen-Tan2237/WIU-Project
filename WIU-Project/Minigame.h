#pragma once
#include <iostream>
#include <string>

class Minigame
{
private:
public:
	Minigame() ;
	Minigame(std::string companyA, std::string companyB);
	~Minigame();
	virtual void play(); 
};

