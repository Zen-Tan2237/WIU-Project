#include "Upgrades.h"

Upgrades::Upgrades() {
	name = " ";
	desc = " ";
	cost = 0;
	speed = 0;
	complexity = 0;
	payload = 0;
	resilience = 0;
}

Upgrades::Upgrades(std::string name, std::string desc, float speed, float complexity, float payload, float resilience, float cost) {
	this->name = name;
	this->desc = desc;
	this->speed = speed;
	this->complexity = complexity;
	this->payload = payload;
	this->resilience = resilience;
	this->cost = cost;
}

Upgrades::~Upgrades() {

}

std::string Upgrades::getName() const {
	return name;
}

float Upgrades::getSpeed() const {
	return speed;
}
float Upgrades::getComplexity() const {
	return complexity;
}
float Upgrades::getPayload() const {
	return payload;
}
float Upgrades::getResilience() const {
	return resilience;
}

std::string Upgrades::getDesc() const {
	return desc;
}

float Upgrades::getCost() const {
	return cost;
}