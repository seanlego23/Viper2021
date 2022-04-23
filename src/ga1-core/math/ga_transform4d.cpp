#include <iostream>

#include "graphics/ga_material.h"
#include "ga_transform4d.h"

float w_slice = 1.0f;

ga_transform4d_program::ga_transform4d_program()
{
}

ga_transform4d_program::~ga_transform4d_program() 
{
	if (_program) 
	{
		_cs->~ga_shader();
		_program->~ga_program();
		delete _cs;
		delete _program;
	}
}

bool ga_transform4d_program::init(const char* shader_loc) 
{
	std::string source_cs;
	load_shader(shader_loc, source_cs);

	_cs = new ga_shader(source_cs.c_str(), GL_COMPUTE_SHADER);
	if (!_cs->compile()) {
		std::cerr << "Failed to compile compute shader:" << std::endl << _cs->get_compile_log() << std::endl;
	}

	_program = new ga_program();
	_program->attach(*_cs);
	if (!_program->link()) {
		std::cerr << "Failed to link compute shader program:\n\t" << std::endl << _program->get_link_log() << std::endl;
	}

	return true;
}

ga_uniform ga_transform4d_program::get_uniform(const char* name) {
	return _program->get_uniform(loc);
}

void ga_transform4d_program::use() 
{
	_program->use();
}
