#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"
#include "MyMath.h"

using Math::DegreeToRadian;

class Camera3 : public Camera
{
public:
	//Vector3 position;
	//Vector3 target;
	//Vector3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 cameraRotate;

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
	bool door = false;
};

#endif