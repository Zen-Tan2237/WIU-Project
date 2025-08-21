#pragma once

#include "Company.h"
#include "Virus.h"


class CyberSecurity {
private:
	float globalCureProgress;
	bool cureComplete;

	int detectionLevel;
	float* fightStrength;
	int maxCompany;

	/*
	enum events {
		firewall,
		antivirus,
		ITLockdowns,

		eventAmt
	};
	*/
	void detectionLevelCheck(const Company&);
	bool isVirusDetected(const Company&, const Virus&) const;
	void cureProgressSpeed(float, const Virus&);

	int getDetectThreshold_individual(const Company&) const;
	int getDetectThreshold_global(const Company&) const;
	void setCureComplete(bool);

public:
	void triggerEvent(const Company&);

	void advanceCure(Company*[], const Virus&);
	
	bool isCureComplete();
	
	void displayStatus() const;


	float getGlobalCureProgress() const;
	int getDetectionLevel() const;
	float getFightStrength(int) const;
	bool getCureComplete() const;

	void setGlobalCureProgress(float);
	void setDetectionLevel(int);
	void setFightStrength(int, float);

	CyberSecurity(int);
	//CyberSecurity(int, int, float);
	~CyberSecurity();
};