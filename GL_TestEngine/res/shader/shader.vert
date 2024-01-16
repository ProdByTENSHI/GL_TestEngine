#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec3 v_Color;
out vec2 v_TexCoord;

uniform mat4 u_ObjectTransform;
uniform mat4 u_CameraMatrix;
uniform vec3 u_Diffuse;

void main()
{
	gl_Position = (u_CameraMatrix * u_ObjectTransform) * vec4(pos, 1.0);
	v_Color  = u_Diffuse;
	v_TexCoord = texCoord;
}