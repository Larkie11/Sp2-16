#ifndef BULLET_H
#define BULLET_H

#include "Vector3.h"
#include "Camera3.h"

class Bullet
{
public:
	//b1 = bullet 1 in the scene, b2 = bullet 2 in the scene
	Vector3 position;
	Vector3 direction;

	float b_Speed;
	float b_Angle;
	float b_distanceTravel = 0;
	float b_distanceLimit;

	bool destoryBullet; 
	bool Update(double dt);

	Bullet();
	Bullet(Camera3 camera);
	~Bullet();
};

#endif