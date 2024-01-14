#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec3 v_Color;
out vec2 v_TexCoord;

uniform vec3 u_ObjectPosition;
uniform mat4 u_CameraMatrix;

void main()
{
	gl_Position = (u_CameraMatrix * vec4(u_ObjectPosition, 1.0)) * vec4(pos, 1.0);
	v_Color = vec3(1.0, 1.0, 1.0);
	v_TexCoord = texCoord;
}