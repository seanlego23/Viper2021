#pragma once

/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_program.h"
#include "ga_texture.h"

#include "math/ga_mat4f.h"
#include "math/ga_vec3f.h"

#include <string>

void load_shader(const char* filename, std::string& contents);

/*
** Base class for all graphical materials.
** Includes the shaders and other state necessary to draw geometry.
*/
class ga_material
{
public:
	virtual bool init() = 0;

	virtual void bind(const ga_mat4f& view_proj, const ga_mat4f& transform) = 0;

	virtual void set_color(const ga_vec3f& color) {}
};

/*
** Simple unlit, single textured material.
*/
class ga_unlit_texture_material : public ga_material
{
public:
	ga_unlit_texture_material(const char* texture_file);
	~ga_unlit_texture_material();

	virtual bool init() override;

	virtual void bind(const ga_mat4f& view_proj, const ga_mat4f& transform) override;

private:
	std::string _texture_file;

	ga_shader* _vs;
	ga_shader* _fs;
	ga_program* _program;
	ga_texture* _texture;
};

/*
** Simple untextured material with a constant color.
*/
class ga_constant_color_material : public ga_material
{
public:
	ga_constant_color_material();
	~ga_constant_color_material();

	virtual bool init() override;

	virtual void bind(const ga_mat4f& view_proj, const ga_mat4f& transform) override;

	virtual void set_color(const ga_vec3f& color) override { _color = color; }

private:
	ga_shader* _vs;
	ga_shader* _fs;
	ga_program* _program;
	ga_vec3f _color;
};

/*
** A material which supports vertex animation.
*/
class ga_animated_material : public ga_material
{
public:
	ga_animated_material(struct ga_skeleton* skeleton);
	~ga_animated_material();

	virtual bool init() override;
	virtual void bind(const ga_mat4f& view_proj, const ga_mat4f& transform) override;

private:
	ga_shader* _vs;
	ga_shader* _fs;
	ga_program* _program;

	struct ga_skeleton* _skeleton;
};

/*
** Simple 4d untextured material
*/
class ga_4d_untextured_material : public ga_material {
public:
	ga_4d_untextured_material(class ga_transform4d* transform);
	~ga_4d_untextured_material();

	virtual bool init() override;

	virtual void bind(const ga_mat4f& view_proj, const ga_mat4f& transform) override;

	virtual void set_color(const ga_vec3f& color) override {}

private:
	ga_shader* _vs;
	ga_shader* _gs;
	ga_shader* _fs;
	ga_program* _program;
	class ga_transform4d* _transform;
};