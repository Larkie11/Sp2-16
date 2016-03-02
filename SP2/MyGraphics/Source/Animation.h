/************************************************************/
/*!
\file	Animation.h
\author	Heng Soon Yap
\par	email:Romeoyap\@hotmail.com
\brief
A class for the animation to define them in the game
*/
/************************************************************/

#ifndef ANIMATION_H
#define ANIMATION_H
#include "Mesh.h"

/************************************************************/
/*!
Class Dweller:
\brief	Defines a player's action in game and its methods
*/
/************************************************************/

class Animation
{
public:
	Animation();
	~Animation();
	void Slash(double dt, float& targetRotation, bool& start);
	void Shoot(double dt, float& targetTranslation, bool& start);
	void Mine(double dt, float& targetRotation, bool& start);
	void moveSword(double dt, float& targetTranslation, bool usingSword);
	void moveGun(double dt, float& targetTranslation, bool usingGun);
	void explosion(double dt, float& explosionScale, bool& playExplosion);
	bool Update(double dt);

	bool sliceUp;
	bool sliceDown;
	bool moveFront;
	bool moveBack;

	bool switchDown;
	bool switchUp;
};

#endif