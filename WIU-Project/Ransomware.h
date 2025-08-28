#pragma once
#include "Virus.h"
class Ransomware :
    public Virus
{

public:

	enum UPGRADES {
		// SPEED UPGRADES
        SPAM_CAMPAIGN,
        NETWORK_PROPAGATION,
        RDP_BRUTE_FORCER,
        EXPLOIT_KIT_INTEGRATION,
        WORM_LIKE_PROPAGATION,
        MALICIOUS_UPDATE_HIJACK,
		//COMPLEXITY/PAYLOAD UPGRADES
        AES_FILE_ENCRYPTION,
        RSA_KEY_EXCHANGE,
        FILE_EXTENSION_TARGETING,
        SHADOW_COPY_DELETION,
        NETWORK_SHARE_ENCRYPTION,
        DOUBLE_EXTORTION_MODULE,
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

    std::string nameUpgradeRansomware[NUM_UPGRADES * 2] = {
        // SPEED / SPREAD (6)
        "Spam Campaign", "Mass phishing with malicious attachments. Spread increases.",
        "Network Propagation", "Scans LAN shares and weak creds to spread laterally.",
        "RDP Brute Forcer", "Breaks into exposed remote desktops; new footholds.",
        "Exploit Kit Integration", "Bundles with exploit kits to auto-deliver. Faster spread.",
        "Worm-Like Propagation", "Self-replicates across reachable hosts. Big speed boost.",
        "Malicious Update Hijack", "Poisons updater channels to push payload widely.",

        // PAYLOAD / COMPLEXITY (6)
        "AES File Encryption", "Encrypts user files with strong symmetric crypto. Payload up.",
        "RSA Key Exchange", "Unique public keys per victim; hard to crack. Complexity up.",
        "File Extension Targeting", "Prioritizes valuable file types first. Payload increases.",
        "Shadow Copy Deletion", "Removes backups to block easy recovery. Complexity up.",
        "Network Share Encryption", "Encrypts files on mapped/network drives. Big payload.",
        "Double Extortion Module", "Steals data before encrypting; leak threats. Huge payload.",

        // RESILIENCE (8)
        "Safe Mode Lockout", "Prevents recovery through safe mode. Resilience up.",
        "Process Killer", "Terminates AV/backup processes before encrypting.",
        "Tor Communication", "C2 hidden via Tor; takedown resistant.",
        "Dynamic Encryption Routine", "Changes methods per run; analysis harder.",
        "Offline Encryption Mode", "No C2 needed to start encryption.",
        "Payment Portal Integration", "Automates ransom payment workflow.",
        "Polymorphic Encryption Keys", "Keys differ per file/host; recovery difficult.",
        "Boot Locker", "Locks at boot with ransom notice; severe disruption."
    };

    float statsUpgradeRansomware[NUM_UPGRADES * 5] = {
        // Spam Campaign
        0.20f, 0.20f, 0.60f, 0.10f, 14,
        // Network Propagation
        0.35f, 0.25f, 0.50f, 0.15f, 22,
        // RDP Brute Forcer
        0.25f, 0.30f, 0.70f, 0.20f, 26,
        // Exploit Kit Integration
        0.30f, 0.40f, 0.80f, 0.25f, 32,
        // Worm-Like Propagation
        0.60f, 0.30f, 1.00f, 0.30f, 40,
        // Malicious Update Hijack
        0.45f, 0.35f, 0.80f, 0.25f, 34,

        // AES File Encryption
        0.00f, 0.40f, 1.50f, 0.30f, 28,
        // RSA Key Exchange
        0.00f, 0.70f, 1.80f, 0.40f, 36,
        // File Extension Targeting
        0.00f, 0.30f, 1.20f, 0.20f, 24,
        // Shadow Copy Deletion
        0.00f, 0.50f, 0.60f, 0.60f, 30,
        // Network Share Encryption
        0.10f, 0.45f, 2.20f, 0.40f, 42,
        // Double Extortion Module
        -0.05f, 0.80f, 3.00f, 0.60f, 50,

        // Safe Mode Lockout
        0.00f, 0.20f, 0.10f, 0.70f, 22,
        // Process Killer
        -0.10f, 0.40f, 0.20f, 0.80f, 28,
        // Tor Communication
        0.00f, 0.35f, 0.00f, 0.90f, 26,
        // Dynamic Encryption Routine
        -0.10f, 0.60f, 0.20f, 0.80f, 34,
        // Offline Encryption Mode
        0.05f, 0.30f, 0.30f, 0.70f, 24,
        // Payment Portal Integration
        0.00f, 0.40f, 0.00f, 0.80f, 30,
        // Polymorphic Encryption Keys
        -0.10f, 0.70f, 0.50f, 0.90f, 38,
        // Boot Locker
        -0.20f, 0.50f, 2.50f, 0.70f, 48
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

