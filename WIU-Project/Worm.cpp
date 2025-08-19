#include "Worm.h"

Worm::Worm() {
	speed = 0;
	stealth = 0;
	payload = 0;
	resilience = 0;
}

Worm::Worm(int speed, int stealth, int payload, int resilience) {
	this->speed = speed;
	this->stealth = stealth;
	this->payload = payload;
	this->resilience = resilience;
}

Worm::~Worm() {

}

void Worm::evolve(std::string name) {

}
void Worm::applyEffect(Company& company) {

}
void Worm::displayStats() const {

}