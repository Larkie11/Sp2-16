#include "Enemy.h"
#include "SP2.h"


Enemy::Enemy()
{
	HP = 100;
	position = Ground = SpawnPoint = { -200, 0, 0 };
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
				Target_To_Move_To.x = Target.SpawnPoint.x + 10 *cos(Math::DegreeToRadian(Angle));
			}
			if (Angle != 0 && Angle != 180)
			{
				Target_To_Move_To.z = Target.SpawnPoint.z + 10 *sin(Math::DegreeToRadian(Angle));
			}
		}
		else if (mode == assassination)
		{
			int Angle = rand() % 360;
			if (Angle != 90 && Angle != 270)
			{
				Target_To_Move_To.x = Camera.x + 10 *cos(Math::DegreeToRadian(Angle));
			}
			if (Angle != 0 && Angle != 180)
			{
				Target_To_Move_To.z = Camera.z + 10 *sin(Math::DegreeToRadian(Angle));
			}
		}
		else if (mode == explore)
		{
			int Angle = rand() % 360;
			if (Angle != 90 && Angle != 270)
			{
				Target_To_Move_To.x = Target.Ground.x + 10 *cos(Math::DegreeToRadian(Angle));
			}
			if (Angle != 0 && Angle != 180)
			{
				Target_To_Move_To.z = Target.Ground.z + 10 *sin(Math::DegreeToRadian(Angle));
			}
		}
	}
	else if (mode < 6)
	{
		if (mode == fake_attack)
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
		if (mode == hold_down)
		{
			int Angle = rand() % 360;
			if (Angle != 90 && Angle != 270)
			{
				Target_To_Move_To.x = Camera.x + 5 * cos(Math::DegreeToRadian(Angle));
			}
			if (Angle != 0 && Angle != 180)
			{
				Target_To_Move_To.z = Camera.z + 5 * sin(Math::DegreeToRadian(Angle));
			}
		}
		if (mode == speed_escape)
		{
			int Angle = rand() % 360;
			if (Angle != 90 && Angle != 270)
			{
				Target_To_Move_To.x = Target.SpawnPoint.x + 10 *cos(Math::DegreeToRadian(Angle));
			}
			if (Angle != 0 && Angle != 180)
			{
				Target_To_Move_To.z = Target.SpawnPoint.z + 10 *sin(Math::DegreeToRadian(Angle));
			}
		}
	}
	else
	{
		if (mode == Surprise_attack)
		{
			int Angle = rand() % 360;
			if (Angle != 90 && Angle != 270)
			{
				Target_To_Move_To.x = Camera.x + 5 * cos(Math::DegreeToRadian(Angle));
			}
			if (Angle != 0 && Angle != 180)
			{
				Target_To_Move_To.z = Target.Ground.z + 5 * sin(Math::DegreeToRadian(Angle));
			}
		}
		if (mode == strategic_planning)
		{
			int Angle = rand() % 360;
			if (Angle != 90 && Angle != 270)
			{
				Target_To_Move_To.x = Camera.x + 5 * cos(Math::DegreeToRadian(Angle));
			}
			if (Angle != 0 && Angle != 180)
			{
				Target_To_Move_To.z = Camera.z + 5 * sin(Math::DegreeToRadian(Angle));
			}
		}
		if (mode == charge)
		{
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


int Enemy::Return_HP(Enemy Target)
{
	return Target.HP;
}

Enemy Enemy::Enemy_movement(Enemy Target, Position Camera, float dt, float Size, char Map[20][20], Enemy enemy[10], int I, float Z_Displacement, float X_Displacement)
{
	if (Target.Current_modetype < 3)
	{
		Target = mode_Action(Target,Camera);
	}
	Target = mode_Action(Target, Camera);
	float speed = 0.2 * dt;
	if (Target.Current_modetype == speed_escape || Target.Current_modetype == fake_attack)
	{
		speed = 0.5 * dt;
	}
	else if (Target.Current_modetype == charge || Target.Current_modetype == Surprise_attack)
	{
		speed = 0.7 * dt;
	}
	Target.position = Movement(Target.position, Target.Ground, speed, Size, Map, I, enemy, Z_Displacement, X_Displacement);
	return Target;

}

Position  Enemy::Movement(Position Current, Position Target, float Speed, float Size, char Map[20][20], int I, Enemy enemy[10], float Z_Displacement, float X_Displacement)
{
	Position T_Enemy = Current;
	if ((Current.x - Target.x) < 0 && (Current.x + Speed) < ((Size * 10) + X_Displacement))
	{
		T_Enemy.x += Speed;
		if (Collision_Detection(T_Enemy, Size, Map, enemy, I,Z_Displacement,X_Displacement))
		{
			Current = T_Enemy;
		}
	}
	else if ((Current.x - Target.x) > 0 && (Current.x - Speed) > ((-Size * 10) + X_Displacement))
	{
		T_Enemy.x -= Speed;
		if (Collision_Detection(T_Enemy, Size, Map, enemy, I, Z_Displacement, X_Displacement))
		{
			Current = T_Enemy;
		}

	}
	if ((Current.z - Target.z) < 0 && (Current.z + Speed) < ((Size * 10) + Z_Displacement))
	{
		T_Enemy.z += Speed;
		if (Collision_Detection(T_Enemy, Size, Map, enemy, I, Z_Displacement, X_Displacement))
		{
			Current = T_Enemy;
		}
	}
	else if ((Current.z - Target.z) > 0 && (Current.z - Speed) > ((-Size * 10) + Z_Displacement))
	{
		T_Enemy.z -= Speed;
		if (Collision_Detection(T_Enemy, Size, Map, enemy, I, Z_Displacement, X_Displacement))
		{
			Current = T_Enemy;
		}
	}
	
	return Current;
}

bool Enemy::Collision_Detection(Position Character, float Size, char Map[20][20], Enemy enemy[10], int I, float Z_Displacement, float X_Displacement, bool enter)
{
	bool check = true;
	bool Inside_Scene = true;
	bool enemys = false;
	int X = 10 + ((Character.x - X_Displacement) / Size);
	int Z = 10 + ((Character.z - Z_Displacement) / Size);
	if (X < 25 && X > 19)
	{
		X = 19;
		Inside_Scene = false;
	}
	if (Z < 25 && Z > 19)
	{
		Z = 19;
		Inside_Scene = false;
	}
	if (X > -5 && X < 0)
	{
		X = 0;
		Inside_Scene = false;
	}
	if (Z > -5 && Z < 0)
	{
		Z = 0;
		Inside_Scene = false;
	}
	if (X > -1 && X < 20 && Z > -1 && Z < 20)
	{
		if (Inside_Scene)
		{
			if (X < 2)
			{
				X = 0;
			}
			if (Z < 2)
			{
				X = 0;
			}
			if (X > 17)
			{
				X = 19;
			}
			if (Z > 17)
			{
				Z = 19;
			}
		}
		if (char(Map[X][Z]) != char(' ') && char(Map[X][Z]) != char('D'))
		{
			check = false;
		}
		else if (char(Map[X][Z]) == char('D') && !enter)
		{
			check = false;
		}
	}
	if (check)
	{
		check = Enemy_Collision(Character, enemy, I);
	}
	return check;
}

bool Enemy::Enemy_Collision(Position Character, Enemy enemy[10], int I)
{
	bool check = true;
	if (I != 9)
	{
		for (int i = I + 1; i < 10; i++)
		{
			float X_distance = Character.x - enemy[i].position.x;
			float Z_distance = Character.z - enemy[i].position.z;
			if (X_distance < 0)
			{
				X_distance = X_distance * -1;
			}
			if (Z_distance < 0)
			{
				Z_distance = Z_distance * -1;
			}
			if (X_distance < 10 && Z_distance < 10)
			{
				check = false;
			}
		}
	}
	return check;
}

Camera3 Enemy::enemy_attack(Enemy enemy[10], Position character, Camera3 view)
{
	for (int i = 0; i < 10; i++)
	{
		float X_distance = character.x - enemy[i].position.x;
		float Z_distance = character.z - enemy[i].position.z;
		if (X_distance < 0)
		{
			X_distance = X_distance * -1;
		}
		if (Z_distance < 0)
		{
			Z_distance = Z_distance * -1;
		}
		if (X_distance < 20 && Z_distance < 20)
		{
			view.Reset();
		}
	}
	return view;
}