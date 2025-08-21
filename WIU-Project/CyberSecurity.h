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

public:
	void triggerEvent(const Company&);

	int detectionThreshold_individual(const Company*) const;
	int detectionThreshold_global(const Company*) const;

	bool isVirusDetected(const Company&, const Virus&) const;
	void cureProgressSpeed(float, const Virus&);
	void advanceCure(const Company*[], const Virus&);

	bool isCureComplete();
	void displayStatus() const;

	float getGlobalCureProgress() const;
	int getDetectionLevel() const;
	float getFightStrength(int) const;
	bool getCureComplete() const;
	int getMaxCompany() const;

	void setGlobalCureProgress(float);
	void setDetectionLevel(int);
	void setFightStrength(int, float);
	void setCureComplete(bool);

	CyberSecurity(int);
	//CyberSecurity(int, int, float);
	~CyberSecurity();
};