#ifndef NPC_H
#define NPC_H

#include "Vector3.h"
#include "Application.h"
#include "Camera3.h"
#include "CollisionDetector.h"

#include <string>
using std::string;

class NPC
{
	struct DOT
	{
		bool negativeDotProduct;
		bool canInteract;
		bool canGoThrough;
		bool Collision;
		Vector3 Nposition;
		string robot;
	};

public:

	DOT door;
	DOT robot1;
	DOT robot2;
	DOT robot3;
	DOT spacebody;
	DOT spacewing;
	DOT spacerocket;

	CollisionDetector detectCollision;
	string interactDia;
	int dialoguePlus = 6;
	double coolDownTime;
	int dialogue;
	
	void Update(Camera3 camera, double dt);
	NPC();
	~NPC();
};

#endif