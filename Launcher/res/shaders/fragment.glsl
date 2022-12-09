#version 330

in vec4 o_color;
in vec2 o_tex_coords;

out vec4 color;

uniform sampler2D u_texture;

void main()
{
	vec4 tex_color = texture(u_texture, o_tex_coords);
	color = tex_color;
}