#include <iostream>
#include "Game.h"
#include "SoundController.h"

int main() {

	srand((unsigned)time(0));

	Game* game = new Game;

	game->initGame();

	std::thread inputHandler(&Game::inputHandler, game);
	//std::thread printInterface(&Game::printInterface, game);

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	inputHandler.detach();
	std::cout << "Awaiting appropriate Window Size...";

	while (true) {
		game->printInterface();
		game->doTurn();
	}

	delete game;

	std::cout << "Halalworld" << std::endl;
	return 0;
}