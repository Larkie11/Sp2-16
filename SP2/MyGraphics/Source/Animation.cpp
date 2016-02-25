#include "Animation.h"

Animation::Animation()
{
	sliceDown = sliceUp = moveFront = moveBack = false;
}
Animation::~Animation(){}

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

void Animation::moveGun(double dt, float& targetTranslation, bool usingGun)
{
	float defaultPos = targetTranslation + 0.3;
	if (usingGun && defaultPos != 0.3)
	{
		if (targetTranslation < 0)
		{
			targetTranslation += (float)(2 * dt);
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