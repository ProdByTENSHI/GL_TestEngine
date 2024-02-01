#version 330 core
out vec4 FragColor;

in vec3 v_Color;
in vec2 v_TexCoord;

// texture sampler
uniform sampler2D u_Texture;

// Light
uniform vec4 u_AmbientColor;
uniform float u_AmbientIntensity;

struct Material {
	float ambient;
	float diffuse;
	float specular;
	float shininess;
};

uniform Material u_Material;

void main()
{
	FragColor = texture(u_Texture, v_TexCoord) * (u_AmbientColor * u_AmbientIntensity * u_Material.ambient);
}