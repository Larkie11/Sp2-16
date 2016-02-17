#ifndef Enemy_H
#define Enemy_H

#include "Vertex.h"

class Acid
{
public:
	Acid(){ position = { 0, 0, 0 }; direction = { 0, 0, 0 }; AcidDamage = 0; fired = false; };
	Position position;
	Position direction;
	float AcidDamage;
	bool fired;
};

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
	int Return_HP(Enemy Target);
	Acid ShootBullet(int bullet, Enemy Target, Position Camera);
	Position Movement(Position Current, Position Target,float Speed);

public:
	Enemy();
	~Enemy();
	Acid Bullet[10];
	Enemy Enemy_movement(Enemy Target, Position Camera, float dt);
	Enemy DamageReceived(Enemy Target, int Damage);
	Position Return_Position(Enemy Target);
	Position Return_Bullet_Position(int bullet, Enemy Target);
};

#endif
