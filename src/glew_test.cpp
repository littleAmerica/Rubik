#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "glew_test.h"

#include <iostream>

void glew_init()
{
	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		std::cout << "Error initializing GLEW: " << glewGetErrorString(err) << "\n";
	}

}