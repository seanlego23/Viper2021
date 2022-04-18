#pragma once

#include "ga_bivec4f.h"

struct ga_rotor4f 
{
	union 
	{
		float i[7];
		struct {
			float scalar;
			ga_bivec4f bivec;
		};
	};
};

