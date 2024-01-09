#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec3 v_Color;
out vec2 v_TexCoord;

uniform mat4 u_CameraMatrix;

void main()
{
	gl_Position = u_CameraMatrix * vec4(aPos, 1.0);
	v_Color = vec3(1.0, 1.0, 1.0);
	v_TexCoord = aTexCoord;
}