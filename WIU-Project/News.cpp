#include "News.h"
#include "Player.h"
#include <iostream>
#include <random>

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

/* Ctrl + E + W to wrap, makes it easier to edit. */
void News::companyCollabNews(std::string companyA, std::string companyB) const {
	srand((unsigned)time(0));
	switch (rand() % 5) {
	case 0:
		std::cout << "Annual International Collaboration Program (ICP)\n";
		std::cout << '\n'
			<< companyA << " and " << companyB <<
			" are having their annual ICP as a way to strengthen their relations overseas. The companies are partnered with each other as they both are foreign organizations to each other, in doing this they strengthen their global ties and expand their international presence."
			<< '\n';
		break;
	case 1:
		std::cout << "Zen.Inc. New Leading Corporation?\n";
		std::cout << '\n'
			<< companyA << " and " << companyB <<
			" has been acquired by Zen.Inc, A crossover program has been started to allow employees from both companies to get to know each other. Zen.Inc is leading in the facilitation of workforce integration, setting an example for other companies."
			<< '\n';
		break;
	case 2:
		std::cout << "Global Initiative By " << companyA << " & " << companyB << '\n';
		std::cout << '\n'
			<< companyA << " and " << companyB <<
			" has partnered in a global initiative called Sustainability Together, which aims to reduce the carbon footprint usage within their companies, they hope, by the end of this year, their carbon footprint gets reduced by 15%. The companies have launched this green initiative, focused on reducing its environmental footprint, this supports the global climate, as it reduces the amount of carbon in the atmosphere, resulting in less heat being trapped."
			<< '\n';
		break;
	case 3:
		std::cout << "Calling All Students! Internship At Well Established Companies.\n";
		std::cout << '\n'
			<< companyA << " and " << companyB <<
			" have both decided to introduce an internship program, in the search for young talent, and to help students gain experience in larger and well known companies. The companies are opening their doors to all aspiring students, with the goal to become professionals in the future."
			<< '\n';
		break;
	case 4:
		std::cout << "News At The National Charity As 2 New Faces From " << companyA << " & " << companyB << " Were Seen\n";
		std::cout << '\n'
			<< "At the National Charity meet-up two new faces coming from "
			<< companyA << " and " << companyB <<
			" are sponsoring this years, charity event. This demonstrates their commitment to upkeep their social responsibilities, the companies are also co-sponsoring another charity event, Peoples United to support those that come from underprivileged communities."
			<< '\n';
		break;
	}
}

void News::virusFoundNews(std::string company, std::string virus) const {
	srand((unsigned)time(0));
	switch (rand() % 5) {
	case 0:
		std::cout << company << " Email Shutdowns After Malware Spread\n";
		std::cout << '\n'
			<< company <<
			" has shut down their emailing systems in response to a " << virus <<
			" circulating via their emails. They hope, by doing this they reduce the rate of which this malware spreads internally. This is an urgent, defensive move, that the company has done in hopes of containing this fast-spreading malware."
			<< '\n';
		break;
	case 1:
		std::cout << "VIIRUS DETECT! Who Will Be Next?\n";
		std::cout << '\n'
			<< company << 
			" is in chaos after viruses were detected within their communication system. \"We don't even know which is a real email at this point\" says employee at the company."
			<< '\n';
		break;
	case 2:
		std::cout << "Data Breach Affecting 300 Million People Worldwide!\n";
		std::cout << '\n'
			<< "A data breach earlier this morning has affected 300 million users. "
			<< company << 
			"'s Chairman have came out, giving a public apology, as due to their failure, sensitive data of millions have been made public putting their personal information at risk. Experts warn users of " << company <<
			" to renew their personal information, to deter fraudulent activities; before it's too late."
			<< '\n';
		break;
	case 3:
		std::cout << "System Crashes After A Malware Attack\n";
		std::cout << '\n'
			<< company << 
			" has reported that they have loss important files after a malware attack crashes their systems. Critical business files were lost when this malware attack was orchestrate causing widespread system failures across departments."
			<< '\n';
		break;
	case 4:
		std::cout << "CEO QUITS!\n";
		std::cout << '\n'
			<< company <<
			"'s CEO quits after losing years of reports \"My heart can't take the loss of years of hard work\" says the CEO."
			<< '\n';
		break;
	}
}

void News::cybersecurityWinningNews(std::string virus) const {
	srand((unsigned)time(0));
	switch (rand() % 5) {
	case 0:
		std::cout << "Breakthrough! Efforts Towards Antivirus Has Seen An Up\n";
		std::cout << '\n'
			<<"The cybersecurity sector has made a breakthrough towards creating an antivirus to the recent malware threat. \"Our team has been hard at work in keeping all of us safe from the new malware threat\" - Biryani Y.N, Ceo of Checkpoint Security."
			<< '\n';
		break;
	case 1:
		std::cout << "Contain! Spread Of " << virus << " Have Been Contained\n";
		std::cout << '\n'
			<< "Global cybersecurity teams contains spread of the fairly recent " << virus << " in Record Time. Through a rapid, well coordinated and real-time response, cybersecurity professionals successfully contain the malware before it could cause more global damage."
			<< '\n';
		break;
	case 2:
		std::cout << "Major Progress! Experts Have Isolated The Recent Malware Threat\n";
		std::cout << '\n'
			<< "Major progress have been made by cybersecurity experts, having successfully isolated a specimen of the recent malware threat, researches have been able to trace the infection vectors, allowing for targeted containment strategies to be instilled across infected systems."
			<< '\n';
		break;
	case 3:
		std::cout << "Weaknesses Found! Research Have Uncovered Potential Weak Points In The Recent Malware Threat\n";
		std::cout << '\n'
			<< "Ongoing research have yield results to the weaknesses of the self-replicating code of the recent malware threat. Security analysts have uncovered potential flaws in the worm’s code structure, fueling hope for the eventual creation of a targeted patch."
			<< '\n';
		break;
	case 4:
		std::cout << "Researchers Uncover Hidden Loop in Malware. Could This Halt Its Spread?\n";
		std::cout << '\n'
			<< "A recent loop was uncovered within the recent " << virus << "'s code. "
			"Researchers, have hint towards a potential halt towards the malware spread. The malware's replication logic have been identified, offering a potential entry point for future containment or neutralization."
			<< '\n';
		break;
	}
}

void News::cyberSecurityLosingNews(std::string virus) const {
	srand((unsigned)time(0));
	switch (rand() % 5) {
	case 0:
		std::cout << "Malware Analysts Overwhelmed As Mutations Were Faster Than Detection Tools Can Adapt\n";
		std::cout << '\n'
			<< "Despite the aggressive countermeasures held to prevent the spread of the recent malware threat, the rate of which it mutates have overwhelm malware analysts as no current malware detection tools can adapt to the rapid spread, exposing serious weaknesses in the current defense systems."
			<< '\n';
		break;
	case 1:
		std::cout << "Reverse Engineering Failed As Code Obfuscation Blocks Malware Analysts\n";
		std::cout << '\n'
			<< "Malware analysts tried to reverse engineer the recent malware threat, but to no prevail, as the code of the malware is obfuscated, making it hard to make of the malware's weaknesses. Following this cybersecurity experts are sounding alarms as containment strategies fall short against the highly evasive malware threat."
			<< '\n';
		break;
	case 2:
		std::cout << "Recent " << virus << " Outpaces Global Cybersecurity Defenses\n";
		std::cout << '\n'
			<< "A new variant of malware has infiltrated international networks, without triggering standard security alerts, prompting urgent calls for upgraded protocols."
			<< '\n';
		break;
	case 3:
		std::cout << "Experts Warn As Cybersecurity Measures Are Failing to Contain " << virus << '\n';
		std::cout << '\n'
			<< "The self-modifying code of the recent " << virus << " have been evolving beyond current antivirus signatures, rendering many security tools ineffective."
			<< '\n';
		break;
	case 4:
		std::cout << "Unstoppable Virus Spreads Through Global Networks\n";
		std::cout << '\n'
			<< "Attempts to dissect the worm’s inner workings have been hampered by complex encryption layers and advanced obfuscation techniques."
			<< '\n';
		break;
	}
}

void News::companyDeadNews(std::string company, std::string virus) const {
	srand((unsigned)time(0));
	switch (rand() % 5) {
	case 0:
		std::cout << company << " Shuts Down Overnight After Devastating Cyber Attack\n";
		std::cout << '\n'
			<< company << 
			" have recently close its doors as devastating cyber attack overwhelm their systems. Employees were seen embracing in the parking lot after learning that years of digital records, finances, and projects had been completely wiped out, forcing immediate closure."
			<< '\n';
		break;
	case 1:
		std::cout << "Many Loses Theirs Jobs After Major Loss Of Networking Ability\n";
		std::cout << '\n'
			<< company <<
			" employees were seen crying together after losing their jobs, a malware have rendered all networking ability within company boundaries unless. Employees are saying that the sudden bricking event, when all their computers got destroyed at the same time by the " << virus << '.'
			<< '\n';
		break;
	case 2:
		std::cout << company << " Has Collapse\n";
		std::cout << '\n'
			<< virus << " has destroyed all payroll and client files, leading to the collapse of " << company << ". Leaving many jobless."
			<< '\n';
		break;
	case 3:
		std::cout << "Operations Of " << company + " Halted\n";
		std::cout << '\n'
			<< "After the" << virus << " erased production schedules, and supplier contacts entirely. With no access to their systems, shipments, and communications " << company << " had no choice but to shut its doors indefinitely."
			<< '\n';
		break;
	case 4:
		std::cout << "Cyberattacks Toward " << company << " Destroys All Files\n";
		std::cout << '\n'
			<< " Crippling Cyberattack Destroys All Orders, Invoices, and Communication Logs. With months of business lost and no records to rebuild from, the CEO said continuing would be \"financially and emotionally impossible\"."
			<< " Cyberattacks towards " << company << " have cripple their records of orders, invoices, and communication logs, resulting in months of business records being lost and unable to recover, the Chairman says that continuing operations would result in an uncertain future for the company, and its people."
			<< '\n';
		break;
	}
}

void News::PlayerWinNews() const {
	srand((unsigned)time(0));
	switch (rand() % 2) {
	case 0:
		std::cout << "Financial Instability & Global Recession\n";
		std::cout << '\n'
			<< "The world's economy has taken a big hit after major companies have closed down, leaving millions jobless, and uncertain about the future. Analysts warn of long-term economic repercussions as malware dismantles IT networks, corrupts backups, and leaks sensitive data from multiple conglomerates."
			<< '\n';
		break;
	case 1:
		std::cout << "Corporate Titans Collapses\n";
		std::cout << '\n'
			<< "The destructive malware variant bypassed conventional defenses and triggered mass outages, resulting in corporate titans collapse. Major players loss millions in credit, leaving the global economy in ruin."
			<< '\n';
		break;
	}
}

void News::PlayerLoseNews() const {
	srand((unsigned)time(0));
	switch (rand() % 2) {
	case 0:
		std::cout << "Anti-Virus Software Developed\n";
		std::cout << '\n'
			<< "Corporations have developed a cyber shield, which successfully deflects the major malware attacks. rendering the digital blitz aimed at crippling global business useless, and neutralized days before crippling any key infrastructures."
			<< '\n';
		break;
	case 1:
		std::cout << "Malware Threat Neutralized\n";
		std::cout << '\n'
			<< "The global malware scare had pushed corporate defenses to their breaking points, causing cybersecurity infrastructures to bend under pressure during the widespread malware blitz, but through sheer determination, rapid-responses and drastic internal measures did companies manage to hold the line."
			<< '\n';
		break;
	}
}