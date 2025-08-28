#pragma once

#include "Company.h"
#include "Virus.h"

class CyberSecurity {
private:
	int maxCompany;
	int detectionLevel;

	static bool winCondition;
	static bool cureComplete;
	static int cyberNewsCount[2];
	static float globalCureProgress;
	static float infectedRate_global;
	
	static const float detectThreshold[4];
	static const float cureThreshold[4];

	static bool cyberNews_Win[4];
	static bool cyberNews_Loss[4];

	bool* isVDetect; // Condition for if a company detects the virus
	bool* newsDetectDone; // use its getters
	bool* newsDetectDone_buffer; // use its getters
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
	/* Go to cpp */
	void triggerEvent(Company* [], const Virus&);
	bool isCureComplete();

	void advanceCure(Company* [], const Virus&);

	//void displayStatus() const;

	bool getCureComplete() const;
	bool getIsVdetect() const; // will change if you run advance cure, a boolean is needed.
	int getNewsIndex(int) const;
	int getDetectionLevel() const;
	/**/
	bool getNewsDetectDone_bool(int) const; // use this to check if the virus is already detected
	int getNewsDetectDone_int(int) const; // use this to set the news
	static int getCyberNewsCount_win();
	static int getCyberNewsCount_loss();
	static bool getCyberNews_Win(int);
	static bool  getCyberNews_Loss(int);
	/**/
	static float getGlobalCureProgress();

	void setNewsDetectDone(bool, int) const;

	CyberSecurity(int);
	CyberSecurity(int, int);
	~CyberSecurity();
};