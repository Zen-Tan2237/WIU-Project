#include <iostream>
#include "Game.h"
#include <windows.h>
#include <thread>

#include "SoundController.h"

int main() {

	srand((unsigned)time(0));

	Game* game = new Game;

	game->initGame();

	std::thread inputHandler(&Game::inputHandler, game);
	std::thread printInterface(&Game::printInterface, game);

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	inputHandler.detach();
	printInterface.detach();
	std::cout << "Please resize your window";

	while (game->getCurrentScreen() != 4) {
		continue;
	}

	std::thread doTurn(&Game::doTurn, game);
	doTurn.join();

	delete game;

	std::cout << "Halalworld" << std::endl;
	return 0;
}