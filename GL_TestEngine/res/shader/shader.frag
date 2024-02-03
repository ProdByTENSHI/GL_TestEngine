#version 330 core
out vec4 FragColor;

in vec3 v_FragPos;
in vec3 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normal;

uniform sampler2D u_Texture;

uniform vec3 u_CameraPosition;

// Light
uniform vec3 u_AmbientColor;
uniform float u_AmbientIntensity;

uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;
uniform float u_LightIntensity;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material u_Material;

void main()
{
	// Ambient Light
	vec3 normalizedNormal = normalize(v_Normal);
	vec3 lightDirection = normalize(u_LightPosition - v_FragPos);
	vec3 ambientColor = u_AmbientColor * u_AmbientIntensity * u_Material.ambient;

	// Diffuse Light
	float diffuseFactor = max(dot(normalizedNormal, lightDirection), 0.0);
	vec3 diffuseColor = diffuseFactor * u_Material.diffuse * u_LightColor;

	// Specular light
	vec3 viewDirection = normalize(u_CameraPosition - v_FragPos);
	vec3 reflectDirection = reflect(-lightDirection, normalizedNormal);
	
	float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
	vec3 specularColor = u_Material.specular * specularFactor * u_LightColor;

	FragColor = texture(u_Texture, v_TexCoord) * (vec4(ambientColor, 1.0)) + (vec4(diffuseColor, 1.0) * u_LightIntensity) + (vec4(specularColor, 1.0));
}