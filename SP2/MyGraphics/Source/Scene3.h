#ifndef SCENE_3_H
#define SCENE_3_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera.h"
#include "Mesh.h"
#include "MatrixStack.h"

class Scene3 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		GEO_TRIANGLE_2,
		GEO_REF_AXES,
		GEO_REF_QUAD,
		GEO_REF_CUBE,
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
	Scene3();
	~Scene3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	unsigned m_vertexArrayID;
	unsigned m_indexBuffer[NUM_GEOMETRY];
	unsigned m_vertexBuffer[NUM_GEOMETRY]; 
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Camera camera;

	//Array of meshes
	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;
	float rotateAngle = 0;
	float rotatePlanet = 0;
	float rotateSun = 0;
	float rotateMoon = 0;
	float rotatePlanet1 = 0;
	float rotatePlanet2 = -180;
	float rotatePlanet3 = -90;
	float rotatePlanet4 = 0;
};
#endif