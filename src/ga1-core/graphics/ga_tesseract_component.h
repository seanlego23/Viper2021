#pragma once

#include "entity/ga_component.h"
#include "math/ga_transform4d.h"

/*
** Renderable tesseract (4D Cube)
*/
class ga_tesseract_component : public ga_component 
{
public:
	ga_tesseract_component(class ga_entity* ent);
	virtual ~ga_tesseract_component();

	virtual void update(struct ga_frame_params* params) override;

private:
	class ga_material* _material;
	ga_transform4d _transform4d;
	uint32_t _vao;
	uint32_t _vbos[4];
	uint32_t _index_count;
};

