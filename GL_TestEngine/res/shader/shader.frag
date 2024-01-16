#version 330 core
out vec4 FragColor;

in vec3 v_Color;
in vec2 v_TexCoord;

// texture sampler
uniform sampler2D u_Texture;

void main()
{
	FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}