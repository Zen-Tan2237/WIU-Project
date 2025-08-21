#include "CyberSecurity.h"
#include <iostream>

/* Function Members */
void CyberSecurity::triggerEvent(const Company& coy) {}

/* 
deadComputers/brickedIn <- If this is a thing, where can I find it?
Detection level has to increase, if not it won't work. | current 1-3;
*/
void CyberSecurity::advanceCure(Company* coy[], const Virus& virus) {
	/* sets fighting strength of each company */
	for (int i = 0; i < maxCompany; i++) {
		bool commonization = 1;
		float researchEfficiency = (((float)coy[i]->getNetworkSize() - (float)coy[i]->getNoOfInfectedComputers()) / (float)coy[i]->getNetworkSize()) * 100.0f; // percentage of uninfected computers
		
		if (researchEfficiency > 20.0f && isVirusDetected(*coy[i], virus)) {
			if (coy[i]->getInfectedStatus() == 0.0f) {
				fightStrength[i] = coy[i]->getNetworkSize() / (25.0f * maxCompany);
				commonization = 0;
			}
			else if (coy[i]->getInfectedStatus() < 1.0f) {
				fightStrength[i] = (coy[i]->getNetworkSize() - coy[i]->getNoOfInfectedComputers()) / (25.0f * maxCompany);
				 commonization = 0;
			}
		}

		if (commonization) {
			fightStrength[i] = 0.0f;
		}
	}

	this->detectionLevelCheck();
	// sets progress speed based on detection level | detection level is set to 0 on initialization.
	switch (detectionLevel) {
	case 1:
		this->cureProgressSpeed(0.005f, virus);
		break;

	case 2:
		this->cureProgressSpeed(0.022f, virus);
		break;

	case 3:
		this->cureProgressSpeed(0.041f, virus);
		break;

	case 4:
		this->cureProgressSpeed(0.087f, virus);
		break;

	default:
		break;
	}
}
void CyberSecurity::detectionLevelCheck() {
	float percentInfected = (float)Company::getTotalNoOfInfectedComputers() / (float)Company::getTotalNetworkSize() * 100.0f;
	
	if (percentInfected >= 80.0f) {
		detectionLevel = 4;
	}
	else if (percentInfected >= 60.0f) {
		detectionLevel = 3;
	}
	else if (percentInfected >= 35.0f) {
		detectionLevel = 2;
	}
	else if (percentInfected >= 5.0f) {
		detectionLevel = 1;
	}
}
bool CyberSecurity::isVirusDetected(const Company& coy, const Virus& virus) const {
	float undeadRate = static_cast<float>((coy.getNetworkSize() /* - getter_brickedIn */) / coy.getNetworkSize()) * 100.0f; // percentage of undead computers
	bool defaulted = false;

	if (undeadRate > 20.0f) {
		if (virus.getPayload() > 1.4f || (coy.getSecurityLevel() >= 9.0f /* && getter_brickedIn >= this->getDetectThreshold_individual()*/)) {}
		else if (/* getter_totalBrickedIn >= this->getDetectThreshold_global() */defaulted) {}
		else if ((coy.getSecurityLevel() >= (virus.getComplexity() - 1)) && (undeadRate > 20.0f)) {}
		else {
			return 0;
		}
		/* if brickedIn means infected */
		/*
			if (virus.getPayload() > 1.4f || (coy.getSecurityLevel() >= 9.0f && coy.getNoOfInfectedComputers() >= this->getDetectThreshold_individual(coy))) {}
			else if (coy.getTotalNoOfInfectedComputers() >= this->getDetectThreshold_global(coy)) {}
			else if ((coy.getSecurityLevel() >= (virus.getComplexity() - 1)) && (undeadRate > 20.0f)) {}
			else {
				return 0;
			}
		*/
	}
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
		
		if (this->globalCureProgress > 100.0f) {
			this->globalCureProgress = 100.0f;
		}
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
	std::cout << "Cure Status " << globalCureProgress << "%\n";
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
int CyberSecurity::getDetectThreshold_individual(const Company& coy) const {
	return static_cast<int>(100 - (coy.getSecurityLevel() / 0.1f)) + 1;
}
int CyberSecurity::getDetectThreshold_global(const Company& coy) const {
	return this->getDetectThreshold_individual(coy) * 10;
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