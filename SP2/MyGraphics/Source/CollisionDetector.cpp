/************************************************************/
/*!
\file	CollisionDetector.cpp
\author	Heng Soon Yap
\par	email:Romeoyap\@hotmail.com
\brief
A Class for the CollisionDetector to define them and their in the game
*/
/************************************************************/

#include "CollisionDetector.h"
#include <iostream>

using std::abs;
using std::cout;
using std::endl;

/************************************************************/
/*!

\brief
CollisionDetector() is a constructor for Bullet class, where I
set the default values needed for the methods.

*/
/************************************************************/

CollisionDetector::CollisionDetector() :dist(0){}

/************************************************************/
/*!

\brief
~CollisionDetector() is a destructor for the class

*/
/************************************************************/

CollisionDetector::~CollisionDetector(){}

/************************************************************/
/*!

\brief
PtoV(Position V) is a convertor function for CollisionDetector
class, where I convert the position values into a vector

\param V
A Position values that need to be convert to Vector3.

\return
A Vector3 that has been converted from a position

*/
/************************************************************/

Vector3 CollisionDetector::PtoV(Position V)
{
	Vector3 P = { V.x, V.y, V.z };
	return P;
}

/************************************************************/
/*!

\brief
collideByDist(Vector3 object, Vector3 target) is a calculator
function for CollisionDetector class, where I calculate the distance
between 2 Vector3.

\param object
A Vector3 values of an object that needs to be calculated with another
to find their distance.

\param target
A Vector3 values of a target that needs to be calculated with another
to find their distance.

\return
A float value that represent the distance between the 2 Vector3

*/
/************************************************************/

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

/************************************************************/
/*!

\brief
swordCollision(Enemy enemy[], Vector3 player) is a checker
function for player's melee attack, if it hit the enemy or not.

\param enemy[]
An enemy array that stores the enemy

\param player
A Vector3 values of the player position

\return
A boolean that represent if the player hit the enemy

*/
/************************************************************/

bool CollisionDetector::swordCollision(Enemy enemy[], Vector3 player)
{
	for (int i = 0; i < 5; i++)
	{
		Position enemyPos = enemy[i].Return_Position();
		Vector3 enemyVec = PtoV(enemyPos);

		if (collideByDist(player, enemyVec) < 40)
		{
			cout << "YOU SLASHED THE ENEMY" << endl;
			enemy[i].DamageReceived(100);
			return true;
		}
	}
	return false;
}
