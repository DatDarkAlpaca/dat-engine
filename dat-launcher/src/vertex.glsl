#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_tex_coords;

out vec2 var_tex_coord;

void main()
{
	gl_Position = vec4(a_position, 1.0);

	var_tex_coord = a_tex_coords;
}