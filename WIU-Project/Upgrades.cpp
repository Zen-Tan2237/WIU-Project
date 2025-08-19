#include "Upgrades.h"

Upgrades::Upgrades() {
	name = " ";
	speed = 0;
	complexity = 0;
	payload = 0;
	resilience = 0;
}

Upgrades::Upgrades(std::string name, int speed, int complexity, int payload, int resilience) {
	this->name = name;
	this->speed = speed;
	this->complexity = complexity;
	this->payload = payload;
	this->resilience = resilience;
}

Upgrades::~Upgrades() {

}

std::string Upgrades::getName() {
	return name;
}

int Upgrades::getSpeed() {
	return speed;
}
int Upgrades::getComplexity() {
	return complexity;
}
int Upgrades::getPayload() {
	return payload;
}
int Upgrades::getResilience() {
	return resilience;
}