#pragma once

#include "entity/ga_component.h"

/*
** Renderable tesseract (4D Cube)
*/
class ga_tesseract_component : public ga_component 
{
public:
	ga_tesseract_component(class ga_entity* ent, const char* texture_file);
	virtual ~ga_tesseract_component();

	virtual void update(struct ga_frame_params* params) override;

private:
	class ga_material*_material;
	uint32_t _vao;
	uint32_t _vbos[4];
	uint32_t _index_count;
};

