/******************************************************************************/
/*!
\file	Npc.cpp
\author Mok Wei Min
\par	email: 155208U\@mymail.nyp.edu.sg
\brief
Checks if player is near and then show and allow the player to do something
*/
/******************************************************************************/
#include "NPC.h"
#include "SharedData.h"

/******************************************************************************/
/*!
\brief
Default constructor 

\exception None
\return None
*/
/******************************************************************************/
NPC::NPC()
{
}
/******************************************************************************/
/*!
\brief
Default destructor 

\exception None
\return None
*/
/******************************************************************************/
NPC::~NPC()
{
}
/******************************************************************************/
/*!
\brief
Function that checks for door animation and collision

\param camera
Takes in player camera position to check if the player is near
\param dt
Delta time for game update

\exception None
\return None
*/
/******************************************************************************/
void NPC::Door(Camera3 camera, double dt)
{
	if (camera.position.x > door.Nposition.x)
	{
		door.negativeDotProduct = true;
	}
	if (camera.position.x < door.Nposition.x)
	{
		door.negativeDotProduct = false;
	}
	if (detectCollision.collideByDist(camera.position, door.Nposition) <= 25)
	{
		//Check if the player is outside the temple and facing door to the inside
		if (door.negativeDotProduct == true && camera.view.Dot(door.Nposition) < 0)
		{
			interactDia = "Press E to open the door";
			door.canInteract = true;
			if (Application::IsKeyPressed('E'))
			{
				door.canGoThrough = true;
			}
		}
		//Update player if player turns away
		else if (door.negativeDotProduct == true && camera.view.Dot(door.Nposition) > 0)
		{
			door.canInteract = false;
			door.canGoThrough = false;
		}
		//Check if player is inside the temple and facing door to the outside
		if (door.negativeDotProduct == false && camera.view.Dot(door.Nposition) > 0)
		{
			door.canInteract = true;
			if (Application::IsKeyPressed('E'))
			{
				door.canGoThrough = true;
			}
		}
		//Update player if player turns away
		else if (door.negativeDotProduct == false && camera.view.Dot(door.Nposition) < 0)
		{
			door.canInteract = false;
			door.canGoThrough = false;
		}
	}
	else
	{
		//Dont show the press e to interact
		door.canInteract = false;
		door.canGoThrough = false;
		door.Collision = true;
	}
}
/******************************************************************************/
/*!
\brief
All NPC interaction and sound effects for NPC

\param camera
Takes in player camera position to check if the player is near
\param dt
Delta time for game update

\exception None
\return None
*/
/******************************************************************************/
void NPC::Scene1(Camera3 camera, double dt)
{
	if (detectCollision.collideByDist(camera.position, robot1.Nposition) <= 25)
	{
		if (camera.view.Dot(robot1.Nposition) > 0)
			{
				interactDia = "Press E to interact and 1 and 2 for choices";
				//Show player press e to interact
				robot1.canInteract = true;
				if (Application::IsKeyPressed('E') && robot1.robot != "robot1")
				{
					sound.playSE("Music//R2D2.mp3");
					coolDownTime = dt / 10;
					dialogue = 0;
					robot1.robot = "robot1";
				}
				if (robot1.robot == "robot1")
				{
					if (Application::IsKeyPressed('1'))
					{
						robot1.robot = "robot1.1";
					}
					if (Application::IsKeyPressed('2'))
					{
						robot1.robot = "robot1.2";
					}
				}
			}

		else
		{
			robot1.canInteract = false;
		}
	}
	else
	{
		robot1.canInteract = false;
		robot1.robot = "";
	}
	if (detectCollision.collideByDist(camera.position, robot2.Nposition) <= 25)
	{
		interactDia = "Press E to interact";
		robot2.canInteract = true;
		if (Application::IsKeyPressed('E') && robot2.robot != "robot2")
		{
			sound.playSE("Music//Dead.mp3");
			robot2.robot = "robot2";
		}
	}
	else
	{
		robot2.canInteract = false;
		robot2.robot = "";
	}
	if (detectCollision.collideByDist(camera.position, robot3.Nposition) <= 25)
	{
		if (camera.view.Dot(robot3.Nposition) > 0)
		{
			//Show player press e to interact
			robot3.canInteract = true;
			interactDia = "Press E to interact";

			if (Application::IsKeyPressed('E') && robot3.robot!= "robot3")
			{
				sound.playSE("Music//R2D2.mp3");
				robot3.robot = "robot3";
			}
		}
		else
		{
			robot3.canInteract = false;
		}
	}
	else
	{
		dialoguePlus = 5;
		robot3.canInteract = false;
		robot3.robot = "";
	}

}
/******************************************************************************/
/*!
\brief
Checks if player is near to the shop, and then allow certain interactions to happen (Like show shop screen, etc)

\param camera
Takes in player camera position to check if the player is near
\param dt
Delta time for game update

\exception None
\return None
*/
/******************************************************************************/
void NPC::Shop(Camera3 camera, double dt)
{
	if (detectCollision.collideByDist(camera.position, seller.Nposition) <= 35)
	{
			interactDia = "Press E browse shop";
			seller.canInteract = true;
	}
	else
	{
		seller.canInteract = false;
	}

	if (detectCollision.collideByDist(camera.position, spaceDoor.Nposition.x) <= 20)
	{
		spaceDoor.canInteract = true;
		interactDia = "Press E to open door and exit";
		if (spaceDoor.Nposition.z < 40 && Application::IsKeyPressed('E'))
		{
			
			spaceDoor.Nposition.z += (float)(60 * dt);

			if (spaceDoor.Nposition.z >= 40)
			{
				if (SharedData::GetInstance()->gameScene == "Scene2" && SharedData::GetInstance()->bomb.quantity <= 0)
				{
					stopMusic = true;
					sound.playSE("Music//Fly.mp3");
					interactDia = "Flying back to land...";
					SharedData::GetInstance()->stateCheck = true;
					SharedData::GetInstance()->gameState = SharedData::SCENE2;
				}
				else if (SharedData::GetInstance()->bomb.quantity >= 0)
				{
					stopMusic = true;
					interactDia = "Loading...";
					SharedData::GetInstance()->stateCheck = true;
					SharedData::GetInstance()->gameState = SharedData::SCENE3;
				}
				else if (SharedData::GetInstance()->gameScene == "Scene3")
				{
					stopMusic = true;
					sound.playSE("Music//Fly.mp3");
					interactDia = "Loading...";
					SharedData::GetInstance()->stateCheck = true;
					SharedData::GetInstance()->gameState = SharedData::SCENE3;
				}
			}
		}
	}

	else if (detectCollision.collideByDist(camera.position, spaceDoor.Nposition.x) >= 20)
	{
		spaceDoor.canInteract = false;

		if (spaceDoor.Nposition.z  > 0)
		{
			stopMusic = false;
			spaceDoor.Nposition.z -= (float)(30 * dt);
		}
	}
}
/******************************************************************************/
/*!
\brief
NPC head rotation

\param dt
Delta time for game update
\param targetMovement
Float to edit for the head movement (rotation float)

\exception None
\return None
*/
/******************************************************************************/
void NPC::NPCmovement(double dt, float& targetMovement)
{
	if (robot3rotate == false)
	{
		targetMovement += (float)(20 * dt);

		if (targetMovement >= 80)
		{
			robot3rotate = true;
		}
	}
	if (robot3rotate)
	{
		targetMovement -= (float)(20 * dt);

		if (targetMovement <= -80)
		{
			robot3rotate = false;
		}
	}
}
/******************************************************************************/
/*!
\brief
NPC move backwards and forwards

\param dt
Delta time for game update

\param targetMovement
Float to edit for the npc movement

\exception None
\return None
*/
/******************************************************************************/
void NPC::NPCmovement2(double dt, float& targetMovement)
{
	if (robot1moved == false)
	{
		targetMovement += (float)(10 * dt);

		if (targetMovement >= -100)
		{
			robot1moved = true;
		}
	}

	if (robot1moved)
	{
		targetMovement -= (float)(10 * dt);

		if (targetMovement <= -160)
		{
			robot1moved = false;
		}
	}
}
