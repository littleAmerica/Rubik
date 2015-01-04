#pragma once
#include "GL/glew.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>

class ShaderProgram
{
public:
	enum GLSLShaderType {
		VERTEX, FRAGMENT
	};

	ShaderProgram();

	unsigned int getShaderProgram();

	void linkProgram();
	
	bool compileShaderFromString( const std::string & source, ShaderProgram::GLSLShaderType type );
	void use();

	//these two function should only be called before linking the program
	void bindAttribLocation( GLuint location, const char * name);
	void bindFragDataLocation( GLuint location, const char * name );

	void setUniform(const glm::mat4& matr, const std::string& name);
	void setUniform(const glm::mat3& matr, const std::string& name);
	void setUniform(const glm::vec2& vec, const std::string& name);
	void setUniform(const glm::vec3& vec, const std::string& name);
	void setUniform(const glm::vec4& vec, const std::string& name);
	void setUniform(float matr, const std::string& name);
	void setUniform(int matr, const std::string& name);
	void setUniform(bool matr, const std::string& name);

	static std::string readShader(const std::string& path);
private:
	unsigned int m_vaoHandle;
	unsigned int m_programHandle;
	unsigned int m_vertextProgram;
	unsigned int m_fragmentProgram;

	std::string m_fragment;
	std::string m_vertex;
};

void initVAO(unsigned int programHandle, unsigned int& vaoHandle);


void glew_init();