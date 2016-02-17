#include "Bullet.h"
#include "Camera3.h"

Bullet::Bullet()
{
	b_Speed = 100; //was 500
	b_Count = 10;
	b1_Spawn = false;
	b2_Spawn = false;
	enableShooting = true;
	b_Switcher = true;
	shotFired = false;

	// set the position out of scene 1st
	b1_position = { 0, -100, 0 };
	b2_position = { 0, -100, 0 };

	b_delay = b_coolDown = 0.8;
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
				//switching which bullet to travel
				shotFired = true;
				velocity = camera.view * b_Speed;
				b_Angel = camera.cameraRotate.y;

				if (!b1_Spawn)
				{
					b1_Spawn = true;
					b2_Spawn = false;
					b1_position = camera.position;
					b1_position += velocity * dt;
				}
				else
				{
					b1_Spawn = false;
					b2_Spawn = true;
					b2_position = camera.position;
					b2_position += velocity * dt;

				}

				b_Count--;
			}
			b_delay -= dt;
			if (b_delay < 0)
				b_delay = b_coolDown;
		}
		else
		{
			enableShooting = false;
		}
	}
	else
	{
		//Ammo reloaded
		if (b_Count == 10)
			enableShooting = true;
	}

}
