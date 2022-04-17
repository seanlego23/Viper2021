#pragma once
#include "ga_rotor4f.h"
#include "ga_vec4f.h"

class ga_transform4d
{
public:

	ga_transform4d();
	~ga_transform4d();

private:

	ga_vec4f _translate;
	ga_vec4f _scale;
	ga_rotor4f _rotation;
};

