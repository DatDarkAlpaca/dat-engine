#version 330 core
out vec4 out_color;

uniform vec3 u_color = vec3(1.0);

void main()
{
	out_color = vec4(u_color, 1.0);
}