#version 460
layout (local_size_x = 2, local_size_y = 16) in;
layout (binding=0, rgba32f) uniform image2D vertices;
layout (binding=1, r32ui) uniform image2D edges;
layout (binding=2, rgba32f) uniform write_only image2D vert3d;

uniform float u_slice;

void main()
{
	ivec2 vert_size = imageSize(vertices);
	int max_x = vert_size.x;
	int max_y = vert_size.y;
	
	vec4 v1 = imageLoad(edges, gl_GlobalInvocationID.xy);
}