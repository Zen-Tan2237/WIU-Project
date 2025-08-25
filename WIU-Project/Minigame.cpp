#include "Minigame.h"

Minigame::Minigame() 
{

}
Minigame::Minigame(std::string companyA, std::string companyB)
{
	std::cout << "Virus is spreading from " << companyA << " to " << companyB << ". Try to hack to earn more points" << std::endl;
	play();
}
Minigame::~Minigame() 
{

}

void Minigame::play()
{
	std::string input;
	bool playing = true;
	while (playing == true) {
		std::cout << "'E' to exit game" << std::endl;
		std::cin >> input;
		if (input == "E" || input == "e") {
			playing = false;
		}
	}
}