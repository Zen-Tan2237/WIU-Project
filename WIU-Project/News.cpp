#include "News.h"
#include "Player.h"
#include <iostream>
#include <random>
/***********************************************************************\
								Unrefined
\***********************************************************************/
News::News()
{
}

News::~News()
{
}

News::News(std::string VirusName)
{
	/*
	randomEventHeadlines[2][1] =
	{ "Global Cybersecurity Teams Contain Spread of " + VirusName + " Virus in Record Time." };
	randomEventHeadlines[3][2] =
	{ VirusName + "Virus Outpaces Global Cybersecurity Defenses." };

	randomEventsDescriptions[4][1] =
	{ "Employee said\"It was so sudden when when our computers all got destroyed at the same time by" + VirusName + "\"" };

	WinOrLoseNewsHeadlines[0][0] =
	{ "The Worlds Economy Has Taken A Big Hit After Major Companies Have Been Destroyed from " + VirusName };
	*/
}
/*
Ctrl + E + W to wrap, makes it easier to edit.
*/
void News::companyCollabNews(std::string companyA, std::string companyB) const
{
	srand((unsigned)time(0));
	switch (rand() % 5) {
	case 0:
		std::cout
			<< companyA << " and " << companyB <<
			" are having their annual International Collaboration Program (ICP) as a way to strengthen their relations overseas. The companies are partnered with each other as they both are foreign organizations to each other, in doing this they strengthen their global ties and expand their international presence."
			<< '\n';
		break;
	case 1:
		std::cout 
			<< companyA << " and " << companyB << 
			" has been acquired by Zen.Inc, A crossover program has been started to allow employees from both companies to get to know each other. Zen.Inc is leading in the facilitation of workforce integration, setting an example for other companies."
			<< '\n';
		break;
	case 2:
		std::cout 
			<< companyA << " and " << companyB << 
			" has partnered in a global initiative called Sustainability Together, which aims to reduce the carbon footprint usage within their companies, they hope, by the end of this year, their carbon footprint gets reduced by 15%. The companies have launched this green initiative, focused on reducing its environmental footprint, this supports the global climate, as it reduces the amount of carbon in the atmosphere, resulting in less heat being trapped."
			<< '\n';
		break;
	case 3:
		std::cout 
			<< companyA << " and " << companyB <<
			" have both decided to introduce an internship program, in the search for young talent, and to help students gain experience in larger and well known companies. The companies are opening their doors to all aspiring students, with the goal to become professionals in the future."
			<< '\n';
		break;
	case 4:
		std::cout <<
			"At the National Charity meet-up two new faces coming from "
			<< companyA << " and " << companyB <<
			" are sponsoring this years, charity event. This demonstrates their commitment to upkeep their social responsibilities, the companies are also co-sponsoring another charity event, People event to support underprivileged communities."
			<< '\n';
		break;
	}
}

void News::virusFoundNews(std::string company) const
{
	srand((unsigned)time(0));
	switch (rand() % 5) {
	case 0:
		std::cout
			<< company
			<< " has shut down their emailing systems in response to a worm virus spread via emails. In an urgent defensive move, the company disabled its email infrastructure to contain a fast-spreading worm targeting internal communications.\n";
		break;
	case 1:
		std::cout
			<< company
			<< " In Chaos After Emails Flooded With Viruses. \"We don't even know which is a real email at this point\" says employee at the company."
			<< '\n';
		break;
	case 2:
		std::cout
			<< company
			<< " Has A Data breach Effecting 300 Million Customers Worldwide. A major cybersecurity failure has exposed sensitive data of millions, triggering global concern and investigations."
			<< '\n';
		break;
	case 3:
		std::cout
			<< company
			<< " Loses Important Files After Malware Crashes Systems Critical business files were lost when a malware attack caused widespread system failures across departments."
			<< '\n';
		break;
	case 4:
		std::cout
			<< company
			<< " CEO Quit After Losing Years Of Reports My heart cant take the loss of years of hard work\" says the Ceo"
			<< '\n';
		break;
	}
}

void News::cybersecurityWinningNews() const
{
	srand((unsigned)time(0));
	switch (rand() % 5) {
	case 0:
		std::cout <<
			"The Cybersecurity Sector Has Made a Breakthrough Towards Creating a Antivirus. \"Our team has been hard at work to keep all of us safe from the new malware\" - Biryani Y.N, Ceo of Checkpoint Security"
			<< '\n';
		break;
	case 1:
		std::cout <<
			"Global Cybersecurity Teams Contain Spread of //virus name here// Virus in Record Time. Through rapid coordination and real-time response, cybersecurity professionals successfully stopped the virus before it could cause global damage."
			<< '\n';
		break;
	case 2:
		std::cout <<
			"Cybersecurity Experts Make Major Progress in Isolating Email - Based Worm Malware. Researchers have successfully traced the infection vectors of a fast-spreading worm virus, allowing targeted containment strategies to be deployed across affected systems."
			<< '\n';
		break;
	case 3:
		std::cout <<
			"Ongoing Research Yields Clues to Weaknesses in Self - Replicating Worm Code. Security analysts have uncovered potential flaws in the worm’s code structure, fueling hope for the eventual creation of a targeted patch."
			<< '\n';
		break;
	case 4:
		std::cout <<
			"Researchers Uncover Hidden Loop in Worm Code That Could Halt Its Spread. Anomalies in the worm’s replication logic have been identified, offering a potential entry point for future containment or neutralization."
			<< '\n';
		break;
	}
}

void News::cyberSecurityLosingNews() const
{
	srand((unsigned)time(0));
	switch (rand() % 5) {
	case 0:
		std::cout <<
			"Malware Analysts Overwhelmed as Worm Mutates Faster Than Detection Tools Can Adapt. Despite aggressive countermeasures, the newly emerged virus spread faster than anticipated, exposing serious weaknesses in current defense systems."
			<< '\n';
		break;
	case 1:
		std::cout <<
			"Efforts to Reverse Engineer Worm Fail as Code Obfuscation Blocks Analysis. Cybersecurity experts are sounding alarms as containment strategies fall short against the highly evasive NetWraith virus."
			<< '\n';
		break;
	case 2:
		std::cout <<
			"//virus name here// Virus Outpaces Global Cybersecurity Defenses. A new variant of malware has infiltrated international networks without triggering standard security alerts, prompting urgent calls for upgraded protocols."
			<< '\n';
		break;
	case 3:
		std::cout <<
			"Experts Warn: Cybersecurity Measures Failing to Contain \'NetWraith\'. The worm’s self-modifying code is evolving beyond current antivirus signatures, rendering many security tools ineffective."
			<< '\n';
		break;
	case 4:
		std::cout <<
			"Unstoppable Virus Variant Spreads Through Global Networks Undetected. Attempts to dissect the worm’s inner workings have been hampered by complex encryption layers and advanced obfuscation techniques."
			<< '\n';
		break;
	}
}

void News::companyDeadNews(std::string company) const
{
	srand((unsigned)time(0));
	switch (rand() % 5) {
	case 0:
		std::cout
			<< company <<
			" Shuts Down Overnight After Devastating Cyber Attack. Employees were seen embracing in the parking lot after learning that years of digital records, finances, and projects had been completely wiped out, forcing immediate closure."
			<< '\n';
		break;
	case 1:
		std::cout
			<< company <<
			" employees were seen crying together after losing their jobs from a computer virus. Employee said\"It was so sudden when when our computers all got destroyed at the same time by //virus name here//\""
			<< '\n';
		break;
	case 2:
		std::cout
			<< company <<
			" Collapses After Computer Virus Destroys Payroll and Client Files.Many left jobless after the incident with no where to go."
			<< '\n';
		break;
	case 3:
		std::cout
			<< company <<
			" Entire Operation Halted as Virus Erases Production Schedules and Supplier Contacts. Without access to systems, shipments, or communications, the company had no choice but to shut its doors indefinitely."
			<< '\n';
		break;
	case 4:
		std::cout
			<< company <<
			" Crippling Cyberattack Destroys All Orders, Invoices, and Communication Logs. With months of business lost and no records to rebuild from, the CEO said continuing would be \"financially and emotionally impossible\"."
			<< '\n';
		break;
	}
}

void News::PlayerWinNews() const
{
	srand((unsigned)time(0));
	switch (rand() % 2) {
	case 0:
		std::cout << 
			"The Worlds Economy Has Taken A Big Hit After Major Companies Have Been Destroyed from //virus name here//. Security analysts warn of long-term economic repercussions as malware dismantles IT networks, corrupts backups, and leaks sensitive data from multiple conglomerates.\n";
		break;
	case 1:
		std::cout <<
			"Malware Meltdown: Corporate Titans Collapse in Wake of Digital Sabotage. Major players across the global economy are facing ruin after a destructive malware variant bypassed conventional defenses and triggered mass outages.\n";
		break;
	}
}

void News::PlayerLoseNews() const
{
	srand((unsigned)time(0));
	switch (rand() % 2) {
	case 0:
		std::cout <<
			"Coordinated Cyber Shield Deflects Major Malware Attack on Corporations. An attempted digital blitz aimed at crippling global business was neutralized days before crippling infastructers."
			<< '\n';
		break;
	case 1:
		std::cout <<
			"Global Malware Scare Pushes Corporate Defenses to Breaking Point. Cybersecurity infrastructures bent under pressure during a widespread malware blitz. Only through rapid-response units and drastic internal measures did companies manage to hold the line."
			<< '\n';
		break;
	}
}
