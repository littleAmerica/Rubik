#include <iostream>
#include <fstream>
#include <streambuf>

#include "GL/glew.h"
#include <GL/gl.h>
#include <GL/glu.h>


#include "ShaderProgram.h"


ShaderProgram::ShaderProgram():
	m_programHandle(0),
	m_vertextProgram(0),
	m_fragmentProgram(0),
	m_vaoHandle(0),
	m_vertex(),
	m_fragment()
{
}


GLuint ShaderProgram::getShaderProgram()
{
	return m_programHandle;
}


void ShaderProgram::linkProgram()
{
	glLinkProgram(m_programHandle);

	GLint status;
	glGetProgramiv( m_programHandle, GL_LINK_STATUS, &status );
	if( GL_FALSE == status ) {
		std::cout << "Failed to link shader program!\n";
		GLint logLen;
		glGetProgramiv(m_programHandle, GL_INFO_LOG_LENGTH,
			&logLen);
		if( logLen > 0 )
		{
			char * log = new char[logLen];
			GLsizei written;
			glGetProgramInfoLog(m_programHandle, logLen,
				&written, log);
			std::cout << "Program log: " << log << "\n";
			delete[] log;
		}
	}
}

void ShaderProgram::use()
{
	if( m_programHandle <= 0 || (! m_programHandle) ) return;
		glUseProgram( m_programHandle );
}


void ShaderProgram::setUniform(const glm::mat4& matr, const std::string& name )
{
	GLuint location =glGetUniformLocation(m_programHandle, name.c_str());
	if( location >= 0 )
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, &matr[0][0]);
	}
}

void ShaderProgram::setUniform( const glm::mat3& matr, const std::string& name )
{
	throw std::exception("Not implemented");
}

void ShaderProgram::setUniform( const glm::vec2& vec, const std::string& name )
{
	throw std::exception("Not implemented");
}

void ShaderProgram::setUniform( const glm::vec3& vec, const std::string& name )
{
	GLuint location =glGetUniformLocation(m_programHandle, name.c_str());
	if( location >= 0 )
	{
		glUniform3f(location, vec[0], vec[1], vec[2]);
	}
}

void ShaderProgram::setUniform( const glm::vec4& vec, const std::string& name )
{
	GLuint location =glGetUniformLocation(m_programHandle, name.c_str());
	if( location >= 0 )
	{
		glUniform4f(location, vec[0], vec[1], vec[2], vec[3]);
	}
}

void ShaderProgram::setUniform( float matr, const std::string& name )
{
	throw std::exception("Not implemented");
}

void ShaderProgram::setUniform( int matr, const std::string& name )
{
	throw std::exception("Not implemented");
}

void ShaderProgram::setUniform( bool matr, const std::string& name )
{
	throw std::exception("Not implemented");
}


void glew_init()
{
	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		std::cout << "Error initializing GLEW: " << glewGetErrorString(err) << "\n";
	}
}


std::string ShaderProgram::readShader(const std::string& path)
{
	std::ifstream t(path);
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	return str;
}


void ShaderProgram::bindAttribLocation( GLuint location, const char * name)
{
	glBindAttribLocation(m_programHandle, location, name);
}


void ShaderProgram::bindFragDataLocation( GLuint location, const char * name )
{
	glBindFragDataLocation(m_programHandle, location, name);
}


bool ShaderProgram::compileShaderFromString( const std::string & source, ShaderProgram::GLSLShaderType type )
{
	if( m_programHandle <= 0 ) {
		m_programHandle = glCreateProgram();
		if( m_programHandle == 0) {
			std::cout << "Unable to create shader program.";
			return false;
		}
	}

	GLuint shaderHandle = 0;

	switch( type ) {
	case ShaderProgram::VERTEX:
		shaderHandle = glCreateShader(GL_VERTEX_SHADER);
		break;
	case ShaderProgram::FRAGMENT:
		shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		return false;
	}

	const char * c_code = source.c_str();
	glShaderSource( shaderHandle, 1, &c_code, NULL );

	// Compile the shader
	glCompileShader(shaderHandle );

	// Check for errors
	int result;
	glGetShaderiv( shaderHandle, GL_COMPILE_STATUS, &result );
	if( GL_FALSE == result )
	{
		std::cout << "Shader compilation failed!\n";
		GLint logLen;
		glGetShaderiv( shaderHandle, GL_INFO_LOG_LENGTH, &logLen );
		if( logLen > 0 )
		{
			char * log = new char[logLen];
			GLsizei written;
			glGetShaderInfoLog(shaderHandle, logLen, &written, log);
			std::cout << "Shader log: " << log << "\n";
			delete[] log;
		}
	} else {
		// Compile succeeded, attach shader and return true
		glAttachShader(m_programHandle, shaderHandle);
		return true;
	}
}