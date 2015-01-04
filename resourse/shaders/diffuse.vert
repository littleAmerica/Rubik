#version 400

in vec3 VertexPosition;
in vec3 VertexNormal;

out vec3 LightIntensity;

uniform vec4 LightPosition; // Light position in eye coords.

uniform mat4 MVP;
uniform vec4 CameraPosition;

void main()
{

	LightIntensity = vec3(1.0);	

    gl_Position = MVP * vec4(VertexPosition,1.0);
}
