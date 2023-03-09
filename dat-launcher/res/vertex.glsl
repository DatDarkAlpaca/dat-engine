#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_colors;

out vec3 v_colors;

void main()
{
	v_colors = a_colors;
	gl_Position = vec4(a_position, 1.0);
}