#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec3 v_Color;
out vec2 v_TexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	v_Color = vec3(0.5, 1.0, 1.0);
	v_TexCoord = aTexCoord;
}