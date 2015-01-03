#include "GL/glew.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include "glew_test.h"

#include <iostream>

void print_glew_info(bool full = false);

					



void print_glew_info(bool full)
{
	const GLubyte *renderer = glGetString( GL_RENDERER );
	const GLubyte *vendor = glGetString( GL_VENDOR );
	const GLubyte *version = glGetString( GL_VERSION );
	const GLubyte *glslVersion =
		glGetString( GL_SHADING_LANGUAGE_VERSION );
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	std::cout <<"GL Vendor : " << vendor << "\n";
	std::cout <<"GL Renderer : " << renderer << "\n";
	std::cout <<"GL Version (string) : " << version << "\n";
	std::cout <<"GL Version (integer) : " << major << "." << minor << "\n";
	std::cout <<"GLSL Version : " << glslVersion << "\n"; 

	if (!full)
		return;
	GLint nExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
	for( int i = 0; i < nExtensions; i++ )
		std::cout << i << " " << glGetStringi( GL_EXTENSIONS, i ) << "\n";
}