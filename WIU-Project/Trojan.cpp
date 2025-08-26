#include "Trojan.h"

Trojan::Trojan() {
	name = "no name lol";
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

/*\
<Task> Trojan: clickbait challenge (shoei)
(1) choose a suitable file name for the victim for 
eg. current victim is manager, you will choose a file from 3 options(minecraft_crack.exe, HRpayments.xlsx, eveningmeetingslides.pdf)

<1> Discover all roles associate with the company
	- Owners, CEOs <- Chairman
	- Managers
	  ~ General Manager
		` Operation Managers
		` Financial Managers
		` Marketing Managers
		` Accounting Managers
		` IT Managers
		` HR Managers

	- Lenders
	- Suppliers
	- Employees
	  ~ Operation Staff
	  ~ Financial Team
	  ~ Sales Team
	  ~ Accounting Team
	  ~ IT Engineers
	  ~ Standard Employees

	- Government
	- Customers
	- Competitors

<2> Files that may be used by those people
	- official company records
	- policy documents
	- human resources (HR) documents like employment contracts and vacation requests
	- financial documents such as purchase orders and invoices
	- operational documents
	- general communication memos used for announcements
	- instructions 
	- reports

<3>
\*/
void Trojan::miniGame(int hackingPoints) {
	std::string coyRoles_Owners[2] = {
		"Chairman",
		"CEO"
	};

	std::string coyNm_Versions[8] = { // Version
		"v1",
		"v2",
		"v3",
		"Draft1",
		"Draft2",
		"Draft3",
		"Final",
		"Final_v2"
	};
	std::string coyNm_Date[4] = { // Date
		"Q1",
		"Q2",
		"Q3",
		"Q4"
	};
}

void Trojan::companyOperation() {
	std::string baitNm_Ops[2][4] = {
		{"Ops_Report", "Operations", "OpsTeam", "Ops" }, // Department
		{"SystemOutage", "MonthlyReport", "IncidentReport", "SLAReview",} // Subject
	};
	printDialog("Team", "Operation");
	//std::cout << 
}
void Trojan::companyFinancial() {
	std::string baitNm_Finance[2][4] = {
		{"Finance", "Treasury", "Ctrl", "FIN" }, // Department
		{"Budget", "AuditReport", "Forecast", "TaxReturn",} // Subject
	};
	printDialog("Team", "Financial");
}
void Trojan::companySales() {
	std::string baitNm_Sales[2][4] = {
		{"Sales", "SalesTeam", "Marketing", "MKT" }, // Department
		{"Report", "Proposal", "Forecast", "PipeLineReport",} // Subject
	};
	std::string coyNm_Client[1] = {};
	printDialog("Team", "Sales");

}
void Trojan::companyAccounting() {
	std::string baitNm_Acct[2][4] = {
		{"Books", "Accounts", "Accounting", "Acct" }, // Department
		{"Ledger", " Invoice", "FinancialStatement", "Expense",} // Subject
	};
	printDialog("Team", "Accounting");

}
void Trojan::companyInfoTech() {
	std::string baitNm_IT[2][4] = {
		{"Tech", "Network", "SysAdmin", "IT" }, // Department
		{"CICDPipeline_Updates", "TopologyDiagram", "SecurityPatch", "Log_Backup",} // Subject
	};
	printDialog("Engineers", "Infomation Technology");

}
void Trojan::companyHumanResource() {
	std::string baitNm_HR[2][4] = {
		{"Human", "People", "EmployeeRelations", "HR" }, // Department
		{"Policy_Leave", "RecruitmentReport", "Incident_Report", "Payroll",} // Subject
	};
	printDialog("Team", "Human Resource");

}
void Trojan::printDialog(std::string employee, std::string departmentt) {
	std::string fileType[10] = {
		".pdf",
		".docx",
		".xlsx",
		".txt",
		".odt",
		".csv",
		".ods",
		".ppt",
		".zip",
		".7z"
	};
	switch (rand() % 2) {
	case 0: // Acting as a manager
		std::cout << "You are acting as a manager, you are to deliver the TROJAn via a " << fileType[rand() % 10] << " to the " << employee << " team.";
		break;
	case 1: // Acting as an employee
		std::cout << "You are acting as an employee of the " << employee << " team, you are to deliver the TROJAN via a " << fileType[rand() % 10] << " to the manager of that department.";
		break;
	}
}