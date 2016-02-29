#ifndef NPC_H
#define NPC_H

#include "Vector3.h"
#include "Application.h"
#include "Camera3.h"
#include "CollisionDetector.h"
#include "Sound.h"
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
	DOT seller;
	DOT spaceDoor;
	DOT spaceShip;
	DOT egg1;
	DOT egg2;
	DOT egg3;
	DOT egg4;
	DOT egg5;
	DOT bomb;

	CollisionDetector detectCollision;
	string interactDia;
	int dialoguePlus = 6;
	double coolDownTime;
	int dialogue;
	bool moveFront;
	bool moveBack;
	bool robot3rotate;
	bool robot1moved;
	bool stopMusic;
	Sound sound;
	void Scene1(Camera3 camera, double dt);
	void Scene2(Camera3 camera, double dt);
	void Door(Camera3 camera, double dt);
	void Shop(Camera3 camera, double dt);
	void NPCmovement(double dt, float& targetMovement);
	void NPCmovement2(double dt, float& targetMovement);
	NPC();
	~NPC();
};

#endif