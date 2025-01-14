/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_material.h"

#include "ga_animation.h"
#include "math/ga_transform4d.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

void load_shader(const char* filename, std::string& contents)
{
	extern char g_root_path[256];
	std::string fullpath = g_root_path;
	fullpath += filename;

	std::ifstream file(fullpath);

	assert(file.is_open());

	contents.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

ga_unlit_texture_material::ga_unlit_texture_material(const char* texture_file) :
	_texture_file(texture_file)
{
}

ga_unlit_texture_material::~ga_unlit_texture_material()
{
}

bool ga_unlit_texture_material::init()
{
	std::string source_vs;
	load_shader("data/shaders/ga_unlit_texture_vert.glsl", source_vs);

	std::string source_fs;
	load_shader("data/shaders/ga_unlit_texture_frag.glsl", source_fs);

	_vs = new ga_shader(source_vs.c_str(), GL_VERTEX_SHADER);
	if (!_vs->compile())
	{
		std::cerr << "Failed to compile vertex shader:" << std::endl << _vs->get_compile_log() << std::endl;
	}

	_fs = new ga_shader(source_fs.c_str(), GL_FRAGMENT_SHADER);
	if (!_fs->compile())
	{
		std::cerr << "Failed to compile fragment shader:\n\t" << std::endl << _fs->get_compile_log() << std::endl;
	}

	_program = new ga_program();
	_program->attach(*_vs);
	_program->attach(*_fs);
	if (!_program->link())
	{
		std::cerr << "Failed to link shader program:\n\t" << std::endl << _program->get_link_log() << std::endl;
	}

	_texture = new ga_texture();
	if (!_texture->load_from_file(_texture_file.c_str()))
	{
		std::cerr << "Failed to load rpi.png" << std::endl;
	}

	return true;
}

void ga_unlit_texture_material::bind(const ga_mat4f& view_proj, const ga_mat4f& transform)
{
	ga_uniform mvp_uniform = _program->get_uniform("u_mvp");
	ga_uniform texture_uniform = _program->get_uniform("u_texture");

	_program->use();

	mvp_uniform.set(transform * view_proj);
	texture_uniform.set(*_texture, 0);

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
}

ga_constant_color_material::ga_constant_color_material()
{
}

ga_constant_color_material::~ga_constant_color_material()
{
}

bool ga_constant_color_material::init()
{
	std::string source_vs;
	load_shader("data/shaders/ga_constant_color_vert.glsl", source_vs);

	std::string source_fs;
	load_shader("data/shaders/ga_constant_color_frag.glsl", source_fs);

	_vs = new ga_shader(source_vs.c_str(), GL_VERTEX_SHADER);
	if (!_vs->compile())
	{
		std::cerr << "Failed to compile vertex shader:" << std::endl << _vs->get_compile_log() << std::endl;
	}

	_fs = new ga_shader(source_fs.c_str(), GL_FRAGMENT_SHADER);
	if (!_fs->compile())
	{
		std::cerr << "Failed to compile fragment shader:\n\t" << std::endl << _fs->get_compile_log() << std::endl;
	}

	_program = new ga_program();
	_program->attach(*_vs);
	_program->attach(*_fs);
	if (!_program->link())
	{
		std::cerr << "Failed to link shader program:\n\t" << std::endl << _program->get_link_log() << std::endl;
	}

	return true;
}

void ga_constant_color_material::bind(const ga_mat4f& view_proj, const ga_mat4f& transform)
{
	ga_uniform mvp_uniform = _program->get_uniform("u_mvp");
	ga_uniform color_uniform = _program->get_uniform("u_color");

	_program->use();

	mvp_uniform.set(transform * view_proj);
	color_uniform.set(_color);

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
}

ga_animated_material::ga_animated_material(ga_skeleton* skeleton) : _skeleton(skeleton)
{
}

ga_animated_material::~ga_animated_material()
{
}

bool ga_animated_material::init()
{
	std::string source_vs;
	load_shader("data/shaders/ga_animated_vert.glsl", source_vs);

	std::string source_fs;
	load_shader("data/shaders/ga_animated_frag.glsl", source_fs);

	_vs = new ga_shader(source_vs.c_str(), GL_VERTEX_SHADER);
	if (!_vs->compile())
	{
		std::cerr << "Failed to compile vertex shader:" << std::endl << _vs->get_compile_log() << std::endl;
	}

	_fs = new ga_shader(source_fs.c_str(), GL_FRAGMENT_SHADER);
	if (!_fs->compile())
	{
		std::cerr << "Failed to compile fragment shader:\n\t" << std::endl << _fs->get_compile_log() << std::endl;
	}

	_program = new ga_program();
	_program->attach(*_vs);
	_program->attach(*_fs);
	if (!_program->link())
	{
		std::cerr << "Failed to link shader program:\n\t" << std::endl << _program->get_link_log() << std::endl;
	}

	return true;
}

void ga_animated_material::bind(const ga_mat4f& view_proj, const ga_mat4f& transform)
{
	ga_uniform mvp_uniform = _program->get_uniform("u_mvp");
	ga_uniform skin_uniform = _program->get_uniform("u_skin");

	_program->use();

	mvp_uniform.set(transform * view_proj);
	
	// Collect the skinning matrices.
	ga_mat4f skin[ga_skeleton::k_max_skeleton_joints];
	for (uint32_t i = 0; i < _skeleton->_joints.size(); ++i)
	{
		assert(i < ga_skeleton::k_max_skeleton_joints);
		skin[i] = _skeleton->_joints[i]->_skin;
	}
	skin_uniform.set(skin, ga_skeleton::k_max_skeleton_joints);

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
}

ga_4d_untextured_material::ga_4d_untextured_material(ga_transform4d* transform) 
{
	_transform = transform;
}

ga_4d_untextured_material::~ga_4d_untextured_material() 
{
	_vs ? delete _vs : (void*)0;
	_gs ? delete _gs : (void*)0;
	_fs ? delete _fs : (void*)0;
	_program ? delete _program : (void*)0;
}

bool ga_4d_untextured_material::init() 
{
	std::string source_vs;
	load_shader("data/shaders/ga_4d_untextured_vert.glsl", source_vs);

	std::string source_gs;
	load_shader("data/shaders/ga_4d_untextured_geo.glsl", source_gs);

	std::string source_fs;
	load_shader("data/shaders/ga_4d_untextured_frag.glsl", source_fs);

	_vs = new ga_shader(source_vs.c_str(), GL_VERTEX_SHADER);
	if (!_vs->compile()) 
	{
		std::cerr << "Failed to compile vertex shader:" << std::endl << _vs->get_compile_log() << std::endl;
	}

	_gs = new ga_shader(source_gs.c_str(), GL_GEOMETRY_SHADER);
	if (!_gs->compile()) 
	{
		std::cerr << "Failed to compile geometry shader:" << std::endl << _gs->get_compile_log() << std::endl;
	}

	_fs = new ga_shader(source_fs.c_str(), GL_FRAGMENT_SHADER);
	if (!_fs->compile()) 
	{
		std::cerr << "Failed to compile fragment shader:\n\t" << std::endl << _fs->get_compile_log() << std::endl;
	}

	_program = new ga_program();
	_program->attach(*_vs);
	_program->attach(*_gs);
	_program->attach(*_fs);
	if (!_program->link()) 
	{
		std::cerr << "Failed to link shader program:\n\t" << std::endl << _program->get_link_log() << std::endl;
	}

	return true;
}

void ga_4d_untextured_material::bind(const ga_mat4f & view_proj, const ga_mat4f & transform) 
{
	ga_uniform mvp_uniform = _program->get_uniform("u_mvp");
	ga_uniform translate4d_uniform = _program->get_uniform("u_transform4d.translate");
	ga_uniform scale4d_uniform = _program->get_uniform("u_transform4d.scale");
	ga_uniform rotor4d_uniform = _program->get_uniform("u_transform4d.rotor");
	ga_uniform slice_uniform = _program->get_uniform("u_slice");

	_program->use();

	mvp_uniform.set(transform * view_proj);
	translate4d_uniform.set(_transform->_translate);
	scale4d_uniform.set(_transform->_scale);
	rotor4d_uniform.set(_transform->_rotation);
	slice_uniform.set(w_slice);

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
}
