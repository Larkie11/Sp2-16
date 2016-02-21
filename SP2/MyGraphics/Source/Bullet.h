#ifndef BULLET_H
#define BULLET_H

#include "Vector3.h"
#include "Camera3.h"

class Bullet
{
public:

	Vector3 position;
	Vector3 direction;

	float b_Speed;
	float b_Angle;
	float b_distanceTravel = 0;
	float b_distanceLimit;
	float b_damage;
	bool destoryBullet;
	bool Update(double dt);

	Bullet();
	Bullet(Camera3 camera);
	~Bullet();
};

#endif