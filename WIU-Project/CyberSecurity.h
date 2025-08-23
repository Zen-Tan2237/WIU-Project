#pragma once

#include "Company.h"
#include "Virus.h"
#include "News.h"

class CyberSecurity {
private:
	int maxCompany;

	static float globalCureProgress;
	static bool cureComplete;
	static int detectionLevel;
	static float infectedRate_global;

	static int cyberNewsCount[2]; 
	static float infectThreshold[4]; // inline if not needed else where
	static float cureThreshold[4]; // inline if not needed else where

	float* fightStrength;
	float* researchEfficiency; // Debug variable
	bool* isVDetect; // Condition for if a company detects the virus
	bool* isResearching; // Debug variable
	float* undeadRate; // 0-100, 100.0f = no dead, 0.0f = all dead

	bool isVirusDetected(float, const Company&, const Virus&) const;
	bool doResearch(int, float) const;

	void detectionLevelCheck();
	void cureProgressSpeed(int, const Virus&);

	int getDetectThreshold_individual(const Company&) const;
	int getDetectThreshold_global(const Company&) const;

public:
	void triggerEvent(Company* [], const Virus&, const News&);
	int whichCompanyIsPossible(Company* []) const;

	void advanceCure(Company* [], const Virus&);

	void displayStatus() const;
	bool isCureComplete();

	float getGlobalCureProgress() const;
	int getDetectionLevel() const;
	float getFightStrength(int) const;
	bool getCureComplete() const;

	bool getIsVDetect(int) const;
	bool getIsResearching(int) const;

	void setGlobalCureProgress(float);
	void setDetectionLevel(int);
	void setFightStrength(int, float);
	void setUndeadRate(int, const Company&);
	void setResearchEfficiency(int, const Company&);
	void setInfectedRate_global();

	CyberSecurity(int);
	~CyberSecurity();
};