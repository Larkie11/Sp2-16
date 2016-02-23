#include "CollisionDetector.h"
#include <iostream>

using std::abs;

CollisionDetector::CollisionDetector():dist(0){}
CollisionDetector::~CollisionDetector(){}

float CollisionDetector::collideByDist(Vector3 object, Vector3 target)
{
	//A
	diffInX = abs(target.x - object.x);

	//B
	diffInZ = abs(target.z - object.z);

	//TOA CAH SOH   A square + B square = C square
	dist = sqrt(diffInX * diffInX + diffInZ * diffInZ);

	return dist;
}