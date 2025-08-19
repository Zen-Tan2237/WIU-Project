#include "CyberSecurity.h"
#include <iostream>

/* Function Members */
void CyberSecurity::triggerEvent(const Company& companies) {}

float CyberSecurity::cureProgressSpeed(float speed, const Virus& virus) const {
	return getGlobalCureProgress() + (speed / virus.getResilience()) * getFightStrength();
}
void CyberSecurity::advanceCure(const Virus& virus, const Company *company) {
	
	setFightStrength(sizeof(company));
	for (int i = 0; i < sizeof(company); i++) {
		if (company[i].getInfectedStatus() == 2) {
			setFightStrength(getFightStrength() - 1);
		}
	}

	switch (getDetectionLevel()) {
	case 1:
		setGlobalCureProgress(cureProgressSpeed(0.01f, virus));
		break;

	case 2:
		setGlobalCureProgress(cureProgressSpeed(0.05f, virus));
		break;

	case 3:
		setGlobalCureProgress(cureProgressSpeed(0.1f, virus));
		break;

	default:
		break;
	}
}

bool CyberSecurity::isCureComplete() {
	if (globalCureProgress >= 100) {
		cureComplete = 1;
	}
	else {
		cureComplete = 0;
	}
	return cureComplete;
}

void CyberSecurity::displayStatus() const {
	std::cout << "Status " << globalCureProgress << "%\n";
}

/* Getters */
float CyberSecurity::getGlobalCureProgress() const{
	return this->globalCureProgress;
}
int CyberSecurity::getDetectionLevel() const {
	return this->detectionLevel;
}
int CyberSecurity::getFightStrength() const {
	return this->fightStrength;
}

/* Setters */
void CyberSecurity::setGlobalCureProgress(int gcp) {
	this->globalCureProgress = gcp;
}
void CyberSecurity::setDetectionLevel(int dl) {
	this->detectionLevel = dl;
}
void CyberSecurity::setFightStrength(int fs) {
	this->fightStrength = fs;
}

/* Constructors / Destructors */
CyberSecurity::CyberSecurity() {
	globalCureProgress = 0.0f;
	cureComplete = 0;
	detectionLevel = 0;
}
/*
CyberSecurity::CyberSecurity(float gcp, int dl) {
	globalCureProgress = gcp;
	cureComplete = 0;
	detectionLevel = dl;
}
*/
CyberSecurity::~CyberSecurity() {}