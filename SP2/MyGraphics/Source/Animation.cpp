#include "Animation.h"

Animation::Animation()
{
	sliceDown = sliceUp = moveFront = moveBack = false;
}
Animation::~Animation(){}

void Animation::Slash(double dt, float& targetRotation)
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
		if (targetRotation < 0 )
		{
			sliceUp = false;
			sliceDown = false;
		}
	}
}

void Animation::Shoot(double dt, float& targetTranslation)
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

void Animation::Mine(double dt, float& targetRotation)
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
		}
	}
}