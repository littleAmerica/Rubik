#include "Game.h"

#include <Windows.h>


#include "ShaderProgram.h"




int main(int argc, char* args[])
{
	AllocConsole(); 
	freopen("CON","w", stdout);



	Game* game = new Game("Chapter 1: Setting up SDL", 200, 200, 
		320, 480, false);

	game->init();

	glew_init();
	ShaderProgram shaderProgram(readShader("C:/Users/matan/Documents/GitHub/Rubik/resourse/shaders/simple.vert"), 
		readShader("C:/Users/matan/Documents/GitHub/Rubik/resourse/shaders/simple.frag"));	

	while(game->running())
	{
		/* Make our background black */
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		game->handleEvents();
		game->update();
		
		glDrawArrays(GL_TRIANGLES, 0, 3 );
	
		game->render();
	}

	game->clean();

	return 0;
}

