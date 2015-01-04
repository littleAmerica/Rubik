#include "Game.h"
#include <iostream>

#include "ShaderProgram.h"

#include "glm/glm.hpp"
using glm::mat4;
using glm::vec3;
#include <glm/gtc/matrix_transform.hpp>

Game::Game(const std::string& name, int xpos, int ypos, int height, int width, bool fullscreen):
m_pWindow(NULL),
m_pRenderer(NULL),
m_name(name),
m_xpos(xpos),
m_ypos(ypos),
m_width(width),
m_height(height),
m_fullscreen(fullscreen),
m_bRunning(false)
{
	std::cout << "Game::Game\n";
}


Game::~Game(void)
{
}


void Game::run()
{
	init();

	while(running())
	{
		handleEvents();
		
		update();
		
		render();
	}

	clean();
}


void Game::init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		int flags = SDL_WINDOW_SHOWN;
		if(m_fullscreen)
		{
			flags |= SDL_WINDOW_FULLSCREEN;	
		}

		bool m_opengl = true;
		if (m_opengl)
		{
			//Use OpenGL 2.1
			SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
			SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			flags |= SDL_WINDOW_OPENGL;
		}



		// if succeeded create our window
		m_pWindow = SDL_CreateWindow(m_name.c_str(), m_xpos, m_ypos, m_width, m_height, flags);

		// if the window creation succeeded create our renderer
		if(m_pWindow != 0)
		{
			m_context = SDL_GL_CreateContext(m_pWindow);
			
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer)
			{
				SDL_SetRenderDrawColor(m_pRenderer,	255, 0, 255, 255);
				m_bRunning = true;
			}
		}

		glew_init();
		InitGLSLProgram();
	}
}


void Game::render()
{
	glClearColor(0.8, 0.8, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3 );

	SDL_GL_SwapWindow(m_pWindow);
}


void Game::update()
{
	mat4 rotationMatrix = glm::rotate(mat4(1.0f), 30.f, vec3(0.0f,0.0f,1.0f));

	shaderProgram.setUniform(rotationMatrix, "RotationMatrix");

}


void Game::handleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		OnEvent(&event);
	}
}


void Game::clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}


bool Game::running() 
{ 
	return m_bRunning; 
}


void Game::OnEvent( SDL_Event* event )
{
	Event::OnEvent(event);
}


void Game::OnExit()
{
	m_bRunning = false;
}


static float positionData[] = {
	-0.8f, -0.8f, 0.0f,
	0.8f, -0.8f, 0.0f,
	0.0f, 0.8f, 0.0f, };

static float colorData[] = {
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 
	0.1f, 0.0f, 0.0f};


void Game::InitGLSLProgram()
{
	shaderProgram.compileShaderFromString(ShaderProgram::readShader("simple.vert"), ShaderProgram::VERTEX);
	shaderProgram.compileShaderFromString(ShaderProgram::readShader("simple.frag"), ShaderProgram::FRAGMENT);
	
	static GLuint vaoHandle = 0;
	static GLuint positionBufferHandle = 0;
	static GLuint colorBufferHandle = 0;

	static GLuint programHandle = shaderProgram.getShaderProgram();

	// Create and set-up the vertex array object
	glGenVertexArrays( 1, &vaoHandle );
	glBindVertexArray(vaoHandle);

	// Populate the position buffer
	glGenBuffers(1, &positionBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );	
	shaderProgram.bindAttribLocation(0, "VertexPosition");

	// Populate the color buffer
	glGenBuffers(1, &colorBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData,	GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0,(GLubyte *)NULL );
	shaderProgram.bindAttribLocation(1, "VertexColor");

	
	shaderProgram.bindFragDataLocation(0, "FragColor");


//	glBindVertexArray(vaoHandle);

	shaderProgram.linkProgram();
	shaderProgram.use();
}

void initVAO(GLuint programHandle, GLuint& vaoHandle)
{

	static GLuint vboHandles[2];


}
