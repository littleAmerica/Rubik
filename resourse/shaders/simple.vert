#version 400
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 LightIntensity;


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

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;
uniform mat4 NormalMatrix;

void main()
{
	vec4 eyeCoord = ViewMatrix * ModelMatrix * vec4(VertexPosition, 1.0);  

	vec4 lightDir_eye = vec4(light.Position, 1.0) - ViewMatrix * vec4(VertexPosition, 1.0); 
	
	vec4 normal_eye = normalize(NormalMatrix * vec4(VertexNormal, 0.0));

	float cosin = dot(normal_eye.rgb, normalize(lightDir_eye.rgb));

	cosin = max(0.0, cosin);

	vec3 s = normalize(light.Position - eyeCoord.rgb);
	vec3 v = normalize(-eyeCoord.xyz + light.Position);
	vec3 r = reflect(-s, normal_eye.rgb); 

	float sDotN = max(dot(s, normal_eye.rgb), 0.0);
	vec3 spec = vec3(0.0);
	if (sDotN > 0.0)
		spec = light.Ls * material.Ks * pow (max(dot(r,v), 0.0), material.Shininess);
	
	
	LightIntensity = spec + material.Kd * light.Ld * cosin;
	gl_Position =  MVP * vec4(VertexPosition, 1.0);
}					