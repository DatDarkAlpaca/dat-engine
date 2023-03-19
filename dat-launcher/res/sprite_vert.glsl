#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_uvs;

out vec2 v_uvs;
out vec3 v_color;

uniform vec3 u_color = vec3(1.0);
uniform mat4 u_model = mat4(1.0);
uniform mat4 u_view = mat4(1.0);
uniform mat4 u_projection = mat4(1.0);

void main()
{
	v_uvs = a_uvs;
	v_color = u_color;
	gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
}
