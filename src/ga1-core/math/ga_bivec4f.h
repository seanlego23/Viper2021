#pragma once
struct ga_bivec4f 
{
	union 
	{
		float i[6];
		struct 
		{
			float xy;
			float xz;
			float xw;
			float yz;
			float yw;
			float zw;
		};
	};


};

