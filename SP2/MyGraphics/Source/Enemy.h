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
	Position Movement(Position Current, Position Target,float Speed);

public:
	Enemy();
	~Enemy();
	int Return_HP(Enemy Target);
	Enemy Enemy_movement(Enemy Target, Position Camera, float dt);
	Enemy DamageReceived(Enemy Target, int Damage);
	Position Return_Position(Enemy Target);
};

#endif
