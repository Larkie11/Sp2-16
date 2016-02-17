#include "Enemy.h"
#include "SP2.h"


Enemy::Enemy()
{
	HP = 100;
	position = Ground = SpawnPoint = { 0, 0, 0 };
	MeleeDamage = rand() % 20;
	Current_modetype = rand() % 3;
}


Enemy::~Enemy()
{
}

int Enemy::mode_Change(Enemy Target)
{
	int mode = 0;
	if (Target.HP >= 90)
	{
		mode = rand() % 3;
	}
	else if (Target.HP > 50)
	{
		mode = rand() % 3 + 3;
	}
	else
	{
		mode = rand() % 3 + 6;
	}
	return mode;
}

Enemy Enemy::DamageReceived(Enemy Target, int Damage)
{
	Target.HP -= Damage;
	if (Target.HP < 0)
	{
		Target.HP = 100;
		Target.position = Target.Ground = Target.SpawnPoint = { 0, 0, 0 };
		for (int i = 0; i < 10; i++)
		{
			Target.Bullet[i].position = { 0, 0, 0 }; 
			Target.Bullet[i].direction = { 0, 0, 0 };
			Target.Bullet[i].AcidDamage = 0;
			Target.Bullet[i].fired = false;
		}
	}
	Target.Current_modetype = mode_Change(Target);
	return Target;
}

Enemy Enemy::mode_Action(Enemy Target, Position Camera)
{
	int mode = Target.Current_modetype;
	Position Target_To_Move_To = { 0, 0, 0 };
	if (mode < 3)
	{
		if (mode == patrol)
		{
			int Angle = rand() % 360;
			if (Angle != 90 && Angle != 270)
			{
				Target_To_Move_To.x = Target.SpawnPoint.x + 20 * cos(Math::DegreeToRadian(Angle));
			}
			if (Angle != 0 && Angle != 180)
			{
				Target_To_Move_To.z = Target.SpawnPoint.z + 20 * sin(Math::DegreeToRadian(Angle));
			}
		}
		else if (mode == assassination)
		{
			int Angle = rand() % 360;
			if (Angle != 90 && Angle != 270)
			{
				Target_To_Move_To.x = Camera.x + 10 * cos(Math::DegreeToRadian(Angle));
			}
			if (Angle != 0 && Angle != 180)
			{
				Target_To_Move_To.z = Camera.z + 10 * sin(Math::DegreeToRadian(Angle));
			}
		}
		else if (mode == explore)
		{
			int Angle = rand() % 360;
			if (Angle != 90 && Angle != 270)
			{
				Target_To_Move_To.x = Target.Ground.x + 20 * cos(Math::DegreeToRadian(Angle));
			}
			if (Angle != 0 && Angle != 180)
			{
				Target_To_Move_To.z = Target.Ground.z + 20 * sin(Math::DegreeToRadian(Angle));
			}
		}
	}
	else if (mode < 6)
	{
		if (mode == fake_attack)
		{
			float Range = sqrt(((Camera.x - Target.position.x)*(Camera.x - Target.position.x)) + ((Camera.z - Target.position.z)*(Camera.z - Target.position.z)));
			if (Range > 10)
			{
				for (int i = 0; i < 10; i++)
				{
					if (Target.Bullet[i].fired == false)
					{
						Position A = (Camera.x + rand() % (i+1), Camera.z + rand() % (i+1), Camera.z + rand() % (i+1));
						Target.Bullet[i] = ShootBullet(i, Target, A);
					}
				}
			}
			else
			{
				//Enemy Melee Attack
			}
			Target_To_Move_To = Camera;
		}
		if (mode == hold_down)
		{
			float Range = sqrt(((Camera.x - Target.position.x)*(Camera.x - Target.position.x)) + ((Camera.z - Target.position.z)*(Camera.z - Target.position.z)));
			if (Range > 10)
			{
				for (int i = 0; i < 10; i++)
				{
					if (Target.Bullet[i].fired == false)
					{
						Position A = (Camera.x + rand() % (i+1), Camera.z + rand() % (i+1), Camera.z + rand() % (i+1));
						Target.Bullet[i] = ShootBullet(i, Target, A);
					}
				}
			}
			else
			{
				//Enemy Melee Attack
			}
			Target_To_Move_To = Camera;
		}
		if (mode == speed_escape)
		{
			Target_To_Move_To = Camera;
		}
	}
	else
	{
		if (mode == Surprise_attack)
		{
			float Range = sqrt(((Camera.x - Target.position.x)*(Camera.x - Target.position.x)) + ((Camera.z - Target.position.z)*(Camera.z - Target.position.z)));
			if (Range > 5)
			{
				for (int i = 0; i < 10; i++)
				{
					if (Target.Bullet[i].fired == false)
					{
						Position A = (Camera.x + rand() % (i+1), Camera.z + rand() % (i+1), Camera.z + rand() % (i+1));
						Target.Bullet[i] = ShootBullet(i, Target, A);
					}
				}
			}
			Target_To_Move_To = Camera;
		}
		if (mode == strategic_planning)
		{
			float Range = sqrt(((Camera.x - Target.position.x)*(Camera.x - Target.position.x)) + ((Camera.z - Target.position.z)*(Camera.z - Target.position.z)));
			if (Range > 2)
			{
				for (int i = 0; i < 10; i++)
				{
					if (Target.Bullet[i].fired == false)
					{
						Position A = (Camera.x + rand() % (i+1), Camera.z + rand() % (i+1), Camera.z + rand() % (i+1));
						Target.Bullet[i] = ShootBullet(i, Target, A);
					}
				}
			}
			Target_To_Move_To = Camera;
		}
		if (mode == charge)
		{
			float Range = sqrt(((Camera.x - Target.position.x)*(Camera.x - Target.position.x)) + ((Camera.z - Target.position.z)*(Camera.z - Target.position.z)));
			if (Range > 20)
			{
				for (int i = 0; i < 10; i++)
				{
					if (Target.Bullet[i].fired == false)
					{
						Position A = (Camera.x + rand() % (i+1), Camera.z + rand() % (i+1), Camera.z + rand() % (i+1));
						Target.Bullet[i] = ShootBullet(i, Target, A);
					}
				}
			}
			Target_To_Move_To = Camera;
		}
	}
	Target.Ground = Target_To_Move_To;
	return Target;
}

Position Enemy::Return_Position(Enemy Target)
{
	return Target.position;
}

Position Enemy::Return_Bullet_Position(int bullet, Enemy Target)
{
	return Target.Bullet[bullet].position;
}

int Enemy::Return_HP(Enemy Target)
{
	return Target.HP;
}

Acid Enemy::ShootBullet(int Bullet, Enemy Target, Position Camera)
{
	Acid Bullets = Target.Bullet[Bullet];
	Bullets.position = Target.position;
	Bullets.direction = Camera;
	Bullets.AcidDamage = 20;
	Bullets.fired = true;
	return Bullets;
}

Enemy Enemy::Enemy_movement(Enemy Target, Position Camera, float dt)
{
	if (Target.Current_modetype < 3)
	{
		Target = mode_Action(Target,Camera);
	}
	Target = mode_Action(Target, Camera);
	float speed = 0.5 * dt;
	if (Target.Current_modetype == speed_escape || Target.Current_modetype == fake_attack)
	{
		speed = -1 * dt;
	}
	else if (Target.Current_modetype == charge || Target.Current_modetype == Surprise_attack)
	{
		speed = 1 * dt;
	}
	for (int i = 0; i < 10; i++)
	{
		if (Target.Bullet[i].fired == true && Target.Bullet[i].position.x == Target.Bullet[i].direction.x && Target.Bullet[i].position.y == Target.Bullet[i].direction.y)
		{
			Target.Bullet[i].fired = false;
			Target.Bullet[i].direction = { 0, 0, 0 };
			Target.Bullet[i].position = { 0, 0, 0 };
			Target.Bullet[i].AcidDamage = 0;
			std::cout << "Shot" << std::endl;
		}
		else if (Target.Bullet[i].fired == true)
		{
			Target.Bullet[i].position = Movement(Bullet[i].position,Bullet[i].direction, 1);
		}
	}
	Target.position = Movement(Target.position, Target.Ground, speed);
	return Target;

}

Position  Enemy::Movement(Position Current, Position Target, float Speed)
{
	float movement[2] = { Speed, Speed };
	if ((Current.x - Target.x) > 0)
	{
		movement[0] = -Speed;
	}
	if ((Current.z - Target.z) > 0)
	{
		movement[1] = -Speed;
	}
 	Current = { Current.x + movement[0], Current.y, Current.z + movement[1] };
	return Current;
}