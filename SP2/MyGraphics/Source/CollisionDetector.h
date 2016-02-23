#ifndef COLLISIONDETECTOR_H
#define	COLLISIONDETECTOR_H

#include "MyMath.h"
#include "Vector3.h"

class CollisionDetector
{
public:

	float dist;
	float diffInX;
	float diffInZ;

	CollisionDetector();
	~CollisionDetector();

	float collideByDist(Vector3 object, Vector3 target);


};

#endif