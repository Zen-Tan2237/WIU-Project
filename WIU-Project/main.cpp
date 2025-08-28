#include <iostream>
#include "Game.h"
#include <windows.h>
#include <thread>

#include "SoundController.h"

int main() {

	srand((unsigned)time(0));

	Game* game = new Game;
	game->initGame();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "Please resize your window";

	std::thread inputHandler(&Game::inputHandler, game);
	std::thread printInterface(&Game::printInterface, game);
	std::thread consoleWidthHandler(&Game::consoleWidthHandler, game);

	inputHandler.detach();
	printInterface.detach();
	consoleWidthHandler.detach();

	while (game->getCurrentScreen() != 4) {
		continue;
	}

	std::thread doTurn(&Game::doTurn, game);
	doTurn.join();

	delete game;

	std::cout << "Halalworld" << std::endl;
	return 0;
}