/******************************************************************************/
/*!
\file	Cutscene.h
\author Mok Wei Min
\par	email: 155208U\@mymail.nyp.edu.sg
\brief
Renders the cutscene where players bombs the place and leaves
*/
/******************************************************************************/
#ifndef CUTSCENE_H
#define CUTSCENE_H

#include "MeshBuilder.h"
#include "Utility.h"
#include "Scene.h"
#include "Mtx44.h"
#include "MyMath.h"
#include "Material.h"
#include "Sound.h"
#include "Application.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Mouse.h"

/******************************************************************************/
/*!
Class Cutscene:
\brief	Meshes/booleans/floats for rendering and animation
*/
/******************************************************************************/
class Cutscene : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_REF_AXES = 0,
		GEO_REF_QUAD,
		GEO_LIGHTBALL,
		GEO_QUAD,

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

	//Array of meshes
	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;

	void RenderSkybox();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderQuadOnScreen(Mesh* mesh, float size, float x, float y, float rotate, float rx, float ry, float rz, float z);

	Camera3 camera;

	void Map_Reading();
	void Map_Rendering();
	void Character_Movement(float dt);

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