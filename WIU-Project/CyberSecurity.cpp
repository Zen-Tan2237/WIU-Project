#include "CyberSecurity.h"
#include <iostream>

/* Function Members */
void CyberSecurity::triggerEvent(const Company& companies) {}

void CyberSecurity::cureProgressSpeed(int coyAmt, float speed, const Virus& virus) {
	float totalFightStrength = 0.0f;
	for (int i = 0; i < coyAmt; i++) {
		totalFightStrength += this->getFightStrength(i);
	}

	/* 
		sets cure progression base on the fighting strength, & virus resilance.
		- Progress Result = Current Progress + speed, affected by virus resilience * fighting stregth-of-each-company.
	*/
	if (virus.getResilience() > 0) {
		this->setGlobalCureProgress(this->getGlobalCureProgress() + (speed / virus.getResilience()) * totalFightStrength);
	}
}
void CyberSecurity::advanceCure(const Company* coy, const Virus& virus) {
	int coyArraySize_Byte = sizeof(coy);
	int coyArraySize = coyArraySize_Byte / sizeof(coy[0]);
	
	// sets fighting strength of each company, change scale variables via float values - in light green.
	for (int i = 0; i < coyArraySize; i++) {
		if (coy[i].getInfectedStatus() == 0) {
			this->setFightStrength(i, coy[i].getNetworkSize() / (25.0f * coyArraySize));
		}
		else if (coy[i].getInfectedStatus() == 1) {
			this->setFightStrength(i, (coy[i].getNetworkSize() - coy[i].getNoOfInfectedComputers()) / (38.0f * coyArraySize));
		}
		else {
			this->setFightStrength(i, 0.0f);
		}
	}

	// sets progress speed based on detection level
	switch (this->getDetectionLevel()) {
	case 1:
		this->cureProgressSpeed(coyArraySize, 0.01f, virus);
		break;

	case 2:
		this->cureProgressSpeed(coyArraySize, 0.04f, virus);
		break;

	case 3:
		this->cureProgressSpeed(coyArraySize, 0.1f, virus);
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
float CyberSecurity::getFightStrength(int type) const {
	return this->fightStrength[type];
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

/* Constructors / Destructors */
CyberSecurity::CyberSecurity(const Company* coy) {
	fightStrength = new float[sizeof(coy)];
	globalCureProgress = 0.0f;
	cureComplete = 0;
	detectionLevel = 0;
}
/*
CyberSecurity::CyberSecurity(int dl, float gcp, const Company* coy) {
	globalCureProgress = gcp;
	cureComplete = 0;
	detectionLevel = dl;
}
*/
CyberSecurity::~CyberSecurity() {
	delete[] fightStrength;
}