#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec3 v_FragPos;
out vec3 v_Color;
out vec2 v_TexCoord;
out vec3 v_Normal;

uniform mat4 u_CameraProjection;
uniform mat4 u_CameraView;
uniform mat4 u_ObjectTransform;

void main()
{
	gl_Position = (u_CameraProjection * u_CameraView * u_ObjectTransform) * vec4(pos, 1);

	v_FragPos = vec3(u_ObjectTransform * vec4(pos, 1.0));
	v_TexCoord = texCoord;
	v_Normal = normal;
}