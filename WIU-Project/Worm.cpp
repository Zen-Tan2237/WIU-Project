#include "Worm.h"

Worm::Worm() {
	speed = 7;       // spreads quickly through networks
	stealth = 3;     // not very stealthy, easy to notice
	payload = 2;     // weak direct damage (annoying but not catastrophic)
	resilience = 4;  // moderate resistance to cleanup
}

Worm::Worm(int speed, int stealth, int payload, int resilience) {
	this->speed = speed;
	this->stealth = stealth;
	this->payload = payload;
	this->resilience = resilience;
}

Worm::~Worm() {

}

