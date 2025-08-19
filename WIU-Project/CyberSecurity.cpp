#include "CyberSecurity.h"
#include <iostream>

int CyberSecurity::globalCureProgress = 0;
//float CyberSecurity::globalCureProgress = 0;


void CyberSecurity::triggerEvent(std::vector<Company>& companies) {
}

void CyberSecurity::advanceCure() {
	globalCureProgress++;
	//globalCureProgress += 0.1;
}

bool CyberSecurity::isCureComplete() const {
	return cureComplete;
}

void CyberSecurity::displayStatus() const {
	std::cout << "Status " << globalCureProgress << "%\n";
}

void CyberSecurity::createCompany() {
	coy = new Company;
}

void CyberSecurity::deleteCompany() {
	delete coy;
	coy = nullptr;
}

int CyberSecurity::getGlobalCureProgress()  {
	return globalCureProgress;
}
int CyberSecurity::getDetectionLevel() const {
	return this->detectionLevel;
}

void CyberSecurity::setGlobalCureProgress(int cp) {
	globalCureProgress = cp;
}

void CyberSecurity::setDetectionLevel(int dl) {
	this->detectionLevel = dl;
}

CyberSecurity::CyberSecurity() {
	detectionLevel = 1;
}

CyberSecurity::CyberSecurity(int dl) {
	detectionLevel = dl;
}

CyberSecurity::~CyberSecurity() {
	if (coy != nullptr) {
		delete coy;
		coy = nullptr;
	}
}