#ifndef Enemy_H
#define Enemy_H

#include "Vertex.h"
#include "Camera3.h"

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
	Position Movement(Position Current, Position Target, float Speed, float Size, char Map[20][20], int I, Enemy enemy[], float Z_Displacement, float X_Displacement,int enemy_size);
	bool Enemy_Collision(Position Character, Enemy enemy[], int I, int enemy_size);

public:
	Enemy();
	~Enemy();
	int Return_HP(Enemy Target);
	Enemy Enemy_movement(Enemy Target, Position Camera, float dt, float Size, char Map[20][20], Enemy enemy[], int I, float Z_Displacement, float X_Displacement, int enemy_size);
	Enemy DamageReceived(Enemy Target, int Damage);
	Position Return_Position(Enemy Target);
	bool Collision_Detection(Position Character, float Size, char Map[20][20], Enemy enemy[], int I, float Z_Displacement, float X_Displacement, int enemy_size, bool enter = false);
	Camera3 enemy_attack(Enemy enemy[], Position character, Camera3 view, int enemy_size);
};

#endif
