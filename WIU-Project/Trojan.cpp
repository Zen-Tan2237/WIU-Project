#include "Trojan.h"
#include <vector>
#include <algorithm>
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
	std::string coyNm_Versions[] = { // Version
		"v1",
		"v2",
		"v3",
		"Final",
		"Final_v2"
	};
	switch (rand() % 6) {
	case 0:
		if (companyOperation((sizeof(coyNm_Versions) / sizeof(*coyNm_Versions)), coyNm_Versions)) {
			hackingPoints++;
		}
		break;
	case 1:
		if (companyFinancial((sizeof(coyNm_Versions) / sizeof(*coyNm_Versions)), coyNm_Versions)) {
			hackingPoints++;
		}
		break;
	case 2:
		if (companySales((sizeof(coyNm_Versions) / sizeof(*coyNm_Versions)), coyNm_Versions)) {
			hackingPoints++;
		}
		break;
	case 3:
		if (companyAccounting((sizeof(coyNm_Versions) / sizeof(*coyNm_Versions)), coyNm_Versions)) {
			hackingPoints++;
		}
	case 4:
		if (companyInfoTech((sizeof(coyNm_Versions) / sizeof(*coyNm_Versions)), coyNm_Versions)) {
			hackingPoints++;
		}
		break;
	case 5:
		if (companyHumanResource((sizeof(coyNm_Versions) / sizeof(*coyNm_Versions)), coyNm_Versions)) {
			hackingPoints++;
		}
		break;
	default:
		break;
	}
}

/* Corporate Teams */
bool Trojan::companyOperation(int verAmt, std::string* ver) {
	char answers[5];
	int condiOffset[2] = { 0, 0 };
	int* condition = new int[5];
	std::string fileType[] = {
		".pdf",
		".docx", /* .odt, is not very common */
		".xlsx", /* .ods, is not very common - not the standard; .csv, no format, and error prone - without commas/quotes. */
		//".txt",
		".pptx",
		".zip", /* .7z, is more secure - better encryption, but software that is compatible may be hard to find/use */
	};
	std::string baitNm[3][4] = {
		{ "OpsDept", "Operations", "OpsTeam", "Ops" }, // Department/Name
		{ "Report_SystemOutage", "MonthlyReport", "IncidentReport", "SLAReview",}, // Subject
		{ "Q1", "Q2", "Q3", "Q4" }, // Date
	};

	condition = winConditions((sizeof(*baitNm) / sizeof(**baitNm)), verAmt, (sizeof(fileType) / sizeof(*fileType)), condition);

	printDialog(
		"Operations",
		baitNm[0][condition[0]],
		baitNm[1][condition[1]],
		baitNm[2][condition[2] + conditionOffset(sizeof(*baitNm) / sizeof(**baitNm), condition[3])],
		ver[condition[3] + conditionOffset(verAmt, condition[4])],
		fileType[condition[4]]
	);
	/* Options Printing */
	std::cout << "Choose from one of these options:\n";
	for (int i = 0; i < 5; i++) {
		printSynSectNm(i);
		/* Syntax Options ---------------------- */ {
			std::vector<std::string> options[4];

			if (i <= 2) { // Syntax Options - baitNm
				minigameOptions_2d(i, (sizeof(*baitNm) / sizeof(**baitNm)), condition[i], baitNm, options);
			}
			else if (i == 3) { // Syntax Options - versions
				minigameOptions_1d(i, verAmt, condition[i], ver, options);
			}
			else if (i == 4) { //Syntax Options - file type
				minigameOptions_1d(i, (sizeof(fileType) / sizeof(*fileType)), condition[i], fileType, options);
			}
			std::random_shuffle(options->begin(), options->end()); // Shuffles options.
			int ansNum = 0;
			for (std::vector<std::string>::iterator it = options->begin(); it < options->end(); it++) { // Prints Options
				std::cout << *it;
				/* Answer Allocation */ {
					if (i <= 2) {
						if (*it == baitNm[i][condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
					else if (i == 3) {
						if (*it == ver[condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
					else if (i == 4) {
						if (*it == fileType[condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
				}
				ansNum++;
			}
			std::cout << '\n'; // Go to next Line
		}
	}
	delete[] condition;
	return playerInput(answers);

}
bool Trojan::companyFinancial(int verAmt, std::string* ver) {
	char answers[5];
	int condiOffset[2] = { 0, 0 };
	int* condition = new int[5];
	std::string fileType[] = {
		".pdf",
		".docx", /* .odt, is not very common */
		".xlsx", /* .ods, is not very common - not the standard */
		//".txt",
		".csv",
		".pptx",
		".zip", /* .7z, is more secure - better encryption, but software that is compatible may be hard to find/use */
	};
	std::string baitNm[3][4] = {
		{ "Finance", "Treasury", "Ctrl", "FIN" }, // Department/Name
		{ "Budget", "AuditReport", "Forecast", "TaxReturn",}, // Subject
		{ "Q1", "Q2", "Q3", "Q4" }, // Date
	};

	condition = winConditions((sizeof(*baitNm) / sizeof(**baitNm)), verAmt, (sizeof(fileType) / sizeof(*fileType)), condition);

	printDialog(
		"Financial",
		baitNm[0][condition[0]],
		baitNm[1][condition[1]],
		baitNm[2][condition[2] + conditionOffset(sizeof(*baitNm) / sizeof(**baitNm), condition[3])],
		ver[condition[3] + conditionOffset(verAmt, condition[4])],
		fileType[condition[4]]
	);
	/* Options Printing */
	std::cout << "Choose from one of these options:\n";
	for (int i = 0; i < 5; i++) {
		printSynSectNm(i);
		/* Syntax Options ---------------------- */ {
			std::vector<std::string> options[4];

			if (i <= 2) { // Syntax Options - baitNm
				minigameOptions_2d(i, (sizeof(*baitNm) / sizeof(**baitNm)), condition[i], baitNm, options);
			}
			else if (i == 3) { // Syntax Options - versions
				minigameOptions_1d(i, verAmt, condition[i], ver, options);
			}
			else if (i == 4) { //Syntax Options - file type
				minigameOptions_1d(i, (sizeof(fileType) / sizeof(*fileType)), condition[i], fileType, options);
			}
			std::random_shuffle(options->begin(), options->end()); // Shuffles options.
			int ansNum = 0;
			for (std::vector<std::string>::iterator it = options->begin(); it < options->end(); it++) { // Prints Options
				std::cout << *it;
				/* Answer Allocation */ {
					if (i <= 2) {
						if (*it == baitNm[i][condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
					else if (i == 3) {
						if (*it == ver[condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
					else if (i == 4) {
						if (*it == fileType[condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
				}
				ansNum++;
			}
			std::cout << '\n'; // Go to next Line
		}
	}
	delete[] condition;
	return playerInput(answers);
}
bool Trojan::companySales(int verAmt, std::string* ver) {
	char answers[5];
	int condiOffset[2] = { 0, 0 };
	int* condition = new int[5];
	std::string fileType[] = {
		".pdf",
		".docx", /* .odt, is not very common */
		".xlsx", /* .ods, is not very common - not the standard; .csv, no format, and error prone - without commas/quotes. */
		".txt",
		".pptx",
		".zip", /* .7z, is more secure - better encryption, but software that is compatible may be hard to find/use */
	};
	std::string baitNm[3][4] = {
		{ "Sales", "SalesTeam", "Marketing", "MKT" }, // Department/Name
		{ "Report", "Proposal", "Forecast", "PipeLineReport",}, // Subject
		{ "Q1", "Q2", "Q3", "Q4" }, // Date
	};

	condition = winConditions((sizeof(*baitNm) / sizeof(**baitNm)), verAmt, (sizeof(fileType) / sizeof(*fileType)), condition);

	printDialog(
		"Sales",
		baitNm[0][condition[0]],
		baitNm[1][condition[1]],
		baitNm[2][condition[2] + conditionOffset(sizeof(*baitNm) / sizeof(**baitNm), condition[3])],
		ver[condition[3] + conditionOffset(verAmt, condition[4])],
		fileType[condition[4]]
	);
	/* Options Printing */
	std::cout << "Choose from one of these options:\n";
	for (int i = 0; i < 5; i++) {
		printSynSectNm(i);
		/* Syntax Options ---------------------- */ {
			std::vector<std::string> options[4];

			if (i <= 2) { // Syntax Options - baitNm
				minigameOptions_2d(i, (sizeof(*baitNm) / sizeof(**baitNm)), condition[i], baitNm, options);
			}
			else if (i == 3) { // Syntax Options - versions
				minigameOptions_1d(i, verAmt, condition[i], ver, options);
			}
			else if (i == 4) { //Syntax Options - file type
				minigameOptions_1d(i, (sizeof(fileType) / sizeof(*fileType)), condition[i], fileType, options);
			}
			std::random_shuffle(options->begin(), options->end()); // Shuffles options.
			int ansNum = 0;
			for (std::vector<std::string>::iterator it = options->begin(); it < options->end(); it++) { // Prints Options
				std::cout << *it;
				/* Answer Allocation */ {
					if (i <= 2) {
						if (*it == baitNm[i][condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
					else if (i == 3) {
						if (*it == ver[condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
					else if (i == 4) {
						if (*it == fileType[condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
				}
				ansNum++;
			}
			std::cout << '\n'; // Go to next Line
		}
	}
	delete[] condition;
	return playerInput(answers);
}
bool Trojan::companyAccounting(int verAmt, std::string* ver) {
	char answers[5];
	int condiOffset[2] = { 0, 0 };
	int* condition = new int[5];
	std::string fileType[] = {
		".pdf",
		".docx", /* .odt, is not very common */
		".xlsx", /* .ods, is not very common - not the standard */
		".txt",
		".csv",
		".pptx",
		".zip", /* .7z, is more secure - better encryption, but software that is compatible may be hard to find/use */
	};
	std::string baitNm[3][4] = {
		{ "Books", "Accounts", "Accounting", "Acct" }, // Department/Name
		{ "Ledger", " Invoice", "FinancialStatement", "Expense",}, // Subject
		{ "Q1", "Q2", "Q3", "Q4" }, // Date
	};

	condition = winConditions((sizeof(*baitNm) / sizeof(**baitNm)), verAmt, (sizeof(fileType) / sizeof(*fileType)), condition);

	printDialog(
		"Accounting",
		baitNm[0][condition[0]],
		baitNm[1][condition[1]],
		baitNm[2][condition[2] + conditionOffset(sizeof(*baitNm) / sizeof(**baitNm), condition[3])],
		ver[condition[3] + conditionOffset(verAmt, condition[4])],
		fileType[condition[4]]
	);
	/* Options Printing */
	std::cout << "Choose from one of these options:\n";
	for (int i = 0; i < 5; i++) {
		printSynSectNm(i);
		/* Syntax Options ---------------------- */ {
			std::vector<std::string> options[4];

			if (i <= 2) { // Syntax Options - baitNm
				minigameOptions_2d(i, (sizeof(*baitNm) / sizeof(**baitNm)), condition[i], baitNm, options);
			}
			else if (i == 3) { // Syntax Options - versions
				minigameOptions_1d(i, verAmt, condition[i], ver, options);
			}
			else if (i == 4) { //Syntax Options - file type
				minigameOptions_1d(i, (sizeof(fileType) / sizeof(*fileType)), condition[i], fileType, options);
			}
			std::random_shuffle(options->begin(), options->end()); // Shuffles options.
			int ansNum = 0;
			for (std::vector<std::string>::iterator it = options->begin(); it < options->end(); it++) { // Prints Options
				std::cout << *it;
				/* Answer Allocation */ {
					if (i <= 2) {
						if (*it == baitNm[i][condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
					else if (i == 3) {
						if (*it == ver[condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
					else if (i == 4) {
						if (*it == fileType[condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
				}
				ansNum++;
			}
			std::cout << '\n'; // Go to next Line
		}
	}
	delete[] condition;
	return playerInput(answers);
}
bool Trojan::companyInfoTech(int verAmt, std::string* ver) {
	char answers[5];
	int condiOffset[2] = { 0, 0 };
	int* condition = new int[5];
	std::string fileType[] = {
		".pdf",
		".docx", /* .odt, is not very common */
		".xlsx", /* .ods, is not very common - not the standard */
		".txt",
		".csv",
		".pptx",
		".7z", /* .zip, is less secure - better encryption, and is less efficient in compression */
	};
	std::string baitNm[3][4] = {
		{ "Tech", "Network", "SysAdmin", "IT" }, // Department/Name
		{ "CICDPipeline_Updates", "TopologyDiagram", "SecurityPatch", "Log_Backup",}, // Subject
		{ "Q1", "Q2", "Q3", "Q4" }, // Date
	};

	condition = winConditions((sizeof(*baitNm) / sizeof(**baitNm)), verAmt, (sizeof(fileType) / sizeof(*fileType)), condition);

	printDialog(
		"Information Technology",
		baitNm[0][condition[0]],
		baitNm[1][condition[1]],
		baitNm[2][condition[2] + conditionOffset(sizeof(*baitNm) / sizeof(**baitNm), condition[3])],
		ver[condition[3] + conditionOffset(verAmt, condition[4])],
		fileType[condition[4]]
	);
	/* Options Printing */
	std::cout << "Choose from one of these options:\n";
	for (int i = 0; i < 5; i++) {
		printSynSectNm(i);
		/* Syntax Options ---------------------- */ {
			std::vector<std::string> options[4];

			if (i <= 2) { // Syntax Options - baitNm
				minigameOptions_2d(i, (sizeof(*baitNm) / sizeof(**baitNm)), condition[i], baitNm, options);
			}
			else if (i == 3) { // Syntax Options - versions
				minigameOptions_1d(i, verAmt, condition[i], ver, options);
			}
			else if (i == 4) { //Syntax Options - file type
				minigameOptions_1d(i, (sizeof(fileType) / sizeof(*fileType)), condition[i], fileType, options);
			}
			std::random_shuffle(options->begin(), options->end()); // Shuffles options.
			int ansNum = 0;
			for (std::vector<std::string>::iterator it = options->begin(); it < options->end(); it++) { // Prints Options
				std::cout << *it;
				/* Answer Allocation */ {
					if (i <= 2) {
						if (*it == baitNm[i][condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
					else if (i == 3) {
						if (*it == ver[condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
					else if (i == 4) {
						if (*it == fileType[condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
				}
				ansNum++;
			}
			std::cout << '\n'; // Go to next Line
		}
	}
	delete[] condition;
	return playerInput(answers);
}
bool Trojan::companyHumanResource(int verAmt, std::string* ver) {
	char answers[5];
	int condiOffset[2] = { 0, 0 };
	int* condition = new int[5];
	std::string fileType[] = {
		".pdf",
		".docx", /* .odt, is not very common */
		".xlsx", /* .ods, is not very common - not the standard */
		//".txt",
		".csv",
		".pptx",
		".zip", /* .7z, is more secure - better encryption, but software that is compatible may be hard to find/use */
	};
	std::string baitNm[3][4] = {
		{"Human", "People", "EmployeeRelations", "HR" }, // Department/Name
		{"Policy_Leave", "RecruitmentReport", "Incident_Report", "Payroll",}, // Subject
		{ "Q1", "Q2", "Q3", "Q4" }, // Date
	};

	condition = winConditions((sizeof(*baitNm) / sizeof(**baitNm)), verAmt, (sizeof(fileType) / sizeof(*fileType)), condition);

	printDialog(
		"Human Resource",
		baitNm[0][condition[0]],
		baitNm[1][condition[1]],
		baitNm[2][condition[2] + conditionOffset(sizeof(*baitNm) / sizeof(**baitNm), condition[3])],
		ver[condition[3] + conditionOffset(verAmt, condition[4])],
		fileType[condition[4]]
	);
	/* Options Printing */
	std::cout << "Choose from one of these options:\n";
	for (int i = 0; i < 5; i++) {
		printSynSectNm(i);
		/* Syntax Options ---------------------- */ {
			std::vector<std::string> options[4];

			if (i <= 2) { // Syntax Options - baitNm
				minigameOptions_2d(i, (sizeof(*baitNm) / sizeof(**baitNm)), condition[i], baitNm, options);
			}
			else if (i == 3) { // Syntax Options - versions
				minigameOptions_1d(i, verAmt, condition[i], ver, options);
			}
			else if (i == 4) { //Syntax Options - file type
				minigameOptions_1d(i, (sizeof(fileType) / sizeof(*fileType)), condition[i], fileType, options);
			}
			std::random_shuffle(options->begin(), options->end()); // Shuffles options.
			int ansNum = 0;
			for (std::vector<std::string>::iterator it = options->begin(); it < options->end(); it++) { // Prints Options
				std::cout << *it;
				/* Answer Allocation */ {
					if (i <= 2) {
						if (*it == baitNm[i][condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
					else if (i == 3) {
						if (*it == ver[condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
					else if (i == 4) {
						if (*it == fileType[condition[i]]) {
							answers[i] = (char)ansNum;
						}
					}
				}
				ansNum++;
			}
			std::cout << '\n'; // Go to next Line
		}
	}
	delete[] condition;
	return playerInput(answers);
}

/* Some Common code */
int* Trojan::winConditions(int c123, int c4, int c5, int* c) {
	c[0] = rand() % c123; // Name
	c[1] = rand() % c123; // Subject
	c[2] = rand() % c123; // Date
	c[3] = rand() % c4; // Version
	c[4] = rand() % c5; // FileType
	return c;
}
int Trojan::conditionOffset(int maxValue, int& condition) { /* Set the string value for the file syntax - the player has to make the potential next version. */
	if (condition == 0) {
		return maxValue;
	}
	else if (condition > 0) {
		return -1;
	}
	return 0;
}
void Trojan::printDialog(std::string department, std::string& fT, std::string& synNm, std::string& synSub, std::string& synDate, std::string& synVer) {

	switch (rand() % 2) {
	case 0: // Acting as a manager
		std::cout << "You are acting as a manager, you are to deliver the TROJAN VIRUS via a \"" << fT << "\" file, to the employees of the " << department << " department.\n";
		break;
	case 1: // Acting as an employee
		std::cout << "You are acting as an employee of the " << department << "department, you are to deliver the TROJAN VIRUS via a \"" << fT << "\" file, to the manager of the department.\n";
		break;
	}
	std::cout << "You have uncovered the latest file with the following syntax:\n";
	std::cout << synNm << '_' << synSub << '_' << synDate << '_' << synVer << fT << '\n';
	std::cout << "Name the TROJAN VIRUS with a similar syntax with the date and version being the follow up of that file.\n";


}
void Trojan::printSynSectNm(int type) {
	if (type == 0) {
		std::cout << "<Department_Name> ";
	}
	else if (type == 1) {
		std::cout << "<Subject> ";
	}
	else if (type == 2) {
		std::cout << "<Date> ";
	}
	else if (type == 3) {
		std::cout << "<Version> ";
	}
	else if (type == 4) {
		std::cout << "<File_Type> ";
	}
}
void Trojan::minigameOptions_2d(int type, int syntaxAmt, int& condi, std::string syntax[][4], std::vector<std::string> opt[]) {
	int k = 1;
	opt[0].push_back(syntax[type][condi]); // Sets answer as 1st value.

	for (int j = 0; j < 4; j++) { // Sets other values that are shown
		int randPos = rand() % syntaxAmt;
		bool push = 1;

		for (int l = 0; l < 4; l++) {
			if (syntax[type][randPos] == opt->at(l)) {
				j--;
				push = 0;
			}
		}
		if (push) {
			opt[k].push_back(syntax[type][randPos]);
			k++;
			if (k == 4) {
				j = 100;
			}
		}
	}
}
void Trojan::minigameOptions_1d(int type, int syntaxAmt, int& condi, std::string* syntax, std::vector<std::string> opt[]) {
	int k = 1;
	opt[0].push_back(syntax[condi]); // Sets answer as 1st value.

	for (int j = 0; j < 4; j++) { // Sets other values that are shown
		int randPos = rand() % syntaxAmt;
		bool push = 1;

		for (int l = 0; l < 4; l++) {
			if (syntax[randPos] == opt->at(l)) {
				j--;
				push = 0;
			}
		}
		if (push) {
			opt[k].push_back(syntax[randPos]);
			k++;
			if (k == 4) {
				j = 100;
			}
		}
	}
}
bool Trojan::playerInput(char* ans) {
	char PLAYERINPUT[5];
	std::cout << "Input options as one sequence: 12345\n";
	std::cin >> PLAYERINPUT;
	if (atoi(PLAYERINPUT) == atoi(ans)) {
		return 1;
	}
	return 0;
}

/*
To reduce the length of the code for each team pull a string from the chosen string type

Than Move the strings into the member functions.

after doing so, take the common code and move it into
*/
std::string Trojan::itemsOps() {
	return "Debug";
};
std::string Trojan::itemsfin() {
	return "Debug";
};
std::string Trojan::itemsSales() {
	return "Debug";
};
std::string Trojan::itemsAcct() {
	return "Debug";
};
std::string Trojan::itemsIT() {
	return "Debug";
};
std::string Trojan::itemsHR() {
	return "Debug";
};

bool Trojan::miniGameBody() {
	return 0;
};
