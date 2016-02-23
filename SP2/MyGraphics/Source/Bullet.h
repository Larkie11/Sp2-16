#ifndef BULLET_H
#define BULLET_H

#include "Enemy.h"
#include "Vector3.h"
#include "Camera3.h"
#include "CollisionDetector.h"

#include <vector>

using std::vector;

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
	Vector3 PtoV(Position V);
	bool CollideWithEnemy(Enemy enemy[], vector<Bullet*>bullet_arr, CollisionDetector detectCollision);

	Bullet();
	Bullet(Camera3 camera);
	~Bullet();
};

#endif