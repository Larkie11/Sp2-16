/****************************************************************************** /
/*!
\file	Camera3.h
\author Mok Wei Min, Yap Heng Soon, Oh Zhan Wei, Francis Wong
\par
\brief
Player's camera
*/
/******************************************************************************/
#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"
#include "MyMath.h"

using Math::DegreeToRadian;

/******************************************************************************/
/*!
Class Camera3:
\brief	Shop enums/Menu enums
*/
/******************************************************************************/
class Camera3 : public Camera
{
public:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 cameraRotate;
	Vector3 view;

	Camera3();
	~Camera3();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();

	float maxCameraX;
	float cameraSpeed;
	float maxX;
	float minX;
	float maxZ;
	float minZ;
};

#endif