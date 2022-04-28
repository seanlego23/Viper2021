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

static GLfloat _vertices[] = 
{
	-1.0f, -1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,  1.0f,
};

static GLuint _triangles[] = 
{
	0, 1, 9, //x = -1, y = -1
	9, 8, 0,

	2, 3, 11, //x = -1, y = 1
	11, 10, 2,

	4, 5, 13, //x = 1, y = -1
	13, 12, 4,

	6, 7, 15, //x = 1, y = 1
	15, 14, 6,

	0, 2, 10, //x = -1, z = -1
	10, 8, 0,

	1, 3, 11, //x = -1, z = 1
	11, 9, 1,

	4, 6, 14, //x = 1, z = -1
	14, 12, 4,

	5, 7, 15, //x = 1, z = 1
	15, 13, 5,

	0, 2, 3, //x = -1, w = -1
	3, 1, 0,

	8, 10, 11, //x = -1, w = 1
	11, 9, 8,

	4, 6, 7, //x = 1, w = -1
	7, 5, 4,

	12, 14, 15, //x = 1, w = 1
	15, 13, 12,

	0, 4, 12, //y = -1, z = -1
	12, 8, 0,

	1, 5, 13, //y = -1, z = 1
	13, 9, 1,

	2, 6, 14, //y = 1, z = -1
	14, 10, 2,

	3, 7, 15, //y = 1, z = 1
	15, 11, 3,

	0, 4, 5, //y = -1, w = -1
	5, 1, 0,

	8, 12, 13, //y = -1, w = 1
	13, 9, 8,

	2, 6, 7, //y = 1, w = -1
	7, 3, 2,

	10, 14, 15, //y = 1, w = 1
	15, 11, 10,

	0, 4, 6, //z = -1, w = -1
	6, 2, 0,

	8, 12, 14, //z = -1, w = 1
	14, 10, 8,

	1, 5, 7, //z = 1, w = -1
	7, 3, 1,

	9, 13, 15, //z = 1, w = 1
	15, 11, 9,
};

static GLuint edges[] =
{
	 0,  1,
	 0,  2,
	 0,  4,
	 1,  3,
	 1,  5,
	 1,  9,
	 2,  3,
	 2,  6,
	 3,  7,
	 3, 11,
	 4,  5,
	 4,  6,
	 5,  7,
	 5, 13,
	 6,  7,
	 7, 15,
	 8,  0,
	 9,  8,
	10,  2,
	10,  8,
	11,  9,
	11, 10,
	12,  4,
	12,  8,
	13,  9,
	13, 12,
	14,  6,
	14, 10,
	14, 12,
	15, 11,
	15, 13,
	15, 14,
};

static GLuint adjacent_triangles[] =
{
	//Organized by edge above
	 0, 17, 33,
	 8, 16, 41,
	24, 32, 40,
	10, 17, 45,
	26, 33, 44,
	 0, 11, 27,
	 2, 16, 37,
	28, 36, 41,
	30, 37, 45,
	 2, 10, 31,
	 4, 21, 32,
	12, 20, 40,
	14, 21, 44,
	 4, 15, 26,
	 6, 20, 36,
	 6, 14, 30,
	 1,  9, 25,
	 1, 19, 35,
	 3,  8, 29,
	 9, 18, 43,
	11, 19, 47,
	 3, 18, 39,
	 5, 13, 24,
	25, 34, 42,
	27, 35, 46,
	 5, 23, 34,
	 7, 12, 28,
	29, 38, 43,
	13, 22, 42,
	31, 39, 47,
	15, 23, 46,
	 7, 22, 38,
};

static GLuint vertex_texture;

ga_tesseract_component::ga_tesseract_component(ga_entity* ent) 
	: ga_component(ent)
{
	_transform4d._translate = ga_vec4f::zero_vector();
	_transform4d._scale = ga_vec4f::one_vector();
	_transform4d._rotation = { 1.0f }; //Identity rotation, i.e. doesn't rotate

	_material = new ga_4d_untextured_material(&_transform4d);
	_material->init();

	glGenTextures(1, &vertex_texture);
	glBindTexture(GL_TEXTURE_2D, vertex_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 4, 24, 0, GL_RGBA, GL_FLOAT, _vertices);

	_index_count = static_cast<uint32_t>(sizeof(indices) / sizeof(indices[0]));

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(4, _vbos);

	glBindBuffer(GL_ARRAY_BUFFER, _vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, _vbos[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, _vbos[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
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
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, vertex_texture);
	glBindImageTexture(0, vertex_texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

	ga_uniform translate = transform4d_program.get_uniform("u_transform4d.translate");
	ga_uniform scale = transform4d_program.get_uniform("u_transform4d.scale");
	ga_uniform rotor = transform4d_program.get_uniform("u_transform4d.rotor");

	transform4d_program.use();

	translate.set(_transform4d._translate);
	scale.set(_transform4d._scale);
	rotor.set(_transform4d._rotation);

	glDispatchCompute(1, 1, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);



	ga_static_drawcall draw;
	draw._name = "ga_tesseract_component";
	draw._vao = _vao;
	draw._index_count = _index_count;
	draw._transform = get_entity()->get_transform();
	draw._draw_mode = GL_TRIANGLES;
	draw._material = _material;

	while (params->_static_drawcall_lock.test_and_set(std::memory_order_acquire)) {}
	params->_static_drawcalls.push_back(draw);
	params->_static_drawcall_lock.clear(std::memory_order_release);
}
