#include "CyberSecurity.h"
#include <iostream>
#include <windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int CyberSecurity::detectionLevel = 0;
float CyberSecurity::globalCureProgress = 0.0f;
bool CyberSecurity::cureComplete = 0;
float CyberSecurity::infectedRate_global = 0;

int CyberSecurity::cyberNewsCount[2] = { 0, 0 };
float CyberSecurity::infectThreshold[4] = { 10.0f, 50.0f, 75.0f, 90.0f };
float CyberSecurity::cureThreshold[4] = { 35.0f, 50.0f, 75.0f, 95.0f };


/* Function Members */
void CyberSecurity::triggerEvent(Company* coy[], const Virus& virus, const News& news) const{
	int coyChoice1 = whichCompanyIsPossible(coy);
	int coyChoice2;

	if (coyChoice1 != -1) {
		do {
			coyChoice2 = whichCompanyIsPossible(coy);
		} while (coyChoice1 == coyChoice2);

		// Code for news and changing of cure status.
		news.companyCollabNews(coy[coyChoice1]->getName(), coy[coyChoice2]->getName());
	}
	for (int i = 0; i < maxCompany; i++) {
		if (isVirusDetected(undeadRate[i], *coy[i], virus)) {
			news.virusFoundNews(coy[i]->getName()); // Call for ew virus
		}
		if (coy[i]->getBrickedStatus() == coy[i]->getNetworkSize()) {
			news.companyDeadNews(coy[i]->getName()); // Code for coy dead
		}
	}
	if (globalCureProgress >= cureThreshold[cyberNewsCount[0]]) {
		news.cybersecurityWinningNews(); // Code for cyber wins
	}
	if (infectedRate_global >= infectThreshold[cyberNewsCount[1]]) {
		news.cyberSecurityLosingNews(); // Code for cyber losses
	}
}
	int CyberSecurity::whichCompanyIsPossible(Company* coy[]) const {
		int coyChoice = -1;
		bool breakLoop = 0;
		do {
			coyChoice = rand() % maxCompany;
			if (Company::getTotalNoOfBrickedComputers() == Company::getTotalNetworkSize()) {
				breakLoop = 1;
				coyChoice = -1;
			}
		} while ((coy[coyChoice]->getNoOfBrickedComputers() != coy[coyChoice]->getNetworkSize()) || breakLoop);
		return coyChoice;
	}

/*
deadComputers/brickedIn <- If this is a thing, where can I find it?
Detection level has to increase, if not it won't work. | current 1-3;
*/
void CyberSecurity::advanceCure(Company* coy[], const Virus& virus) {
	for (int i = 0; i < maxCompany; i++) { // determines if fighting strength is 0 or a value.
		bool commonization = 1;
		this->setResearchEfficiency(i, coy);
		this->setUndeadRate(i, coy);
		this->setInfectedRate_global();
		isResearching[i] = 0;

		if (this->isVirusDetected(undeadRate[i], *coy[i], virus)) { // can the company detect the virus.
			this->detectionLevelCheck(); // values are thresholds, smallest-to-largest percentage of infected computers.
			if (undeadRate[i] > 20.0f) {
				if (detectionLevel >= 1) {
					isResearching[i] = 1;
				}
				fightStrength[i] = ((coy[i]->getNetworkSize() - coy[i]->getNoOfBrickedComputers()) / (250.0f * maxCompany)) * researchEfficiency[i];
				commonization = 0;
			}
		}

		if (commonization) { // communized code if the conditions are not met.
			fightStrength[i] = 0.0f;
		}
	}

	switch (detectionLevel) { // sets progress speed based on detection level | detection level is set to 0 on initialization.
	case 1: {
		this->cureProgressSpeed(0.016f, virus);
		break;
	}
	case 2: {
		this->cureProgressSpeed(0.036f, virus);
		break;
	}
	case 3: {
		this->cureProgressSpeed(0.049f, virus);
		break;
	}
	case 4: {
		this->cureProgressSpeed(0.093f, virus);
		break;
	}
	default: {
		break;
	}
	}
}
	bool CyberSecurity::isVirusDetected(float udr, const Company& coy, const Virus& virus) const { // does the company detect the virus
		if (virus.getPayload() > 1.4f || (coy.getSecurityLevel() >= 9.0f && (coy.getNoOfBrickedComputers() >= getDetectThreshold_individual(coy)))) {}
		else if (Company::getTotalNoOfBrickedComputers() >= this->getDetectThreshold_global(coy)) {}
		else if ((coy.getSecurityLevel() >= (virus.getComplexity() - 1)) && (udr > 20.0f)) {}
		else {
			return 0;
		}
		return 1;
	}
	void CyberSecurity::detectionLevelCheck() {
		if (infectedRate_global >= infectThreshold[3]) {
			detectionLevel = 4;
		}
		else if (infectedRate_global >= infectThreshold[2]) {
			detectionLevel = 3;
		}
		else if (infectedRate_global >= infectThreshold[1]) {
			detectionLevel = 2;
		}
		else if (infectedRate_global >= infectThreshold[0]) {
			detectionLevel = 1;
		}
	}
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

/* Display Status */
void CyberSecurity::displayStatus() const {
	std::cout
		<< "Cure Status " << globalCureProgress << "%\n"
		<< "Detection Level " << detectionLevel << '\n';
	/* Program Debug Values */
	/*
	SetConsoleTextAttribute(hConsole, 3);
	for (int i = 1; i < maxCompany+1; i++) {
		std::cout << "R" << i << " " << isResearching[i - 1] << " ";
	}
	std::cout << '\n';
	for (int i = 1; i < maxCompany+1; i++) {
		std::cout << "RsrcEfincy" << i << " " << researchEfficiency[i - 1] << " ";
	}
	std::cout << '\n';
	for (int i = 1; i < maxCompany + 1; i++) {
		std::cout << "FStr" << i << " " << fightStrength[i - 1] << " ";
	}
	std::cout << '\n';
	SetConsoleTextAttribute(hConsole, 7);
	*/
}
/* Losing Condition */
bool CyberSecurity::isCureComplete() {
	if (globalCureProgress == 100.0f) {
		return cureComplete = 1;
	}
	else {
		return cureComplete = 0;
	}
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
bool* CyberSecurity::getCompaniesResearchStatus() const{
	return isResearching;
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
void CyberSecurity::setUndeadRate(int type, Company* coy[]) {
	this->undeadRate[type] = ((coy[type]->getNetworkSize() - coy[type]->getNoOfBrickedComputers()) / (float)coy[type]->getNetworkSize()) * 100.0f; // percentage of undead computers
}
void CyberSecurity::setResearchEfficiency(int type, Company* coy[]) {
	this->researchEfficiency[type] = (coy[type]->getNetworkSize() - coy[type]->getNoOfInfectedComputers()) / (float)coy[type]->getNetworkSize(); // value of uninfected computers 0-1, the scalar value.
	if (this->researchEfficiency[type] < 0.01f) {
		this->researchEfficiency[type] = 0.01f;
	}
}
void CyberSecurity::setInfectedRate_global() {
	this->infectedRate_global = (Company::getTotalNoOfInfectedComputers() / (float)Company::getTotalNetworkSize()) * 100.0f;
}

/* Constructors / Destructors */
CyberSecurity::CyberSecurity(int coyAmt) {
	maxCompany = coyAmt;
	fightStrength = new float[coyAmt];
	researchEfficiency = new float[coyAmt];
	isResearching = new bool[coyAmt];
	undeadRate = new float[coyAmt];
}
CyberSecurity::~CyberSecurity() {
	delete[] 
		fightStrength, 
		undeadRate,
		researchEfficiency,
		isResearching
		;
	researchEfficiency = nullptr;
	undeadRate = nullptr;
	fightStrength = nullptr;
	isResearching = nullptr;
}