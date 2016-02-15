#ifndef LIGHT_H
#define LIGHT_H


#include "Vertex.h"


struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	Light()
	{
		position.Set(1, 1, 1);
		color.Set(0, 0, 0);
		power = 1.f;
		kC = kL = kQ = 1;
	}
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};

	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutOff;
	float cosInner;
	float exponent;
};

#endif  