#include "CyberSecurity.h"
#include <iostream>

/* Function Members */
void CyberSecurity::triggerEvent(const Company& coy) {}

void CyberSecurity::cureProgressSpeed(float speed, const Virus& virus) {
	float totalFightStrength = 0.0f;
	for (int i = 0; i < maxCompany; i++) {
		totalFightStrength += fightStrength[i];
	}

	/* 
		sets cure progression base on the fighting strength, virus resilience & virus complexity.
		- Progress Result = Current Progress + speed, affected by virus resilience * fighting strength-of-each-company.
	*/
	if (virus.getResilience() > 0 && virus.getComplexity() > 0) {
		globalCureProgress += (speed / (virus.getResilience() * virus.getComplexity())) * totalFightStrength;
	}
	if (globalCureProgress > 100.0f) {
		globalCureProgress = 100.0f;
	}
}
void CyberSecurity::advanceCure(const Company* coy, const Virus& virus) {
	// sets fighting strength of each company, change scale variables via float values - in light green.
	for (int i = 0; i < maxCompany; i++) {
		if (coy[i].getInfectedStatus() == 0) {
			fightStrength[i] =  coy[i].getNetworkSize() / (25.0f * maxCompany);
		}
		else if (coy[i].getInfectedStatus() == 1) {
			fightStrength[i] = (coy[i].getNetworkSize() - coy[i].getNoOfInfectedComputers()) / (38.0f * maxCompany);
		}
		else {
			fightStrength[i] = 0.0f;
		}
	}

	// sets progress speed based on detection level | detection level is set to 0 on initialization.
	switch (detectionLevel) {
	case 1:
		this->cureProgressSpeed(0.01f, virus);
		break;

	case 2:
		this->cureProgressSpeed(0.04f, virus);
		break;

	case 3:
		this->cureProgressSpeed(0.1f, virus);
		break;

	default:
		break;
	}
}

bool CyberSecurity::isCureComplete() {
	if (globalCureProgress == 100.0f) {
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
float CyberSecurity::getFightStrength(int type) const {
	return this->fightStrength[type];
}
bool CyberSecurity::getCureComplete() const {
	return this->cureComplete;
}
int CyberSecurity::getMaxCompany() const {
	return this->maxCompany;
}

/* Setters */
void CyberSecurity::setGlobalCureProgress(float gcp) {
	this->globalCureProgress = gcp;
}
void CyberSecurity::setDetectionLevel(int dl) {
	this->detectionLevel = dl;
}
void CyberSecurity::setFightStrength(int type, float fs) {
	this->fightStrength[type] = fs;
}
void CyberSecurity::setCureComplete(bool cc) {
	this->cureComplete = cc;
}

/* Constructors / Destructors */
CyberSecurity::CyberSecurity(int coyamt) {
	maxCompany = coyamt;
	fightStrength = new float[coyamt];
	globalCureProgress = 0.0f;
	cureComplete = 0;
	detectionLevel = 0;
}
/*
CyberSecurity::CyberSecurity(int coyamy, int dl, float gcp) {
	maxCompany = coyamt;
	fightStrength = new float[coyamt];
	globalCureProgress = gcp;
	cureComplete = 0;
	detectionLevel = dl;
}
*/
CyberSecurity::~CyberSecurity() {
	delete[] fightStrength;
	fightStrength = nullptr;
}