#pragma once

#include "Company.h"
#include "Virus.h"

class CyberSecurity {
private:
	int maxCompany;
	int detectionLevel;

	static bool cureComplete;
	static int cyberNewsCount[2];
	static float globalCureProgress;
	static float infectedRate_global;
	
	static const float infectThreshold[4];
	static const float cureThreshold[4];


	bool* isVDetect; // Condition for if a company detects the virus
	bool* newsDetectDone;
	int* newsIndex; // for both head and body
	float* fightStrength;
	float* researchEfficiency;



	//bool* isResearching; // Debug variable
	float* undeadRate; // 0-100, 100.0f = no dead, 0.0f = all dead

	bool isVirusDetected(float, const Company&, const Virus&) const;
	bool doResearch(int, float) const;

	void detectionLevelCheck();
	void cureProgressSpeed(int, const Virus&);

	int getDetectThreshold_individual(const Company&) const;
	int getDetectThreshold_global(const Company&) const;

	void setUndeadRate(int, const Company&);
	void setResearchEfficiency(int, const Company&);
	void setInfectedRate_global();
	void setFightStrength(int, const Company&);

public:
	void triggerEvent(Company* [], const Virus&);
	bool isCureComplete();

	void advanceCure(Company* [], const Virus&);

	//void displayStatus() const;

	bool getCureComplete() const;
	bool getIsVdetect() const; // will change if you run advance cure, a boolean is needed.
	int getNewsIndex(int) const;
	int getDetectionLevel() const;
	bool getNewsDetectDone_bool(int) const; // use this to check if the virus is already detected
	int getNewsDetectDone_int(int) const; // use this to set the news
	static float getGlobalCureProgress();

	CyberSecurity(int);
	CyberSecurity(int, int);
	~CyberSecurity();
};