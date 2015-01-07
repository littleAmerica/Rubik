#include "Game.h"
#include <iostream>

#include "ShaderProgram.h"
#include "Triangle.h"
#include "Torus.h"

#include "glm/glm.hpp"
using glm::mat4;
using glm::vec3;
#include <glm/gtc/matrix_transform.hpp>

#include "GL/glew.h"
#include <GL/gl.h>
#include <GL/glu.h>

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

		SDL_Delay(100);
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
	glClearColor ( 0.0, 0.0, 1.0, 1.0 );
	glClear ( GL_COLOR_BUFFER_BIT );

	if (drawable)
		drawable->render();

	SDL_GL_SwapWindow(m_pWindow);
}


void Game::update()
{

	Model = glm::rotate(Model, 0.1f, glm::vec3(0.f, 1.f, 0.f));

	glm::mat4 MVP        = Projection * View * Model;
	shaderProgram.setUniform(MVP, "MVP");
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
	shaderProgram.compileShaderFromString(ShaderProgram::readShader("../../../resourse/shaders/diffuse.vert"), ShaderProgram::VERTEX);
	shaderProgram.compileShaderFromString(ShaderProgram::readShader("../../../resourse/shaders/diffuse.frag"), ShaderProgram::FRAGMENT);
	
	shaderProgram.bindFragDataLocation(0, "FragColor");

//	glClearColor(0.0,0.0,0.0,1.0);
//	glEnable(GL_DEPTH_TEST);

	drawable.reset(new Torus(0.5f, 0.3f, 30, 30));

	shaderProgram.linkProgram();
	shaderProgram.use();
	//glm::mat4 model = glm::mat4(1.0f);
	//model *= glm::rotate(-35.0f, glm::vec3(1.0f,0.0f,0.0f));
	//model *= glm::rotate(35.0f, glm::vec3(0.0f,1.0f,0.0f));
	//
	//glm::mat4 view = glm::lookAt(glm::vec3(0.0f,0.0f,2.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	//
	//glm::mat4 projection = mat4(1.0f);

	//shaderProgram.setUniform(glm::vec3(0.9f, 0.5f, 0.3f), "Kd");
	//shaderProgram.setUniform(glm::vec3(1.0f, 1.0f, 1.0f), "Ld");
	

	//glm::mat4 mv = view * model;
	//shaderProgram.setUniform(mv, "ModelViewMatrix");
	//shaderProgram.setUniform(glm::mat3(vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]) ), "NormalMatrix");
	//shaderProgram.setUniform(projection * mv, "MVP");

	Projection = glm::perspective(45.f, 4.0f / 3.0f, 0.1f, 100.0f);

	View       = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0));

	Model      = glm::mat4(1.0f);

	shaderProgram.setUniform(glm::vec4(5.0f,5.0f,2.0f,1.0f), "LightPosition" );
	shaderProgram.setUniform(glm::vec4(4.f,-3.f,3.f,1.f), "CameraPosition");
}


void Game::OnKeyDown(SDL_Keycode sym, Uint16 mod) 
{
	//if(sym.)
}