#include "ga_material.h"
#include "ga_tesseract_component.h"

#include "entity/ga_entity.h"

static GLfloat vertices[] = {
	//Fix 2 axis, create a square with the other two

	//Fix x = -1, y = -1
	-1.0f, -1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,  1.0f,

	//Fix x = 1, y = -1
	 1.0f, -1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,  1.0f,

	//Fix x = -1, y = 1
	-1.0f,  1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,  1.0f,

	//Fix x = 1, y = 1
	 1.0f,  1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,  1.0f,

	//Fix x = -1, z = -1
	-1.0f, -1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,  1.0f,

	//Fix x = 1, z = -1
	 1.0f, -1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,  1.0f,

	//Fix x = -1, z = 1
	-1.0f, -1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,  1.0f,

	//Fix x = 1, z = 1
	 1.0f, -1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,  1.0f,

	//Fix x = -1, w = -1
	-1.0f, -1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f, -1.0f,

	//Fix x = 1, w = -1
	 1.0f, -1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f, -1.0f,

	//Fix x = -1, w = 1
	-1.0f, -1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,  1.0f,

	//Fix x = 1, w = 1
	 1.0f, -1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,  1.0f,

	//Fix y = -1, z = -1
	-1.0f, -1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,  1.0f,

	//Fix y = 1, z = -1
	-1.0f,  1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,  1.0f,

	//Fix y = -1, z = 1
	-1.0f, -1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,  1.0f,

	//Fix y = 1, z = 1
	-1.0f,  1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,  1.0f,

	//Fix y = -1, w = -1
	-1.0f, -1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f, -1.0f,

	//Fix y = 1, w = -1
	-1.0f,  1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f, -1.0f,

	//Fix y = -1, w = 1
	-1.0f, -1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,  1.0f,

	//Fix y = 1, w = 1,
	-1.0f,  1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,  1.0f,

	//Fix z = -1, w = -1
	-1.0f, -1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f, -1.0f,

	//Fix z = 1, w = -1
	-1.0f, -1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f, -1.0f,

	//Fix z = -1, w = 1
	-1.0f, -1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,  1.0f,

	//Fix z = 1, w = 1
	-1.0f, -1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,  1.0f,
};

static GLfloat color[] = {
	//Fix x = -1, y = -1
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	//Fix x = 1, y = -1
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,

	//Fix x = -1, y = 1
	0.0f, 0.92f, 1.0f,
	0.0f, 0.92f, 1.0f,
	0.0f, 0.92f, 1.0f,
	0.0f, 0.92f, 1.0f,

	//Fix x = 1, y = 1
	0.67f, 0.0f, 1.0f,
	0.67f, 0.0f, 1.0f,
	0.67f, 0.0f, 1.0f,
	0.67f, 0.0f, 1.0f,

	//Fix x = -1, z = -1
	1.0f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.0f,

	//Fix x = 1, z = -1
	0.75f, 1.0f, 0.0f,
	0.75f, 1.0f, 0.0f,
	0.75f, 1.0f, 0.0f,
	0.75f, 1.0f, 0.0f,

	//Fix x = -1, z = 1
	0.0f, 0.58f, 1.0f,
	0.0f, 0.58f, 1.0f,
	0.0f, 0.58f, 1.0f,
	0.0f, 0.58f, 1.0f,

	//Fix x = 1, z = 1
	1.0f, 0.0f, 0.67f,
	1.0f, 0.0f, 0.67f,
	1.0f, 0.0f, 0.67f,
	1.0f, 0.0f, 0.67f,

	//Fix x = -1, w = -1
	1.0f, 0.83f, 0.0f,
	1.0f, 0.83f, 0.0f,
	1.0f, 0.83f, 0.0f,
	1.0f, 0.83f, 0.0f,

	//Fix x = 1, w = -1
	0.42f, 1.0f, 0.0f,
	0.42f, 1.0f, 0.0f,
	0.42f, 1.0f, 0.0f,
	0.42f, 1.0f, 0.0f,

	//Fix x = -1, w = 1
	0.0f, 0.25f, 1.0f,
	0.0f, 0.25f, 1.0f,
	0.0f, 0.25f, 1.0f,
	0.0f, 0.25f, 1.0f,

	//Fix x = 1, w = 1
	0.92f, 0.73f, 0.73f,
	0.92f, 0.73f, 0.73f,
	0.92f, 0.73f, 0.73f,
	0.92f, 0.73f, 0.73f,

	//Fix y = -1, z = -1
	0.73f, 0.84f, 0.93f,
	0.73f, 0.84f, 0.93f,
	0.73f, 0.84f, 0.93f,
	0.73f, 0.84f, 0.93f,

	//Fix y = 1, z = -1
	0.91f, 0.91f, 0.73f,
	0.91f, 0.91f, 0.73f,
	0.91f, 0.91f, 0.73f,
	0.91f, 0.91f, 0.73f,

	//Fix y = -1, z = 1
	0.86f, 0.73f, 0.93f,
	0.86f, 0.73f, 0.93f,
	0.86f, 0.73f, 0.93f,
	0.86f, 0.73f, 0.93f,

	//Fix y = 1, z = 1
	0.73f, 0.93f, 0.88f,
	0.73f, 0.93f, 0.88f,
	0.73f, 0.93f, 0.88f,
	0.73f, 0.93f, 0.88f,

	//Fix y = -1, w = -1
	0.56f, 0.14f, 0.14f,
	0.56f, 0.14f, 0.14f,
	0.56f, 0.14f, 0.14f,
	0.56f, 0.14f, 0.14f,

	//Fix y = 1, w = -1
	0.14f, 0.38f, 0.56f,
	0.14f, 0.38f, 0.56f,
	0.14f, 0.38f, 0.56f,
	0.14f, 0.38f, 0.56f,

	//Fix y = -1, w = 1
	0.56f, 0.42f, 0.14f,
	0.56f, 0.42f, 0.14f,
	0.56f, 0.42f, 0.14f,
	0.56f, 0.42f, 0.14f,

	//Fix y = 1, w = 1
	0.42f, 0.14f, 0.56f,
	0.42f, 0.14f, 0.56f,
	0.42f, 0.14f, 0.56f,
	0.42f, 0.14f, 0.56f,

	//Fix z = -1, w = -1
	0.31f, 0.56f, 0.14f,
	0.31f, 0.56f, 0.14f,
	0.31f, 0.56f, 0.14f,
	0.31f, 0.56f, 0.14f,

	//Fix z = 1, w = -1
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,

	//Fix z = -1, w = 1
	0.45f, 0.45f, 0.45f,
	0.45f, 0.45f, 0.45f,
	0.45f, 0.45f, 0.45f,
	0.45f, 0.45f, 0.45f,

	//Fix z = 1, w = 1
	0.8f, 0.8f, 0.8f,
	0.8f, 0.8f, 0.8f,
	0.8f, 0.8f, 0.8f,
	0.8f, 0.8f, 0.8f,
};

static GLfloat texcoords[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
};

static GLushort indices[] = {
	0, 1, 2,
	2, 3, 0,

	4, 5, 6,
	6, 7, 4,

	8, 9, 10,
	10, 11, 8,

	12, 13, 14,
	14, 15, 12,

	16, 17, 18,
	18, 19, 16,

	20, 21, 22,
	22, 23, 20,

	24, 25, 26,
	26, 27, 24,

	28, 29, 30,
	30, 31, 28,

	32, 33, 34,
	34, 35, 32,

	36, 37, 38,
	38, 39, 36,

	40, 41, 42,
	42, 43, 40,

	44, 45, 46,
	46, 47, 44,

	48, 49, 50,
	50, 51, 48,

	52, 53, 54,
	54, 55, 52,

	56, 57, 58,
	58, 59, 56,

	60, 61, 62,
	62, 63, 60,

	64, 65, 66,
	66, 67, 64,

	68, 69, 70,
	70, 71, 68,

	72, 73, 74,
	74, 75, 72,

	76, 77, 78,
	78, 79, 76,

	80, 81, 82,
	82, 83, 80,

	84, 85, 86,
	86, 87, 84,

	88, 89, 90,
	90, 91, 88,

	92, 93, 94,
	94, 95, 92,
};

ga_tesseract_component::ga_tesseract_component(ga_entity * ent, const char* texture_file) 
	: ga_component(ent)
{
	_transform4d._translate = ga_vec4f::zero_vector();
	_transform4d._scale = ga_vec4f::one_vector();
	_transform4d._rotation = { 1.0f }; //Identity rotation, i.e. doesn't rotate

	_material = new ga_4d_untextured_material(&_transform4d);
	_material->init();

	_index_count = static_cast<uint32_t>(sizeof(indices) / sizeof(indices[0]));

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(4, _vbos);

	glBindBuffer(GL_ARRAY_BUFFER, _vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, _vbos[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, _vbos[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbos[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

ga_tesseract_component::~ga_tesseract_component() 
{
	glDeleteBuffers(4, _vbos);
	glDeleteVertexArrays(1, &_vao);

	delete _material;
}

void ga_tesseract_component::update(ga_frame_params * params) 
{

}
