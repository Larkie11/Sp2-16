#include "Objects.h"


Objects::Objects()
{
}

Objects::~Objects()
{

}


void Objects::CheckDistance(Vector3 objects, Camera3 camera)
{



	// using 2 vector pythagoras postion  x-x+ z-z= distance rooted  
	if (sqrt(((camera.position.x - objects.x)*(camera.position.x - objects.x)) + ((camera.position.x - objects.z)*(camera.position.x - objects.z))) < 20)
	{
		pickupcoke = true;

	}

	if ((sqrt(((camera.position.x - objects.x)*(camera.position.x - objects.x)) + ((camera.position.x - objects.z)*(camera.position.x - objects.z))) < 20))
	{
		pickupvending = true;
	}
}



	//pick up is part of objhects objects now return 000 only need to make it go with items binded distance into pick up
	//distancee need call according to objects different onees. at one go it calculate different object distance and pick up those within my pick up 20 raidus









// calculating self and objects place

//enable item position to move up x yzfo llkow camera