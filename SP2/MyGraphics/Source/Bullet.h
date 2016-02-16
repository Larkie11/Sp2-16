#ifndef BULLET_H
#define BULLET_H

#include "Vector3.h"
#include "Camera3.h"

class Bullet
{
	public:
		Vector3 position;
		Vector3 velocity;

		float b_Speed;
		float b_Angel;
		int b_Count;
		bool enableShooting;

		void Shoot(double dt, Camera3 camera);

		Bullet();
		~Bullet();
};

#endif