#ifndef Enemy_H
#define Enemy_H

#include "Vertex.h"

class Enemy
{
	float HP;
	float MeleeDamage;
	signed int Current_modetype;
	Position position;
	Position Ground;
	Position SpawnPoint;

	enum ModeType
	{
		//normal mode
		patrol,
		assassination,
		explore,
		//Retreat mode
		fake_attack,
		hold_down,
		speed_escape,
		//Defence mode
		Surprise_attack,
		strategic_planning,
		charge,

	};

	Enemy mode_Action(Enemy Target,Position Camera);
	int mode_Change(Enemy Target);
	Position Movement(Position Current, Position Target, float Speed, float Size, char Map[20][20], int I, Enemy enemy[10], float Z_Displacement, float X_Displacement);
	bool Enemy_Collision(Position Character, Enemy enemy[10], int I);

public:
	Enemy();
	~Enemy();
	int Return_HP(Enemy Target);
	Enemy Enemy_movement(Enemy Target, Position Camera, float dt, float Size, char Map[20][20], Enemy enemy[10], int I, float Z_Displacement, float X_Displacement);
	Enemy DamageReceived(Enemy Target, int Damage);
	Position Return_Position(Enemy Target);
	bool Collision_Detection(Position Character, float Size, char Map[20][20], Enemy enemy[10], int I, float Z_Displacement, float X_Displacement, bool enter = false);
};

#endif
