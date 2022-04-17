#pragma once

struct ga_bivec3f 
{
	float yz;
	float zx;
	float xy;
};

ga_bivec3f ga_wedge_product(class ga_vec3f a, class ga_vec3f b);

