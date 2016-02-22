#ifndef SHOP_H
#define SHOP_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Material.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Objects.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::string;

class Shop : public Scene
{
	enum SHOP_OPTION
	{
		S_BUY,
		S_SELL,
		S_BACK,
		S_MAX,
	};
	enum SHOP_BUY
	{
		SB_AMMO,
		SB_BOMB,
		SB_BACK,
		SB_MAX,
	};
	enum SHOP_SELL
	{
		SS_AMMO,
		SS_BOMB,
		SS_EGG,
		SS_BACK,
		SS_MAX,
	};
	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		GEO_TRIANGLE_2,
		GEO_SHOPKEEPER,
		GEO_REF_AXES,
		GEO_REF_QUAD,
		GEO_LIGHTBALL,
		GEO_QUAD,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_SHOP,
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
		GEO_STAR,
		GEO_TEXT,
		GEO_WALL,
		GEO_OUTER,
		GEO_FLOOR,
		GEO_PATH,
		GEO_BENCH,
		GEO_VENDING,
		GEO_BUILDING,
		GEO_COKE,
		GEO_BULLET,
		GEO_MOONBALL,
		GEO_PYRAMID,
		GEO_PYRAMIDNEW,
		GEO_PYRAMIDWALL,
		GEO_PYRAMIDPILLAR,
		GEO_SPACESHIP,
		GEO_PLANEBODY,
		GEO_PLANEWING,
		GEO_PLANEROCKET,
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


	enum Items
	{
		None = -1,
		SPACEBODY,
		SPACEWING,
		SPACEROCKET,
		ENEGRYCELL,
		SWORD,
		GUN,
		CAMERA,
		Num_Object,
	};

public:

	char Map[20][20];
	float Size = 10;
	Shop();
	~Shop();

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
	

	bool renderMenu = false;

	//Array of meshes
	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;
	float LSPEED = 10.f;
	float moveSkyBoxZ = 91.f;
	float moveSkyBoxX = 0.f;
	string shopInput;

	Light light[8]; //shader max 8 lights

	void RenderSkybox();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderQuadOnScreen(Mesh* mesh, float size, float x, float y, float rotate, float rx, float ry, float rz, float z);
	void RenderMenu();
	void Dialogue(string filename);
	bool Menu = true;
	bool exitGame = false;
	bool Options = false;
	string new_line;
	Camera3 camera;
	
	Color colorShop[15];

	string Input;
	string color;
	vector<string>my_arr;
	vector<Bullet*>bullet_arr;
	double b_coolDown;
	double b_coolDownLimit;
	bool startCoolDdown;
	int b_Ammo;

	float deltaTime;
	Bullet bullet;
	Objects objects;

	Enemy enemy[10];
	void Enemy_Rendering();
	void Enemy_Updating(float dt);

	void ObjectsHolding(Mesh*mesh, float size);
	void RenderObjects(Mesh*mesh, float size, float x, float y, float z);


	void Map_Reading();
	void Map_Rendering();
	void Character_Movement(float dt);

	float icon;
	float icon2;
	float rotateCoke;
	float menuIcon;
	
	Objects object[Num_Object];
	Objects object_on_hand;
	int T_object_Num;
	void Object_Reading();
	void Object_Rendering();
	void Object_Updating(float dt);
	float JumpTime;
	float PressTime;
	SHOP_OPTION s_option;
	SHOP_SELL s_sell;
	bool b_gold;
	bool g_gold;
	string nomore;
	bool none = false;
	float coolDown;
	bool sell_gold;
	int gold;
	SHOP_BUY s_buy;
};
#endif