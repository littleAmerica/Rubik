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

static GLuint createShader(GLenum type);
static GLuint createShaderProgram();
static void compileShader(GLuint shader, const std::string& shader_code);
static void ComposeShaderProgram(GLuint programHandle, GLuint vertex, GLuint fragment);
static void initVAO(GLuint programHandle, GLuint& vaoHandle);


ShaderProgram::ShaderProgram(const std::string& vertex, const std::string& fragment):
	m_shaderProgram(0),
	m_vertextProgram(0),
	m_fragmentProgram(0),
	m_vaoHandle(0),
	m_vertex(vertex),
	m_fragment(fragment)
{	
	initVAO(m_shaderProgram, m_vaoHandle);
}

void ShaderProgram::GeneratePrograms()
{
	m_shaderProgram = createShaderProgram();
	m_vertextProgram = createShader(GL_VERTEX_SHADER);
	m_fragmentProgram = createShader(GL_FRAGMENT_SHADER);
}


ShaderProgram::ShaderProgram():
	m_shaderProgram(0),
	m_vertextProgram(0),
	m_fragmentProgram(0),
	m_vaoHandle(0),
	m_vertex(),
	m_fragment()
{
}


GLuint ShaderProgram::getShaderProgram()
{
	return m_shaderProgram;
}


void ShaderProgram::linkProgram()
{
	GeneratePrograms();

	initVAO(m_shaderProgram, m_vaoHandle);
	compileShader(m_vertextProgram, m_vertex);
	compileShader(m_fragmentProgram, m_fragment);

	ComposeShaderProgram(m_shaderProgram, m_vertextProgram, m_fragmentProgram);

	glUseProgram(m_shaderProgram);

	glBindVertexArray(m_vaoHandle);
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


GLuint createShader(GLenum type)
{
	GLuint vertShader = glCreateShader( type );
	if( 0 == vertShader )
	{
		std::cout << "Error creating vertex shader.\n";
		return 0; 
	}
	return vertShader;
}


GLuint createShaderProgram()
{
	GLuint shaderProgram = glCreateProgram();
	if( 0 == shaderProgram )
	{
		std::cout << "Error creating program object.\n";
		return 0;
	}
	return shaderProgram;
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


void ComposeShaderProgram(GLuint programHandle, GLuint vertex, GLuint fragment)
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


std::string ShaderProgram::readShader(const std::string& path)
{
	std::ifstream t(path);
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	return str;
}

void ShaderProgram::setShaders( const std::string& vertex, const std::string& fragment )
{
	m_vertex = vertex;
	m_fragment = fragment;
}

void ShaderProgram::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 3 );
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
