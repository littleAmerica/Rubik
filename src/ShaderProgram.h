#pragma once
#include "GL/glew.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <streambuf>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertex, const std::string& fragment);

	GLuint getShaderProgram();
	void linkProgram();
	
	void SetMatrix(glm::mat4& matr, const std::string& name);

private:
	GLuint m_vaoHandle;
	GLuint m_shaderProgram;
	GLuint m_vertextProgram;
	GLuint m_fragmentProgram;
};

void initVAO(GLuint programHandle, GLuint& vaoHandle);
std::string readShader(const std::string& path);

void glew_init();