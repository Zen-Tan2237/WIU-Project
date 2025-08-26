#include "Worm.h"

Worm::Worm() {
    name = "no name lol";
	speed = 2; // 1 for slow 5 max
	complexity = 3; // 1 to 10
	payload = 1; // 1 to 10
	resilience = 4; //1 to 10
}

Worm::~Worm() {

}
void Worm::evolve(Upgrades* toUpgrade) {
	std::cout << "Speed to upgrade: " << (toUpgrade->getSpeed() + 0.5f) << std::endl
		<< " Complexity to upgrade: " << toUpgrade->getComplexity() << std::endl
		<< " Payload to upgrade" << toUpgrade->getPayload() << std::endl
		<< " Resilience to upgrade" << toUpgrade->getResilience() << std::endl;

	speed += (toUpgrade->getSpeed() + 0.5f);
	complexity += toUpgrade->getComplexity();
	payload += toUpgrade->getPayload();
	resilience += toUpgrade->getResilience();
}

void Worm::miniGame(int &hackingPoints) {
	std::cout << "Mini Game: Identify the fake domain name from the two options given.\n";
    srand(static_cast<unsigned int>(time(0)));
    std::string realArray[10] = {
        "paypal.com",
        "microsoft.com",
        "google.com",
        "apple.com",
        "amazon.com",
        "bankofamerica.com",
        "facebook.com",
        "twitter.com",
        "dropbox.com",
        "linkedin.com"
    };
    std::string fakeArray[10] = {
        "paypa1.com",
        "micros0ft.com",
        "goog0l.com",
        "apple-support.com",
        "arnazon.com",
        "bancofamerica.com",
        "facebok-login.com",
        "twltter.com",
        "dropdox.net",
        "1inkedin.com"
    };
	int tracker[6] = { -1, -1, -1, -1, -1, -1 };//to check if the random number has been used before
    int userInput;
    int randomIndex = 0;

    for (int i = 0; i < 3; i++) {
        do {
            randomIndex = rand() % 20;
        } while (randomIndex == tracker[0] || randomIndex == tracker[1] || randomIndex == tracker[2] ||
            randomIndex == tracker[3] || randomIndex == tracker[4] || randomIndex == tracker[5]);

        if (randomIndex < 10) {
            std::cout << "1." << realArray[randomIndex] << "\n\n2." << fakeArray[randomIndex] << std::endl;
			tracker[i] = randomIndex;
            tracker[i + 3] = randomIndex + 10;
        }
        else {
            std::cout << "1." << fakeArray[randomIndex - 10] << "\n\n2." << realArray[randomIndex - 10] << std::endl;
			tracker[i] = randomIndex;
			tracker[i+3] = randomIndex - 10;
        }
        do {
            std::cout << "Enter the FAKE domain:\n";
            std::cin >> userInput;
        } while (userInput < 1 || userInput > 2);
        if (randomIndex < 10 && userInput == 2) {
            std::cout << "Successful hack! Gain 1 hacker points" << std::endl;
            hackingPoints++;
        }
        else if (randomIndex >= 10 && userInput == 1) {
            std::cout << "Successful hack! Gain 1 hacker points" << std::endl;
            hackingPoints++;
        }
        else {
            std::cout << "Hack Failed! You sent the real link" << std::endl;
        }
    }
}