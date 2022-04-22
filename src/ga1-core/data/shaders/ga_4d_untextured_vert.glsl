#version 460

layout(location = 0) in vec4 in_vertex;
layout(location = 1) in vec3 in_color;

out vec3 o_color;

void main() 
{
	gl_Position = in_vertex;
	o_color = in_color;
}
