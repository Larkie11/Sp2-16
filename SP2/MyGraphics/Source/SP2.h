#ifndef SP2_H
#define SP2_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Material.h"
#include "Bullet.h"
#include <string>
#include <vector>
#include <iostream>

using std::string;

class SP2 : public Scene
{
	enum MENU
	{
		MENU1 = 0,
		STARTGAME,
		OPTIONS,
		QUIT,
		MAX,
	};
	enum OPTION
	{
		O_SETTING,
		O_QUIT,
		O_MAX,
	};
	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		GEO_TRIANGLE_2,
		GEO_REF_AXES,
		GEO_REF_QUAD,
		GEO_LIGHTBALL,
		GEO_QUAD,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_LEFT1,
		GEO_RIGHT1,
		GEO_TOP1,
		GEO_BOTTOM1,
		GEO_FRONT1,
		GEO_BACK1,
		GEO_MCHAIR,
		GEO_MDART,
		GEO_MDARTBOARD,
		GEO_MDOORMAN,
		GEO_MSHOE,
		GEO_MWINEBOTTLE,
		GEO_MLAND,
		GEO_MFLY,
		GEO_MHOLDER,
		GEO_TEXT,
		GEO_WALL,
		GEO_OUTER,
		GEO_FLOOR,
		GEO_PATH,
		GEO_BENCH,
		GEO_DOOR,
		GEO_LAMP,
		GEO_SANTA,
		GEO_SANTAL,
		GEO_SANTAR,
		GEO_SANTALEG,
		GEO_STEVE,
		GEO_STEVEL,
		GEO_STEVER,
		GEO_STEVELEG,
		GEO_SHELVES,
		GEO_TABLE,
		GEO_VENDING,
		GEO_TREE,
		GEO_BUILDING,
		GEO_BUILDING1,
		GEO_BROAD,
		GEO_COKE,
		GEO_BULLET,
		GEO_MOONBALL,
		GEO_PYRAMID,
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

		U_LIGHT4_POSITION, //copy all the light parts for multiplie light
		U_LIGHT4_COLOR,
		U_LIGHT4_POWER,
		U_LIGHT4_KC,
		U_LIGHT4_KL,
		U_LIGHT4_KQ,
		U_LIGHT4ENABLED,
		U_LIGHT4_TYPE,
		U_LIGHT4_SPOTDIRECTION,
		U_LIGHT4_COSCUTOFF,
		U_LIGHT4_COSINNER,
		U_LIGHT4_EXPONENT,

		U_LIGHT5_POSITION, //copy all the light parts for multiplie light
		U_LIGHT5_COLOR,
		U_LIGHT5_POWER,
		U_LIGHT5_KC,
		U_LIGHT5_KL,
		U_LIGHT5_KQ,
		U_LIGHT5ENABLED,
		U_LIGHT5_TYPE,
		U_LIGHT5_SPOTDIRECTION,
		U_LIGHT5_COSCUTOFF,
		U_LIGHT5_COSINNER,
		U_LIGHT5_EXPONENT,

		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

public:
	SP2();
	~SP2();

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
	Camera3 camera;
	Color colorA;
	Color colorB;
	Color colorC;
	string Input;
	string color;

	bool Red1 = false;
	bool Red2 = false;
	bool Red3 = false;
	bool Red4 = false;
	bool Red5 = false;
	bool renderMenu = false;

	//Array of meshes
	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;
	float LSPEED = 10.f;
	float moveSkyBoxZ = 91.f;
	float moveSkyBoxX = 0.f;

	Light light[8]; //shader max 8 lights

	void RenderSkybox();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMuseum();
	void RenderMenu();
	bool Menu = true;
	bool exitGame = false;
	bool Options = false;
	MENU choose;
	OPTION c_option;

	bool door;
	float textdir=0;
	float open;
	float night = 0;
	float deltaTime;
	bool change = false;
	std::vector <std::string> data;
	float key1 = 0;
	float coca =0;
	bool cokeFollow = false;
	float cokeY = -7;
	bool showInstructions = false;
	bool returned = false;
	bool showC = false;
	bool showV = false;
	bool showS = false;
	float dialogueVending;
	float dialogueDoor;
	float dialogueCoke;
	float dialogueSteve = 13;
	float rotateCokeY=0;
	float rotateCokeX=150;
	float cokeX=0;
	float cokeZ=0;

	Bullet bullet;

};
#endif