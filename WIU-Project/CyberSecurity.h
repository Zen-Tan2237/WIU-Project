#pragma once

#include <string>
#include <random>
#include "Company.h"


class CyberSecurity {
private:
	float globalCureProgress;
	bool cureComplete;

	int detectionLevel;
	float fightStrength;


	/*
	enum events {
		fireWall,
		antiVirus,
		itLockdowns,

		eventsAmount
	};
	*/

public:
	void triggerEvent(const Company&);
	void advanceCure(const Virus&, const Company*);
	float cureProgressSpeed(float, const Virus&) const;
	bool isCureComplete();
	void displayStatus() const;

	float getGlobalCureProgress() const;
	int getDetectionLevel() const;
	float getFightStrength() const;

	void setGlobalCureProgress(float);
	void setDetectionLevel(int);
	void setFightStrength(float);

	CyberSecurity();
	//CyberSecurity(float, int);
	~CyberSecurity();
};

