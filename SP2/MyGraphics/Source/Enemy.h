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

	void mode_Action(Position Camera);
	void mode_Change();
	Position Movement(Position Current, Position Target, float Speed, float Size, char Map[20][20], int I, Enemy enemy[5], float Z_Displacement, float X_Displacement);
	bool Enemy_Collision(Position Character, Enemy enemy[5], int I);

public:
	Enemy();
	~Enemy();
	bool Quick_check();
	int Return_HP();
	void Enemy_movement(Position Camera, float dt, float Size, char Map[20][20], Enemy enemy[5], int I, float Z_Displacement, float X_Displacement);
	void DamageReceived(int Damage);
	Position Return_Position();
	bool Collision_Detection(Position Character, float Size, char Map[20][20], Enemy enemy[5], int I, float Z_Displacement, float X_Displacement, bool enter = false);
	Camera3 enemy_attack(Enemy enemy[5], Position character, Camera3 view);
};

#endif
