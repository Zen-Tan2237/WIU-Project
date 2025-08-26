#include "CyberSecurity.h"
#include <iostream>
#include <windows.h>

bool CyberSecurity::cureComplete = 0; // Keep
int CyberSecurity::cyberNewsCount[2] = { 0, 0 }; // Keep
float CyberSecurity::globalCureProgress = 0.0f; // Keep
float CyberSecurity::infectedRate_global = 0; // Keep

const float CyberSecurity::infectThreshold[4] = { 3.0f, 15.0f, 39.0f, 75.0f }; // Keep
const float CyberSecurity::cureThreshold[4] = { 35.0f, 50.0f, 75.0f, 95.0f }; // Keep

/* Function Members --------------------------------------------------------------------- */
/* News */
void CyberSecurity::triggerEvent(Company* coy[], const News& news) {
	HANDLE debug_cS = GetStdHandle(STD_OUTPUT_HANDLE);
	
	/* Virus Found ------------------------------------------ */ {
		/**/	SetConsoleTextAttribute(debug_cS, 4);	/**/
		for (int i = 0; i < maxCompany; i++) {
			if (isVDetect[i] && !newsDetectDone[i] && (coy[i]->getInfectedStatus() >= 0.80f || coy[i]->getBrickedStatus() >= 0.1f)) { // news out at 0.33 / 33% infected and if ;
				news.virusFoundNews(coy[i]->getName());
				newsDetectDone[i] = 1;
			}
		}
	}
	/* Collab ----------------------------------------------- */ {
		/**	SetConsoleTextAttribute(debug_cS, 14);	/**/
		/*
		int coyChoice1 = whichCompanyIsPossible(coy);
		int coyChoice2;

		if (coyChoice1 != -1 && coyChoice1 != -2) {
			do {
				coyChoice2 = whichCompanyIsPossible(coy);
			} while (coyChoice1 == coyChoice2 && coyChoice2 != -2);

			// Code for news and changing of cure status.
			if (coyChoice2 != -1 && coyChoice2 != -2) {
				news.companyCollabNews(coy[coyChoice1]->getName(), coy[coyChoice2]->getName());
			}
		}
	*/
	}
	/* Cyber Win/Loss --------------------------------------- */ {
		/**/	SetConsoleTextAttribute(debug_cS, 6);	/**/
		if (cyberNewsCount[0] < (sizeof(cureThreshold) / sizeof(cureThreshold[0]))) { // Prevents memory corruption / crashes
			if (globalCureProgress >= cureThreshold[cyberNewsCount[0]]) {
				news.cybersecurityWinningNews(); // Code for cyber wins
				cyberNewsCount[0]++;
			}
		}
		if (cyberNewsCount[1] < (sizeof(infectThreshold) / sizeof(infectThreshold[0]))) { // Prevents memory corruption / crashes
			if (infectedRate_global >= infectThreshold[cyberNewsCount[1]]) {
				news.cyberSecurityLosingNews(); // Code for cyber losses
				cyberNewsCount[1]++;
			}
		}
	}
	/* Game Win/Loss Condition ----------------------------------- */ {
		/**/	SetConsoleTextAttribute(debug_cS, 10);		/**/
		if (Company::getTotalNoOfBrickedComputers() == Company::getTotalNetworkSize()) {
			news.PlayerWinNews();
		}
		else if (isCureComplete()) {
			news.PlayerLoseNews();
		}
		/**/	SetConsoleTextAttribute(debug_cS, 7);	/**/
	}
}
/*
int CyberSecurity::whichCompanyIsPossible(Company* coy[]) const {
	int coyChoice = -1;
	bool breakLoop = 0;
	int count;
	do {
		count = 0;
		coyChoice = rand() % maxCompany;
		if ((Company::getTotalNoOfBrickedComputers() == Company::getTotalNetworkSize()) || (!isVDetect[coyChoice])) {
			breakLoop = 1;
			coyChoice = -1;
		}
		for (int i = 0; i < maxCompany; i++) {
			if (!doResearch(coyChoice, 20.0f) || coy[i]->getInfectedStatus() > 0.7f) {
				count++;
				coyChoice = -2;
			}
		}
	} while ((coy[coyChoice]->getNoOfBrickedComputers() == coy[coyChoice]->getNetworkSize()) && !breakLoop && count != 5);
	return coyChoice;
}
*/
bool CyberSecurity::isCureComplete() {
	if (globalCureProgress == 100.0f) {
		return cureComplete = 1;
	}
	else {
		return cureComplete = 0;
	}
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

		if (commonization) { // code if the conditions are not met.
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
// undeadRate used V
bool CyberSecurity::doResearch(int type, float threshold) const {
	if (undeadRate[type] >= threshold && detectionLevel > 0 && Company::getTotalNoOfBrickedComputers() > 0) {
		return 1;
	}
	return 0;
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
	HANDLE debug_cS = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout
		<< "Cure Status " << globalCureProgress << "%\n"
		<< "Detection Level " << detectionLevel << '\n';
	/* Program Debug Values */
	/**/
	SetConsoleTextAttribute(debug_cS, 3);
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
		std::cout << "UdR" << i << " " << undeadRate[i - 1] << "% ";
	}
	std::cout << '\n';
	for (int i = 1; i < maxCompany + 1; i++) {
		std::cout << "FStr" << i << " " << fightStrength[i - 1] << " ";
	}
	std::cout << '\n';
	SetConsoleTextAttribute(debug_cS, 7);
	/**/
}

/* Getters ------------------------------------------------------------------------------ */
/* Public */
bool CyberSecurity::getCureComplete() const {
	return this->cureComplete;
}
bool CyberSecurity::getIsVDetect(int type) const {
	return this->isVDetect[type];
} // Might not be used
bool CyberSecurity::getIsResearching(int type) const {
	return this->isResearching[type];
} // Might not be used
bool CyberSecurity::getNewsDetectDone(int type) const {
	return this->newsDetectDone[type];
} // Might not be used
int CyberSecurity::getDetectionLevel() const {
	return this->detectionLevel;
} // Might not be used
float CyberSecurity::getFightStrength(int type) const {
	return this->fightStrength[type];
} // Might not be used
float CyberSecurity::getGlobalCureProgress() const {
	return this->globalCureProgress;
} // Might not be used

/* Private */
int CyberSecurity::getDetectThreshold_individual(const Company& coy) const {
	return (int)(100 - (coy.getSecurityLevel() / 0.1f)) + 1;
}
int CyberSecurity::getDetectThreshold_global(const Company& coy) const {
	return this->getDetectThreshold_individual(coy) * 10;
}

/* Setters ------------------------------------------------------------------------------ */
/* Private */
void CyberSecurity::setUndeadRate(int type, const Company& coy) {
	this->undeadRate[type] = (1 - coy.getBrickedStatus()) * 100.0f; // percentage of undead computers
} // Not used if localized
void CyberSecurity::setResearchEfficiency(int type, const Company& coy) {
	this->researchEfficiency[type] = 1 - coy.getInfectedStatus(); // value of uninfected computers 0-1, the scalar value.
	
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

/* Constructors / Destructors ----------------------------------------------------------- */
CyberSecurity::CyberSecurity(int coyAmt) {
	maxCompany = coyAmt;
	detectionLevel = 0;

	isVDetect = new bool[coyAmt];
	newsDetectDone = new bool[coyAmt];
	fightStrength = new float[coyAmt];
	researchEfficiency = new float[coyAmt];

	isResearching = new bool[coyAmt]; // Remove
	undeadRate = new float[coyAmt]; // Remove if localized

	for (int i = 0; i < coyAmt; i++) {
		isVDetect[i] = 0;
		newsDetectDone[i] = 0;

		isResearching[i] = 0; // Remove
	}
}
CyberSecurity::CyberSecurity(int coyAmt, int dL) {
	maxCompany = coyAmt;
	detectionLevel = dL; // 0 to 4;

	isVDetect = new bool[coyAmt];
	newsDetectDone = new bool[coyAmt];
	fightStrength = new float[coyAmt];
	researchEfficiency = new float[coyAmt];

	isResearching = new bool[coyAmt]; // Remove
	undeadRate = new float[coyAmt]; // Remove if localized

	for (int i = 0; i < coyAmt; i++) {
		isVDetect[i] = 0;
		newsDetectDone[i] = 0;

		isResearching[i] = 0; // Remove
	}
}
CyberSecurity::~CyberSecurity() {
	delete[] 
		isVDetect,
		newsDetectDone,
		fightStrength,
		researchEfficiency,

		isResearching, // Remove
		undeadRate // Remove if localized
		;

	isVDetect = nullptr;
	newsDetectDone = nullptr;
	fightStrength = nullptr;
	researchEfficiency = nullptr;

	isResearching = nullptr; // Remove
	undeadRate = nullptr; // Remove if localized
}