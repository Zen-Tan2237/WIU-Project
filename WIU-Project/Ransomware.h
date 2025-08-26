#pragma once
#include "Virus.h"
class Ransomware :
    public Virus
{

public:
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

