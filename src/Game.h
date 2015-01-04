#pragma once

#include <string>

#include "SDL.h"

#include "Event.h"
#include "ShaderProgram.h"
#include "drawable.h"
#include <memory>



class Game : private Event
{
public:
	Game(const std::string& name, int xpos, int ypos, int height, int width, bool fullscreen);
	~Game(void);

	void run();


private:

	//Game routine
	void init();
	void render();
	void update();
	void handleEvents();
	void clean();
	bool running();

	virtual void OnEvent(SDL_Event* event);
	virtual void OnExit();
	void InitGLSLProgram();

	SDL_Window*		m_pWindow;
	SDL_Renderer*	m_pRenderer;

	SDL_GLContext	 m_context;

	//SDL_Texture*	m_pTexture; // the new SDL_Texture variable
	//SDL_Rect		m_sourceRectangle; // the first rectangle
	//SDL_Rect		m_destinationRectangle; // another rectangle

	ShaderProgram	shaderProgram;

	bool			m_bRunning;

	std::string		m_name;
	int				m_xpos;
	int				m_ypos;
	int				m_width;
	int				m_height;
	bool			m_fullscreen;

	std::shared_ptr<Drawable> drawable;
};

