#ifndef LAB5B_H
#define LAB5B_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"

class Lab5b : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		GEO_TRIANGLE_2,
		GEO_REF_AXES,
		GEO_REF_QUAD,
		GEO_REF_CUBE,
		GEO_REF_BODY,
		GEO_REF_ARM,
		GEO_REF_CIRCLE,
		GEO_REF_CIRCLE1,
		GEO_REF_HEM,
		GEO_REF_SPHERE,
		GEO_REF_SPHERE1,
		GEO_REF_PLANET,
		GEO_REF_PLANET1,
		GEO_REF_PLANET2,
		GEO_REF_PLANET3,
		GEO_REF_PLANET4,
		GEO_REF_MOON,
		GEO_REF_SUN,
		GEO_REF_RING,
		GEO_REF_RING1,
		GEO_REF_RING2,
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};

public:
	Lab5b();
	~Lab5b();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	void RenderLimb();
	void RenderBody();
	void RenderHead();
	void RenderRobot();
	unsigned m_vertexArrayID;
	unsigned m_indexBuffer[NUM_GEOMETRY];
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Camera2 camera;

	//Array of meshes
	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;
	float rotateAngle = 0;
	bool Rotate = true;

	float rotateAngle1 = 0;
	bool Rotate1 = false;

	float rotateAngle2 = 0;
	bool Rotate2 = true;

	float rotateAngle3 = 0;
	bool Rotate3 = false;
};
#endif