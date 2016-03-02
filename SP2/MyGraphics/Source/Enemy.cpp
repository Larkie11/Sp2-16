/******************************************************************************/
/*!
\file	Enemy.CPP
\author Francis Wong
\par
\brief
Contain all function code for enemy NPC
*/
/******************************************************************************/
#include "Enemy.h"
#include "SP2.h"

/******************************************************************************/
/*!
\brief
Default Constructor
\exception None
\return None
*/
/******************************************************************************/
Enemy::Enemy()
{
	HP = 100;
	float X = (-8 * 15) + rand() % (16 * 15) - 100;
	float Z = (-8 * 15) + rand() % (16 * 15);
	position = Ground = SpawnPoint = { X, 0, Z };
	if (!Quick_check())
	{
		X = (-8 * 15) + rand() % (16 * 15) - 100;
		Z = (-8 * 15) + rand() % (16 * 15);
		position = Ground = SpawnPoint = { X, 0, Z };
	}
	MeleeDamage = rand() % 20;
	Current_modetype = rand() % 3;
}


/******************************************************************************/
/*!
\brief
Default destructor
\exception None
\return None
*/
/******************************************************************************/
Enemy::~Enemy()
{
}


/******************************************************************************/
/*!
\brief
Collision Detection with map
\exception None
\return None
*/
/******************************************************************************/
bool Enemy::Quick_check()
{
	string line;
	ifstream myfile("Map//Map1.txt");
	if (myfile.is_open())
	{
		char Map[20][20];
		for (int i = 0; i < 20; i++)
		{
			getline(myfile, line);
			for (int j = 0; j < 20; j++)
			{
				Map[i][j] = line.at(j);
			}
		}
		myfile.close();

		bool check = true;
		int X = 10 + ((this->position.x - -100) / 15);
		int Z = 10 + ((this->position.z - 0) / 15);
		if (X > -1 && X < 20 && Z > -1 && Z < 20)
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

			if (char(Map[X][Z]) != char(' ') && char(Map[X][Z]) != char('D'))
			{
				check = false;
			}
		}
		return check;
	}
	else
	{
		cout << "Unable To Open Map" << endl;
		return false;
	}
}

/******************************************************************************/
/*!
\brief
Changing mode for the enemy
\exception None
\return None
*/
/******************************************************************************/
void Enemy::mode_Change()
{
	if (this->HP >= 90)
	{
		this->Current_modetype = rand() % 3;
	}
	else if (this->HP > 50)
	{
		this->Current_modetype = rand() % 3 + 3;
	}
	else
	{
		this->Current_modetype = rand() % 3 + 6;
	}
}


/******************************************************************************/
/*!
\brief
Reducing enemy hp based on attack
\exception None
\return None
*/
/******************************************************************************/
void Enemy::DamageReceived(int Damage)
{
	this->HP -= Damage;
	if (this->HP < 0)
	{
		this->HP = 100;
		float X = (-8 * 15) + rand() % (16 * 15) - 100;
		float Z = (-8 * 15) + rand() % (16 * 15);
		position = Ground = SpawnPoint = { X, 0, Z };
		if (!Quick_check())
		{
			X = (-8 * 15) + rand() % (16 * 15) - 100;
			Z = (-8 * 15) + rand() % (16 * 15);
			position = Ground = SpawnPoint = { X, 0, Z };
		}
	}
	mode_Change();
}


/******************************************************************************/
/*!
\brief
carrying out action decided by the enemy mode
\exception None
\return None
*/
/******************************************************************************/
void Enemy::mode_Action(Position Camera)
{
	int mode = this->Current_modetype;
	Position Target_To_Move_To = { 0, 0, 0 };
	if (mode < 3)
	{
		if (mode == patrol)
		{
			int Angle = rand() % 360;
			if (Angle != 90 && Angle != 270)
			{
				Target_To_Move_To.x = this->SpawnPoint.x + 10 *cos(Math::DegreeToRadian(Angle));
			}
			if (Angle != 0 && Angle != 180)
			{
				Target_To_Move_To.z = this->SpawnPoint.z + 10 *sin(Math::DegreeToRadian(Angle));
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
				Target_To_Move_To.x = this->Ground.x + 10 *cos(Math::DegreeToRadian(Angle));
			}
			if (Angle != 0 && Angle != 180)
			{
				Target_To_Move_To.z = this->Ground.z + 10 *sin(Math::DegreeToRadian(Angle));
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
				Target_To_Move_To.x = this->Ground.x + 20 * cos(Math::DegreeToRadian(Angle));
			}
			if (Angle != 0 && Angle != 180)
			{
				Target_To_Move_To.z = this->Ground.z + 20 * sin(Math::DegreeToRadian(Angle));
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
				Target_To_Move_To.x = this->SpawnPoint.x + 10 *cos(Math::DegreeToRadian(Angle));
			}
			if (Angle != 0 && Angle != 180)
			{
				Target_To_Move_To.z = this->SpawnPoint.z + 10 *sin(Math::DegreeToRadian(Angle));
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
				Target_To_Move_To.z = this->Ground.z + 5 * sin(Math::DegreeToRadian(Angle));
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
	this->Ground = Target_To_Move_To;
}


/******************************************************************************/
/*!
\brief
Return enemy position
\exception None
\return None
*/
/******************************************************************************/
Position Enemy::Return_Position()
{
	return this->position;
}


/******************************************************************************/
/*!
\brief
Return enemy HP
\exception None
\return None
*/
/******************************************************************************/
int Enemy::Return_HP()
{
	return this->HP;
}


/******************************************************************************/
/*!
\brief
Deciding enemy speed based on their mode
\exception None
\return None
*/
/******************************************************************************/
void Enemy::Enemy_movement(Position Camera, float dt, float Size, char Map[20][20], Enemy enemy[5], int I, float Z_Displacement, float X_Displacement)
{
	mode_Action(Camera);
	float speed = 0.5 * dt;
	if (this->Current_modetype == speed_escape || this->Current_modetype == fake_attack)
	{
		speed = 1 * dt;
	}
	else if (this->Current_modetype == charge || this->Current_modetype == Surprise_attack)
	{
		speed = 1.5 * dt;
	}
	this->position = Movement(this->position, this->Ground, speed, Size, Map, I,enemy, Z_Displacement, X_Displacement);

}


/******************************************************************************/
/*!
\brief
Updating the enemy position based on their action and speed
\exception None
\return None
*/
/******************************************************************************/
Position  Enemy::Movement(Position Current, Position Target, float Speed, float Size, char Map[20][20], int I, Enemy enemy[5], float Z_Displacement, float X_Displacement)
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


/******************************************************************************/
/*!
\brief
Full Collision Detection for enemy and player
\exception None
\return None
*/
/******************************************************************************/
bool Enemy::Collision_Detection(Position Character, float Size, char Map[20][20], Enemy enemy[5], int I, float Z_Displacement, float X_Displacement, bool enter)
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


/******************************************************************************/
/*!
\brief
Full Collision Detection for enemy and enemy
\exception None
\return None
*/
/******************************************************************************/
bool Enemy::Enemy_Collision(Position Character, Enemy enemy[5], int I)
{
	bool check = true;
	if (I != 9)
	{
		for (int i = I + 1; i < 5; i++)
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


/******************************************************************************/
/*!
\brief
Detecting if player is within range for enemy to attack
\exception None
\return None
*/
/******************************************************************************/
bool Enemy::enemy_attack(Enemy enemy[5], Position character, Camera3 view)
{
	int attack = false;
	for (int i = 0; i < 5; i++)
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
		if (X_distance < 15 && Z_distance < 15)
		{
			attack = true;
		}
	}
	return attack;
}