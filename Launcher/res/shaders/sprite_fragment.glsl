#version 330
in vec2 textureCoords;

out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{
	color = vec4(spriteColor, 1.0) * texture(image, textureCoords);
}