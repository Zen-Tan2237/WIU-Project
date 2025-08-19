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
	speed += toUpgrade.getSpeed();
	complexity += toUpgrade.getComplexity();
	payload += toUpgrade.getPayload();
	resilience += toUpgrade.getResilience();
}

std::string Virus::getName() const {
	return name;
}

int Virus::getPayload() const {
	return payload;
}

int Virus::getResilience() const{
	return resilience;
}
int Virus::getSpeed() const {
	return speed;
}

int Virus::getComplexity() const{
	return complexity;
}

void Virus::setName(std::string name) {
	this->name = name;
}

void Virus::setPayload(int payload) {
	this->payload = payload;
}

void Virus::setResilience(int resilience) {
	this->resilience = resilience;
}

void Virus::setSpeed(int speed) {
	this->speed = speed;
}

void Virus::setComplexity(int complexity) {
	this->complexity = complexity;
}