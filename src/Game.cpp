#include "Game.h"
#include <iostream>

#include "ShaderProgram.h"
#include "Triangle.h"

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
	if (drawable)
		drawable->render();

	SDL_GL_SwapWindow(m_pWindow);
}


void Game::update()
{
	//mat4 rotationMatrix = glm::rotate(mat4(1.0f), 30.f, vec3(0.0f,0.0f,1.0f));

	//shaderProgram.setUniform(rotationMatrix, "RotationMatrix");
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
	drawable.reset();

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


void Game::InitGLSLProgram()
{
	shaderProgram.compileShaderFromString(ShaderProgram::readShader("../../../resourse/shaders/simple.vert"), ShaderProgram::VERTEX);
	shaderProgram.compileShaderFromString(ShaderProgram::readShader("../../../resourse/shaders/simple.frag"), ShaderProgram::FRAGMENT);
	
	shaderProgram.bindFragDataLocation(0, "FragColor");

	drawable.reset(new Triangle());

	shaderProgram.linkProgram();
	shaderProgram.use();
}
