#version 330 core
out vec4 FragColor;

in vec3 v_FragPos;
in vec3 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normal;

// texture sampler
uniform sampler2D u_Texture;

// Light
uniform vec3 u_AmbientColor;
uniform float u_AmbientIntensity;

uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;
uniform float u_LightIntensity;

struct Material {
	float ambient;
	float diffuse;
	float specular;
	float shininess;
};

uniform Material u_Material;

void main()
{
	vec3 normalizedNormal = normalize(v_Normal);
	vec3 lightDirection = normalize(u_LightPosition - v_FragPos);

	float diffuseFactor = max(dot(normalizedNormal, lightDirection), 0.0);
	vec3 diffuseColor = diffuseFactor * u_LightColor;

	FragColor = texture(u_Texture, v_TexCoord) * (vec4(u_AmbientColor, 1.0) * u_AmbientIntensity * u_Material.ambient) + (vec4(diffuseColor, 1.0) * u_LightIntensity * u_Material.diffuse);
}