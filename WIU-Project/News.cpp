#include "News.h"
#include "Player.h"
#include <iostream>
#include <random>

std::string News::HEAD = "A Bright & Sunny Day!";
std::string News::BODY = "A bright and sunny day.";
std::string News::EFFECTS = "None";

News::News() {}
News::~News() {}
News::News(std::string VirusName) {




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

/* Ctrl + E + W to wrap, makes it easier to edit. */

/* Randomization is to be done outside */ 
/*\ 

\1/ Code to get a news type
	- int newsType = rand() % 5;
	- news.companyCollabNews(newsType, company[]->getName(), company[]->getName())
	- news.setPastNews(0, 0, newsType);

\2/ Code to get past news
	- news.companyCollabNews(pastNews[0][0], company[]->getName(), company[]->getName())

\3/ Code to get specific news
	- news.companyCollabNews(0, company[]->getName(), company[]->getName())

\4/ Code to get current news string
	- News::getHEAD();
	- News::getBODY();

\*/

/* 5 Instances */
void News::companyCollabNews(int type, std::string companyA, std::string companyB) const {
	switch (type) {
	case 0: {
		setHEAD("Annual International Collaboration Program (ICP)");
		setBODY(companyA + " and " + companyB + " are having their annual ICP as a way to strengthen their relations overseas. The companies are partnered with each other as they both are foreign organizations to each other, in doing this they strengthen their global ties and expand their international presence.");
	}
		break;
	case 1: {
		setHEAD("Zen.Inc. New Leading Corporation?");
		setBODY(companyA + " and " + companyB + " has been acquired by Zen.Inc. A crossover program has been started to allow employees from both companies to get to know each other. Zen.Inc is leading in the facilitation of workforce integration, setting an example for other companies.");
	}
		break;
	case 2: {
		setHEAD("Global Initiative By " + companyA + " & " + companyB);
		setBODY(companyA + " and " + companyB + " has partnered in a global initiative called Sustainability Together, which aims to reduce the carbon footprint usage within their companies, they hope that by the end of this year, their carbon footprint will be reduced by 15%. The companies have launched this green initiative, focused on reducing its environmental footprint, this supports the global climate, as it reduces the amount of carbon in the atmosphere, resulting in less heat being trapped.");
	}
		break;
	case 3: {
		setHEAD("Calling All Students! Internship At Well Established Companies.");
		setBODY(companyA + " and " + companyB + " have both decided to introduce an internship program, in the search for young talent, and to help students gain experience in larger and well-known companies. The companies are opening their doors to all aspiring students, with the goal to become professionals in the future.");
	}
		break;
	case 4: {
		setHEAD("News At The National Charity As 2 New Faces From " + companyA + " & " + companyB + " Were Seen");
		setBODY("At the National Charity meet-up two new faces coming from " + companyA + " and " + companyB + " are sponsoring this year's, charity event. This demonstrates their commitment to upkeep their social responsibilities, the companies are also co-sponsoring another charity event, Peoples United to support those that come from underprivileged communities.");
	}
		break;
	default:
		break;
	}

	setEFFECTS("The spread rate between " + companyA + " and " + companyB + " has increased (virus can spread more easily)");
}

/* 5 Instances */
void News::virusFoundNews(int type, std::string company, std::string virus) const {
	switch (type) {
	case 0: {
		setHEAD(company + " Email Shutdowns After Malware Spread");
		setBODY(company + " has shut down their emailing systems in response to a " + virus + " circulating via their emails. They hope, by doing this they reduce the rate of which this malware spreads internally. This is an urgent, defensive move, that the company has done in hopes of containing this fast-spreading malware.");
	}
		break;
	case 1: {
		setHEAD("VIRUS DETECT! Who Will Be Next?");
		setBODY(company + " is in chaos after viruses were detected within their communication system. \"We don't even know which is a real email at this point\" says employee at the company.");
	}
		break;
	case 2: {
		setHEAD("Data Breach Affecting 300 Million People Worldwide!");
		setBODY("A data breach earlier this morning has affected 300 million users. " + company + "'s Chairman have came out, giving a public apology, as due to their failure, sensitive data of millions have been made public putting their personal information at risk. Experts warn users of " + company + " to renew their personal information, to deter fraudulent activities; before it's too late.");
	}
		break;
	case 3: {
		setHEAD("System Crashes After A Malware Attack");
		setBODY(company + " has reported that they have loss important files after a malware attack crashes their systems. Critical business files were lost when this malware attack was orchestrate causing widespread system failures across departments.");
	}
		break;
	case 4: {
		setHEAD("CEO QUITS!");
		setBODY(company + "'s CEO quits after losing years of reports \"My heart can't take the loss of years of hard work\" says the CEO.");
	}
		break;
	default:
		break;
	}

	setEFFECTS("Cybersecurity has been triggered and started researching for a digital cure against " + virus);
}

/* 5 Instances */
void News::cybersecurityWinningNews(int type, std::string virus) const {
	switch (type) {
	case 0: {
		setHEAD("Breakthrough! Efforts Towards Antivirus Has Seen An Up");
		setBODY("The cybersecurity sector has made a breakthrough towards creating an antivirus to the recent malware threat. \"Our team has been hard at work in keeping all of us safe from the new malware threat\" - Biryani Y.N, Ceo of Checkpoint Security.");
	}
		break;
	case 1: {
		setHEAD("Contain! Spread Of " + virus + " Have Been Contained");
		setBODY("Global cybersecurity teams contains spread of the fairly recent " + virus + " in Record Time. Through a rapid, well coordinated and real-time response, cybersecurity professionals successfully contain the malware before it could cause more global damage.");
	}
		break;
	case 2: {
		setHEAD("Major Progress! Experts Have Isolated The Recent Malware Threat");
		setBODY("Major progress have been made by cybersecurity experts, having successfully isolated a specimen of the recent malware threat, researches have been able to trace the infection vectors, allowing for targeted containment strategies to be instilled across infected systems.");
	}
		break;
	case 3: {
		setHEAD("Weaknesses Found! Research Have Uncovered Potential Weak Points In The Recent Malware Threat");
		setBODY("Ongoing research have yield results to the weaknesses of the self-replicating code of the recent malware threat. Security analysts have uncovered potential flaws in the worm’s code structure, fueling hope for the eventual creation of a targeted patch.");
	}
		break;
	case 4: {
		setHEAD("Researchers Uncover Hidden Loop in Malware. Could This Halt Its Spread?");
		setBODY("A recent loop was uncovered within the recent " + virus + "'s code. " + "Researchers, have hint towards a potential halt towards the malware spread. The malware's replication logic have been identified, offering a potential entry point for future containment or neutralization.");
	}
		break;
	default:
		break;
	}

	setEFFECTS("");
}

/* 5 Instances */
void News::cyberSecurityLosingNews(int type, std::string virus) const {
	switch (type) {
	case 0: {
		setHEAD("Malware Analysts Overwhelmed As Mutations Were Faster Than Detection Tools Can Adapt");
		setBODY("Despite the aggressive countermeasures held to prevent the spread of the recent malware threat, the rate of which it mutates have overwhelm malware analysts as no current malware detection tools can adapt to the rapid spread, exposing serious weaknesses in the current defense systems.");
	}
		  break;
	case 1: {
		setHEAD("Reverse Engineering Failed As Code Obfuscation Blocks Malware Analysts");
		setBODY("Malware analysts tried to reverse engineer the recent malware threat, but to no prevail, as the code of the malware is obfuscated, making it hard to make of the malware's weaknesses. Following this cybersecurity experts are sounding alarms as containment strategies fall short against the highly evasive malware threat.");
	}
		  break;
	case 2: {
		setHEAD("Recent " + virus + " Outpaces Global Cybersecurity Defenses");
		setBODY("A new variant of malware has infiltrated international networks, without triggering standard security alerts, prompting urgent calls for upgraded protocols.");
	}
		  break;
	case 3: {
		setHEAD("Experts Warn As Cybersecurity Measures Are Failing to Contain " + virus);
		setBODY("The self-modifying code of the recent " + virus + " have been evolving beyond current antivirus signatures, rendering many security tools ineffective.");
	}
		  break;
	case 4: {
		setHEAD("Unstoppable Virus Spreads Through Global Networks");
		setBODY("Attempts to dissect the worm’s inner workings have been hampered by complex encryption layers and advanced obfuscation techniques.");
	}
		  break;
	default:
		break;
	}

	setEFFECTS("");
}

/* 5 Instances */
void News::companyDeadNews(int type, std::string company, std::string virus) const {
	switch (type) {
	case 0: {
		setHEAD(company + " Shuts Down Overnight After Devastating Cyber Attack");
		setBODY(company + " have recently close its doors as devastating cyber attack overwhelm their systems. Employees were seen embracing in the parking lot after learning that years of digital records, finances, and projects had been completely wiped out, forcing immediate closure.");
	}
		break;
	case 1: {
		setHEAD("Many Loses Theirs Jobs After Major Loss Of Networking Ability");
		setBODY(company + " employees were seen crying together after losing their jobs, a malware have rendered all networking ability within company boundaries unless. Employees are saying that the sudden bricking event, when all their computers got destroyed at the same time by the " + virus + '.');
	}
		break;
	case 2: {
		setHEAD(company + " Has Collapse");
		setBODY(virus + " has destroyed all payroll and client files, leading to the collapse of " + company + ". Leaving many jobless.");
	}
		break;
	case 3: {
		setHEAD("Operations Of " + company + " Halted");
		setBODY("After the" + virus + " erased production schedules, and supplier contacts entirely. With no access to their systems, shipments, and communications " + company + " had no choice but to shut its doors indefinitely.");
	}
		break;
	case 4: {
		setHEAD("Cyberattacks Toward " + company + " Destroys All Files");
		setBODY(" Crippling Cyberattack Destroys All Orders, Invoices, and Communication Logs. With months of business lost and no records to rebuild from, the CEO said continuing would be \"financially and emotionally impossible\". Cyberattacks towards " + company + " have crippled their records of orders, invoices, and communication logs, resulting in months of business records being lost and unable to recover, the Chairman says that continuing operations would result in an uncertain future for the company, and its people.");
	}
		break;
	default:
		break;
	}

	setEFFECTS(company + " has fallen");
}

/* 2 Instances */
void News::PlayerWinNews(int type) const {
	switch (type) {
	case 0: {
		setHEAD("Financial Instability & Global Recession");
		setBODY("The world's economy has taken a big hit after major companies have closed down, leaving millions jobless, and uncertain about the future. Analysts warn of long-term economic repercussions as malware dismantles IT networks, corrupts backups, and leaks sensitive data from multiple conglomerates.");
	}
		break;
	case 1: {
		setHEAD("Corporate Titans Collapses");
		setBODY("The destructive malware variant bypassed conventional defenses and triggered mass outages, resulting in corporate titans collapse. Major players loss millions in credit, leaving the global economy in ruin.");
	}
		break;
	default: 
		break;
	}

	setEFFECTS("GAME WON");
}

/* 2 Instances */
void News::PlayerLoseNews(int type) const {
	switch (type) {
	case 0: {
		setHEAD("Anti-Virus Software Developed");
		setBODY("Corporations have developed a cyber shield, which successfully deflects the major malware attacks. rendering the digital blitz aimed at crippling global business useless, and neutralized days before crippling any key infrastructures.");
	}
		break;
	case 1: {
		setHEAD("Malware Threat Neutralized");
		setBODY("The global malware scare had pushed corporate defenses to their breaking points, causing cybersecurity infrastructures to bend under pressure during the widespread malware blitz, but through sheer determination, rapid-responses and drastic internal measures did companies manage to hold the line.");
	}
		break;
	default:
		break;
	}

	setEFFECTS("YOU LOST");
}

std::string News::getHEAD() {
	return HEAD;
}
std::string News::getBODY() {
	return BODY;
}

std::string News::getEFFECTS() {
	return EFFECTS;
}

void News::setHEAD(std::string head) {
	HEAD = head;
}
void News::setBODY(std::string body) {
	BODY = body;
}
void News::setEFFECTS(std::string effects) {
	EFFECTS = effects;
}