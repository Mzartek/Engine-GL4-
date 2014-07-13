#version 330

uniform mat4 MVP;

layout(location = 0) in vec3 vertexArray;
layout(location = 1) in vec2 textureArray;

out vec2 outTexCoord;

void main(void)
{
	gl_Position = MVP * vec4(vertexArray, 1.0);
	outTexCoord = textureArray;
}