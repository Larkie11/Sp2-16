/******************************************************************************/
/*!
\file	Camera3.cpp
\author Mok Wei Min, Yap Heng Soon, Oh Zhan Wei, Francis Wong
\par	email: 155208U\@mymail.nyp.edu.sg
\brief
Player's camera and bounds
*/
/******************************************************************************/
#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"
#include "MyMath.h"
#include "SharedData.h"
/******************************************************************************/
/*!
\brief
Default constructor

\exception None
\return None
*/
/******************************************************************************/
Camera3::Camera3()
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
Camera3::~Camera3()
{
}
/******************************************************************************/
/*!
\brief
Initializes player camera

\param pos
Passes in camera position to initialize 
\param target
Camera target to initialize
\param up
Camera up to initialize

\exception None
\return None
*/
/******************************************************************************/
void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	maxCameraX = 49.99f;
	cameraSpeed = 100.f;
	maxX = 500;
	minX = -500;
	maxZ = 500;
	minZ = -500;

	if (SharedData::GetInstance()->gameState == SharedData::SHOP)
	{
		maxX = -11;
		minX = -85;
		maxZ = 48;
		minZ = -44;
	}

	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
}
/******************************************************************************/
/*!
\brief
Updates camera every scene

\param dt
Updates camera based on delta time

\exception None
\return None
*/
/******************************************************************************/
void Camera3::Update(double dt)
{
	if (Application::IsKeyPressed('R'))
	{
		Reset();
	}

	//Changing view (target)
	if (Application::IsKeyPressed(VK_LEFT))
	{
		cameraRotate.y += (float)(100 * dt);
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		cameraRotate.y -= (float)(100 * dt);
	}
	if (Application::IsKeyPressed(VK_UP))
	{
		cameraRotate.x -= (float)(100 * dt);
	}
	if (Application::IsKeyPressed(VK_DOWN))
	{
		cameraRotate.x += (float)(100 * dt);
	}
	if (Application::IsKeyPressed('N'))
	{
		position.y -= 1;
	}
	if (Application::IsKeyPressed('M'))
	{
		position.y += 1;
	}
	//Bounds checking based on maximum and minimum
	if (position.x > maxX)
	{
		position.x = maxX;
	}
	if (position.x < minX)
	{
		position.x = minX;
	}
	if (position.z > maxZ)
	{
		position.z = maxZ;
	}
	if (position.z < minZ)
	{
		position.z = minZ;
	}

	if (Application::IsKeyPressed('W'))
	{
		position.x += sin(DegreeToRadian(cameraRotate.y)) * cameraSpeed*dt;
		position.z += cos(DegreeToRadian(cameraRotate.y)) * cameraSpeed *dt;
	}

	if (Application::IsKeyPressed('S'))
	{
		position.x += sin(DegreeToRadian(cameraRotate.y + 180)) * cameraSpeed *dt;
		position.z += cos(DegreeToRadian(cameraRotate.y + 180)) * cameraSpeed *dt;
	}

	if (Application::IsKeyPressed('A'))
	{
		position.x += sin(DegreeToRadian(cameraRotate.y + 90)) * cameraSpeed *dt;
		position.z += cos(DegreeToRadian(cameraRotate.y + 90)) * cameraSpeed *dt;
	}

	if (Application::IsKeyPressed('D'))
	{
		position.x += sin(DegreeToRadian(cameraRotate.y + 270)) * cameraSpeed *dt;
		position.z += cos(DegreeToRadian(cameraRotate.y + 270)) * cameraSpeed *dt;
	}

	if (SharedData::GetInstance()->gameState != SharedData::CUTSCENE)
	{
		//Only allow rotating to look 90 degrees up and 90 degrees down
		if (cameraRotate.x > maxCameraX)
		{
			cameraRotate.x = maxCameraX;
		}

		else if (cameraRotate.x < -maxCameraX)
		{
			cameraRotate.x = -maxCameraX;
		}
	}

	//Changing target
	target = Vector3(sin(DegreeToRadian(cameraRotate.y))*cos(DegreeToRadian(cameraRotate.x)) + this->position.x, -sin(DegreeToRadian(cameraRotate.x)) + this->position.y,
		cos(DegreeToRadian(cameraRotate.y))*cos(DegreeToRadian(cameraRotate.x)) + this->position.z);
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(defaultUp);
	right.y = 0;
	up = right.Cross(view);
}
/******************************************************************************/
/*!
\brief
Resets camera when needed

\exception None
\return None
*/
/******************************************************************************/
void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}