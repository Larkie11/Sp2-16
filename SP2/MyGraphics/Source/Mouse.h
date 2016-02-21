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
};
#endif

