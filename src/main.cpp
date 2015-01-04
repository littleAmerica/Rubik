#include "Game.h"

#include <Windows.h>

#include <fstream>


int main(int argc, char* args[])
{
	AllocConsole(); 
	freopen("CON","w", stdout);

	Game* game = new Game("Chapter 1: Setting up SDL", 200, 200, 
		320, 480, false);

	game->run();

	delete game;

	return 0;
}

