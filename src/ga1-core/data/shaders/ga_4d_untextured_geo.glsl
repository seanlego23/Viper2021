#version 400
layout (triangles) in;
layout (triangles, max_vertices = 3) out;

struct transform4d 
{
	vec4 translate;
	vec4 scale;
	float[7] rotor;
};

uniform mat4 u_mvp;
uniform transform4d u_transform4d;

uniform float u_slice;

in vec3 o_color[];

out vec3 fcolor;

float dot;
float b1;
float b2;
float b3;
float b4;
float b5;
float b6;

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
	dot = u_transform4d.rotor[0];
	b1 = u_transform4d.rotor[1];
	b2 = u_transform4d.rotor[2];
	b3 = u_transform4d.rotor[3];
	b4 = u_transform4d.rotor[4];
	b5 = u_transform4d.rotor[5];
	b6 = u_transform4d.rotor[6];
	
	//Transform triangles
	vec4[3] positions;
	for (int i = 0; i < 3; i++) 
	{
		vec4 pos = gl_in[i].gl_Position;
		pos *= u_transform4d.scale;
		pos = _vec4_rot_rotor(pos);
		pos += u_transform4d.translate;
		positions[i] = pos;
	}
	
	//Slice 4th dimension
	//Find new triangle vertices if any
	bool first = equalf(positions[0].w, u_slice);
	bool second = equalf(positions[1].w, u_slice);
	bool third = equalf(positions[2].w, u_slice);
	
	bool two = ((first && second) || (first && third) || (second && third)) && !(first && second && third);
	
	if (!two) //If only two vertices are visible, then a line is useless
	{
		bool between = !(first && second && third);
		vec4 pos1 = between ? vec4(positions[0].xyz, 1.0) : vec4(point_between(positions[0], positions[1]).xyz, 1.0);
		vec4 pos2 = between ? vec4(positions[1].xyz, 1.0) : vec4(point_between(positions[1], positions[2]).xyz, 1.0);
		vec4 pos3 = between ? vec4(positions[2].xyz, 1.0) : vec4(point_between(positions[2], positions[0]).xyz, 1.0);
		
		fcolor = o_color[0];
		gl_Position = u_mvp * pos1;
		EmitVertex();
		gl_Position = u_mvp * pos2;
		EmitVertex();
		gl_Position = u_mvp * pos3;
		EmitVertex();
		EndPrimitive();
	}
}