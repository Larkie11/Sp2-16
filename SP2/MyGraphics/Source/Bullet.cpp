#include "Bullet.h"
#include "Camera3.h"

Bullet::Bullet()
{
	b_Speed = 30;
	b_Count = 10;
	enableShooting = true;
	shotFired = false;
	b_delay = b_coolDown = 0.4;
}

Bullet::~Bullet()
{
}

void Bullet::Shoot(double dt, Camera3 camera)
{
	if (enableShooting)
	{
		//Ammo > 0
		if (b_Count > 0)
		{
			//delay setting
			if (b_delay == b_coolDown)
			{
				shotFired = true;
				velocity = camera.view * b_Speed;
				position = camera.position;
				b_Angel = camera.cameraRotate.y;
				position += velocity * dt;
				b_Count--;
			}
			b_delay-=dt;
			if (b_delay < 0)
				b_delay = b_coolDown;
		}
		else
		{
			enableShooting = false;
		}
	}
	
}
