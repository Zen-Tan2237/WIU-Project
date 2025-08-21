#include "CyberSecurity.h"
#include <iostream>

/* Function Members */
void CyberSecurity::triggerEvent(const Company& coy) {}

int CyberSecurity::detectionThreshold_individual(const Company& coy) const {
	float value = coy.getSecurityLevel() / 0.5f;
	return static_cast<int>((20 - value) * 5) + 5;
}
int CyberSecurity::detectionThreshold_global(const Company& coy) const {
	float value = coy.getSecurityLevel() / 0.5f;
	return static_cast<int>((((20 - value) * 5) + 5) * 10);
}

bool CyberSecurity::isVirusDetected(const Company& coy, const Virus& virus) const {
	float undeadRate = static_cast<float>((coy.getNetworkSize() /* - getter_brickedIn */) / coy.getNetworkSize()) * 100.0f; // percentage of undead computers
	
	if (virus.getPayload() > 1.4f || (coy.getSecurityLevel() >= 9.0f /* && getter_brickedIn > this->detectionThreshold_individual()*/)) {}
	else if (/* getter_totalBrickedIn > this->detectionThreshold_global() */1) {}
	else if ((coy.getSecurityLevel() >= (virus.getComplexity() - 1)) && (undeadRate > 20.0f)) {}
	else {
		return 0;
	}
	return 1;
}
void CyberSecurity::cureProgressSpeed(float speed, const Virus& virus) {
	float totalFightStrength = 0.0f;
	for (int i = 0; i < maxCompany; i++) {
		totalFightStrength += fightStrength[i];
	}
	
	// sets cure progression base on the fighting strength, virus resilience & virus complexity.
	if (virus.getResilience() > 0 && virus.getComplexity() > 0) {
		this->globalCureProgress += (speed / (virus.getResilience() * virus.getComplexity())) * totalFightStrength;
	}
	if (this->globalCureProgress > 100.0f) {
		this->globalCureProgress = 100.0f;
	}
}
void CyberSecurity::advanceCure(const Company* coy[], const Virus& virus) {
	/* sets fighting strength of each company */
	for (int i = 0; i < maxCompany; i++) {
		bool commonization = 1;
		float researchEfficiency = static_cast<float>((coy[i]->getNetworkSize() - coy[i]->getNoOfInfectedComputers()) / coy[i]->getNetworkSize()) * 100.0f; // percentage of uninfected computers

		if (this->isVirusDetected(*coy[i], virus) && researchEfficiency < 80.0f) {
			if (coy[i]->getInfectedStatus() == 0) {
				fightStrength[i] = coy[i]->getNetworkSize() / (25.0f * maxCompany);
				commonization = 0;
			}
			else if (coy[i]->getInfectedStatus() == 1) {
				fightStrength[i] = (coy[i]->getNetworkSize() - coy[i]->getNoOfInfectedComputers()) / (25.0f * maxCompany);
				 commonization = 0;
			}
		}
		if (commonization) {
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
CyberSecurity::CyberSecurity(int coyAmt, int dl, float gcp) {
	maxCompany = coyAmt;
	fightStrength = new float[coyAmt];
	globalCureProgress = gcp;
	cureComplete = 0;
	detectionLevel = dl;
}
*/
CyberSecurity::~CyberSecurity() {
	delete[] fightStrength;
	fightStrength = nullptr;
}