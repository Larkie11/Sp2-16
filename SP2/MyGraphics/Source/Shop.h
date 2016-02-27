#ifndef SHOP_H
#define SHOP_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Material.h"
#include "Mouse.h"
#include "Sound.h"
#include "CollisionDetector.h"
#include "NPC.h"
#include <string>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::string;

#include "MenuShop.h"

class Shop : public Scene
{
	struct DOT
	{
		bool negativeDotProduct;
		bool canInteract;
		Vector3 Nposition;
	};
	enum GEOMETRY_TYPE
	{
		GEO_SHOPKEEPER3D = 0,
		GEO_SHOPKEEPER,
		GEO_TABLE,
		GEO_REF_AXES,
		GEO_REF_QUAD,

		GEO_LIGHTBALL,
		GEO_AMMOICON,
		GEO_GOLDICON,
		GEO_EGGICON,
		GEO_BOMBICON,
		GEO_OREICON,

		GEO_SPACEDOOR,
		GEO_QUAD,
		GEO_LEFT1,
		GEO_RIGHT1,
		GEO_TOP1,
		GEO_BOTTOM1,
		GEO_FRONT1,
		GEO_BACK1,
		GEO_SHOPWALL,
		GEO_TEXT,
		GEO_WALL,
		GEO_OUTER,
		GEO_SHOPICON,
		GEO_CEILING,
		GEO_FLOOR,
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
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

public:
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
	MenuShop menuShop;
	float spaceDoor = 0;
	Mouse mouse;

	//Array of meshes
	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;
	float LSPEED = 10.f;
	float moveSkyBoxZ = 91.f;
	float moveSkyBoxX = 0.f;
	string shopInput;

	void RenderSkybox();
	void RenderShop();
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
	
	MenuShop::SHOP_OPTION shop;
	MenuShop::SHOP_BUY buy;
	MenuShop::SHOP_SELL sell;
	Color colorShop[15];

	string Input;
	string color;
	vector<string>my_arr;

	float deltaTime;

	void Character_Movement(float dt);

	float icon;
	float icon2;
	float menuIcon;

	NPC npc;
	Sound sound;
	
	float JumpTime;
	float PressTime;
	string description;
	bool b_gold;
	bool g_gold;
	string nomore;
	bool none = false;
	float coolDown;
	bool sell_gold;
	CollisionDetector detectCollision;
	int gold;

	void ShopOptions();
	void userInput();
};
#endif