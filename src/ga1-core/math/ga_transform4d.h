#pragma once
#include "graphics/ga_program.h"
#include "ga_rotor4f.h"
#include "ga_vec4f.h"

struct ga_transform4d
{
	ga_vec4f _translate;
	ga_vec4f _scale;
	ga_rotor4f _rotation;
};

extern float w_slice;

class ga_transform4d_program 
{
public:

	ga_transform4d_program();
	~ga_transform4d_program();

	bool init();
	
	void use();

private:
	ga_program* _program = nullptr;
	ga_shader* _cs = nullptr;
};

extern ga_transform4d_program transform4d_program;