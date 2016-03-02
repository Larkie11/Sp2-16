/************************************************************/
/*!
\file	Mouse.h
\author	Heng Soon Yap
\par	email:Romeoyap\@hotmail.com
\brief
A class for the mouse the player using to define them in the game
*/
/************************************************************/

#ifndef MOUSE_H
#define MOUSE_H
#include "Camera3.h"
#include <Windows.h>
#include <winuser.h>
#include <iostream>
#include <iomanip>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

/************************************************************/
/*!
Class Dweller:
\brief	Defines a player's mouse attribute and its methods
*/
/************************************************************/

class Mouse
{
public:
	//Mouse setting
	int mouseSensitivity;
	int resetX, resetY;
	LONG boundaryCheckX;
	LONG boundaryCheckY;
	Vector3 pos;
	vector<Vector3>position_Vector;

	Mouse();
	~Mouse();
	void AssignePointToVector(POINT point, Vector3 &vec);
	void MouseUpdate(double dt, Camera3 &camera);
	void MouseUpdate(double dt, Camera3 &camera, float& followx, float& followy);
	void Callback();
};
#endif

