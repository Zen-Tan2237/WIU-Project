#pragma once
#include "Virus.h"

class Trojan : public Virus {
private:


    enum UPGRADES {
        // SPEED UPGRADES
        PHISHING_EMAILS,
        FAKE_SOFTWARE_INSTALLER,
        DRIVEBY_DOWNLOAD,
        SOCIAL_ENGINEERING_TOOLKIT,
        MALVERTISING_NETWORK,
        SUPPY_CHAIN_INJECTION,
        //COMPLEXITY/PAYLOAD UPGRADES
        CREDENTIAL_STEALER,
        REMOTE_ACCESS_MODULE,
        PRIVILAGE_EXTENSION_EXPLOIT,
        SYSTEM_SERVICE_INJECTION,
        DATA_EXFILTRATION,
        BANKING_TROJAN_MODULE,
        //RESILIENCE UPGRADES
        CODE_OBFUSCATION_I,
        CODE_OBFUSCATION_II,
        CODE_REFACTOR_I,
        CODE_REFACTOR_II,
        CODE_REFACTOR_III,
        KILL_SWITCH,
        SIGNATURE_MUTATION,
        VIRTUAL_MACHINE_DETECTION,
        NUM_UPGRADES,
    };

    int dependentIndices[NUM_UPGRADES + 6]{
        //Dependency chain 1
        0, 1, 2, 4, -1,
        //Depenency Chain 2
        0, 3, 5, -1,
        //Dependency Chain 3
        6, 8, 11, -1,
        //Dependency Chain 4
        7, 10, 9, -1,
        //Dependency Chain 5
        14, 15, 16, 18, -1,
        //Dependency Chain 6
        17, -1,
        //Dependency Chain 7
        19, -1
    };


    int dependentIndicesLength = NUM_UPGRADES + 6;

    std::string nameUpgrade[NUM_UPGRADES * 2] = {
        // SPEED / SPREAD (6)
        "Phishing Email Campaign", "Disguises as a harmless attachment to trick users. Slight speed boost.",
        "Fake Software Installer", "Masquerades as a legit installer; users self-infect. Modest speed boost.",
        "Drive-by Download", "Auto-installs from compromised sites without prompts. Increases speed.",
        "Social Engineering Toolkit", "Prompts users to grant permissions. Speed and complexity rise slightly.",
        "Malvertising Network", "Delivers the Trojan via ad networks on popular sites. Speed increases.",
        "Supply Chain Injection", "Hides inside trusted software updates. Huge spread once seeded.",

        // PAYLOAD / COMPLEXITY (6)
        "Credential Stealer", "Collects saved credentials from browsers and OS stores. Payload up.",
        "Remote Access Module", "Creates a backdoor for full remote control. Payload and complexity up.",
        "Privilege Escalation Exploit", "Gains admin rights to bypass restrictions. Big complexity & payload.",
        "System Service Injection", "Runs inside privileged services; hard to spot. Complexity up.",
        "Data Exfiltration", "Steals sensitive files and exfiltrates them. Payload significantly up.",
        "Banking Trojan Module", "Intercepts banking sessions and OTP flows. High payload & complexity.",

        // RESILIENCE (8)
        "Process Hollowing", "Hides inside trusted processes. Detection becomes harder.",
        "Persistence Service", "Auto-start on boot; reinstalls if removed. Resilience up.",
        "Polymorphic Loader", "Loader changes per install to evade signatures. Resilience & complexity up.",
        "Bootkit Component", "Loads before OS security; very hard to remove. Strong resilience.",
        "Anti-VM Check", "Avoids running in sandboxes/VMs used by analysts.",
        "Encrypted C2 Channel", "Encrypts command & control traffic; analysis slowed.",
        "Self-Repair Routine", "Rebuilds missing components if partially removed.",
        "Steganography Delivery", "Hides payload in media files to avoid detection."
    };

    float statsUpgrade[NUM_UPGRADES * 5] = {
        // Phishing Email Campaign
        0.25f, 0.20f, 0.15f, 0.10f, 12,
        // Fake Software Installer
        0.30f, 0.25f, 0.35f, 0.10f, 18,
        // Drive-by Download
        0.35f, 0.25f, 0.40f, 0.10f, 22,
        // Social Engineering Toolkit
        0.25f, 0.30f, 0.25f, 0.15f, 20,
        // Malvertising Network
        0.40f, 0.20f, 0.30f, 0.10f, 26,
        // Supply Chain Injection
        0.55f, 0.35f, 0.40f, 0.15f, 34,

        // Credential Stealer
        0.00f, 0.35f, 0.80f, 0.10f, 24,
        // Remote Access Module
        0.00f, 0.45f, 1.10f, 0.20f, 30,
        // Privilege Escalation Exploit
        0.00f, 0.60f, 1.30f, 0.25f, 36,
        // System Service Injection
        -0.05f, 0.50f, 0.90f, 0.30f, 28,
        // Data Exfiltration
        0.00f, 0.55f, 1.80f, 0.20f, 40,
        // Banking Trojan Module
        -0.05f, 0.70f, 2.20f, 0.30f, 45,

        // Process Hollowing
        0.00f, 0.20f, 0.00f, 0.60f, 22,
        // Persistence Service
        0.00f, 0.15f, 0.00f, 0.70f, 24,
        // Polymorphic Loader
        -0.10f, 0.50f, 0.00f, 0.80f, 30,
        // Bootkit Component
        -0.15f, 0.45f, 0.20f, 1.10f, 38,
        // Anti-VM Check
        0.00f, 0.30f, 0.00f, 0.60f, 20,
        // Encrypted C2 Channel
        0.00f, 0.40f, 0.10f, 0.70f, 26,
        // Self-Repair Routine
        -0.05f, 0.30f, 0.00f, 0.80f, 28,
        // Steganography Delivery
        0.00f, 0.35f, 0.10f, 0.75f, 27
    };


    void nMConvention_Ops(std::string**);
    void nMConvention_Fin(std::string**);
    void nMConvention_Sales(std::string**);
    void nMConvention_Acct(std::string**);
    void nMConvention_IT(std::string**);
    void nMConvention_HR(std::string**);

    void winConditions(int, int, int, int, int*);
    int conditionOffset(int, int&);
    void printDialog(std::string, std::string&, std::string&, std::string&, std::string&, std::string&);
    void printSynSectNm(int);
    void minigameOptions_2d(int, int, int, std::string**, std::string*);
    void minigameOptions_1d(int, int, std::string*, std::string*);
    bool playerInput(char*);

public:

    Trojan();
    ~Trojan();

    void evolve(Upgrades*);
    int miniGame();


    const std::string* getNameUpgrade() const;
    const float* getStatsUpgrades() const;
    const int* getDependentIndices() const;
    const int getNumUpgrades() const;
    const int getDependentIndicesLength() const { return dependentIndicesLength; };

};