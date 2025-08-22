#include "CyberSecurity.h"
#include <iostream>

/* Function Members */
void CyberSecurity::triggerEvent(const Company& coy) {}

/*
deadComputers/brickedIn <- If this is a thing, where can I find it?
Detection level has to increase, if not it won't work. | current 1-3;
*/
/* Start */
void CyberSecurity::advanceCure(Company* coy[], const Virus& virus) {
	for (int i = 0; i < maxCompany; i++) { // determines if fighting strength is 0 or a value.
		bool commonization = 1;
		float researchEfficiency = (coy[i]->getNetworkSize() - coy[i]->getNoOfInfectedComputers()) / (float)coy[i]->getNetworkSize(); // value of uninfected computers 0-1, the scalar value.
		float undeadRate = ((coy[i]->getNetworkSize() - coy[i]->getBrickedStatus()) / (float)coy[i]->getNetworkSize()) * 100.0f; // percentage of undead computers

		/* 1 */
		if (/*a*/isVirusDetected(undeadRate, *coy[i], virus)) { // can the company detect the virus.
			/*b*/this->detectionLevelCheck(15.0f, 45.0f, 70.0f, 90.0f); // values are thresholds, smallest-to-largest percentage of infected computers.
			/*c*/
			if (coy[i]->getInfectedStatus() == 0.0f && undeadRate > 20.0f) {
				fightStrength[i] = ((coy[i]->getNetworkSize() - coy[i]->getInfectedStatus()) / (25.0f * maxCompany)) * researchEfficiency;
				commonization = 0;
			}
		}

		if (commonization) { // communized code if the conditions are not met.
			fightStrength[i] = 0.0f;
		}
	}

	/*d*/
	switch (detectionLevel) { // sets progress speed based on detection level | detection level is set to 0 on initialization.
	case 1:
		this->cureProgressSpeed(0.016f, virus);
		break;

	case 2:
		this->cureProgressSpeed(0.036f, virus);
		break;

	case 3:
		this->cureProgressSpeed(0.049f, virus);
		break;

	case 4:
		this->cureProgressSpeed(0.093f, virus);
		break;

	default:
		break;
	}
}
/*a*/
bool CyberSecurity::isVirusDetected(float ur, const Company& coy, const Virus& virus) const {
	if (virus.getPayload() > 1.4f || (coy.getSecurityLevel() >= 9.0f && coy.getBrickedStatus() >= this->getDetectThreshold_individual(coy))) {}
	else if (Company::getTotalNoOfBrickedComputers() >= this->getDetectThreshold_global(coy)) {}
	else if ((coy.getSecurityLevel() >= (virus.getComplexity() - 1)) && (ur > 20.0f)) {}
	else {
		return 0;
	}
	return 1;
}
/*b*/
void CyberSecurity::detectionLevelCheck(float threshold1, float threshold2, float threshold3, float threshold4) {
	float percentInfected = (Company::getTotalNoOfInfectedComputers() / (float)Company::getTotalNetworkSize()) * 100.0f;

	if (percentInfected >= threshold4) {
		detectionLevel = 4;
	}
	else if (percentInfected >= threshold3) {
		detectionLevel = 3;
	}
	else if (percentInfected >= threshold2) {
		detectionLevel = 2;
	}
	else if (percentInfected >= threshold1) {
		detectionLevel = 1;
	}
}
/*d*/
void CyberSecurity::cureProgressSpeed(float speed, const Virus& virus) {
	float totalFightStrength = 0.0f;

	for (int i = 0; i < maxCompany; i++) {
		totalFightStrength += fightStrength[i]; // Sets total fight strength.
	}

	if (virus.getResilience() > 0 && virus.getComplexity() > 0) { // sets cure progression
		this->globalCureProgress += (speed / (virus.getResilience() * virus.getComplexity())) * totalFightStrength;

		if (this->globalCureProgress > 100.0f) {
			this->globalCureProgress = 100.0f;
		}
	}
}

/* Losing Condition */
bool CyberSecurity::isCureComplete() {
	if (globalCureProgress == 100.0f) {
		cureComplete = 1;
	}
	else {
		cureComplete = 0;
	}
	return cureComplete;
}
/* Display Status */
void CyberSecurity::displayStatus() const {
	std::cout << "Cure Status " << globalCureProgress << "%\n";
}

/* Getters */
float CyberSecurity::getGlobalCureProgress() const {
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
	return (int)(100 - (coy.getSecurityLevel() / 0.1f)) + 1;
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
	globalCureProgress = 0.0f;
	cureComplete = 0;
	detectionLevel = 0;
	fightStrength = new float[coyamt];
}
/*
CyberSecurity::CyberSecurity(int coyAmt, int dl, float gcp) {
	maxCompany = coyAmt;
	globalCureProgress = gcp;
	cureComplete = 0;
	detectionLevel = dl;
	fightStrength = new float[coyAmt];
}
*/
CyberSecurity::~CyberSecurity() {
	delete[] fightStrength;
	fightStrength = nullptr;
}