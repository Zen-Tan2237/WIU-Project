#include "Worm.h"

Worm::Worm() {
	speed = 2; // 1 for slow 5 max
	complexity = 3; // 1 to 10
	payload = 1; // 1 to 10
	resilience = 4; //1 to 10
}

Worm::~Worm() {

}

void Worm::mutate(int chainIndex) {
	
}