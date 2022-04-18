#pragma once
#include "ga_rotor4f.h"
#include "ga_vec4f.h"

struct ga_transform4d
{
	ga_vec4f _translate;
	ga_vec4f _scale;
	ga_rotor4f _rotation;
};

extern float w_slice;
