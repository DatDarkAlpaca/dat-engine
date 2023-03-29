#version 330 core
out vec4 out_color;

in vec4 v_color;
in vec2 v_uvs;

uniform sampler2D u_texture;

void main()
{
	out_color = texture(u_texture, v_uvs) * v_color;
}