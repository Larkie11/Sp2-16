#include "CollisionDetector.h"
#include <iostream>

using std::abs;
using std::cout;
using std::endl;

CollisionDetector::CollisionDetector():dist(0){}
CollisionDetector::~CollisionDetector(){}

Vector3 CollisionDetector::PtoV(Position V)
{
	Vector3 P = { V.x, V.y, V.z };
	return P;
}


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

bool CollisionDetector::swordCollision(Enemy enemy[], Vector3 player)
{
	for (int i = 0; i < 5; i++)
	{
		Position enemyPos = enemy[i].Return_Position(enemy[i]);
		Vector3 enemyVec = PtoV(enemyPos);

		if (collideByDist(player, enemyVec) < 40)
		{
			cout << "YOU SLASHED THE ENEMY" << endl;
			enemy[i] = enemy[i].DamageReceived(enemy[i], 100);
			return true;
		}
		else
		{
			return false;
		}
	}
}
