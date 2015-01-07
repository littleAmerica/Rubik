#include "Triangle.h"

#include "GL/glew.h"
#include <GL/gl.h>
#include <GL/glu.h>

static float positionData[] = {
	-0.8f, -0.8f, 0.0f,
	0.8f, -0.8f, 0.0f,
	0.0f, 0.8f, 0.0f, };

static float colorData[] = {
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 
	0.1f, 0.0f, 0.0f};


Triangle::Triangle()
{
	static GLuint positionBufferHandle = 0;
	static GLuint colorBufferHandle = 0;

	// Create and set-up the vertex array object
	glGenVertexArrays( 1, &vaoHandle );
	glBindVertexArray(vaoHandle);

	// Populate the position buffer
	glGenBuffers(1, &positionBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)0 );	
	//shaderProgram.bindAttribLocation(0, "VertexPosition");
	//glBindAttribLocation(m_programHandle, 0, "VertexPosition");

	// Populate the color buffer
	glGenBuffers(1, &colorBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData,	GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0,(GLubyte *)0 );
	//shaderProgram.bindAttribLocation(1, );
	//glBindAttribLocation(m_programHandle, 1, "VertexColor");
}


void Triangle::render()
{
	glBindVertexArray(vaoHandle);
	glClearColor(0.8, 0.8, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3 );
}

Triangle::~Triangle()
{

}


