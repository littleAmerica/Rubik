#version 400						
in vec3 Color;						
out vec4 gl_FragColor;				
void main() 
{						
	gl_FragColor = vec4(Color,1.0);	
}									