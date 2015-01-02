#include "Game.h"

#include <Windows.h>
#include <iostream>

#include "glew_test.h"

int main(int argc, char* args[])
{
	AllocConsole(); 
	freopen("CON","w", stdout);



	Game* game = new Game("Chapter 1: Setting up SDL", 200, 200, 
		640, 480, false);

	game->init();

	glew_init();

	while(game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}

