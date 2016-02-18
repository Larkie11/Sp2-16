#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"
#include "MyMath.h"

Camera3::Camera3()
{

}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	maxCameraX = 49.99f;
	cameraSpeed = 150.f;
	maxX = 275;
	minX = -300;
	maxZ = 275;
	minZ = -300;

	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();

	//Default camera rotation
	cameraRotate = Vector3(0, -270, 0);

}

void Camera3::Update(double dt)
{
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}