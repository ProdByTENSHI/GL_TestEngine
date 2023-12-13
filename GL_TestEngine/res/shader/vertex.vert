#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoords;

out vec4 v_Color;
out vec2 v_TexCoord;

uniform mat4 u_CamMatrix;

void main() {
	gl_Position = u_CamMatrix * vec4(position, 1.0);
	v_TexCoord = texCoords;
}