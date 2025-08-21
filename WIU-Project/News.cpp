#include "News.h"
#include <iostream>
#include <cstdlib>
#include <ctime>  

News::News()
{
	srand(time(0));
}

News::~News()
{
}

void News::companyCollabNews()
{
	int i = rand() % 5;
	std::cout << randomEventHeadlines[0][i] << std::endl
			  << randomEventsDescriptions[0][i] << std::endl;
}

void News::virusFoundNews()
{
	int i = rand() % 5;
	std::cout << randomEventHeadlines[1][i] << std::endl
			  << randomEventsDescriptions[1][i] << std::endl;
}

void News::cybersecurityWinningNews()
{
	int i = rand() % 5;
	std::cout << randomEventHeadlines[2][i] << std::endl
			  << randomEventsDescriptions[2][i] << std::endl;
}

void News::cyberSecurityLosingNews()
{
	int i = rand() % 5;
	std::cout << randomEventHeadlines[3][i] << std::endl
			  << randomEventsDescriptions[3][i] << std::endl;
}

void News::companyDeadNews()
{
	int i = rand() % 5;
	std::cout << randomEventHeadlines[4][i] << std::endl
			  << randomEventsDescriptions[4][i] << std::endl;
}