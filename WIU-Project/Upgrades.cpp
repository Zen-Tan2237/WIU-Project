#include "Upgrades.h"

Upgrades::Upgrades() {
	name = " ";
	speed = 0;
	complexity = 0;
	payload = 0;
	resilience = 0;
}

Upgrades::Upgrades(std::string name, std::string desc, float speed, float complexity, float payload, float resilience) {
	this->name = name;
	this->desc = desc;
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

float Upgrades::getSpeed() {
	return speed;
}
float Upgrades::getComplexity() {
	return complexity;
}
float Upgrades::getPayload() {
	return payload;
}
float Upgrades::getResilience() {
	return resilience;
}