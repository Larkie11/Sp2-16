#ifndef OBJECTS_H
#define OBJECTS_H
#include "MyMath.h"
#include "Vector3.h"
#include "Camera3.h"


class Objects
{
public:
	int ItemType;
	Vector3 position;
	enum OBJECTS
	{
		COKE=0,
		VENDINGMACHINE,
	};
	
	Objects();
	~Objects();
	
};




#endif