#version 460
layout (local_size_x = 4, local_size_y = 4) in;
layout (binding=0, rgba32f) uniform image2D vertices;

struct transform4d 
{
	vec4 translate;
	vec4 scale;
	float[7] rotor;
};

uniform transform4d u_transform4d;

shared float dot;
shared float b1;
shared float b2;
shared float b3;
shared float b4;
shared float b5;
shared float b6;

vec4 _bivec_dot_vec4(vec4 pos)
{
	vec4 result;
	result.x = b1 * pos.y + b2 * pos.z + b3 * pos.w;
	result.y = -b1 * pos.x + b4 * pos.z + b5 * pos.w;
	result.z = -b2 * pos.x - b4 * pos.y + b6 * pos.w;
	result.w = -b3 * pos.x - b5 * pos.y - b6 * pos.z;
	return result;
}

//Returns a trivector disguised as a vec4
vec4 _bivec_wedge_vec4(vec4 pos)
{
	vec4 result;
	result.x = b1 * pos.z - b2 * pos.y + b4 * pos.x;
	result.y = b1 * pos.w - b3 * pos.y + b5 * pos.x;
	result.z = b2 * pos.w - b3 * pos.z + b6 * pos.x;
	result.w = b4 * pos.w - b5 * pos.z + b6 * pos.y;
	return result;
}

vec4 _trivec_dot_bivec(vec4 tri)
{
	vec4 result;
	result.x = -b4 * tri.x - b5 * tri.y - b6 * tri.z;
	result.y = b2 * tri.x + b3 * tri.y - b6 * tri.w;
	result.z = -b1 * tri.x + b3 * tri.z + b5 * tri.w;
	result.w = -b1 * tri.y - b2 * tri.z - b4 * tri.w;
	return result;
}

vec4 _vec4_rot_rotor(vec4 pos) 
{
	vec4 dot2_vec = dot * dot * pos;
	vec4 bdotv = _bivec_dot_vec4(pos);
	vec4 dot_2_vec = -2.0 * dot * bdotv;
	vec4 bdotvdotb = _bivec_dot_vec4(bdotv); //Negatives cancel
	vec4 tri = _bivec_wedge_vec4(pos);
	vec4 tridotb = -_trivec_dot_bivec(tri);
	return dot2_vec + dot_2_vec + bdotvdotb + tridotb;
}

bool equalf(float a, float b)
{
	const float eps = 0.0000005;
	float diff = abs(a - b);
	return diff < eps || diff < abs(a * eps) || diff < abs(b * eps);
}

vec4 point_between(vec4 a, vec4 b)
{
	float t = abs(a.w - u_slice) / abs(a.w - b.w);
	return a * (1.0 - t) + b * t;
}

void main() 
{
	//Set global variables
	if (gl_LocalInvocationIndex == 0)
	{
		dot = u_transform4d.rotor[0];
		b1 = u_transform4d.rotor[1];
		b2 = u_transform4d.rotor[2];
		b3 = u_transform4d.rotor[3];
		b4 = u_transform4d.rotor[4];
		b5 = u_transform4d.rotor[5];
		b6 = u_transform4d.rotor[6];
	}
	memoryBarrierShared();
	
	//Transform vertices
	vec4 pos = imageLoad(vertices, gl_GlobalInvocationID.xy);
	pos *= u_transform4d.scale;
	pos = _vec4_rot_rotor(pos);
	pos += u_transform4d.translate;
	imageStore(vertices, gl_GlobalInvocationID.xy, pos);
	pixel.x++;
}