#pragma once

#include "Company.h"
#include "Virus.h"
#include "News.h"

class CyberSecurity {
private:
	int maxCompany;

	float globalCureProgress;
	bool cureComplete;

	int detectionLevel;
	float* fightStrength;
	float* undeadRate;
	float* researchEfficiency;

	/*
	enum events {
		coyCollabs
		,
		ITLockdowns,

		eventAmt
	};
	*/

	bool isVirusDetected(float, const Company&, const Virus&) const;
	void detectionLevelCheck(float, float, float, float);
	void cureProgressSpeed(float, const Virus&);

	int getDetectThreshold_individual(const Company&) const;
	int getDetectThreshold_global(const Company&) const;
	void setCureComplete(bool);

public:
	void triggerEvent(Company* [], const Virus&, const News&) const; // Not used yet
	int whichCompanyIsPossible(Company* []) const;

	void advanceCure(Company* [], const Virus&);

	void displayStatus() const;
	bool isCureComplete();


	float getGlobalCureProgress() const;
	int getDetectionLevel() const;
	float getFightStrength(int) const;
	bool getCureComplete() const;

	void setGlobalCureProgress(float);
	void setDetectionLevel(int);
	void setFightStrength(int, float);
	void setUndeadRate(int, Company* []);
	void setResearchEfficiency(int, Company* []);

	CyberSecurity(int);
	//CyberSecurity(int, int, float);
	~CyberSecurity();
};