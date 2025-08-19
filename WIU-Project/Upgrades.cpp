#include "Upgrades.h"

Upgrades::Upgrades() {
	name = " ";
	speed = 0;
	stealth = 0;
	payload = 0;
	resilience = 0;
}

Upgrades::Upgrades(std::string name, int speed, int stealth, int payload, int resilience) {
	this->name = name;
	this->speed = speed;
	this->stealth = stealth;
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
int Upgrades::getStealth() {
	return stealth;
}
int Upgrades::getPayload() {
	return payload;
}
int Upgrades::getResilience() {
	return resilience;
}