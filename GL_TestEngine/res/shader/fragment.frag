#version 330 core

layout(location = 1) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main() {
    vec4 texColor = texture(u_Texture, v_TexCoord) * v_Color;
    color = texColor;
}