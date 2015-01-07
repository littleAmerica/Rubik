#version 400

out vec4 FragColor;
in vec4 normal_eye;
in vec4 lightDir_eye;

void main() {
	float cosin = dot(normalize(normal_eye.rgb), normalize(lightDir_eye.rgb));

	cosin = max(0.0, cosin);

	FragColor = vec4(0.0, 1.0, 0.0, 1.0) * cosin;
	FragColor.a = 1.0;
}