#version 400

in vec3 LightIntensity;

out vec4 FragColor;

void main() {
	 FragColor = vec4(LightIntensity, 1.0);
//	FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
