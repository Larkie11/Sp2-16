/******************************************************************************/
/*!
\file	Scene2.h
\author Mok Wei Min, Heng Soon Yap, Oh Zhan Wei, Francis Wong
\par	
\brief
Renders the 2nd Scene for player to pick up eggs and access shop
*/
/******************************************************************************/
#ifndef Scene2_H
#define Scene2_H

#include "MeshBuilder.h"
#include "Utility.h"
#include "Scene.h"
#include "Mtx44.h"
#include "MyMath.h"
#include "Light.h"
#include "Material.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Bullet.h"
#include "NPC.h"
#include "Enemy.h"

#include "Mouse.h"
#include "rawMaterial.h"
#include "Sound.h"
#include "Animation.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using std::ifstream;
using std::vector;
using std::string;

/******************************************************************************/
/*!
Class SceneWin:
\brief	Class objects, meshes to render, booleans, floats and strings
*/
/******************************************************************************/
class Scene2 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_REF_AXES = 0,
		GEO_REF_QUAD,
		GEO_QUAD,

		GEO_ENEMY,
		GEO_CROSSHAIR,

		//Skybox
		GEO_LEFT1,
		GEO_RIGHT1,
		GEO_TOP1,
		GEO_BOTTOM1,
		GEO_FRONT1,
		GEO_BACK1,
		GEO_STAR,

		//Story text
		GEO_STORY1,
		GEO_TEXT,

		//Icons
		GEO_AMMOICON,
		GEO_GOLDICON,
		GEO_EGGICON,
		GEO_BOMBICON,
		GEO_OREICON,
		GEO_GUNICON,
		GEO_PICKAXEICON,
		GEO_SWORDICON,

		//Collectibles
		GEO_BOMB,
		GEO_CCTV,
		GEO_EGG,
		GEO_BAG,
		GEO_RING,
		GEO_PRISM,
		GEO_SPEHERE,

		GEO_BULLET,

		//Enemy
		GEO_ROBOTH,
		GEO_ROBOTB,
		GEO_ROBOT,
		GEO_ROBOT1,
		GEO_ROBOT2,
		GEO_SPEECH,

		//Scene
		GEO_MOONBALL,
		GEO_PYRAMID,
		GEO_PYRAMIDNEW,
		GEO_PYRAMIDFLOOR,
		GEO_PYRAMIDWALL,
		GEO_PYRAMIDDOOR,
		GEO_PYRAMIDPILLAR,
		GEO_SPACESHIP,
		GEO_PLANEBODY,
		GEO_PLANEWING,
		GEO_PLANEROCKET,
		GEO_POTATO,

		//Weapons
		GEO_PICKAXE,
		GEO_GUN,
		GEO_SWORD,

		//Minerals
		GEO_RMSMALL,
		GEO_RMMEDIUM,
		GEO_RMBIG,

		//Others
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
	float Z_Displacement;
	float X_Displacement;
	Scene2();
	~Scene2();

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

	NPC npc;
	bool robot1moved;
	bool robot1rotate;
	float robot1rotation;
	float xtranslate;
	float ytranslate;
	int parts;

	//Array of meshes
	Mesh* meshList[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack;
	float LSPEED = 10.f;
	float moveSkyBoxZ;
	float moveSkyBoxX;
	float potatoRotate;
	
	Light light[8]; //shader max 8 lights

	void RenderSkybox();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderQuadOnScreen(Mesh* mesh, float size, float x, float y, float rotate, float rx, float ry, float rz, float z);
	void Dialogue(string filename);
	string new_line;

	//Check for distance of object
	float checkNear(Camera3 camera, Vector3 rhs);
	//Check for player view
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
	string story;

	float deltaTime;
	Bullet bullet;

	int Died_Time;
	Enemy enemy[5];
	void Enemy_Rendering();
	void Enemy_Updating(float dt);

	void ObjectsHolding(Mesh*mesh, float size);
	float throwingdown;
	float throwingforward;
	float throwup;
	Vector3 newcameraposition;
	Vector3 oldcameraposition;
	bool throwbomb;
	bool thrown;
	bool toggle;
	bool cam1;
	bool movement;
	bool pickupegg1;
	bool pickupegg2;
	bool pickupegg3;
	bool pickupegg4;
	bool pickupegg5;

	//picking up space ship parts
	bool pickupwing;
	bool pickuprocket;
	float followx;
	float followy;
	bool fixwing;
	bool fixrocket;
	float coolDownTime;
	string shop;
	bool doorinteract;

	void Map_Reading();
	void Map_Rendering();
	void Character_Movement(float dt);


	float JumpTime;
	float PressTime;

	Mouse mouse;
	CollisionDetector detectCollision;

	bool On_Plane = false;
	float Speed = 0;
	Position Plane;
	void Plane_Rendering();

	Animation animation;
	float swordRotation;
	float pickAxeRotation;
	float gunRotation;

	float gunTranslation;
	float swordTranslation;
	float pickAxeTranslation;

	bool playSlashingAnimation;
	bool playShootingAnimation;
	bool playMiningAnimation;

	bool usingSword;
	bool usingGun;
	bool usingPickAxe;
	int weaponChoice;

	int gun;
	int sword;
	int pickaxe;

	Sound sound;

	rawMaterial oreMaterial_arr[3];
	double rm_coolDown;
	double rm_coolDownLimit;
	bool startRMcoolDown;
};
#endif