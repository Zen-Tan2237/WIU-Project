#include "Trojan.h"

Trojan::Trojan() {
	speed = 2.1f; // 1 for slow 5 max
	complexity = 3; // 1 to 10
	payload = 3; // 1 to 10
	resilience = 4; //1 to 10
}

Trojan::~Trojan() {
	
}

void Trojan::evolve(Upgrades* toUpgrade) {
	std::cout << "Speed to upgrade: " << (toUpgrade->getSpeed() + 0.5f) << std::endl
		<< " Complexity to upgrade: " << toUpgrade->getComplexity() << std::endl
		<< " Payload to upgrade" << toUpgrade->getPayload() << std::endl
		<< " Resilience to upgrade" << toUpgrade->getResilience() << std::endl;

	speed += (toUpgrade->getSpeed() + 0.5f);
	complexity += toUpgrade->getComplexity();
	payload += toUpgrade->getPayload();
	resilience += toUpgrade->getResilience();
}

void Trojan::miniGame(int hackingPoints) {

}