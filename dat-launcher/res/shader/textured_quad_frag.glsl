#version 330 core
out vec4 out_color;
in vec2 v_uvs;

uniform vec4 u_color = vec4(1.0);
uniform sampler2D u_texture;

void main()
{
	out_color = texture(u_texture, v_uvs) * u_color;
}