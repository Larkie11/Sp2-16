#ifndef SCENEWIN_H
#define SCENEWIN_H

#include "Scene.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Camera3.h"
#include "Material.h"
#include "Application.h"
#include "MenuShop.h"
#include "Sound.h"

#include <vector>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;

class SceneWin : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_REF_AXES = 0,
		GEO_QUAD,
		GEO_STAR,
		GEO_TEXT,
		GEO_PATH,
		GEO_VENDING,
		GEO_COKE,
		GEO_INSTRUCTIONS,
		GEO_PLANEWING,
		GEO_PLANEROCKET,
		GEO_PLANEBODY,
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
	SceneWin();
	~SceneWin();

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
	MenuShop menushop;

	bool clicked;
	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;
	float LSPEED = 10.f;
	float moveSkyBoxZ = 91.f;
	float moveSkyBoxX = 0.f;

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderQuadOnScreen(Mesh* mesh, float size, float x, float y, float rotate, float rx, float ry, float rz, float z);
	void Dialogue(string filename);

	Camera3 camera;

	Sound sound;

	vector<string>my_arr;
	float deltaTime;
};
#endif