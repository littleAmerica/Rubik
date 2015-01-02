#pragma once

#include "string"

#include "SDL.h"



class Game
{
public:
	Game(const std::string& name, int xpos, int ypos, int height, int width, bool fullscreen);
	~Game(void);

	//Game routine
	void init();
	void render();
	void update();
	void handleEvents();
	void clean();
	bool running();

private:

	SDL_Window*		m_pWindow;
	SDL_Renderer*	m_pRenderer;

	SDL_GLContext	 m_context;

	SDL_Texture*	m_pTexture; // the new SDL_Texture variable
	SDL_Rect		m_sourceRectangle; // the first rectangle
	SDL_Rect		m_destinationRectangle; // another rectangle

	bool			m_bRunning;

	std::string		m_name;
	int				m_xpos;
	int				m_ypos;
	int				m_width;
	int				m_height;
	bool			m_fullscreen;
};

