#include "Worm.h"

Worm::Worm() {
	speed = 4; // 1 for slow 5 max
	complexity = 2; // 1 to 10
	payload = 1; // 1 to 10
	resilience = 2; //1 to 10
	mutationProbability = 15;
}

Worm::~Worm() {

}

void Worm::mutate(int** upgradesArray, int* currentUpgradesIndexs) {
	
}

void Worm::evolve(Upgrades* toUpgrade) {
	std::cout << "Speed to upgrade: " << (toUpgrade->getSpeed() + 0.5f) << std::endl
		<< " Complexity to upgrade: " << toUpgrade->getComplexity() << std::endl
		<< " Payload to upgrade" << toUpgrade->getPayload() << std::endl
		<< " Resilience to upgrade" << toUpgrade->getResilience() << std::endl;

	speed += (toUpgrade->getSpeed() + 0.5f);
	complexity += toUpgrade->getComplexity();
	payload += toUpgrade->getPayload();
	resilience += toUpgrade->getResilience();
}

void Worm::miniGame(int hackingPoints) {

}