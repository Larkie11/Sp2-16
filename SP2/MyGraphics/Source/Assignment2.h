#ifndef ASSIGNMENT2_H
#define ASSIGNMENT2_H

#include "Scene.h"
#include "Mtx44.h"
//#include "Camera.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Material.h"

class Assignment2 : public Scene
{

	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		GEO_TRIANGLE_2,
		GEO_REF_AXES,
		GEO_REF_QUAD,
		
		GEO_REF_CIRCLE,
		GEO_REF_SPHERE,
		GEO_REF_HEM,

		//Tree
		GEO_REF_CUBE,
		GEO_REF_TCONE,

		//Head
		GEO_REF_EYES,
		GEO_REF_MOUTH,


		//Body
		GEO_REF_BSPHERE,
		GEO_REF_CYL,
		GEO_REF_CONE,
		GEO_REF_BCONE,
		GEO_REF_WCIRCLE,
		GEO_REF_WQUAD,
		GEO_REF_ASPHERE,

		//Arms
		GEO_REF_GUARD,
		GEO_REF_ACYL,
		GEO_REF_JSPHERE,
		GEO_REF_ACYL2,
		GEO_REF_AARM,

		//Legs
		GEO_REF_LSPHERE,
		GEO_REF_LCYL,
		GEO_REF_LCYL1,
		GEO_REF_LCYL2,
		GEO_REF_LHEM,
		GEO_REF_LCONE,
		GEO_REF_LJOINT,
		GEO_REF_ALEG,

		//Item Toolbox
		GEO_REF_TOP,
		GEO_REF_BOTTOM,

		//Sphere
		GEO_REF_SPHERE1,

		//Flying effect
		GEO_REF_FSPHERE,
		GEO_REF_FCONE,

		GEO_REF_RING,
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
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_NUMLIGHTS,
		U_TOTAL,
	};

public:
	Assignment2();
	~Assignment2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	void RenderABaymax();


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
	void RenderFloor();
	void RenderTrees();
	void RenderBody();
	void RenderArm();
	void RenderLowerArm();
	void RenderLeg();
	void RenderLowerLeg();
	void RenderFace();
	void RenderFlyEffect();
	void ItemBox();

	float angle;
	float wing;
	float wingx;
	float fly;
	float flyScale;
	
	struct Pos
	{
		float x;
		float y;
	};
	Pos position;
	Light light[1]; //shader max 8 lights

	float eyeSize;
	bool eyes;
	float rotateArm;
	float rotateArmB;
	float rotateLeg;
	float sphere;
	bool showsphere;
	bool baymaxA;
	bool baymaxB;
	bool rotate;
	bool rotateleg;
};
#endif