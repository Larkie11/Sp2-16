/************************************************************/
/*!
\file	Bullet.cpp
\author	Heng Soon Yap
\par	email:Romeoyap\@hotmail.com
\brief
A Class for the Bullet to define them in the game
*/
/************************************************************/

#include "Bullet.h"
#include "Enemy.h"
#include "Camera3.h"
#include "CollisionDetector.h"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

/************************************************************/
/*!

\brief
Bullet() is a constructor for Bullet class, where I
set the default values needed for the methods.

*/
/************************************************************/

Bullet::Bullet(){}

/************************************************************/
/*!

\brief
Bullet(Camera3 camera) is an overloaded constructor for Bullet
class, where I set the default values needed for the methods.

\param damageTaken
A Camera3 class for the bullet to spawn from by taking the
position, view and rotation of the player's camera.

*/
/************************************************************/

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

/************************************************************/
/*!

\brief
~Bullet() is the destructor for Bullet class.

*/
/************************************************************/

Bullet::~Bullet(){}

/************************************************************/
/*!

\brief
Update(double dt) is a update function for Bullet class,
where I update the position values for the bullet that
has been shot.

\param damageTaken

A double dt that represent the delta time in update.
*/
/************************************************************/

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

/************************************************************/
/*!

\brief
PtoV(Position V) is a convertor function for Bullet class,
where I convert the position values into a vector

\param V
A Position values that need to be convert to Vector3.

\return
A Vector3 that has been converted from a position
*/
/************************************************************/

Vector3 Bullet::PtoV(Position V)
{
	Vector3 P = { V.x, V.y, V.z };
	return P;
}

/************************************************************/
/*!

\brief
CollideWithEnemy(Enemy enemy[], vector<Bullet*>bullet_arr,
CollisionDetector detectCollision) is a function for Bullet
class to calculate if each of the bullet in the scene did
or did not collide with any enemy, if it didn't it will only
travel a distance before it gets destoryed or if it hits an
enemy it will get destoryed too.

\param enemy[]
An Enemy array that consists of all the enemy inside the game,

\param bullet_arr
A Bullet vector to store all the bullet in the game,

\param detectCollision
A Collision detector that the scene are using to check distance
and if 2 objects are collided together.
*/
/************************************************************/

bool Bullet::CollideWithEnemy(Enemy enemy[], vector<Bullet*>bullet_arr, CollisionDetector detectCollision)
{
	for (vector<Bullet*>::iterator iter = bullet_arr.begin(); iter != bullet_arr.end();)
	{
		for (int i = 0; i < 5; i++)
		{
			Position enemyPos = enemy[i].Return_Position();
			Vector3 enemyVec = PtoV(enemyPos);

			if (detectCollision.collideByDist((*iter)->position, enemyVec) < 35)
			{
				enemy[i].DamageReceived(30);
				destoryBullet = true;
			}
		}

		if (!destoryBullet)
			cout << position.y << endl;

		return destoryBullet;
	}


}
