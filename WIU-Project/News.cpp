#include "News.h"
#include <iostream>
#include <cstdlib>
#include <ctime>  

News::News()
{
}

News::~News()
{
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