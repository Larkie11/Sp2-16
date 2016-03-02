/******************************************************************************/
/*!
\file	SceneMenu.h
\author Mok Wei Min
\par
\brief
Renders Scene menu where player choses what option they want to choose (Play, instructions, credits, quit)
*/
/******************************************************************************/
#ifndef SCENEMENU_H
#define SCENEMENU_H

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
#include <fstream>

using std::ifstream;
using std::vector;

/******************************************************************************/
/*!
Class SceneMenu:
\brief	Class objects, meshes to render, booleans, floats and strings
*/
/******************************************************************************/
class SceneMenu : public Scene
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
		GEO_CREDITS,
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
	SceneMenu();
	~SceneMenu();

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
	void RenderMenu();
	void Dialogue(string filename);
	bool Menu = true;
	bool exitGame = false;
	bool Options = false;
	string new_line;
	MenuShop::MENU choose;
	MenuShop::OPTION c_option;

	Application app;
	Camera3 camera;
	void setColor(int which, string color);

	Sound sound;

	Color colorA[16];
	Color colorBlue;
	Color colorNormal;
	int px;
	int py;

	bool instructions;
	bool credits;

	string Input;
	string color;
	vector<string>my_arr;
	float deltaTime;

	void userInput();
	void mouseControl();

	float menu_pos = 5;
	float icon;
	float icon2;
	float rotateCoke;
	float menuIcon;
};
#endif