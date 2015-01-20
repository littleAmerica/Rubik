#include "Game.h"
#include <iostream>

#include "ShaderProgram.h"
#include "Triangle.h"
#include "Torus.h"
#include "Cube.h"


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
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

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
		SDL_WarpMouseInWindow(m_pWindow, m_width / 2, m_height / 2);
//		SDL_SetRelativeMouseMode(SDL_TRUE);

		glew_init();
		InitGLSLProgram();
		
		m_camera.reset(new Camera(glm::vec3(0.f, 0.f, 3.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.0f)));
	}
}


void Game::render()
{
	clear_screen();
	if (m_drawable)
		m_drawable->render();

	SDL_GL_SwapWindow(m_pWindow);
}


void Game::InitGLSLProgram()
{
	shaderProgram.compileShaderFromString(ShaderProgram::readShader("../../../resourse/shaders/simple.vert"), ShaderProgram::VERTEX);
	shaderProgram.compileShaderFromString(ShaderProgram::readShader("../../../resourse/shaders/simple.frag"), ShaderProgram::FRAGMENT);

	shaderProgram.bindFragDataLocation(0, "FragColor");

	shaderProgram.use();

	//drawable.reset(new Cube());
	m_drawable.reset(new Torus(0.7f, 0.3f, 30, 30));

	shaderProgram.linkProgram();
	shaderProgram.use();

	shaderProgram.printActiveAttribs();
	shaderProgram.printActiveUniforms();

	//ADS
	shaderProgram.setUniform(100.0f, "material.Shininess");
	shaderProgram.setUniform(glm::vec3(0.9f, 0.5f, 0.3f), "material.Kd");
	shaderProgram.setUniform(glm::vec3(0.9f, 0.5f, 0.3f), "material.Ka");
	shaderProgram.setUniform(glm::vec3(0.8f, 0.8f, 0.8f), "material.Ks");
	shaderProgram.setUniform(glm::vec3(1.0f, 1.0f, 1.0f), "light.Ld");
	shaderProgram.setUniform(glm::vec3(0.4f, 0.4f, 0.4f), "light.La");
	shaderProgram.setUniform(glm::vec3(1.0f, 1.0f, 1.0f), "light.Ls");
	glm::vec3 LightPos = glm::vec3(0.f, 3.f, -40.f);	   
	shaderProgram.setUniform(LightPos, "Light.Position");	
	
}


void Game::update()
{
	//TODO refactored this 
	int currentTime = SDL_GetTicks(); 
	Interpolations::iterator iter = m_interpolations.begin();
	while( iter != m_interpolations.end())
	{
		if ((*iter)->isValid(currentTime))
		{
			(*iter)->interpolate(currentTime);
			iter++;
		}
		else
			m_interpolations.erase(iter++);		
	}

	shaderProgram.use();


	//SDL_Delay(100);

	m_model *= glm::rotate(.02f, glm::vec3(0.f, 1.f, 0.0f));
	mat4 normalMatrix = glm::transpose(glm::inverse(m_camera->View() * m_model));
	glm::mat4 MVP = m_camera->Projection() * m_camera->View() *  m_model;

	shaderProgram.setUniform(m_camera->View(), "ViewMatrix");
	shaderProgram.setUniform(m_model, "ModelMatrix");
	shaderProgram.setUniform(m_camera->Projection(), "ProjectionMatrix");
	shaderProgram.setUniform(normalMatrix, "NormalMatrix");
	shaderProgram.setUniform(MVP, "MVP");
	shaderProgram.setUniform(m_camera->View() * m_model, "ModelViewMatrix");
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
	shaderProgram.release();

	m_drawable.reset();

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

void Game::OnKeyDown(SDL_Keycode sym, Uint16 mod) 
{
	//TODO refactored this 
	if(sym == SDLK_w)
	{
		m_interpolations.push_back(m_camera->getMoveInterpolation(0.f, 0.f, 1.f, SDL_GetTicks(), SDL_GetTicks() + 1000));
	}else if (sym == SDLK_s)
	{
		m_interpolations.push_back(m_camera->getMoveInterpolation(0.f, 0.f, -1.f, SDL_GetTicks(), SDL_GetTicks() + 1000));
	}
	if(sym == SDLK_a)
	{
		m_interpolations.push_back(m_camera->getMoveInterpolation(-1.f, 0.f, 0.f, SDL_GetTicks(), SDL_GetTicks() + 1000));
	}else if (sym == SDLK_d)
	{
		m_interpolations.push_back(m_camera->getMoveInterpolation(1.f, 0.f, 0.f, SDL_GetTicks(), SDL_GetTicks() + 1000));
	}


	if (sym == SDLK_ESCAPE)
	{
		m_bRunning = false;
	}

	if (sym == SDLK_F1)
	{
		m_camera.reset(new Camera(glm::vec3(0.f, 0.f, 3.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.0f)));
	}
}


void Game::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
#ifdef _DEBUG
	static bool debug_skipp_mouse = true;
	if(debug_skipp_mouse)
		return;
#endif
	
	static bool skipped = true; 

	if (!skipped)
	{
		std::cout << relX << " " << relY << "\n";
		m_camera->rotate(glm::radians((float)relX / 10.f), glm::radians((float)relY / 10.f));


		SDL_WarpMouseInWindow(m_pWindow, m_width / 2, m_height / 2);
		skipped = true;
	}
	else
	{
		skipped = false;
	}
}
