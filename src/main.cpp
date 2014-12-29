#include "Game.h"

#include <Windows.h>
#include <iostream>

int main(int argc, char* args[])
{
	AllocConsole(); 
	freopen("CON","w", stdout);

	Game* game = new Game("Chapter 1: Setting up SDL", 200, 200, 
		640, 480, false);

	game->init();

	while(game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}

