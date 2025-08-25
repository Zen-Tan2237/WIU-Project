#include <iostream>
#include "Game.h"
#include "SoundController.h"

int main() {

	srand((unsigned)time(0));

	Game* game = new Game;

	game->initGame();
	SoundController::playSoundLoop(L"resources\\yipeeee.wav");
	while (true) {
		game->printInterface();
		game->doTurn();
	}

	delete game;

	std::cout << "Halalworld" << std::endl;
	return 0;
}