#ifndef SCENE_LIGHT_H
#define SCENE_LIGHT_H

#include "Scene.h"
#include "Mtx44.h"
//#include "Camera.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Material.h"

class SceneLight : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		GEO_TRIANGLE_2,
		GEO_REF_AXES,
		GEO_REF_QUAD,
		GEO_REF_CUBE,
		GEO_REF_CONE,
		GEO_REF_SPHERE,
		GEO_REF_SPHERE1,
		GEO_REF_SPHERE2,
		GEO_REF_SPHERE3,
		GEO_REF_SPHERE4,
		GEO_REF_SPHERE5,
		GEO_REF_SPHERE6,
		GEO_REF_SPHERE7,
		GEO_REF_SPHERE8,
		GEO_REF_CYL,
		//GEO_REF_CONE,
		GEO_LIGHTBALL,
		GEO_QUAD,
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION, //copy all the light parts for multiplie light
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_TOTAL,
	};

public:
	SceneLight();
	~SceneLight();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	void RenderMesh(Mesh *mesh, bool enableLight);

	unsigned m_vertexArrayID;
	unsigned m_indexBuffer[NUM_GEOMETRY];
	unsigned m_vertexBuffer[NUM_GEOMETRY]; 
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	//Camera camera;
	Camera2 camera;

	//Array of meshes
	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;
	float LSPEED = 10.f;

	Light light[1]; //shader max 8 lights
};
#endif