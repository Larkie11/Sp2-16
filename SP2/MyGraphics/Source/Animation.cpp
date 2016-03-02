/************************************************************/
/*!
\file	Animation.cpp
\author	Heng Soon Yap
\par	email:Romeoyap\@hotmail.com
\brief
A Class for the animation to define them in the game
*/
/************************************************************/

#include "Animation.h"

/************************************************************/
/*!

\brief
Animation() is a constructor for animation class, where I
set the default values needed for the methods.

*/
/************************************************************/

Animation::Animation()
{
	sliceDown = sliceUp = moveFront = moveBack = false;
}

/************************************************************/
/*!

\brief
~Animation() is the destructor for animation class.

*/
/************************************************************/

Animation::~Animation(){}

/************************************************************/
/*!

\brief
Slash(double dt, float& targetRotation, bool& start),
Animates the player's slashing animation when using sword,
by using sliceUp and sliceDown boolean to check if it completes
the animation.

\param dt
A double that represents the delta time needed for calculation for
the animation.

\param targetRotation
A float that represents the target's rotation that this function
is using on.

\param start
A boolean that represents when the animation should start playing
or stop.
*/
/************************************************************/

void Animation::Slash(double dt, float& targetRotation, bool& start)
{
	if (!sliceDown && !sliceUp)
		sliceDown = true;

	if (sliceDown)
	{
		targetRotation += (float)(300 * dt);
		if (targetRotation > 100)
		{
			sliceUp = true;
			sliceDown = false;
		}
	}
	if (sliceUp)
	{
		targetRotation -= (float)(300 * dt);
		if (targetRotation < 0)
		{
			sliceUp = false;
			sliceDown = false;
			start = false;
		}
	}
}

/************************************************************/
/*!

\brief
Shoot(double dt, float& targetRotation, bool& start),
Animates the player's shooting animation when using gun,
by checking if the gun has moved according to the recoils
and using the boolean to check if it completes the animation.

\param dt
A double that represents the delta time needed for calculation for
the animation.

\param targetTranslation
A float that represents the target's translation that this function
is using on.

\param start
A boolean that represents when the animation should start playing
or stop.
*/
/************************************************************/

void Animation::Shoot(double dt, float& targetTranslation, bool& start)
{
	if (targetTranslation < 0.05)
	{
		targetTranslation += (float)(0.13 * dt);
		if (targetTranslation > 0.06)
			targetTranslation = 0.05f;

	}
	else
	{
		targetTranslation -= (float)(0.13 * dt);
		targetTranslation = 0.f;
	}
}

/************************************************************/
/*!

\brief
Mine(double dt, float& targetRotation, bool& start),
Animates the player's mining animation when using pick axe,
by using sliceUp and sliceDown boolean to check if it completes
the animation.

\param dt
A double that represents the delta time needed for calculation for
the animation.

\param targetRotation
A float that represents the target's rotation that this function
is using on.

\param start
A boolean that represents when the animation should start playing
or stop.
*/
/************************************************************/

void Animation::Mine(double dt, float& targetRotation, bool& start)
{
	if (!sliceDown && !sliceUp)
		sliceDown = true;

	if (sliceDown)
	{
		targetRotation += (float)(400 * dt);
		if (targetRotation > 100)
		{
			sliceUp = true;
			sliceDown = false;
		}
	}
	if (sliceUp)
	{
		targetRotation -= (float)(400 * dt);
		if (targetRotation < 0)
		{
			sliceUp = false;
			sliceDown = false;
			start = false;
		}
	}
}

/************************************************************/
/*!

\brief
moveSword(double dt, float& targetTranslation, bool& usingSword),
Animates the player's changing to sword animation, by checking
if the sword has move to certain position and using the boolean
to check if the animations is completed.

\param dt
A double that represents the delta time needed for calculation for
the animation.

\param targetTranslation
A float that represents the target's translation that this function
is using on.

\param start
A boolean that represents when the animation should start playing
or stop.
*/
/************************************************************/

void Animation::moveSword(double dt, float& targetTranslation, bool usingSword)
{
	float defaultPos = targetTranslation + 0.5;
	if (usingSword && defaultPos != 0.5)
	{
		if (targetTranslation < 0)
		{
			targetTranslation += (float)(2 * dt);
		}
	}
	else if (!usingSword && targetTranslation != -0.8)
	{
		if (targetTranslation > -0.8)
		{
			targetTranslation -= (float)(10 * dt);
			if (targetTranslation < -0.8)
				targetTranslation = -0.8;
		}
	}
}

/************************************************************/
/*!

\brief
moveGun(double dt, float& targetTranslation, bool& usingSword),
Animates the player's changing to gun animation, by checking
if the gun has move to certain position and using the boolean
to check if the animations is completed.

\param dt
A double that represents the delta time needed for calculation for
the animation.

\param targetTranslation
A float that represents the target's translation that this function
is using on.

\param usingGun
A boolean that represents when the animation should start playing
or stop.
*/
/************************************************************/

void Animation::moveGun(double dt, float& targetTranslation, bool usingGun)
{
	float defaultPos = targetTranslation + 0.3;
	if (usingGun && defaultPos != 0.3)
	{
		if (targetTranslation < 0)
		{
			targetTranslation += (float)(5 * dt);
		}
	}
	else if (!usingGun && targetTranslation != -2)
	{
		if (targetTranslation > -2)
		{
			targetTranslation -= (float)(10 * dt);
			if (targetTranslation < -2)
				targetTranslation = -2;
		}
	}
}

/************************************************************/
/*!

\brief
explosion(double dt, float& explosionScale, bool& playExplosion),
Animates the explosion animation, by checking if the explosion
has scale up to certain scale and using the boolean to check if
the animations is completed.

\param dt
A double that represents the delta time needed for calculation for
the animation.

\param explosionScale
A float that represents the target's scale that this function
is using on.

\param playExplosion
A boolean that represents when the animation should start playing
or stop.
*/
/************************************************************/

void Animation::explosion(double dt, float& explosionScale, bool& playExplosion)
{
	if (playExplosion && explosionScale < 0.4)
	{
		explosionScale += (float)(dt);
	}
	else
	{
		explosionScale = 0.2;
		playExplosion = false;
	}
}