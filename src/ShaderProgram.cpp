#include <iostream>

#include "ShaderProgram.h"

static float positionData[] = {
	-0.8f, -0.8f, 0.0f,
	0.8f, -0.8f, 0.0f,
	0.0f, 0.8f, 0.0f, };

static float colorData[] = {
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 
	0.1f, 0.0f, 0.0f};

static GLuint createShaderProgram(GLenum type);
static void compileShader(GLuint shader, const std::string& shader_code);
static void createGLProgram(GLuint programHandle, GLuint vertex, GLuint fragment);
static void initVAO(GLuint programHandle, GLuint& vaoHandle);


ShaderProgram::ShaderProgram(const std::string& vertex, const std::string& fragment)
{
	m_vertextProgram = createShaderProgram(GL_VERTEX_SHADER);
	m_fragmentProgram = createShaderProgram(GL_FRAGMENT_SHADER);
	compileShader(m_vertextProgram, vertex);
	compileShader(m_fragmentProgram, fragment);

	m_shaderProgram = glCreateProgram();
	if( 0 == m_shaderProgram )
	{
		std::cout << "Error creating program object.\n";
	}
	initVAO(m_shaderProgram, m_vaoHandle);

	linkProgram();
	glUseProgram(m_shaderProgram);

	glBindVertexArray(m_vaoHandle);
}

GLuint ShaderProgram::getShaderProgram()
{
	return m_shaderProgram;
}

void ShaderProgram::linkProgram()
{
	createGLProgram(m_shaderProgram, m_vertextProgram, m_fragmentProgram);
}

void ShaderProgram::SetMatrix( glm::mat4& matr, const std::string& name )
{
	GLuint location =glGetUniformLocation(m_shaderProgram, name.c_str());
	if( location >= 0 )
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, &matr[0][0]);
	}
}

void glew_init()
{
	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		std::cout << "Error initializing GLEW: " << glewGetErrorString(err) << "\n";
	}
}

GLuint createShaderProgram(GLenum type)
{
	GLuint vertShader = glCreateShader( type );
	if( 0 == vertShader )
	{
		std::cout << "Error creating vertex shader.\n";
		return 0; 
	}
	return vertShader;
}

void compileShader(GLuint shader, const std::string& shader_code)
{
	const GLchar* c_code = shader_code.c_str();
	glShaderSource( shader, 1, &c_code, NULL );

	glCompileShader( shader );
	GLint result;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &result );
	if( GL_FALSE == result )
	{
		std::cout << "Vertex shader compilation failed!\n";
		GLint logLen;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLen );
		if( logLen > 0 )
		{
			char * log = new char[logLen];
			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, log);
			std::cout << "Shader log: " << log << "\n";
			delete[] log;
		}
	}
}

void createGLProgram(GLuint programHandle, GLuint vertex, GLuint fragment)
{

	glAttachShader(programHandle, vertex);
	glAttachShader(programHandle, fragment);

	glLinkProgram(programHandle);

	GLint status;
	glGetProgramiv( programHandle, GL_LINK_STATUS, &status );
	if( GL_FALSE == status ) {
		std::cout << "Failed to link shader program!\n";
		GLint logLen;
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH,
			&logLen);
		if( logLen > 0 )
		{
			char * log = new char[logLen];
			GLsizei written;
			glGetProgramInfoLog(programHandle, logLen,
				&written, log);
			std::cout << "Program log: " << log << "\n";
			delete[] log;
		}
	}
}

std::string readShader(const std::string& path)
{
	std::ifstream t(path);
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	return str;
}

void initVAO(GLuint programHandle, GLuint& vaoHandle)
{

	static GLuint vboHandles[2];
	
	static GLuint positionBufferHandle = vboHandles[0];
	static GLuint colorBufferHandle = vboHandles[1];

	// Create and set-up the vertex array object
	glGenVertexArrays( 1, &vaoHandle );
	glBindVertexArray(vaoHandle);

	// Populate the position buffer
	glGenBuffers(1, &positionBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );
	glBindAttribLocation(programHandle, 0, "VertexPosition");

	// Populate the color buffer
	glGenBuffers(1, &colorBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData,	GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0,(GLubyte *)NULL );
	glBindAttribLocation(programHandle, 1, "VertexColor");
	

	glBindFragDataLocation(programHandle, 0, "FragColor");
}
