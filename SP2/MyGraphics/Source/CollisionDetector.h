/************************************************************/
/*!
\file	CollisionDetector.h
\author	Heng Soon Yap
\par	email:Romeoyap\@hotmail.com
\brief
A class for the collisions in the game to define them in the game
*/
/************************************************************/

#ifndef COLLISIONDETECTOR_H
#define	COLLISIONDETECTOR_H

#include "MyMath.h"
#include "Enemy.h"
#include "Vector3.h"
#include "SharedData.h"

/************************************************************/
/*!
Class Dweller:
\brief	Defines a player's weapons collision in game and its methods
*/
/************************************************************/

class CollisionDetector
{
public:

	float dist;
	float diffInX;
	float diffInZ;

	CollisionDetector();
	~CollisionDetector();

	float collideByDist(Vector3 object, Vector3 target);
	bool swordCollision(Enemy enemy[], Vector3 player);
	Vector3 PtoV(Position V);

};

#endif