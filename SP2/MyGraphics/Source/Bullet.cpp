#include "Bullet.h"
#include "Enemy.h"
#include "Camera3.h"
#include "CollisionDetector.h"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

Bullet::Bullet()
{

}
Bullet::Bullet(Camera3 camera)
{
	b_Speed = 100; //was 500

	// set the position out of scene 1st
	position = camera.position;
	direction = camera.view;
	b_Angle = camera.cameraRotate.y;
	b_distanceLimit = 6;
	b_distanceTravel = 0;
	destoryBullet = false;
}


Bullet::~Bullet()
{
}

bool Bullet::Update(double dt)
{
	//Bullet travel distance
	position += direction * b_Speed * dt;
	b_distanceTravel += dt;
	if (b_distanceTravel > b_distanceLimit)
	{
		destoryBullet = true;
	}
	return destoryBullet;
}

Vector3 Bullet::PtoV(Position V)
{
	Vector3 P = { V.x, V.y, V.z };
	return P;
}

bool Bullet::CollideWithEnemy(Enemy enemy[], vector<Bullet*>bullet_arr, CollisionDetector detectCollision)
{
	for (vector<Bullet*>::iterator iter = bullet_arr.begin(); iter != bullet_arr.end();)
	{
		for (int i = 0; i < 5; i++)
		{
			Position enemyPos = enemy[i].Return_Position(enemy[i]);
			Vector3 enemyVec = PtoV(enemyPos);

			if (detectCollision.collideByDist((*iter)->position, enemyVec) < 25)
			{
				cout << "COLLIDED WITH ENEMY" << endl;
				enemy[i] = enemy[i].DamageReceived(enemy[i], 30);
				destoryBullet = true;
			}
		}
		if (!destoryBullet)
			cout << "NEVER COLLIDED WITH ENEMY" << endl;
		return destoryBullet;
	}


}
