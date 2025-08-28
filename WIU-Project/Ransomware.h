#pragma once
#include "Virus.h"
class Ransomware :
    public Virus
{

public:

	enum UPGRADES {
		// SPEED UPGRADES
		POLYMORHPIC_ENGINE,
		LAN_SCANNER,
		SMB_EXPLOIT,
		USB_PROPAGATION,
		BOTNET_BOOST,
		EMAIL_WORM_BOOST,
		//COMPLEXITY/PAYLOAD UPGRADES
		ENCRYPTION_LAYER,
		KEYLOGGER_MODULE,
		ROOTKIT_INJECTION,
		BRICKING_ROUTINE,
		DATA_WIPER,
		ANTIVIRUS_BYPASS,
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

	std::string nameUpgrade[NUM_UPGRADES * 2] = {
		// SPEED UPGRADES
		"Email Spam Botnet", "Spreads via mass phishing campaigns. Speed increases slightly.",
		"Exploit Kit Loader", "Uses known software vulnerabilities to spread. Speed increases moderately.",
		"Remote Desktop Attack", "Brute-forces weak RDP logins to spread. Speed increases slightly.",
		"Network Share Encryption", "Spreads through shared folders. Speed increases slightly.",
		"Worm-Ransom Hybrid", "Combines worm-like spreading with ransomware. Speed increases significantly.",

		// PAYLOAD / COMPLEXITY UPGRADES
		"File Encryption", "Encrypts files with basic algorithm. Increases payload.",
		"Advanced Encryption", "Switches to stronger AES/RSA encryption. Increases complexity and payload.",
		"Master Boot Record Hijack", "Locks system at boot with ransom note. Payload increases significantly.",
		"Shadow Copy Deletion", "Deletes Windows backups to enforce ransom. Increases complexity.",
		"Network File Encryption", "Encrypts files on mapped network drives. Significantly increases payload.",
		"Double Extortion", "Steals data before encrypting. Victims face data leak threats. Significantly increases payload and complexity.",

		// RESILIENCE UPGRADES
		"Ransom Note Customizer", "Automatically generates notes per victim. Increases resilience.",
		"Offline Encryption Mode", "Does not require contact with C2 server. Increases resilience.",
		"Polymorphic Encryption Key", "Encryption key changes per victim, harder to crack. Increases resilience significantly.",
		"Kill Switch Removal", "Removes built-in kill switch to prevent shutdown. Increases resilience.",
		"Tor C2 Channel", "Uses Tor network for ransom communication. Increases resilience.",
		"Payment Deadline Escalation", "Doubles ransom over time. Slows cure and increases victim pressure."
	};




    float statsUpgradeRansomware[NUM_UPGRADES * 5] = {
        // Simple Locker
        0.2f, 0.2f, 0.8f, 0.1f, 14,
        // Screen Blocker
        0.1f, 0.3f, 1.0f, 0.2f, 18,
        // File Encryptor I
        0.2f, 0.4f, 1.5f, 0.3f, 24,
        // File Encryptor II
        0.3f, 0.6f, 2.0f, 0.4f, 32,
        // Network Encryptor
        0.3f, 0.7f, 2.5f, 0.5f, 36,
        // Double Extortion
        0.1f, 0.8f, 3.0f, 0.6f, 40,

        // Anti-Recovery
        0, 0.5f, 0.5f, 0.7f, 28,
        // Shadow Copy Deleter
        0, 0.6f, 0.8f, 0.8f, 34,
        // Boot Locker
        -0.3f, 0.7f, 2.2f, 0.5f, 42,
        // Offline Encryption Mode
        0.2f, 0.6f, 1.5f, 0.4f, 30,
        // Polymorphic Encryption
        0, 0.9f, 1.8f, 0.6f, 38,
        // Ransom Note Obfuscation
        0, 0.4f, 0, 0.9f, 20,

        // Crypto Upgrade (AES→RSA→Hybrid)
        0, 1.0f, 3.5f, 0.7f, 50,
        // Worm-Like Spread
        0.7f, 0.5f, 2.0f, 0.5f, 45,
        // RaaS (Ransomware as a Service)
        0.3f, 1.2f, 3.0f, 0.8f, 60,
        // Wiper Mode
        -0.5f, 0.8f, 4.5f, 1.0f, 70
    };


    Ransomware();
    ~Ransomware();

    void evolve(Upgrades*) override;
    void miniGame(int& hackingPoints);

private:
    // minigame
    int option[3];
    std::string NoteBuilder[3][3]
    {
        {
            "We control your systems. Failure to pay will result in complete data destruction, exposure of private files, and system - wide corruption.\n",
            "Your files have been encrypted. We are professionals and will restore access upon payment.Follow instructions carefully to avoid permanent loss.\n",
            "Apologies for the inconvenience. Your files are temporarily inaccessible. A small payment will restore full access. Thank you for understanding.\n"
        },
        {
            "Send 1000 Bitcoins to Downstairs_auntie67.\n",
            "Meet me at Yishun kopitiam with $40,000 Cash.\n",
            "PayLater my number 94832767, $40,000 \n"
        },
        {
            "You have 24 Hours. After that, your files will be gone forever.\n",
            "You have 10 Minutes to comply. Otherwise the decryption key will be destroyed.\n",
            "You have 7 Days to complete the payment. We will not extend the deadline.\n",
        }
    };
    int NoteBuilderPoints[3][3]
    {
        {3, 2, 1},
        {3, 1, 2},
        {3, 1, 2},
    };
    std::string NoteBuilderHeader[3]
    {
        "Choose a tone for the note:\n",
        "Choose the payment method\n",
        "Choose a Deadline\n"
    };
};

