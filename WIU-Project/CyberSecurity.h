#pragma once

#include <cstring>
#include <random>
#include "Company.h"


class CyberSecurity {
private:
	static int globalCureProgress;
	int detectionLevel;

	bool cureComplete;
	
	/*enum events {
		fireWall,
		antiVirus,
		itLockdowns,

		eventsAmount
	};*/

	Company* coy;

public:
	void triggerEvent(std::vector<Company>&);
	void advanceCure();
	bool isCureComplete() const;
	void displayStatus() const;
	void createCompany();
	void deleteCompany();

	static int getGlobalCureProgress();
	int getDetectionLevel() const;

	static void setGlobalCureProgress(int cp);
	void setDetectionLevel(int dl);

	CyberSecurity(int dl);
	~CyberSecurity();
};

