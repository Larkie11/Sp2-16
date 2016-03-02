/************************************************************/
/*!
\file	Bullet.h
\author	Heng Soon Yap
\par	email:Romeoyap\@hotmail.com
\brief
A class for the bullets to define them in the game
*/
/************************************************************/

#ifndef BULLET_H
#define BULLET_H

#include "Enemy.h"
#include "Vector3.h"
#include "Camera3.h"
#include "CollisionDetector.h"

#include <vector>

using std::vector;

/************************************************************/
/*!
Class Bullet:
\brief	Defines a player's bullet in game and its methods
*/
/************************************************************/

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