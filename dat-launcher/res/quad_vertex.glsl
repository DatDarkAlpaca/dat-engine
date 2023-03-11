#version 330 core
layout (location = 0) in vec3 a_position;

uniform mat4 u_model = mat4(1.0);
uniform mat4 u_projection = mat4(1.0);

void main()
{
	gl_Position = u_projection * u_model * vec4(a_position, 1.0);
}