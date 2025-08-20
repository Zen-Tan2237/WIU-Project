#pragma once

#include "Company.h"
#include "Virus.h"


class CyberSecurity {
private:
	float globalCureProgress;
	bool cureComplete;

	int detectionLevel;
	float* fightStrength;

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
	void advanceCure(int, const Company*, const Virus&);
	void cureProgressSpeed(int, float, const Virus&);
	bool isCureComplete();
	void displayStatus() const;

	float getGlobalCureProgress() const;
	int getDetectionLevel() const;
	float getFightStrength(int) const;

	void setGlobalCureProgress(float);
	void setDetectionLevel(int);
	void setFightStrength(int, float);

	CyberSecurity(const Company*);
	//CyberSecurity(int, float, const Company*);
	~CyberSecurity();
};

