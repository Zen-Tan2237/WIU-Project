#pragma twice
#include <iostream>
#include <string>
class News
{

private:
    std::string randomEventHeadlines[5][5] // 1 for company collaborations(virus spread chance increase), 2 for cybersecurity triggerd,
                                           //3 for cybersecurity reports, 4 for company destroyed reports (sad stories)
    {
        { // company virus spread increase
            " is having a international collaboration as a way to increase relations.",
            " have been acquired by a parent company Zen.Inc and have started employee crossover program.",
            " started a sustainability program to help on Earths global warming.",
            " have decided to introduce a internship program to help students gain experience in larger and well known companies.",
            " have cooperated in sponsering a charity event to help others in need.",
        },

        { // company virus news (trigger cybersecurity)
            " Has Shut Down Their Email Systems In Response To A Worm Virus Spreading Via Emails.", // Worms
            " In Chaos After Emails Flooded With Viruses.", 
            " Has A Databreach Effecting 300 Million Customers Worldwide.",  
            " Loses Important Files After Malware Crashes Systems",
            " CEO Quit After Losing Years Of Reports"
        },

        { // cybersecurity news making progress against virus
            "The Cybersecurity Sector Has Made a Breakthrough Towards Creating a Antivirus.",
            "Global Cybersecurity Teams Contain Spread of \'downstairs_auntie3886\' Virus in Record Time.",
            "Cybersecurity Experts Make Major Progress in Isolating Email - Based Worm Virus",
            "Ongoing Research Yields Clues to Weaknesses in Self - Replicating Worm Code",
            "Researchers Uncover Hidden Loop in Worm Code That Could Halt Its Spread", 
        },

        { // cybersecurity news losing against virus
            "Malware Analysts Overwhelmed as Worm Mutates Faster Than Detection Tools Can Adapt",
            "Efforts to Reverse Engineer Worm Fail as Code Obfuscation Blocks Analysis",
            "\'downstairs_auntie3886\' Virus Outpaces Global Cybersecurity Defenses.",
            "Experts Warn: Cybersecurity Measures Failing to Contain \'NetWraith\'.",
            "Unstoppable Virus Variant Spreads Through Global Networks Undetected.",
        },

        { // news of when company die (the bad effects to teach the evil of a compter virus on companies)
             " Shuts Down Overnight After Devastating Cyber Attack.",
             " employees were seen crying together after losing their jobs from a computer virus.",
             " Collapses After Computer Virus Destroys Payroll and Client Files.",
             " Entire Operation Halted as Virus Erases Production Schedules and Supplier Contacts.",
             " Crippling Cyberattack Destroys All Orders, Invoices, and Communication Logs.",
        }
    };

    std::string randomEventsDescriptions[5][5]
    {
        { // company virus spread increase events
            "The companies has partnered with foreign organizations to strengthen global ties and expand its international presence.",
            "Following the acquisition by Zen.Inc, the company is facilitating workforce integration through a cross-company employee exchange initiative.",
            "The company has launched a green initiative focused on reducing its environmental footprint and supporting global climate action.",
            "The company is opening doors to aspiring professionals by launching an internship program aimed at offering real-world corporate experience.",
            "Demonstrating its commitment to social responsibility, the company co-sponsored a charitable event to support underprivileged communities.",
        },

        { // company virus news (trigger cybersecurity)
            "In an urgent defensive move, the company disabled its email infrastructure to contain a fast-spreading worm targeting internal communications.",
            "\"We dont even know which is a real email at this point\" says employee at the company.",
            "A major cybersecurity failure has exposed sensitive data of millions, triggering global concern and investigations.",
            "Critical business files were lost when a malware attack caused widespread system failures across departments.",
            "\"My heart cant take the loss of years of hard work\" says the Ceo",
        },

        { // cybersecurity news making progress against virus
            "\"Our team has been hard at work to keep all of us safe from the new malware\" - Bryani Y.N, Ceo of Checkpoint Security",
            "Through rapid coordination and real-time response, cybersecurity professionals successfully stopped the virus before it could cause global damage.",
            "Researchers have successfully traced the infection vectors of a fast-spreading worm virus, allowing targeted containment strategies to be deployed across affected systems.",
            "Security analysts have uncovered potential flaws in the worm’s code structure, fueling hope for the eventual creation of a targeted patch.",
            "Anomalies in the worm’s replication logic have been identified, offering a potential entry point for future containment or neutralization.",
        },

        { // cybersecurity news losing against virus
            "Despite aggressive countermeasures, the newly emerged virus spread faster than anticipated, exposing serious weaknesses in current defense systems."
            "Cybersecurity experts are sounding alarms as containment strategies fall short against the highly evasive NetWraith virus.",
            "A new variant of malware has infiltrated international networks without triggering standard security alerts, prompting urgent calls for upgraded protocols.",
            "The worm’s self-modifying code is evolving beyond current antivirus signatures, rendering many security tools ineffective.",
            "Attempts to dissect the worm’s inner workings have been hampered by complex encryption layers and advanced obfuscation techniques.",
        },

        { // news of when company die (the bad effects to teach the evil of a compter virus on companies)
            "Employees were seen embracing in the parking lot after learning that years of digital records, finances, and projects had been completely wiped out, forcing immediate closure.",
            "Emplyee said\"It was so sudden when when our computers all got destroyed at the same time by the virus\""
            "Many left jobless after the incident with no where to go.",
            "Without access to systems, shipments, or communications, the company had no choice but to shut its doors indefinitely.",
            "With months of business lost and no records to rebuild from, the CEO said continuing would be \"financially and emotionally impossible\"."
        }
    };

public:
    News();
    ~News();
    
    void companyCollabNews(char companyA, char companyB) const;
    void virusFoundNews(char company) const;
    void cybersecurityWinningNews() const;
    void cyberSecurityLosingNews() const;
    void companyDeadNews(char company) const;
    
};

// in case there is more than 1 virus type
//  "In Chaos As Randsomeware Hits Every Computer In The Company.", // Ransomeware
//  "Has A Databreach Effecting 300 Million Customers Worldwide.", //Trojan  

