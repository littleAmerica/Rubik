#include "Game.h"

#include <Windows.h>


#include "ShaderProgram.h"

#include "glm/glm.hpp"
using glm::mat4;
using glm::vec3;
#include <glm/gtc/matrix_transform.hpp>



int main(int argc, char* args[])
{
	AllocConsole(); 
	freopen("CON","w", stdout);



	Game* game = new Game("Chapter 1: Setting up SDL", 200, 200, 
		320, 480, false);

	game->init();

	glew_init();
	ShaderProgram shaderProgram(readShader("../../../resourse/shaders/simple.vert"), 
		readShader("../../../resourse/shaders/simple.frag"));	

	float angle = 1;

	while(game->running())
	{

		mat4 rotationMatrix = glm::rotate(mat4(1.0f), 30.f, vec3(0.0f,0.0f,1.0f));

		shaderProgram.SetMatrix(rotationMatrix, "RotationMatrix");

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

