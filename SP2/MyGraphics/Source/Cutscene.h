#ifndef CUTSCENE_H
#define CUTSCENE_H

#include "MeshBuilder.h"
#include "Utility.h"
#include "Scene.h"
#include "Mtx44.h"
#include "MyMath.h"
#include "Light.h"
#include "Material.h"
#include "Sound.h"
#include "Application.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Mouse.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::string;

class Cutscene : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_REF_AXES = 0,
		GEO_REF_QUAD,
		GEO_LIGHTBALL,
		GEO_QUAD,
		
		GEO_BB8HEAD,
		GEO_BB8BODY,
		GEO_CROSSHAIR,

		GEO_THRUSTER,

		//Skybox
		GEO_LEFT1,
		GEO_RIGHT1,
		GEO_TOP1,
		GEO_BOTTOM1,
		GEO_FRONT1,
		GEO_BACK1,
		GEO_STAR,
		GEO_STORY1,
		GEO_TEXT,
		
		//Scene
		GEO_MOONBALL,
		GEO_PYRAMIDNEW,
		GEO_PYRAMIDWALL,
		GEO_PYRAMIDPILLAR,
		GEO_SPACESHIP,
		GEO_PLANEBODY,
		GEO_PLANEWING,
		GEO_PLANEROCKET,
		GEO_PYRAMIDFLOOR,
		GEO_PYRAMIDDOOR,

		GEO_EXPLOSION,
		GEO_BULLETSKIN,
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

		U_LIGHT1_POSITION, //copy all the light parts for multiplie light
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1ENABLED,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		U_LIGHT2_POSITION, //copy all the light parts for multiplie light
		U_LIGHT2_COLOR,
		U_LIGHT2_POWER,
		U_LIGHT2_KC,
		U_LIGHT2_KL,
		U_LIGHT2_KQ,
		U_LIGHT2ENABLED,
		U_LIGHT2_TYPE,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT2_COSINNER,
		U_LIGHT2_EXPONENT,

		U_LIGHT3_POSITION, //copy all the light parts for multiplie light
		U_LIGHT3_COLOR,
		U_LIGHT3_POWER,
		U_LIGHT3_KC,
		U_LIGHT3_KL,
		U_LIGHT3_KQ,
		U_LIGHT3ENABLED,
		U_LIGHT3_TYPE,
		U_LIGHT3_SPOTDIRECTION,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT3_COSINNER,
		U_LIGHT3_EXPONENT,

		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

public:

	char Map[20][20];
	float Size = 15;
	float Z_Displacement = 0;
	float X_Displacement = -100;
	Cutscene();
	~Cutscene();

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
	void UpdateMenu();


	//Array of meshes
	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;
	Light light[8]; //shader max 8 lights

	void RenderSkybox();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderQuadOnScreen(Mesh* mesh, float size, float x, float y, float rotate, float rx, float ry, float rz, float z);

	Camera3 camera;


	void Map_Reading();
	void Map_Rendering();
	void Character_Movement(float dt);

	Mouse mouse;
	Sound sound;
	float planePos=-20;
	float planePos2 = 350;
	int cameraShake;
	int randNum;
	bool blowUp;
	float explosionScale;
	float thrusterScale;
};
#endif