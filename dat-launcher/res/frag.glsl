#version 330 core
out vec4 v_out_color;

in vec3 v_colors;

void main()
{
	v_out_color = vec4(v_colors, 1.0);
}