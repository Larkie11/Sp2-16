#ifndef OBJECTS_H
#define OBJECTS_H
#include "MyMath.h"
#include "Vector3.h"
#include "Camera3.h"


class Objects
{
public:
	Vector3 position;
	enum OBJECTS
	{
		COKE=0,
		VENDINGMACHINE,
	};
	
	Objects();
	~Objects();
	bool pickupcoke = false;
	bool pickupvending = false;


	float measuere;

	float followx = 0;
	float followy = 0;


	void CheckDistance(Vector3 objects, Camera3 camera);

	
private:
	Vector3 cameravector;
	

	// calculating self and objects place
	
};




#endif