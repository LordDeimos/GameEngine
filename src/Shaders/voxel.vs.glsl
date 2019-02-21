#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in mat4 model;
layout (location = 5) in vec3 colour;

uniform mat4 transform;

out vec3 OutColor;

void main()
{
	OutColor = colour;
    gl_Position = transform * model * vec4(aPos, 1.0);
}