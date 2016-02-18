#include "Bullet.h"
#include "Camera3.h"

Bullet::Bullet()
{

}
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


Bullet::~Bullet()
{
}

bool Bullet::Update(double dt)
{
	position += direction * b_Speed * dt;
	b_distanceTravel += dt;
	if (b_distanceTravel > b_distanceLimit)
	{
		destoryBullet = true;
	}
	return destoryBullet;
}
