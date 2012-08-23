#include "game.h"

int main (int argc, char *argv[])
{
	int exit_code = 0;

	Game *game = new Game();

	exit_code = game->loop();

	game->close();

	delete game;

	return exit_code;
}

