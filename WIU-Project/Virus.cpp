#include "Virus.h"

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

int Virus::getStealth() const{
	return stealth;
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

void Virus::setStealth(int stealth) {
	this->stealth = stealth;
}