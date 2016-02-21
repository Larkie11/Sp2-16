#include "Mouse.h"
#include "Camera3.h"
Mouse::Mouse() :mouseSensitivity(100)
{
	boundaryCheckX = GetSystemMetrics(SM_CXSCREEN) - 10;
	boundaryCheckY = GetSystemMetrics(SM_CYSCREEN) - 10;

	resetX = GetSystemMetrics(SM_CXSCREEN) / 2;
	resetY = GetSystemMetrics(SM_CYSCREEN) / 2;
}
Mouse::~Mouse()
{
}

void Mouse::AssignePointToVector(POINT point, Vector3 &vec)
{
	vec.x = point.x;
	vec.y = point.y;
}

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
		if (position_Vector.size() > 2)
		{
			//Mouse move Left
			if (position_Vector.at(0).x > position_Vector.at(1).x)
				camera.cameraRotate.y += (float)(mouseSensitivity * dt);
			//Mouse move Right
			else if (position_Vector.at(0).x < position_Vector.at(1).x)
				camera.cameraRotate.y -= (float)(mouseSensitivity * dt);
			//Mouse move Down
			else if (position_Vector.at(0).y > position_Vector.at(1).y)
				camera.cameraRotate.x -= (float)(mouseSensitivity * dt);
			//Mouse move Up
			else if (position_Vector.at(0).y < position_Vector.at(1).y)
				camera.cameraRotate.x += (float)(mouseSensitivity * dt);

			position_Vector.at(0) = position_Vector.at(1);



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
