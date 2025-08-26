#include "Virus.h"
#include "Upgrades.h"

Virus::Virus() {

	name = "I nate higgers";
	speed = 0;
	complexity = 0;
	payload = 0;
	resilience = 0;
}

Virus::~Virus() {

}

void Virus::evolve(Upgrades* toUpgrade) {
	std::cout << "Speed to upgrade: " << toUpgrade->getSpeed() << std::endl
		<< " Complexity to upgrade: " << toUpgrade->getComplexity() << std::endl
		<< " Payload to upgrade" << toUpgrade->getPayload() << std::endl
		<< " Resilience to upgrade" << toUpgrade->getResilience() << std::endl;

	speed += toUpgrade->getSpeed();
	complexity += toUpgrade->getComplexity();
	payload += toUpgrade->getPayload();
	resilience += toUpgrade->getResilience();
}

void Virus::setAll10() {
	speed += 10;
	complexity += 10;
	payload += 10;
	resilience += 10;
}

void Virus::displayStats() {
	std::cout << "Speed: " << speed << std::endl
		<< " Complexity: " << complexity << std::endl
		<< " Payload: " << payload << std::endl
		<< " Resilience: " << resilience << std::endl;
}

std::string Virus::getName() const {
	return name;
}

float Virus::getPayload() const {
	return payload;
}

float Virus::getResilience() const{
	return resilience;
}
float Virus::getSpeed() const {
	return speed;
}

float Virus::getComplexity() const{
	return complexity;
}

void Virus::setName(std::string name) {
	this->name = name;
}

void Virus::setPayload(float payload) {
	this->payload = payload;
}

void Virus::setResilience(float resilience) {
	this->resilience = resilience;
}

void Virus::setSpeed(float speed) {
	this->speed = speed;
}

void Virus::setComplexity(float complexity) {
	this->complexity = complexity;
}