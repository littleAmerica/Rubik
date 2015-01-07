#version 400
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;
uniform mat4 NormalMatrix;
uniform vec4 LightPos;

out float cosin;
out vec4 normal_eye;
out vec4 lightDir_eye;

void main()
{

	lightDir_eye = LightPos - ViewMatrix * vec4(VertexPosition, 1.0); 
	
	normal_eye = NormalMatrix * vec4(VertexNormal, 0.0);

 gl_Position =  MVP * vec4(VertexPosition, 1.0);
}					