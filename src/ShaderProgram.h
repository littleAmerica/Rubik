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
	ShaderProgram();

	unsigned int getShaderProgram();
	void GeneratePrograms();
	void linkProgram();
	
	void SetMatrix(glm::mat4& matr, const std::string& name);

	void setShaders(const std::string& vertex, const std::string& fragment);

	static std::string readShader(const std::string& path);

	void draw();

private:
	unsigned int m_vaoHandle;
	unsigned int m_shaderProgram;
	unsigned int m_vertextProgram;
	unsigned int m_fragmentProgram;

	std::string m_fragment;
	std::string m_vertex;
};

void initVAO(unsigned int programHandle, unsigned int& vaoHandle);


void glew_init();