/************************************************************/
/*!
\file	Mouse.cpp
\author	Heng Soon Yap
\par	email:Romeoyap\@hotmail.com
\brief
A Class for the Mouse for the user to use in the game
*/
/************************************************************/

#include "Mouse.h"
#include "Camera3.h"

/************************************************************/
/*!

\brief
	Mouse() is a constructor for Mouse class, where I
	set the default values needed for the methods.

*/
/************************************************************/

Mouse::Mouse() :mouseSensitivity(48)
{
	boundaryCheckX = GetSystemMetrics(SM_CXSCREEN) - 10;
	boundaryCheckY = GetSystemMetrics(SM_CYSCREEN) - 10;

	resetX = GetSystemMetrics(SM_CXSCREEN) / 2;
	resetY = GetSystemMetrics(SM_CYSCREEN) / 2;
}

/************************************************************/
/*!

\brief
	~Mouse() is a destructor for Mouse class.

*/
/************************************************************/

Mouse::~Mouse()
{
}

/************************************************************/
/*!

\brief
	AssignePointToVector(POINT point, Vector3 &vec),
	is a convertor function for Mouse class, where I convert 
	the POINT values into a vector value

\param point
	A Point values that need to be convert to Vector3.

\param vec
	A Vector3 that stores the point value after converting


*/
/************************************************************/

void Mouse::AssignePointToVector(POINT point, Vector3 &vec)
{
	vec.x = point.x;
	vec.y = point.y;
}

/************************************************************/
/*!

\brief
	MouseUpdate(double dt, Camera3 &camera, float& followx, float& followy)
	is a update function for Mouse class, where I update the position values 
	for the mouse cursor.

\param dt
	A double dt that represent the delta time in update.

\param camera
	A camera class for the update, to update the camera rotation according to
	the mouse position movement.

\param followx
	A float that represent the weapon's position x on screen where the player
	holds it.

\param followy
	A float that represent the weapon's position y on screen where the player
	holds it.
*/
/************************************************************/

void Mouse::MouseUpdate(double dt, Camera3 &camera, float& followx, float& followy)
{
	//Mouse Movement
	POINT mousePos;
	GetCursorPos(&mousePos);
	AssignePointToVector(mousePos, pos);
	position_Vector.push_back(pos);

	for (vector<Vector3>::iterator iter = position_Vector.begin(); iter != position_Vector.end();)
	{
		//Check if there is a 3rd vector pushed in , vector size start count from 0
		if (position_Vector.size() > 6)
		{
			for (int i = 0; i < 5; ++i)
			{
				if (position_Vector.at(i).x > position_Vector.at(i+1).x)
				{
					camera.cameraRotate.y += (float)(mouseSensitivity * dt);
					followy += (float)(mouseSensitivity * dt);
				}

				if (position_Vector.at(i).x < position_Vector.at(i+1).x)
				{
					camera.cameraRotate.y -= (float)(mouseSensitivity * dt);
					followy -= (float)(mouseSensitivity * dt);
				}

				if (position_Vector.at(i).y > position_Vector.at(i+1).y)
				{
					camera.cameraRotate.x -= (float)(mouseSensitivity/2 * dt);
					followx += (float)(mouseSensitivity/2 * dt);
				}

				if (position_Vector.at(i).y < position_Vector.at(i+1).y)
				{
					camera.cameraRotate.x += (float)(mouseSensitivity/2 * dt);
					followx -= (float)(mouseSensitivity/2 * dt);
				}
				position_Vector.at(i) = position_Vector.at(i+1);
			}
			iter = position_Vector.erase(iter);
		}
		iter++;
	}
	if (mousePos.x > boundaryCheckX ||
		mousePos.y > boundaryCheckY ||
		mousePos.x < 1 ||
		mousePos.y < 1)
		SetCursorPos(resetX, resetY);


}

/************************************************************/
/*!

\brief
	MouseUpdate(double dt, Camera3 &camera) is a overloaded update 
	function for Mouse class, where I update the position values
	for the mouse cursor.

\param dt
	A double dt that represent the delta time in update.

\param camera
	A camera class for the update, to update the camera rotation according to
	the mouse position movement.
*/
/************************************************************/

void Mouse::MouseUpdate(double dt, Camera3 &camera)
{
	//Mouse Movement
	POINT mousePos;
	GetCursorPos(&mousePos);
	AssignePointToVector(mousePos, pos);
	position_Vector.push_back(pos);

	for (vector<Vector3>::iterator iter = position_Vector.begin(); iter != position_Vector.end();)
	{
		//Check if there is a 3rd vector pushed in , vector size start count from 0
		if (position_Vector.size() > 6)
		{
			for (int i = 0; i < 5; ++i)
			{
				if (position_Vector.at(i).x > position_Vector.at(i + 1).x)
				{
					camera.cameraRotate.y += (float)(mouseSensitivity * dt);
				}

				if (position_Vector.at(i).x < position_Vector.at(i + 1).x)
				{
					camera.cameraRotate.y -= (float)(mouseSensitivity * dt);
				}

				if (position_Vector.at(i).y > position_Vector.at(i + 1).y)
				{
					camera.cameraRotate.x -= (float)(mouseSensitivity / 2 * dt);
				}

				if (position_Vector.at(i).y < position_Vector.at(i + 1).y)
				{
					camera.cameraRotate.x += (float)(mouseSensitivity / 2 * dt);
				}
				position_Vector.at(i) = position_Vector.at(i + 1);
			}
			iter = position_Vector.erase(iter);
		}
		iter++;
	}
	if (mousePos.x > boundaryCheckX ||
		mousePos.y > boundaryCheckY ||
		mousePos.x < 1 ||
		mousePos.y < 1)
		SetCursorPos(resetX, resetY);


}
