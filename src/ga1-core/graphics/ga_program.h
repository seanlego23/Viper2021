#pragma once

/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include <cstdint>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

/*
** Represents a shader uniform (constant).
** @see ga_shader
*/
class ga_uniform
{
	friend class ga_program;

public:
	void set(const float val);
	void set(const struct ga_vec3f& vec);
	void set(const struct ga_vec4f& vec);
	void set(const struct ga_rotor4f& vec);
	void set(const struct ga_mat4f& mat);
	void set(const struct ga_mat4f* mats, uint32_t count);
	void set(const class ga_texture& tex, uint32_t unit);

private:
	ga_uniform(int32_t location);

	const int32_t _location;
};

/*
** Represents a shader.
** @see ga_program
*/
class ga_shader
{
	friend class ga_program;

public:
	ga_shader(const char* source, GLenum type);
	~ga_shader();

	bool compile();

	std::string get_compile_log() const;

private:
	uint32_t _handle;
	const char* _source;
};

/*
** Represents a full shading pipeline.
** Vertex shader and fragment shader linked together.
** @see ga_shader
*/
class ga_program
{
public:
	ga_program();
	~ga_program();

	void attach(const ga_shader& shader);
	void detach(const ga_shader& shader);

	bool link();

	std::string get_link_log() const;

	ga_uniform get_uniform(const char* name);

	void use();

private:
	uint32_t _handle;
};
