#include <iostream>
#include <windows.h>
#include "Game.h"
#include <thread>

int main() {
	srand(time(0));
	SetConsoleOutputCP(CP_UTF8);

	Game* game = new Game;

	game->initGame();

	std::thread inputHandler(&Game::inputHandler, game);
	//std::thread printInterface(&Game::printInterface, game);

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	inputHandler.detach();
	std::cout << "Awaiting appropriate Window Size...";

	while (true) {
		game->printInterface();
	}

	delete game;

	std::cout << "Halalworld" << std::endl;
	return 0;
}