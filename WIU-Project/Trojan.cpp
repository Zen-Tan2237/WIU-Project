#include "Trojan.h"
#include <stdlib.h>

Trojan::Trojan() {
	speed = 2.1f; // 1 for slow 5 max
	complexity = 3; // 1 to 10
	payload = 3; // 1 to 10
	resilience = 4; //1 to 10
}
Trojan::~Trojan() {

}

void Trojan::evolve(Upgrades* toUpgrade) {
	std::cout << "Speed to upgrade: " << (toUpgrade->getSpeed() + 0.5f) << std::endl
		<< " Complexity to upgrade: " << toUpgrade->getComplexity() << std::endl
		<< " Payload to upgrade" << toUpgrade->getPayload() << std::endl
		<< " Resilience to upgrade" << toUpgrade->getResilience() << std::endl;

	speed += (toUpgrade->getSpeed() + 0.5f);
	complexity += toUpgrade->getComplexity();
	payload += toUpgrade->getPayload();
	resilience += toUpgrade->getResilience();
}

void Trojan::miniGame(int& hackingPoints) {
	char answers[5] = { '-', '-', '-', '-', '-' };
	int condiOffset[2] = { 0, 0 };
	int* condition = new int[5];
	std::string date[] = {
		"Q1",
		"Q2",
		"Q3",
		"Q4"
	}; // Date
	std::string ver[] = {
		"v1",
		"v2",
		"v3",
		"Final",
		"Final_v2"
	}; // Version
	std::string fT[] = {
		".pdf",
		".docx", /* .odt, is not very common */
		".xlsx", /* .ods, is not very common - not the standard */
		".csv",
		".pptx",
		".zip", /* .7z, is more secure - better encryption, but software that is compatible may be hard to find/use */
	};
	std::string** p_con = new std::string * [2];
	for (int i = 0; i < 2; i++) {
		p_con[i] = new std::string[4];
	}
	
	winConditions(4, (sizeof(date) / sizeof(*date)), (sizeof(ver) / sizeof(*ver)), (sizeof(fT) / sizeof(*fT)), condition);
	/* Defining Naming Conventions & Printing -------------------------------- */ {
		{
			std::string departName;
			switch (rand() % 6) {
			case 0:
				nMConvention_Ops(p_con);
				departName = "Operations";
				break;

			case 1:
				nMConvention_Fin(p_con);
				departName = "Financial";
				break;

			case 2:
				nMConvention_Sales(p_con);
				departName = "Sales";
				break;

			case 3:
				nMConvention_Acct(p_con);
				departName = "Accounting";
				break;

			case 4:
				nMConvention_IT(p_con);
				departName = "Information Technology";
				break;

			case 5:
				nMConvention_HR(p_con);
				departName = "Human Resource";
				break;

			default: 
				break;
			}
			printDialog(
				departName,
				p_con[0][condition[0]],
				p_con[1][condition[1]],
				date[condition[2] + conditionOffset(sizeof(date) / sizeof(*date), condition[2])],
				ver[condition[3] + conditionOffset((sizeof(ver) / sizeof(*ver)), condition[3])],
				fT[condition[4]]
			);
		}
		for (int i = 0; i < 5; i++) {
			printSynSectNm(i);
			/* Syntax Options Printing ======================================== */ {
				std::string* options;
				options = new std::string[4];
				for (int j = 0; j < 4; j++) {
					options[j] = "debug";
				}

				/* What other options will be shown +++++++++++++++++++++++++++ */ {
					if (i <= 1) { // Syntax Options - p_con, pointer_convention
						minigameOptions_2d(i, 4, condition[i], p_con, options);
					}
					else if (i == 2) { // Syntax Options - date
						minigameOptions_1d((sizeof(date) / sizeof(*date)), condition[i], date, options);
					}
					else if (i == 3) { // Syntax Options - versions
						minigameOptions_1d((sizeof(ver) / sizeof(*ver)), condition[i], ver, options);
					}
					else if (i == 4) { //Syntax Options - file type
						minigameOptions_1d((sizeof(fT) / sizeof(*fT)), condition[i], fT, options);
					}
				}
				/* Printing Options ++++++++++++++++++++++++++++++++++++++++++++ */ {
					std::string randOpt[4] = { "debug", "debug", "debug", "debug" };
					bool push = 1;
					for (int j = 0; j < 4; j++) {
						int randPos = rand() % 4;

						if (randOpt[randPos] == "debug") {
							randOpt[randPos] = options[j];
						}
						else {
							j--;
						}
					}
					delete[] options;
					options = nullptr;

					int ansNum = 1;
					for (int j = 0; j < 4; j++) { // Prints Options
						std::cout << '(' << ansNum << ") " << randOpt[j] << " ";
						/* Answer Allocation ++++++++++++++++++++++++++++++++++++++ */ {
							if (i <= 1) {
								if (randOpt[j] == p_con[i][condition[i]]) {
									answers[i] = ansNum + '0';
								}
							}
							else if (i == 2) {
								if (randOpt[j] == date[condition[i]]) {
									answers[i] = ansNum + '0';
								}
							}
							else if (i == 3) {
								if (randOpt[j] == ver[condition[i]]) {
									answers[i] = ansNum + '0';
								}
							}
							else if (i == 4) {
								if (randOpt[j] == fT[condition[i]]) {
									answers[i] = ansNum + '0';
								}
							}
						}
						ansNum++;
					}
					std::cout << '\n'; // Go to next Line
				}
			}
		}
	}
	
	for (int i = 0; i < 2; i++) {
		delete[] p_con[i];
	}
	delete[] condition, p_con;
	condition = nullptr;
	p_con = nullptr;

	if (playerInput(answers)) {
		hackingPoints++;
	}
}

/* Naming Conventions */
void Trojan::nMConvention_Ops(std::string** pushBaitNm) {
	std::string baitNm[2][4] = {
		{ "OpsDept", "Operations", "OpsTeam", "Ops" }, // Department/Name
		{ "Report_SystemOutage", "MonthlyReport", "IncidentReport", "SLAReview",}, // Subject
	};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			pushBaitNm[i][j] = baitNm[i][j];
		}
	}
};
void Trojan::nMConvention_Fin(std::string** pushBaitNm) {
	std::string baitNm[2][4] = {
		{ "Finance", "Treasury", "Ctrl", "FIN" }, // Department/Name
		{ "Budget", "AuditReport", "Forecast", "TaxReturn",}, // Subject
	};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			pushBaitNm[i][j] = baitNm[i][j];
		}
	}
};
void Trojan::nMConvention_Sales(std::string** pushBaitNm) {
	std::string baitNm[2][4] = {
		{ "Sales", "SalesTeam", "Marketing", "MKT" }, // Department/Name
		{ "Report", "Proposal", "Forecast", "PipeLineReport",}, // Subject
	};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			pushBaitNm[i][j] = baitNm[i][j];
		}
	}
};
void Trojan::nMConvention_Acct(std::string** pushBaitNm) {
	std::string baitNm[2][4] = {
		{ "Books", "Accounts", "Accounting", "Acct" }, // Department/Name
		{ "Ledger", " Invoice", "FinancialStatement", "Expense",}, // Subject
	};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			pushBaitNm[i][j] = baitNm[i][j];
		}
	}
};
void Trojan::nMConvention_IT(std::string** pushBaitNm) {
	std::string baitNm[2][4] = {
		{ "Tech", "Network", "SysAdmin", "IT" }, // Department/Name
		{ "CICDPipeline_Updates", "TopologyDiagram", "SecurityPatch", "Log_Backup",}, // Subject
	};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			pushBaitNm[i][j] = baitNm[i][j];
		}
	}
};
void Trojan::nMConvention_HR(std::string** pushBaitNm) {
	std::string baitNm[2][4] = {
		{"Human", "People", "EmployeeRelations", "HR" }, // Department/Name
		{"Policy_Leave", "RecruitmentReport", "Incident_Report", "Payroll",}, // Subject
	};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			pushBaitNm[i][j] = baitNm[i][j];
		}
	}
};

/* Some Common code */
void Trojan::winConditions(int c12, int c3, int c4, int c5, int* c) {
	c[0] = rand() % c12; // Name
	c[1] = rand() % c12; // Subject
	c[2] = rand() % c3; // Date
	c[3] = rand() % c4; // Version
	c[4] = rand() % c5; // FileType
}
int Trojan::conditionOffset(int maxValue, int& condition) { /* Set the string value for the file syntax - the player has to make the potential next version. */
	if (condition == 0) {
		return maxValue - 1;
	}
	else if (condition > 0) {
		return -1;
	}
	return 0;
}
void Trojan::printDialog(std::string department, std::string& synNm, std::string& synSub, std::string& synDate, std::string& synVer, std::string& fT) {
	switch (rand() % 2) {
	case 0: // Acting as a manager
		std::cout << "You are acting as a manager, you are to deliver the TROJAN VIRUS via a \"" << fT << "\" file, to the employees of the " << department << " department.\n";
		break;
	case 1: // Acting as an employee
		std::cout << "You are acting as an employee of the " << department << " department, you are to deliver the TROJAN VIRUS via a \"" << fT << "\" file, to the manager of the department.\n";
		break;
	default:
		break;
	}
	std::cout << "You have uncovered the latest file with the following syntax:\n";
	std::cout << synNm << '_' << synSub << '_' << synDate << '_' << synVer << fT << '\n';
	std::cout << "Name the TROJAN VIRUS with a similar syntax with the date and version being the follow up of that file.\n";
	std::cout << '\n';
}
void Trojan::printSynSectNm(int type) {
	switch (type) {
	case 0: 
		std::cout << "Department_Name: ";
		break;

	case 1:
		std::cout << "Subject: ";
		break;

	case 2:
		std::cout << "Date: ";
		break;

	case 3:
		std::cout << "Version: ";
		break;

	case 4:
		std::cout << "File_Type: ";
		break;

	default:
		break;
	}
}
void Trojan::minigameOptions_2d(int type, int syntaxAmt, int condi, std::string** syntax, std::string* opt) {
	int k = 1;
	opt[0] = syntax[type][condi]; // Sets answer as 1st value.

	for (int j = 0; j < 4; j++) { // Sets other values that are shown
		int randPos = rand() % syntaxAmt;
		bool push = 1;

		for (int l = 0; l < 4; l++) {
			if (syntax[type][randPos] == opt[l]) {
				j--;
				push = 0;
				l = 10;
			}
		}
		if (push) {
			opt[k] = syntax[type][randPos];
			k++;
			if (k == 4) {
				j = 100;
			}
		}
	}
}
void Trojan::minigameOptions_1d(int syntaxAmt, int condi, std::string* syntax, std::string* opt) {
	int k = 1;
	opt[0] = syntax[condi]; // Sets answer as 1st value.

	for (int j = 0; j < 4; j++) { // Sets other values that are shown
		int randPos = rand() % syntaxAmt;
		bool push = 1;

		for (int l = 0; l < 4; l++) {
			if (syntax[randPos] == opt[l]) {
				j--;
				push = 0;
				l = 10;
			}
		}
		if (push) {
			opt[k] = syntax[randPos];
			k++;
			if (k == 4) {
				j = 100;
			}
		}
	}
}
bool Trojan::playerInput(char* ans) {
	std::string PLAYERINPUT_str;
	char PLAYERINPUT_char[5] = { '-', '-', '-', '-', '-' };

	std::cout << "Input options as one sequence: 12345\n";
	do {
		std::cin >> PLAYERINPUT_str;
		if (PLAYERINPUT_str.length() != 5) {
			std::cout << "Enter 5 Character Values\n";
		}
	} while (PLAYERINPUT_str.length() != 5);
	for (int i = 0; i < 5; i++) {
		PLAYERINPUT_char[i] = PLAYERINPUT_str[i];
	}
	if (atoi(PLAYERINPUT_char) == atoi(ans)) {
		return 1;
	}
	return 0;
}