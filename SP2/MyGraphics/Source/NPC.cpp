#include "NPC.h"
#include "SharedData.h"

NPC::NPC()
{

}

NPC::~NPC()
{

}
void NPC::Door(Camera3 camera, double dt)
{
	if (coolDownTime > 0)
	{
		coolDownTime -= (float)(1 * dt);
	}
	else
	{
		coolDownTime = 0;
	}

	//cout << camera.view.Dot(robot1.Nposition) << endl;
	//If player is on the outside of the pyramid
	if (camera.position.x > door.Nposition.x)
	{
		door.negativeDotProduct = true;
	}
	//If player is on the inside of the pyramid
	if (camera.position.x < door.Nposition.x)
	{
		door.negativeDotProduct = false;
	}
	//This is to check if player is near to the door and facing the door using dot product
	//Since a door has 2 side, the character view dot product door will have both negative and positive, so we have to handle both cases
	if (detectCollision.collideByDist(camera.position, door.Nposition) <= 25)
	{
		//Check if the player is outside the temple and facing door to the inside
		if (door.negativeDotProduct == true && camera.view.Dot(door.Nposition) < 0)
		{
			interactDia = "Press E to open the door";
			//Show player press e to interact
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
void NPC::Scene1(Camera3 camera, double dt)
{
	if (detectCollision.collideByDist(camera.position, robot1.Nposition) <= 25)
	{
		if (camera.view.Dot(robot1.Nposition) > 0)
			{
				interactDia = "Press E to interact and 1 and 2 for choices";
				//Show player press e to interact
				robot1.canInteract = true;
				if (Application::IsKeyPressed('E') && coolDownTime == 0)
				{
					dialogue = 0;
					coolDownTime = dt;
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
		if (Application::IsKeyPressed('E') && coolDownTime == 0)
		{
			coolDownTime = dt / 5;
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

			if (Application::IsKeyPressed('E'))
			{
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
		dialoguePlus = 6;
		robot3.canInteract = false;
		robot3.robot = "";
	}

}
void NPC::Scene2(Camera3 camera, double dt)
{
	if (detectCollision.collideByDist(camera.position, robot1.Nposition) <= 25)
	{
		if (camera.view.Dot(robot1.Nposition) < 0)
		{
			interactDia = "Press E to interact and 1 and 2 for choices";
			//Show player press e to interact
			robot1.canInteract = true;
			if (Application::IsKeyPressed('E') && coolDownTime == 0)
			{
				dialogue = 0;
				coolDownTime = dt;
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
		if (Application::IsKeyPressed('E') && coolDownTime == 0)
		{
			coolDownTime = dt / 5;
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

			if (Application::IsKeyPressed('E'))
			{
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
		dialoguePlus = 6;
		robot3.canInteract = false;
		robot3.robot = "";
	}
}

void NPC::Shop(Camera3 camera)
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

}