#include "Virus.h"
#include "Upgrades.h"

Virus::Virus() {
	name = " ";
	speed = 0;
	complexity = 0;
	payload = 0;
	resilience = 0;
}

Virus::~Virus() {

}

void Virus::evolve(Upgrades& toUpgrade) {
	std::cout << "Speed to upgrade: " << toUpgrade.getSpeed()
		<< "Complexity to upgrade: " << toUpgrade.getComplexity()
		<< "Payload to upgrade" << toUpgrade.getPayload()
		<< "Resilience to upgrade" << toUpgrade.getResilience() << std::endl;

	speed += toUpgrade.getSpeed();
	complexity += toUpgrade.getComplexity();
	payload += toUpgrade.getPayload();
	resilience += toUpgrade.getResilience();
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