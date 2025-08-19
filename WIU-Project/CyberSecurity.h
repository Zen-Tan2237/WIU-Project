#pragma once

#include <string>
#include <random>
#include "Company.h"


class CyberSecurity {
private:
	float globalCureProgress;
	bool cureComplete;

	int detectionLevel;
	int fightStrength;


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
	int getFightStrength() const;

	void setGlobalCureProgress(int);
	void setDetectionLevel(int);
	void setFightStrength(int);

	CyberSecurity();
	//CyberSecurity(float, int);
	~CyberSecurity();
};

