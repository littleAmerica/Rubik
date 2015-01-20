#version 400

out vec4 FragColor;


in vec3 Position;
in vec3 Normal;


struct MaterialInfo
{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
};

struct LightInfo
{
	vec3 Position;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
};

uniform LightInfo light;
uniform MaterialInfo material;


void main() 
{
	vec3 n = normalize(Normal);
	vec3 s = normalize(vec3( light.Position.xyz - Position));
	vec3 v = normalize(-light.Position.xyz);
	vec3 r = reflect(-s, n); 

	float ambient = material.Ka * light.La;
	float diffuse = material.Kd * light.Ld * max(0.0, dot(s, n));
	float spec = material.Ks * light.Ls * pow( max(0.0, dot(r, v)), material.Shininess);

	float lightKoef = ambient + diffuse + spec;

	FragColor =  vec4(vec3(0.8, 0.8, 0.8) * lightKoef, 1.0) ;
}