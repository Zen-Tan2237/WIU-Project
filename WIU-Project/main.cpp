#include <iostream>
#include "Game.h"

int main() {

	Game* game = new Game;

	game->initGame();
	while (true) {
		game->printInterface();
		game->doTurn();
	}


	delete game;


	std::cout << "Halalworld" << std::endl;
	return 0;
}