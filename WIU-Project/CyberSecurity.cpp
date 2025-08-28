#include "CyberSecurity.h"
#include <iostream>
//#include <windows.h>

bool CyberSecurity::winCondition = 0; // Keep
bool CyberSecurity::cureComplete = 0; // Keep
int CyberSecurity::cyberNewsCount[2] = { 0, 0 }; // Keep
float CyberSecurity::globalCureProgress = 0.0f; // Keep
float CyberSecurity::infectedRate_global = 0; // Keep

const float CyberSecurity::detectThreshold[4] = { 25.0f, 40.0f, 65.0f, 85.0f }; // Keep
const float CyberSecurity::cureThreshold[4] = { 35.0f, 50.0f, 75.0f, 95.0f }; // Keep

/* Function Members --------------------------------------------------------------------- */
/* News */
/* Go to section 3 of the text below */
void CyberSecurity::triggerEvent(Company* coy[], const Virus& virus) {
	/** HANDLE debug_cS = GetStdHandle(STD_OUTPUT_HANDLE); /**/
	int which;
	//std::string newsHeader;
	//std::string newsBody;

	/* Virus Found ------------------------------------------ */ {
		/**	SetConsoleTextAttribute(debug_cS, 4);	/**/
		for (int i = 0; i < maxCompany; i++) {
			which = -1; // Reset every instance.
			if (isVDetect[i] && !newsDetectDone[i] && coy[i]->getBrickedStatus() >= 0.1f) { // news out at 0.33 / 33% infected and if ;
				which = rand() % 5;
				newsDetectDone[i] = 1;
				newsDetectDone_buffer[i] = 1;
			}
			newsIndex[i] = which;
		}
	}
	/* Cyber Win/Loss --------------------------------------- */ {
		/**	SetConsoleTextAttribute(debug_cS, 6);	/**/
		which = -1; // Reset
		if (cyberNewsCount[0] < (sizeof(cureThreshold) / sizeof(cureThreshold[0]))) { // Prevents memory corruption / crashes
			if (globalCureProgress >= cureThreshold[cyberNewsCount[0]]) {
				which = rand() % 5;
				cyberNewsCount[0]++;
			}
		}
		newsIndex[maxCompany] = which;
		which = -1; // Reset
		if (cyberNewsCount[1] < (sizeof(detectThreshold) / sizeof(detectThreshold[0]))) { // Prevents memory corruption / crashes
			if (infectedRate_global >= detectThreshold[cyberNewsCount[1]]) {
				which = rand() % 5;
				cyberNewsCount[1]++;
			}
		}
		newsIndex[maxCompany + 1] = which;

	}
	/* Game Win/Loss Condition ------------------------------ */ {
		bool push = 0;
		which = -1; // Reset
		/**	SetConsoleTextAttribute(debug_cS, 10);		/**/
		if (Company::getTotalNoOfBrickedComputers() == Company::getTotalNetworkSize() && !winCondition) {
			winCondition = 1;
			which = rand() % 2;
			push = 1;
		}
		else if (isCureComplete() && !winCondition) {
			winCondition = 1;
			which = rand() % 2;
		}
		if (push && !winCondition) {
			newsIndex[maxCompany + 2] = which;
		}
		else if  (!winCondition){
			newsIndex[maxCompany + 3] = which;
		}
		/**	SetConsoleTextAttribute(debug_cS, 7);	/**/
	}
}
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
		//isResearching[i] = 0;
		isVDetect[i] = 0;

		if (this->isVirusDetected(undeadRate[i], *coy[i], virus)) { // can the company detect the virus.
			isVDetect[i] = 1;
			this->detectionLevelCheck();
			if (doResearch(i, 20.0f)) {
				//isResearching[i] = 1;
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
		this->cureProgressSpeed(439, virus); // 0.001 -> 1 to INF;
		break;
	}
	case 2: {
		this->cureProgressSpeed(647, virus); // 0.001 -> 1 to INF;
		break;
	}
	case 3: {
		this->cureProgressSpeed(855, virus); // 0.001 -> 1 to INF;
		break;
	}
	case 4: {
		this->cureProgressSpeed(1483, virus); // 0.001 -> 1 to INF;
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
		else if (coy.getInfectedStatus() >= getDetectThreshold_individual(coy) / 40.0f && detectionLevel == 3) {}
		else {
			return 0;
		}
		return 1;
	}
	return 0;
}
void CyberSecurity::detectionLevelCheck() { // Checks if total infected networks have reached the thresholds
	if (infectedRate_global >= detectThreshold[3]) {
		detectionLevel = 4;
	}
	else if (infectedRate_global >= detectThreshold[2]) {
		detectionLevel = 3;
	}
	else if (infectedRate_global >= detectThreshold[1]) {
		detectionLevel = 2;
	}
	else if (infectedRate_global >= detectThreshold[0]) {
		detectionLevel = 1;
	}
}
// undeadRate used V
bool CyberSecurity::doResearch(int type, float threshold) const {
	if (undeadRate[type] >= threshold && detectionLevel > 0) {
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
/**
void CyberSecurity::displayStatus() const {

	std::cout
		<< "Cure Status " << globalCureProgress << "%\n"
		<< "Detection Level " << detectionLevel << '\n';
	// Program Debug Values
	/**
	HANDLE debug_cS = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(debug_cS, 3);
	for (int i = 1; i < maxCompany + 1; i++) {
		std::cout << "D" << i << " " << isVDetect[i - 1] << " ";
	}
	// std::cout << '\n';
	// for (int i = 1; i < maxCompany + 1; i++) {
	//	std::cout << "R" << i << " " << isResearching[i - 1] << " ";
	// }
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
	/**
}
/**/

/* Getters ------------------------------------------------------------------------------ */
/* Public */
bool CyberSecurity::getCureComplete() const {
	return this->cureComplete;
}
bool CyberSecurity::getIsVdetect() const {
	return this->isVDetect;
}
int CyberSecurity::getNewsIndex(int type) const {
	if (type == -1) {
		return -1;
	}
	return this->newsIndex[type];
}
int CyberSecurity::getDetectionLevel() const {
	return this->detectionLevel;
}
float CyberSecurity::getGlobalCureProgress() {
	return globalCureProgress;
}
bool CyberSecurity::getNewsDetectDone_bool(int type) const {
	return newsDetectDone[type];
}
int CyberSecurity::getNewsDetectDone_int(int type) const {
	if (newsDetectDone[type]) {
		return type;
	}
	return -1;
}

/* Private */
int CyberSecurity::getDetectThreshold_individual(const Company& coy) const {
	return (int)(100 - (coy.getSecurityLevel() / 0.1f)) + 1;
}
int CyberSecurity::getDetectThreshold_global(const Company& coy) const {
	return this->getDetectThreshold_individual(coy) * 10;
}

/* Setters ------------------------------------------------------------------------------ */
/* Public */
void CyberSecurity::setNewsDetectDone(bool value, int type) const {
	this->newsDetectDone[type] = value;
}

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
	newsDetectDone_buffer = new bool[coyAmt];
	newsIndex = new int[coyAmt + 4];
	fightStrength = new float[coyAmt];
	researchEfficiency = new float[coyAmt];

	//isResearching = new bool[coyAmt]; // Remove
	undeadRate = new float[coyAmt];

	for (int i = 0; i < coyAmt; i++) {
		isVDetect[i] = 0;
		newsDetectDone[i] = 0;
		newsDetectDone_buffer[i] = 0;;

		//isResearching[i] = 0; // Remove
	}
	for (int i = 0; i < coyAmt + 4; i++) {
		newsIndex[i] = -1;
	}
}
CyberSecurity::CyberSecurity(int coyAmt, int dL) {
	maxCompany = coyAmt;
	detectionLevel = dL; // 0 to 4;

	isVDetect = new bool[coyAmt];
	newsDetectDone = new bool[coyAmt];
	newsDetectDone_buffer = new bool[coyAmt];
	newsIndex = new int[coyAmt + 4];
	fightStrength = new float[coyAmt];
	researchEfficiency = new float[coyAmt];
	
	//isResearching = new bool[coyAmt]; // Remove
	undeadRate = new float[coyAmt];

	for (int i = 0; i < coyAmt; i++) {
		isVDetect[i] = 0;
		newsDetectDone[i] = 0;
		newsDetectDone_buffer[i] = 0;;

		//isResearching[i] = 0; // Remove
	}

	for (int i = 0; i < coyAmt + 4; i++) {
		newsIndex[i] = -1;
	}
}
CyberSecurity::~CyberSecurity() {
	delete[]
		isVDetect,
		newsDetectDone,
		newsDetectDone_buffer,
		newsIndex,
		fightStrength,
		researchEfficiency,

		//isResearching, // Remove
		undeadRate
		;

	isVDetect = nullptr;
	newsDetectDone = nullptr;
	newsDetectDone_buffer = nullptr;
	newsIndex = nullptr;
	fightStrength = nullptr;
	researchEfficiency = nullptr;

	//isResearching = nullptr; // Remove
	undeadRate = nullptr;
}

/*\
To set & print the news.
\1/
for (int i = 0; i < maxCompany + 4;; i++) {
	if (i < maxCompany) {
		newZ->virusFoundNews(cyberSecurity->getNewsIndex(i), company[]->getName(), virus->getName()); // everytime this code is run the static string will get overwriten.
		std::cout << News::getHEAD; // this is how to print it if you need to 
		std::cout << News::getBODY;
	}
	else if (i == maxCompany) {
		newZ->cybersecurityWinningNews(cyberSecurity->getNewsIndex(i), virus->getName()); 
		std::cout << News::getHEAD;
		std::cout << News::getBODY;
	}
	else if (i == maxCompany + 1) {
		newZ->cyberSecurityLosingNews(cyberSecurity->getNewsIndex(i), virus->getName());
		std::cout << News::getHEAD;
		std::cout << News::getBODY;
	}
	else if (i == maxCompany + 2) {
		newZ->PlayerWinNews(cyberSecurity->getNewsIndex(i));
		std::cout << News::getHEAD;
		std::cout << News::getBODY;
	}
	else if (i == maxCompany + 3) {
		newZ->PlayerLoseNews(cyberSecurity->getNewsIndex(i));
		std::cout << News::getHEAD;
		std::cout << News::getBODY;
	}
}

\2/ set indivisual News 
	(0 to (maxCompany - 1))	|| VIRUS FOUND
	(maxCompany)			|| CYBER WINNING
	(maxCompany + 1)		|| CYBER LOSING
	(maxCompany + 2)		|| PLAYER WIN
	(maxCompany + 3)		|| PLAYER LOSE

	cyberSecurity->getNewsIndex(maxCompany - (maxCompany - 0));

newsSetectDone
\3/
if newsDetectDone == true; returns value i;
else; returns -1;

cyberSecurity->getNewsIndex(getNewsDetectDone_int(i));
getNewsDetectDone_bool() // gives true if it has been detected, triggerEvent() has to be run first. Afterwards you can set it to false once used, using setNewsDetectDone(bool, int).
getNewsDetectDone_int() // can be used to get the company name as it retuns a value as shown above.

\*/