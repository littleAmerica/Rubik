#pragma once

#include <string>
#include <list>

#include "SDL.h"

#include "Event.h"
#include "ShaderProgram.h"
#include "Drawable.h"
#include "Camera.h"
#include <memory>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"

using glm::vec4;
using glm::mat4;


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
	void OnKeyDown(SDL_Keycode sym, Uint16 mod);
	virtual void OnExit();
	void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);

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

	std::shared_ptr<Drawable> m_drawable;
	std::shared_ptr<Camera> m_camera;

	typedef std::list<std::shared_ptr<Interpolation>> Interpolations;
	Interpolations m_interpolations;

	mat4 m_model;
};

