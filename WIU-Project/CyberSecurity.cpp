#include "CyberSecurity.h"
#include <iostream>
#include <windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int CyberSecurity::detectionLevel = 0;
float CyberSecurity::globalCureProgress = 0.0f;
bool CyberSecurity::cureComplete = 0;
float CyberSecurity::infectedRate_global = 0;

int CyberSecurity::cyberNewsCount[2] = { 0, 0 };
float CyberSecurity::infectThreshold[4] = { 3.0f, 15.0f, 39.0f, 75.0f };
float CyberSecurity::cureThreshold[4] = { 35.0f, 50.0f, 75.0f, 95.0f };

/* +++++++++++++++++++++++++++++++++++++++++++++ */
/* Function Members */

/* News */
void CyberSecurity::triggerEvent(Company* coy[], const Virus& virus, const News& news) {
	/* Virus Found ------------------------------------------ */ {
		for (int i = 0; i < maxCompany; i++) {
			if (isVDetect[i]) {
				news.virusFoundNews(coy[i]->getName());
			}
		}
	}
	/* Collab ----------------------------------------------- */ {
		int coyChoice1 = whichCompanyIsPossible(coy);
		int coyChoice2;

		if (coyChoice1 != -1) {
			do {
				coyChoice2 = whichCompanyIsPossible(coy);
			} while (coyChoice1 == coyChoice2);

			// Code for news and changing of cure status.
			if (coyChoice2 != -1) {
				news.companyCollabNews(coy[coyChoice1]->getName(), coy[coyChoice2]->getName());
			}
		}
	}
	/* Cyber Win/Loss --------------------------------------- */ {
		if (globalCureProgress >= cureThreshold[cyberNewsCount[0]]) {
			news.cybersecurityWinningNews(); // Code for cyber wins
			cyberNewsCount[0]++;
		}
		if (infectedRate_global >= infectThreshold[cyberNewsCount[1]]) {
			news.cyberSecurityLosingNews(); // Code for cyber losses
			cyberNewsCount[1]++;
		}
	}
	/* Win/Loss Condition ----------------------------------- */ {
		if (Company::getTotalNoOfBrickedComputers() == Company::getTotalNetworkSize()) {
			news.PlayerWinNews();
		}
		else if (isCureComplete()) {
			news.PlayerLoseNews();
		}

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
	} while ((coy[coyChoice]->getNoOfBrickedComputers() == coy[coyChoice]->getNetworkSize()) || breakLoop);
	return coyChoice;
}

/* Cure Progress Bar */
void CyberSecurity::advanceCure(Company* coy[], const Virus& virus) {
	this->setInfectedRate_global();

	for (int i = 0; i < maxCompany; i++) { // determines if fighting strength is 0 or a value.
		bool commonization = 1;
		this->setResearchEfficiency(i, *coy[i]);
		this->setUndeadRate(i, *coy[i]);
		isResearching[i] = 0;
		isVDetect[i] = 0;

		if (this->isVirusDetected(undeadRate[i], *coy[i], virus)) { // can the company detect the virus.
			isVDetect[i] = 1;
			this->detectionLevelCheck();
			if (doResearch(i, 20.0f)) {
				isResearching[i] = 1;
				this->setFightStrength(i, *coy[i]);
				commonization = 0;
			}
		}

		if (commonization) { // communized code if the conditions are not met.
			fightStrength[i] = 0.0f;
		}
	}

	switch (detectionLevel) { // sets progress speed based on detection level | detection level is set to 0 on initialization.
	case 1: {
		this->cureProgressSpeed(409, virus); // 0.001 -> 1 to INF;
		break;
	}
	case 2: {
		this->cureProgressSpeed(617, virus); // 0.001 -> 1 to INF;
		break;
	}
	case 3: {
		this->cureProgressSpeed(825, virus); // 0.001 -> 1 to INF;
		break;
	}
	case 4: {
		this->cureProgressSpeed(1433, virus); // 0.001 -> 1 to INF;
		break;
	}
	default: {
		break;
	}
	}
}
bool CyberSecurity::isVirusDetected(float udr, const Company& coy, const Virus& virus) const { // does the company detect the virus
	/* 
	True:
	If number of infected is more than 0 ---AND---,
	If payload is more than 1.4 ---OR---, 
	if company security level is more or equals to 9, with the number of bricked/dead computers being more or equals to the individual threshold for bricked/dead computers on company property ---OR---,
	if total/global bricked/dead computers being more ot equals to the individual thresholds for bricked computers globally ---OR---,
	if the company securityLevel is more than the virus complexity, with the number of bricked/dead computers being less than 80%.

	False:
	otherwise.
	*/
	if (coy.getNoOfInfectedComputers() > 0) {
		if (virus.getPayload() > 1.4f) {}
		else if (coy.getSecurityLevel() >= 9.0f && coy.getNoOfBrickedComputers() >= getDetectThreshold_individual(coy)) {}
		else if (Company::getTotalNoOfBrickedComputers() >= this->getDetectThreshold_global(coy)) {}
		else if ((coy.getSecurityLevel() >= (virus.getComplexity() - 1)) && (udr > 20.0f)) {}
		else {
			return 0;
		}
		return 1;
	}
	return 0;
}
bool CyberSecurity::doResearch(int type, float threshold) const {
	if (undeadRate[type] > threshold && detectionLevel > 0 && Company::getTotalNoOfBrickedComputers() > 0) {
		return 1;
	}
	return 0;
}
void CyberSecurity::detectionLevelCheck() { // Checks if total infected networks have reached the thresholds
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
void CyberSecurity::cureProgressSpeed(int scaleSpeed, const Virus& virus) { // Increment towards the cure progress bar
	float totalFightStrength = 0.0f; // reset

	for (int i = 0; i < maxCompany; i++) {
		totalFightStrength += fightStrength[i]; // Sets total fight strength.
	}

	globalCureProgress += ((0.001f * scaleSpeed) / (virus.getResilience() * virus.getComplexity())) * totalFightStrength;

	if (globalCureProgress > 100.0f) { // cap
		globalCureProgress = 100.0f;
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
	for (int i = 1; i < maxCompany + 1; i++) {
		std::cout << "D" << i << " " << isVDetect[i - 1] << " ";
	}
	std::cout << '\n';
	for (int i = 1; i < maxCompany + 1; i++) {
		std::cout << "R" << i << " " << isResearching[i - 1] << " ";
	}
	std::cout << '\n';
	for (int i = 1; i < maxCompany + 1; i++) {
		std::cout << "REff" << i << " " << researchEfficiency[i - 1] << " ";
	}
	std::cout << '\n';
	for (int i = 1; i < maxCompany + 1; i++) {
		std::cout << "UdR" << i << "% " << undeadRate[i - 1] << " ";
	}
	std::cout << '\n';
	for (int i = 1; i < maxCompany + 1; i++) {
		std::cout << "FStr" << i << " " << fightStrength[i - 1] << " ";
	}
	std::cout << '\n';
	SetConsoleTextAttribute(hConsole, 7);
	/**/
}
/* Loss/Win Condition */
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

/* Outside */
bool CyberSecurity::getIsVDetect(int type) const{
	return this->isVDetect[type];
}
bool CyberSecurity::getIsResearching(int type) const {
	return this->isResearching[type];
}

/* Setters */
void CyberSecurity::setGlobalCureProgress(float gcp) {
	this->globalCureProgress = gcp;
}
void CyberSecurity::setDetectionLevel(int dl) {
	this->detectionLevel = dl;
}

/* Private */
void CyberSecurity::setUndeadRate(int type, const Company& coy) {
	this->undeadRate[type] = ((coy.getNetworkSize() - coy.getNoOfBrickedComputers()) / (float)coy.getNetworkSize()) * 100.0f; // percentage of undead computers
}
void CyberSecurity::setResearchEfficiency(int type, const Company& coy) {
	this->researchEfficiency[type] = (coy.getNetworkSize() - coy.getNoOfInfectedComputers()) / (float)coy.getNetworkSize(); // value of uninfected computers 0-1, the scalar value.
	if (this->researchEfficiency[type] < 0.01f) {
		this->researchEfficiency[type] = 0.01f;
	}
}
void CyberSecurity::setInfectedRate_global() {
	infectedRate_global = (Company::getTotalNoOfInfectedComputers() / (float)Company::getTotalNetworkSize()) * 100.0f;
}
void CyberSecurity::setFightStrength(int type, const Company& coy) {
	this->fightStrength[type] = ((coy.getNetworkSize() - coy.getNoOfBrickedComputers()) / ((Company::getTotalNetworkSize() - (coy.getNetworkSize() * (maxCompany / 2.0f))) / coy.getSecurityLevel())) * researchEfficiency[type];;
}

/* Constructors / Destructors */
CyberSecurity::CyberSecurity(int coyAmt) {
	maxCompany = coyAmt;
	fightStrength = new float[coyAmt];
	researchEfficiency = new float[coyAmt];
	isResearching = new bool[coyAmt];
	isVDetect = new bool[coyAmt];
	undeadRate = new float[coyAmt];
}
CyberSecurity::~CyberSecurity() {
	delete[] 
		fightStrength, 
		undeadRate,
		researchEfficiency,
		isResearching,
		isVDetect
		;
	researchEfficiency = nullptr;
	undeadRate = nullptr;
	fightStrength = nullptr;
	isResearching = nullptr;
	isVDetect = nullptr;
}