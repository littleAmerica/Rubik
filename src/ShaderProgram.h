#pragma once
#include "GL/glew.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <fstream>
#include <streambuf>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertex, const std::string& fragment);

	GLuint getShaderProgram();
	void linkProgram();
	
private:
	GLuint m_vaoHandle;
	GLuint m_shaderProgram;
	GLuint m_vertextProgram;
	GLuint m_fragmentProgram;
};

void initVAO(GLuint programHandle, GLuint& vaoHandle);
std::string readShader(const std::string& path);

void glew_init();