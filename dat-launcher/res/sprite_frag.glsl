#version 330 core
out vec4 out_color;

in vec2 v_uvs;
in vec3 v_color;

uniform sampler2D u_texture;

void main()
{
	out_color = texture(u_texture, v_uvs) * vec4(v_color, 1.0);
}
