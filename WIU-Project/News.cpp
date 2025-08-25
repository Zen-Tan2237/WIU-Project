#include "News.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>  

News::News()
{
}

News::~News()
{
}

News::News(std::string VirusName)
{
	randomEventHeadlines[2][1] =
	{ "Global Cybersecurity Teams Contain Spread of " + VirusName + " Virus in Record Time." };
	randomEventHeadlines[3][2] =
	{ VirusName + "Virus Outpaces Global Cybersecurity Defenses." };

	randomEventsDescriptions[4][1] =
	{ "Employee said\"It was so sudden when when our computers all got destroyed at the same time by" + VirusName + "\"" };

	WinOrLoseNewsHeadlines[0][0] =
	{ "The Worlds Economy Has Taken A Big Hit After Major Companies Have Been Destroyed from " + VirusName };
}

void News::companyCollabNews(std::string companyA, std::string companyB) const
{
	srand(time(0));
	int i = rand() % 5;
	std::cout << companyA << " and " << companyB << randomEventHeadlines[0][i] << std::endl
			  << randomEventsDescriptions[0][i] << std::endl;	
}

void News::virusFoundNews(std::string company) const
{
	srand(time(0));
	int i = rand() % 5;
	std::cout << company << randomEventHeadlines[1][i] << std::endl
			  << randomEventsDescriptions[1][i] << std::endl;
}

void News::cybersecurityWinningNews() const
{
	srand(time(0));
	int i = rand() % 5;
	std::cout << randomEventHeadlines[2][i] << std::endl
			  << randomEventsDescriptions[2][i] << std::endl;
}

void News::cyberSecurityLosingNews() const
{
	srand(time(0));
	int i = rand() % 5;
	std::cout << randomEventHeadlines[3][i] << std::endl
			  << randomEventsDescriptions[3][i] << std::endl;
}

void News::companyDeadNews(std::string company) const
{
	srand(time(0));
	int i = rand() % 5;
	std::cout << company << randomEventHeadlines[4][i] << std::endl
			  << randomEventsDescriptions[4][i] << std::endl;
}

void News::PlayerWinNews() const
{
	srand(time(0));
	int i = rand() % 2;
	std::cout << WinOrLoseNewsHeadlines[0][i] << std::endl
		     << WinOrLoseNewsDescriptions[0][i] << std::endl;
}

void News::PlayerLoseNews() const
{
	srand(time(0));
	int i = rand() % 2;
	std::cout << WinOrLoseNewsHeadlines[1][i] << std::endl
		     << WinOrLoseNewsDescriptions[1][i] << std::endl;
}
