#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 uv;

uniform mat4 u_model_matrix = mat4(1.0);
uniform mat4 u_view_matrix  = mat4(1.0);
uniform mat4 u_proj_matrix  = mat4(1.0);

out vec4 o_color;
out vec2 o_tex_coords;

void main()
{
	gl_Position = u_proj_matrix * u_view_matrix * u_model_matrix *  vec4(position, 1.0);
	o_color = color;
	o_tex_coords = uv;
}