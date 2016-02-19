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
#include <vector>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;

class SceneMenu : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_REF_AXES = 0,
		GEO_REF_QUAD,
		GEO_LIGHTBALL,
		GEO_QUAD,
		GEO_STAR,
		GEO_TEXT,
		GEO_FLOOR,
		GEO_PATH,
		GEO_BENCH,
		GEO_VENDING,
		GEO_BUILDING,
		GEO_COKE,
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
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};


	enum Items
	{
		None = -1,
		COKE,
		VENDINGMACHINE,
		Num_Object,
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
	//Camera camera;
	MenuShop menushop;

	bool renderMenu = false;

	//Array of meshes
	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;
	float LSPEED = 10.f;
	float moveSkyBoxZ = 91.f;
	float moveSkyBoxX = 0.f;

	Light light[1]; //shader max 8 lights

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

	Color colorA[5];
	Color colorBlue;
	Color colorNormal;

	string Input;
	string color;
	vector<string>my_arr;
	float deltaTime;

	void userInput(int user);

	float menu_pos = 5;
	float icon;
	float icon2;
	float rotateCoke;
	float menuIcon;
	MenuShop menuShop;
};
#endif