#include "Bullet.h"
#include "Camera3.h"

Bullet::Bullet()
{
	b_Speed = 30;
	b_Count = 10;
	enableShooting = true;
}

Bullet::~Bullet()
{
}

void Bullet::Shoot(double dt, Camera3 camera)
{
	if (enableShooting)
	{
		if (b_Count > 0)
		{
			velocity = camera.view * b_Speed;
			position = camera.position;
			b_Angel = camera.cameraRotate.y;
			position += velocity * dt;
			b_Count--;
		}
		else
		{
			enableShooting = false;
		}
	}
	
}
