#ifndef BULLET_H
#define BULLET_H

#include "Vector3.h"
#include "Camera3.h"

class Bullet
{
public:
	//b1 = bullet 1 in the scene, b2 = bullet 2 in the scene
	Vector3 b1_position;
	Vector3 b2_position;
	Vector3 velocity;

	float b_Speed;
	float b_Angel;
	float b_delay;
	float b_coolDown;
	int b_Count;
	bool enableShooting;
	bool shotFired;
	bool b1_Spawn;
	bool b2_Spawn;

	//True = bullet 1 move, False = bullet 2 move
	bool b_Switcher;
	void Shoot(double dt, Camera3 camera);

	Bullet();
	~Bullet();
};

#endif