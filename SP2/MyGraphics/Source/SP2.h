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
#include "Enemy.h"
#include "Objects.h"
#include "MyMath.h"
#include "Mouse.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::string;

class SP2 : public Scene
{
	struct DOT
	{
		bool negativeDotProduct;
		bool canInteract;
		bool canGoThrough;
		bool Collision;
		Vector3 Nposition;
		string robot;
	};
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
	enum SHOP_OPTION
	{
		S_YES,
		S_NO,
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
	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		GEO_TRIANGLE_2,
		GEO_REF_AXES,
		GEO_REF_QUAD,
		GEO_LIGHTBALL,
		GEO_QUAD,
		GEO_BB8HEAD,
		GEO_BB8BODY,
		GEO_CROSSHAIR,
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
		GEO_STAR,
		GEO_STORY1,
		GEO_TEXT,
		GEO_PATH,
		GEO_AMMOICON,
		GEO_GOLDICON,
		GEO_EGGICON,
		GEO_BOMBICON,
		GEO_OREICON,
		GEO_VENDING,
		GEO_BAG,
		GEO_PYRAMIDDOOR,
		GEO_INVENTORY,
		GEO_BUILDING,
		GEO_COKE,
		GEO_BULLET,
		GEO_ROBOT,
		GEO_ROBOT1,
		GEO_ROBOT2,
		GEO_MOONBALL,
		GEO_PYRAMID,
		GEO_PYRAMIDNEW,
		GEO_PYRAMIDWALL,
		GEO_PYRAMIDPILLAR,
		GEO_SPACESHIP,
		GEO_PLANEBODY,
		GEO_PLANEWING,
		GEO_PLANEROCKET,
		GEO_PICKAXE,
		GEO_GUN,
		GEO_SWORD,
		GEO_RAWMATERIAL,
		GEO_EXPLOSION,
		GEO_BULLETSKIN,
		GEO_SWORDHAND,
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

		SPACEWING,
		SPACEROCKET,



		Num_Object,
	};

public:

	char Map[20][20];
	float Size = 15;
	float Z_Displacement = 0;
	float X_Displacement = -100;
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


	//Check distance for interactable items
	//NPC and doors
	DOT door;
	DOT robot1;
	DOT robot2;
	DOT robot3;
	DOT spacebody;
	DOT spacewing;
	DOT spacerocket;

	int dialoguePlus = 6;
	int parts = 0;
	void RobotTalk();


	//Array of meshes
	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;
	float LSPEED = 10.f;
	float moveSkyBoxZ = 91.f;
	float moveSkyBoxX = 0.f;

	string interactDia;

	Light light[8]; //shader max 8 lights

	void RenderSkybox();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderQuadOnScreen(Mesh* mesh, float size, float x, float y, float rotate, float rx, float ry, float rz, float z);
	void Dialogue(string filename);
	string new_line;

	//Check for distance of object
	float checkNear(Camera3 camera, Vector3 rhs);
	bool checkFaceNorth(Camera3 camera, Vector3 rhs, bool north);
	//Check for player view
	bool negativeDotProduct;
	string whichRobot = "";
	int dialogue = -1;
	//Show when player can interact with items
	bool canInteract;

	Camera3 camera;

	vector<string>my_arr;
	vector<Bullet*>bullet_arr;
	Vector3 RobotPosition1;
	double b_coolDown;
	double b_coolDownLimit;
	bool startCoolDdown;
	int b_Ammo;

	//for story tab
	float storyPosition;
	bool storyDismiss;
	bool storyShow;
	float coolDownTime;
	string story;

	float deltaTime;
	Bullet bullet;
	Objects objects;
	string shop = "";

	Enemy enemy[10];
	void Enemy_Rendering();
	void Enemy_Updating(float dt);

	void ObjectsHolding(Mesh*mesh, float size);
	void EquipmentHolding(Mesh*mesh, float size,float x,float y,float z);
	void RenderObjects(Mesh*mesh, float size, float x, float y, float z);
	float followx = 0;
	float followy = 0;

	bool pickupwing = false;
	bool pickuprocket = false;
	

	bool fixwing = false;
	bool fixrocket = false;
	

	void Map_Reading();
	void Map_Rendering();
	void Character_Movement(float dt);

	Objects object[Num_Object];
	Objects object_on_hand;
	int T_object_Num;
	
	float JumpTime;
	float PressTime;

	Mouse mouse;
	CollisionDetector detectCollision;

	//TEMPO OBJECT FOR TESTING ONLY
	Vector3 rawMaterial;
};
#endif