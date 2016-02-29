#include "GL\glew.h"
#include "Scene3.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "LoadTGA.h"
#include "SharedData.h"

//This class is to render the first scenario where player has to fix his own spaceship
static Position VtoP(Vector3 V)
{
	Position P = { V.x, V.y, V.z };
	return P;
}
static Vector3 PtoV(Position V)
{
	Vector3 P = { V.x, V.y, V.z };
	return P;
}
Scene3::Scene3()
{
}
Scene3::~Scene3()
{
}
void Scene3::Init()
{
	srand(time(NULL));
	Map_Reading();

	JumpTime = 0;
	storyShow = true;
	Dialogue("Text//RobotScene3.txt");
	sound.playMusic("Music//Music1.mp3");
	SharedData::GetInstance()->gameScene = "Scene3";
	PressTime = 0;
	On_Plane = false;
	Plane.Set(350, -20, 0);
	// Init VBO here
	gun = 0;
	b_coolDown = b_coolDownLimit = 1;
	startCoolDdown = false;
	usingSword = true;
	usingGun = usingPickAxe = false;
	rm_coolDown = rm_coolDownLimit = 10;
	startRMcoolDown = false;
	weaponChoice = 1;

	gunTranslation = swordTranslation = pickAxeTranslation = swordRotation = pickAxeRotation = gunRotation = 0;
	storyPosition = 2.5;

	camera.cameraRotate = Vector3(0, 90, 0);

	//ore positions
	oreMaterial_arr[0].pos = Vector3(215, -21, -120);
	oreMaterial_arr[1].pos = Vector3(255, -21, -120);

	//Position of door
	npc.door.Nposition = Vector3(92, -22, 0);
	npc.door.canGoThrough = false;
	npc.door.Collision = true;
	npc.robot1.Nposition = Vector3(280, -21, -150);
	npc.robot2.Nposition = Vector3(245, -21, 150);
	npc.robot3.Nposition = Vector3(92, -21, 361);
	npc.spaceShip.Nposition = Vector3(-100, 230, 0);
	npc.spacebody.Nposition = Vector3(350, -20, 0);
	npc.bomb.Nposition = Vector3(-115, -18, 0);
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	//glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Blending.fragmentshader");
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");

	m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
	m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
	m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
	m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
	m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");
	m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
	m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
	m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
	m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID, "lights[3].cosInner");
	m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID, "lights[3].exponent");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");


	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(m_programID);

	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 1, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 0.2;
	light[0].kC = 5.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutOff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	//Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutOff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	light[1].type = Light::LIGHT_SPOT;
	light[1].position.Set(350, 37, 0);
	light[1].color.Set(1, 1, 1);
	light[1].power = 3;
	light[1].kC = 1.f;
	light[1].kL = 0.1f;
	light[1].kQ = 0.001f;
	light[1].cosCutOff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutOff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

	light[2].type = Light::LIGHT_POINT;
	light[2].position.Set(-100, 55, 0);
	light[2].color.Set(1, 0, 1);
	light[2].power = 3;
	light[2].kC = 1.f;
	light[2].kL = 0.1f;
	light[2].kQ = 0.001f;
	light[2].cosCutOff = cos(Math::DegreeToRadian(45));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 3.f;
	light[2].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT2_TYPE], light[2].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &light[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], light[2].cosCutOff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], light[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[2].exponent);

	light[3].type = Light::LIGHT_POINT;
	light[3].position.Set(-100, 55, 0);
	light[3].color.Set(1, 1, 1);
	light[3].power = 3;
	light[3].kC = 1.f;
	light[3].kL = 0.1f;
	light[3].kQ = 0.001f;

	glUniform1i(m_parameters[U_LIGHT3_TYPE], light[3].type);
	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &light[3].color.r);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], light[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], light[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], light[3].kQ);

	glUniform1i(m_parameters[U_NUMLIGHTS], 4);

	//Initialize camera settings
	camera.Init(Vector3(300, -10, 0), Vector3(0, 0, 0), Vector3(0, 1, 0));
	meshList[GEO_REF_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	GLuint floor = LoadTGA("Image//Scene_Floor.tga");

	//meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1, 0));
	meshList[GEO_QUAD] = MeshBuilder::GenerateRepeatQuad("quad", Color(1, 1, 0), 1, 1, 10);
	meshList[GEO_QUAD]->textureID = floor;
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_PYRAMIDFLOOR] = MeshBuilder::GenerateRepeatQuad("quad", Color(1, 1, 0), 1.4, 1.4, 10);
	meshList[GEO_PYRAMIDFLOOR]->textureID = floor;
	meshList[GEO_PYRAMIDFLOOR]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_PYRAMIDFLOOR]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_PYRAMIDFLOOR]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_PYRAMIDFLOOR]->material.kShininess = 1.f;

	meshList[GEO_AMMOICON] = MeshBuilder::GenerateQuad("ammoicon", Color(1, 1, 1), 3, 3);
	meshList[GEO_AMMOICON]->textureID = LoadTGA("Image//I_Ammo.tga");

	meshList[GEO_GOLDICON] = MeshBuilder::GenerateQuad("goldicon", Color(1, 1, 1), 3, 3);
	meshList[GEO_GOLDICON]->textureID = LoadTGA("Image//I_Gold.tga");

	meshList[GEO_EGGICON] = MeshBuilder::GenerateQuad("eggicon", Color(1, 1, 1), 3, 3);
	meshList[GEO_EGGICON]->textureID = LoadTGA("Image//I_Egg.tga");

	meshList[GEO_GUNICON] = MeshBuilder::GenerateQuad("gun", Color(1, 1, 1), 3, 3);
	meshList[GEO_GUNICON]->textureID = LoadTGA("Image//I_Gun.tga");

	meshList[GEO_PICKAXEICON] = MeshBuilder::GenerateQuad("pickaxe", Color(1, 1, 1), 3, 3);
	meshList[GEO_PICKAXEICON]->textureID = LoadTGA("Image//I_PickAxe.tga");

	meshList[GEO_SWORDICON] = MeshBuilder::GenerateQuad("sword", Color(1, 1, 1), 3, 3);
	meshList[GEO_SWORDICON]->textureID = LoadTGA("Image//I_Sword.tga");

	meshList[GEO_OREICON] = MeshBuilder::GenerateQuad("Ore", Color(1, 1, 1), 3, 3);
	meshList[GEO_OREICON]->textureID = LoadTGA("Image//I_Ore.tga");

	meshList[GEO_BOMBICON] = MeshBuilder::GenerateQuad("Bomb", Color(1, 1, 1), 3, 3);
	meshList[GEO_BOMBICON]->textureID = LoadTGA("Image//I_Bomb.tga");

	meshList[GEO_FRONT1] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1, 1);
	meshList[GEO_FRONT1]->textureID = LoadTGA("Image//d_front.tga");

	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateQuad("crosshair", Color(1, 1, 1), 5, 5);
	meshList[GEO_CROSSHAIR]->textureID = LoadTGA("Image//Crosshair.tga");

	meshList[GEO_BACK1] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1, 1);
	meshList[GEO_BACK1]->textureID = LoadTGA("Image//d_back.tga");

	meshList[GEO_LEFT1] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1, 1);
	meshList[GEO_LEFT1]->textureID = LoadTGA("Image//d_left.tga");

	meshList[GEO_RIGHT1] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1, 1);
	meshList[GEO_RIGHT1]->textureID = LoadTGA("Image//d_right.tga");

	meshList[GEO_TOP1] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1, 1);
	meshList[GEO_TOP1]->textureID = LoadTGA("Image//d_top.tga");

	meshList[GEO_BOTTOM1] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1, 1);
	meshList[GEO_BOTTOM1]->textureID = LoadTGA("Image//d_bottom.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//_Font.tga");

	GLuint R2D2 = LoadTGA("Image//Scene_R2D2_D.tga");
	meshList[GEO_ROBOTH] = MeshBuilder::GenerateOBJ("Robot", "OBJ//R2D2_head.obj");
	meshList[GEO_ROBOTH]->textureID = R2D2;
	meshList[GEO_ROBOTB] = MeshBuilder::GenerateOBJ("Robot", "OBJ//R2D2_body.obj");
	meshList[GEO_ROBOTB]->textureID = R2D2;

	meshList[GEO_ROBOT] = MeshBuilder::GenerateOBJ("Robot", "OBJ//R2D2.obj");
	meshList[GEO_ROBOT]->textureID = R2D2;

	meshList[GEO_ROBOT1] = MeshBuilder::GenerateOBJ("Robot1", "OBJ//R2D2.obj");
	meshList[GEO_ROBOT1]->textureID = LoadTGA("Image//Scene_R2D2_A.tga");

	meshList[GEO_COKE] = MeshBuilder::GenerateOBJ("coke", "OBJ//BB8.obj");
	meshList[GEO_COKE]->textureID = LoadTGA("Image//Scene_BB8.tga");

	meshList[GEO_STORY1] = MeshBuilder::GenerateQuad("story3", Color(1, 1, 1), 4, 5);
	meshList[GEO_STORY1]->textureID = LoadTGA("Image//story3.tga");

	meshList[GEO_MOONBALL] = MeshBuilder::GenerateOBJ("moonball", "OBJ//moon.obj");
	meshList[GEO_MOONBALL]->textureID = LoadTGA("Image//Scene_moon.tga");

	GLuint pyramid = LoadTGA("Image//Scene_Pyramid.tga");
	meshList[GEO_PYRAMID] = MeshBuilder::GenerateOBJ("pyramid", "OBJ//pryramidobj.obj");
	meshList[GEO_PYRAMID]->textureID = pyramid;
	meshList[GEO_PYRAMIDNEW] = MeshBuilder::GenerateOBJ("pyramid", "OBJ//PyramidNew.obj");
	meshList[GEO_PYRAMIDNEW]->textureID = pyramid;
	meshList[GEO_PYRAMIDDOOR] = MeshBuilder::GenerateOBJ("pyramid", "OBJ//PyramidDoor.obj");
	meshList[GEO_PYRAMIDDOOR]->textureID = LoadTGA("Image//Scene_slabs.tga");
	meshList[GEO_PYRAMIDWALL] = MeshBuilder::GenerateOBJ("Walls", "OBJ/Wall.obj");
	meshList[GEO_PYRAMIDWALL]->textureID = pyramid;
	meshList[GEO_PYRAMIDPILLAR] = MeshBuilder::GenerateOBJ("Pillars", "OBJ//Pillar.obj");
	meshList[GEO_PYRAMIDPILLAR]->textureID = pyramid;

	meshList[GEO_SPACESHIP] = MeshBuilder::GenerateOBJ("Star", "OBJ//SPACESHIP.obj");
	meshList[GEO_SPACESHIP]->textureID = LoadTGA("Image//Scene_SpaceShip.tga");

	meshList[GEO_BB8HEAD] = MeshBuilder::GenerateOBJ("Star", "OBJ//BB8head.obj");
	meshList[GEO_BB8HEAD]->textureID = LoadTGA("Image//Scene_BB8head.tga");

	meshList[GEO_BB8BODY] = MeshBuilder::GenerateOBJ("Star", "OBJ//BB8sphere.obj");
	meshList[GEO_BB8BODY]->textureID = LoadTGA("Image//Scene_BB8sphere.tga");

	GLuint plane = LoadTGA("Image//Scene_Plane.tga");
	meshList[GEO_PLANEBODY] = MeshBuilder::GenerateOBJ("Star", "OBJ//planebody.obj");
	meshList[GEO_PLANEBODY]->textureID = plane;

	meshList[GEO_PLANEWING] = MeshBuilder::GenerateOBJ("Star", "OBJ//planewing.obj");
	meshList[GEO_PLANEWING]->textureID = plane;

	meshList[GEO_PLANEROCKET] = MeshBuilder::GenerateOBJ("Star", "OBJ//planerocket.obj");
	meshList[GEO_PLANEROCKET]->textureID = plane;

	meshList[GEO_PICKAXE] = MeshBuilder::GenerateOBJ("pickaxe", "OBJ//pickaxe.obj");
	meshList[GEO_PICKAXE]->textureID = LoadTGA("Image//Weapon_PickAxe.tga");

	meshList[GEO_GUN] = MeshBuilder::GenerateOBJ("gun", "OBJ//M24_R_Low_Poly_Version_obj.obj");
	meshList[GEO_GUN]->textureID = LoadTGA("Image//Weapon_Gun.tga");

	meshList[GEO_SWORD] = MeshBuilder::GenerateOBJ("sword", "OBJ//Sword.obj");
	meshList[GEO_SWORD]->textureID = LoadTGA("Image//Weapon_Sword.tga");
	
	meshList[GEO_RMSMALL] = MeshBuilder::GenerateOBJ("material", "OBJ//rawMaterial3.obj");
	meshList[GEO_RMSMALL]->textureID = LoadTGA("Image//RawMaterial.tga");

	meshList[GEO_RMMEDIUM] = MeshBuilder::GenerateOBJ("material", "OBJ//rawMaterial2.obj");
	meshList[GEO_RMMEDIUM]->textureID = meshList[GEO_RMSMALL]->textureID;

	meshList[GEO_RMBIG] = MeshBuilder::GenerateOBJ("material", "OBJ//rawMaterial.obj");
	meshList[GEO_RMBIG]->textureID = meshList[GEO_RMSMALL]->textureID;

	meshList[GEO_EXPLOSION] = MeshBuilder::GenerateQuad("explosion1", Color(1, 1, 1), 5, 5);
	meshList[GEO_EXPLOSION]->textureID = LoadTGA("Image//Scene_Explosion.tga");

	meshList[GEO_BULLETSKIN] = MeshBuilder::GenerateOBJ("gun", "OBJ//bulletskin.obj");
	meshList[GEO_BULLETSKIN]->textureID = LoadTGA("Image//Scene_Bullet.tga");

	meshList[GEO_BOMB] = MeshBuilder::GenerateOBJ("bomb", "OBJ//bomb.obj");
	meshList[GEO_BOMB]->textureID = LoadTGA("Image//Scene_Bomb.tga");


	meshList[GEO_CCTV] = MeshBuilder::GenerateOBJ("cctv", "OBJ//camera.obj");
	meshList[GEO_CCTV]->textureID = LoadTGA("Image//Scene_Camera.tga");


	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSpheres("Sph", Color(1, 1, 1), 18, 36);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 16.0f / 9.0f, 0.1f, 10000.0f);
	projectionStack.LoadMatrix(projection);
}
static float LSPEED = 10.f;
static bool Lighting9 = true;
//Check for player and object distance
//Takes in camera and object vector3
float Scene3::checkNear(Camera3 camera, Vector3 rhs)
{
	return (sqrt(((camera.position.x - rhs.x)*(camera.position.x - rhs.x)) + ((camera.position.z - rhs.z)*(camera.position.z - rhs.z))));

}
void Scene3::Update(double dt)
{
	if (coolDownTime > 0)
	{
		coolDownTime -= (float)(10 * dt);
	}
	else
	{
		coolDownTime = 0;
	}
	Enemy_Updating(dt);

	//Talking to npc or opening door
	npc.Door(camera, dt);
	npc.Scene1(camera, dt);
	//Dialogue for robot with rotating head
	if (Application::IsKeyPressed('E') && npc.robot3.robot == "robot3" && coolDownTime == 0)
	{
		coolDownTime = deltaTime / 10;
		robot1rotation = 0;
		if (npc.dialoguePlus < my_arr.size() - 1)
		{
			++npc.dialoguePlus;
		}
	}

	if (plantbomb == true && checkNear(camera, npc.spacebody.Nposition) <= 50)
	{
		if (Application::IsKeyPressed('E'))
		{
			SharedData::GetInstance()->stateCheck = true;
			SharedData::GetInstance()->gameState = SharedData::CUTSCENE;
		}
	}

	//NPC movement/rotatio
	else if (npc.robot3.robot != "robot3")
	{
		if (robot1rotate == false)
		{
			robot1rotation += (float)(20 * dt);

			if (robot1rotation >= 80)
			{
				robot1rotate = true;
			}
		}
		if (robot1rotate)
		{
			robot1rotation -= (float)(20 * dt);

			if (robot1rotation <= -80)
			{
				robot1rotate = false;
			}
		}
	}
	if (npc.robot1.robot != "robot1" && npc.robot1.robot != "robot1.1" && npc.robot1.robot != "robot1.2")
	{
		if (robot1moved == false)
		{
			npc.robot1.Nposition.z += (float)(10 * dt);

			if (npc.robot1.Nposition.z >= -100)
			{
				robot1moved = true;
			}
		}

		if (robot1moved)
		{
			npc.robot1.Nposition.z -= (float)(10 * dt);

			if (npc.robot1.Nposition.z <= -160)
			{
				robot1moved = false;
			}
		}
	}
	if (npc.door.canGoThrough)
	{
		npc.door.Collision = false;
		if (npc.door.Nposition.y > -60)
		{
			npc.door.canGoThrough = true;
			npc.door.Nposition.y -= (float)(100 * dt);
		}
	}
	if (detectCollision.collideByDist(camera.position, npc.door.Nposition) >= 25)
	{
		if (npc.door.Nposition.y < -23)
		{
			npc.door.canGoThrough = false;
			npc.door.Nposition.y += (float)(100 * dt);
		}
	}

	if (detectCollision.collideByDist(camera.position, npc.spaceShip.Nposition) <= 150 && On_Plane)
	{
		npc.spaceShip.canInteract = true;
		npc.door.canInteract = false;
		if (SharedData::GetInstance()->gameState != SharedData::SHOP)
		{
			npc.interactDia = "Press E to enter Shop";
		}
		if (Application::IsKeyPressed('E'))
		{
			npc.interactDia = "Loading shop...";
			SharedData::GetInstance()->stateCheck = true;
			SharedData::GetInstance()->gameState = SharedData::SHOP;
		}
	}
	else
	{
		npc.spaceShip.canInteract = false;
	}
	Character_Movement(dt);
	mouse.MouseUpdate(dt, camera, followx, followy);

	//Check if player presses tab and start to move the story upwards
	if (storyShow == true && Application::IsKeyPressed(VK_TAB) && coolDownTime == 0)
	{
		coolDownTime = deltaTime / 10;
		if (storyPosition >= 2.5)
		{
			storyDismiss = true;
			storyShow = false;
		}
	}
	//Check if player presses tab and start to move story downwards
	if (storyDismiss == true && Application::IsKeyPressed(VK_TAB) && coolDownTime == 0)
	{
		coolDownTime = deltaTime / 10;
		if (storyPosition <= -3)
		{
			storyDismiss = false;
			storyShow = true;
		}
	}

	if (Application::IsKeyPressed('E'))
	{

		if (detectCollision.collideByDist(camera.position, npc.bomb.Nposition) <= 25 && coolDownTime == 0 && plantbomb == false)
		{
			//	if (camera.view.Dot(npc.bomb.Nposition) > 0)
			//{
			coolDownTime = deltaTime / 10;

			SharedData::GetInstance()->bomb.quantity -= 1;
			plantbomb = true;
		}
	}

	if (storyDismiss && storyPosition > -3)
	{
		storyPosition -= (float)(3 * dt);

	}
	if (storyShow && storyPosition < 2.5)
	{
		storyPosition += (float)(3 * dt);
	}
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	if (Application::IsKeyPressed('Z'))
	{
		Lighting9 = false;
	}
	else if (Application::IsKeyPressed('X'))
	{
		Lighting9 = true;
	}
	if (Application::IsKeyPressed('H'))
	{
		SharedData::GetInstance()->bullet.quantity = 30;
	}
	if (Application::IsKeyPressed(VK_LBUTTON) || Application::IsKeyPressed(VK_SPACE))
	{
		switch (weaponChoice)
		{
		case 1:

			if (usingSword)
				detectCollision.swordCollision(enemy, camera.position);

			if (coolDownTime == 0)
			{
				coolDownTime = deltaTime / 10;
				sound.playSE("Music//Sword.mp3");
			}
			playSlashingAnimation = true;
			break;

		case 2:
			if (SharedData::GetInstance()->bullet.quantity > 0)
			{
				startCoolDdown = true;
				if (b_coolDown == b_coolDownLimit)
				{
					sound.playSE("Music//Gun.mp3");
					SharedData::GetInstance()->bullet.quantity--;
					bullet_arr.push_back(new Bullet(camera));
				}
				animation.Shoot(dt, gunTranslation, playShootingAnimation);
			}
			break;

		case 3:
			playMiningAnimation = true;
			break;
		}
	}
	if (playSlashingAnimation)
	{
		animation.Slash(dt, swordRotation, playSlashingAnimation);
	}
	if (playMiningAnimation)
	{
		animation.Mine(dt, pickAxeRotation, playMiningAnimation);
	}

	if (startCoolDdown)
	{
		b_coolDown -= dt;
		if (b_coolDown < 0)
		{
			b_coolDown = b_coolDownLimit;
			startCoolDdown = false;
		}
	}
	for (vector<Bullet*>::iterator iter = bullet_arr.begin(); iter != bullet_arr.end();)
	{
		//if destory bullet = true 
		if ((*iter)->Update(dt) || (*iter)->CollideWithEnemy(enemy, bullet_arr, detectCollision))
		{
			iter = bullet_arr.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	//Check if enemy got slashed by the player
	if (usingSword)
		detectCollision.swordCollision(enemy, camera.position);

	// MINING COLLISION
	for (int i = 0; i < 2; ++i)
	{
		if (detectCollision.collideByDist(camera.position, oreMaterial_arr[i].pos) < 18 && Application::IsKeyPressed(VK_LBUTTON) ||
			detectCollision.collideByDist(camera.position, oreMaterial_arr[i].pos) < 18 && Application::IsKeyPressed(VK_SPACE))
		{
			if (usingPickAxe && oreMaterial_arr[i].hp > 0)
			{
				if (coolDownTime == 0)
				{
					coolDownTime = deltaTime / 15;
					sound.playSE("Music//Mining.mp3");
				}

				startCoolDdown = true;
				if (b_coolDown == b_coolDownLimit)
				{
					SharedData::GetInstance()->mineral.quantity++;
					oreMaterial_arr[i].hp--;
					cout << "Mineral : " << SharedData::GetInstance()->mineral.quantity << endl;
				}
			}
		}

		switch (oreMaterial_arr[i].hp)
		{
		case 0:
			oreMaterial_arr[i].isAlive = false;
			startRMcoolDown = true;
			break;
		case 1:
			oreMaterial_arr[i].shape = meshList[GEO_RMSMALL];
			oreMaterial_arr[i].shape->textureID = meshList[GEO_RMSMALL]->textureID;
			break;
		case 2:
			oreMaterial_arr[i].shape = meshList[GEO_RMMEDIUM];
			oreMaterial_arr[i].shape->textureID = meshList[GEO_RMMEDIUM]->textureID;
			break;
		case 3:
			oreMaterial_arr[i].shape = meshList[GEO_RMBIG];
			oreMaterial_arr[i].shape->textureID = meshList[GEO_RMBIG]->textureID;
			break;
		}

		if (startRMcoolDown)
		{
			rm_coolDown -= dt;
			cout << rm_coolDown << endl;
			if (rm_coolDown < 0)
			{
				oreMaterial_arr[i].isAlive = true;
				oreMaterial_arr[i].hp = 3;
				startRMcoolDown = false;
			}
		}
		else
		{
			rm_coolDown = rm_coolDownLimit;
		}

	}

	if (startCoolDdown)
	{
		b_coolDown -= dt;
		if (b_coolDown < 0)
		{
			b_coolDown = b_coolDownLimit;
			startCoolDdown = false;
		}
	}

	deltaTime = (1.0 / dt);
	if (Application::IsKeyPressed('5') && coolDownTime == 0)
	{


		/*bool toggle = false;
		bool cam1 = false;
		bool movement = true;
		*/
		coolDownTime = deltaTime / 5;
		/// when untoggle below runs agains
		if (cam1 == true && toggle == false)
		{
			//press again then teleport 
			camera.position = newcameraposition;   // teleports u there 
			movement = false;
			toggle = true;
			cout << "u are now in camera mode" << endl;
			/// restrrrict movement 
			/// NEED TO MAKE SURE ITS 2ND TIME

		}

		else if (toggle == true && movement == false)
		{
			movement = true;
			camera.position = oldcameraposition;
			toggle = false;

			cout << "u are now not in camera mode" << endl;

			/// make sure camera mode dont exit and reenter
		}



		if (cam1 == false)
		{

			newcameraposition = camera.position;
			oldcameraposition = camera.position;
			cout << newcameraposition << endl;
			cout << oldcameraposition << "locked old " << endl;
			cam1 = true;

		}
		// toggle== false means normal mode haven toggle into camnera mode


	}// this allow new position to be camera position

	if (Application::IsKeyPressed(VK_F1))
	{
		//SWORD
		weaponChoice = 1;
		usingSword = true;
		usingGun = false;
		usingPickAxe = false;
	}

	if (Application::IsKeyPressed(VK_F2))
	{
		//PICKAXE
		weaponChoice = 3;
		usingSword = false;
		usingGun = false;
		usingPickAxe = true;
	}

	if (Application::IsKeyPressed(VK_F3))
	{
		//GUN
		weaponChoice = 2;

		usingSword = false;
		usingGun = true;
		usingPickAxe = false;
	}


	if (weaponChoice == 1)
	{
		gun = 0;
		sword = 1;
		pickaxe = 0;
	}

	if (weaponChoice == 2)
	{
		gun = 1;
		sword = 0;
		pickaxe = 0;
	}

	if (weaponChoice == 3)
	{
		gun = 0;
		sword = 0;
		pickaxe = 1;
	}
	animation.moveSword(dt, swordTranslation, usingSword);
	animation.moveGun(dt, gunTranslation, usingGun);
	animation.moveSword(dt, pickAxeTranslation, usingPickAxe);

}
//Reading from text file
void Scene3::Dialogue(string filename)
{
	ifstream myfile(filename.c_str());
	string line;

	while (std::getline(myfile, line))
	{
		new_line = line + "\n";
		cout << new_line;
		my_arr.push_back(new_line);
	}
}
void Scene3::RenderMesh(Mesh * mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight && Lighting9)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
void Scene3::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}
void Scene3::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);

	//Add these code just after glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.7f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	//Add these code just before glEnable(GL_DEPTH_TEST);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}
//Takes in mesh, the size of the mesh, the position, the rotation, and z layering
void Scene3::RenderQuadOnScreen(Mesh* mesh, float size, float x, float y, float rotate, float rx, float ry, float rz, float z)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, z);
	modelStack.Rotate(rotate, rx, ry, rz);
	RenderMesh(mesh, false);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}
//Rendering current skybox
static float SBSCALE1 = 1000.f;
void Scene3::RenderSkybox()
{
	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Translate(0, -20, -398);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
	RenderMesh(meshList[GEO_FRONT1], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Translate(0, 0, -0.9);
	modelStack.Translate(0, -20, 600);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
	RenderMesh(meshList[GEO_BACK1], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Translate(5, 0, 0);
	modelStack.Translate(-500, -20, 100);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(-180, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
	RenderMesh(meshList[GEO_LEFT1], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here	
	modelStack.Translate(-5, 0, 0);
	modelStack.Translate(500, -20, 100);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
	RenderMesh(meshList[GEO_RIGHT1], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Translate(0, -500, 100);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
	RenderMesh(meshList[GEO_BOTTOM1], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Translate(0, -13, 0);
	modelStack.Translate(0, 490, 100);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(360, 0, 0, 1);
	modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
	RenderMesh(meshList[GEO_TOP1], false);
	modelStack.PopMatrix();
}
//Render codes
void Scene3::Render()
{
	std::ostringstream oss;
	oss << "Camera X: " << camera.position.x;
	string var = oss.str();

	std::ostringstream oss1;
	oss1 << "Camera Z: " << camera.position.z;
	string var1 = oss1.str();

	std::ostringstream ammoOSS;
	std::ostringstream bombOSS;
	std::ostringstream oreOSS;
	std::ostringstream eggOSS;
	std::ostringstream goldOSS;
	std::ostringstream fpsOSS;

	ammoOSS << SharedData::GetInstance()->bullet.quantity;
	goldOSS << SharedData::GetInstance()->gold.quantity;
	bombOSS << SharedData::GetInstance()->bomb.quantity;
	oreOSS << SharedData::GetInstance()->mineral.quantity;
	eggOSS << SharedData::GetInstance()->egg.quantity;

	fpsOSS << "FPS : " << deltaTime;
	string Fps = fpsOSS.str();
	string ammo = ammoOSS.str();
	string bomb = bombOSS.str();
	string egg = eggOSS.str();
	string ore = oreOSS.str();
	string s_gold = goldOSS.str();

	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set view matrix using camera settings
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);

	modelStack.LoadIdentity();
	Plane_Rendering();

	//All the light codes
	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[2].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[2].position.x, light[2].position.y, light[2].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[2].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[2].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT2_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[3].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[3].position.x, light[3].position.y, light[3].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[3].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[3].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[3].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT3_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[3].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[4].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[4].position.x, light[4].position.y, light[4].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[4].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[4].position;
		glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[4].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT4_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[4].position;
		glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[5].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[5].position.x, light[5].position.y, light[5].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT5_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[5].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[5].position;
		glUniform3fv(m_parameters[U_LIGHT5_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[5].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT5_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[5].position;
		glUniform3fv(m_parameters[U_LIGHT5_POSITION], 1, &lightPosition_cameraspace.x);
	}

	modelStack.PushMatrix();
	Enemy_Rendering();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	Map_Rendering();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, 0);
	modelStack.Scale(30, 30, 30);

	RenderMesh(meshList[GEO_MOONBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(npc.spaceShip.Nposition.x, npc.spaceShip.Nposition.y, npc.spaceShip.Nposition.z);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_SPACESHIP], false);
	modelStack.PopMatrix();

	if (plantbomb == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(npc.bomb.Nposition.x, npc.bomb.Nposition.y, npc.bomb.Nposition.z);
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[GEO_BOMB], false);
		modelStack.PopMatrix();
	}

	//Move skybox
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 0, -90 + camera.position.z + 50);
	modelStack.Scale(2, 2, 2);
	RenderSkybox();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(npc.door.Nposition.x, npc.door.Nposition.y, npc.door.Nposition.z);
	modelStack.Scale(37, 37, 37);
	RenderMesh(meshList[GEO_PYRAMIDDOOR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(npc.robot1.Nposition.x, npc.robot1.Nposition.y, npc.robot1.Nposition.z);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_ROBOT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(npc.robot3.Nposition.x, npc.robot3.Nposition.y, npc.robot3.Nposition.z);
	modelStack.Rotate(150, 0, 1, 0);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_ROBOTB], false);
	modelStack.PushMatrix();
	modelStack.Rotate(robot1rotation, 0, 1, 0);
	RenderMesh(meshList[GEO_ROBOTH], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(npc.robot2.Nposition.x, npc.robot2.Nposition.y, npc.robot2.Nposition.z);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_ROBOT1], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();

	//Mining rock 
	for (int i = 0; i < 2; ++i)
	{
		if (oreMaterial_arr[i].isAlive)
		{
			modelStack.PushMatrix();
			modelStack.Translate(oreMaterial_arr[i].pos.x, oreMaterial_arr[i].pos.y, oreMaterial_arr[i].pos.z);
			modelStack.Scale(10, 10, 10);
			RenderMesh(oreMaterial_arr[i].shape, false);
			modelStack.PopMatrix();
		}
	}
	modelStack.PushMatrix();

	modelStack.Translate(camera.position.x, camera.position.y + (throwup), camera.position.z);
	modelStack.Rotate(followy, 0, 1, 0);
	modelStack.Rotate(followx, 0, 0, 1);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0.9, -0.12, -0.3);
	modelStack.Scale(0.1, 0.1, 0.1);
	RenderMesh(meshList[GEO_CCTV], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Rotate(followy, 0, 1, 0);
	modelStack.Rotate(followx, 0, 0, 1);
	modelStack.PushMatrix();
	modelStack.Translate(pickAxeTranslation + 0.5, -0.3, 0.22);
	modelStack.Rotate(-pickAxeRotation, 0, 0, 1);
	modelStack.Scale(0.5, 0.2, 0.5);
	RenderMesh(meshList[GEO_PICKAXE], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Rotate(followy, 0, 1, 0);
	modelStack.Rotate(followx, 0, 0, 1);
	modelStack.PushMatrix();
	modelStack.Translate(swordTranslation + 0.5, -0.35, 0.3);
	modelStack.Rotate(-swordRotation, 0, 0, 1);
	modelStack.Scale(0.1, 0.1, 0.1);
	RenderMesh(meshList[GEO_SWORD], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Rotate(followy, 0, 1, 0);
	modelStack.Rotate(followx, 0, 0, 1);
	modelStack.PushMatrix();
	modelStack.Translate(gunTranslation + 0.3, -0.15, 0.3);
	modelStack.Rotate(-gunRotation, 0, 0, 1);
	modelStack.Scale(0.1, 0.1, 0.1);
	RenderMesh(meshList[GEO_GUN], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();





	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(0, -20, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(2000, 1, 2000);
	RenderMesh(meshList[GEO_QUAD], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(-108, -19.9, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(300, 1, 300);
	RenderMesh(meshList[GEO_PYRAMIDFLOOR], true);
	modelStack.PopMatrix();

	//Bullet render
	for (vector<Bullet*>::iterator iter = bullet_arr.begin(); iter != bullet_arr.end(); ++iter)
	{
		modelStack.PushMatrix();
		modelStack.Translate((*iter)->position.x, (*iter)->position.y, (*iter)->position.z);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Rotate((*iter)->b_Angle, 0, 1, 0);

		modelStack.Scale(0.3, 0.3, 0.3);
		RenderMesh(meshList[GEO_BULLETSKIN], false);
		modelStack.PopMatrix();
	}

	var.resize(16);
	var1.resize(16);
	Fps.resize(11);


	if (On_Plane && npc.spaceShip.canInteract)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], npc.interactDia, Color(1, 1, 0), 1.5, 7, 20);
	}
	if (Plane.y < 0)
	{
		if (!On_Plane)
		{
			float distance = sqrt(((camera.position.x - Plane.x)*(camera.position.x - Plane.x)) + ((camera.position.z - Plane.z)*(camera.position.z - Plane.z)));
			if (distance <= 100)
			{
				modelStack.PushMatrix();
				RenderTextOnScreen(meshList[GEO_TEXT], "Press \' E \' to board Ship", Color(1, 1, 0), 1.5, 7, 20);
				modelStack.PopMatrix();
			}
		}
		else if (On_Plane)
		{
			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Press \' Q \' to unboard Ship", Color(1, 1, 0), 1.5, 7, 20);
			modelStack.PopMatrix();
		}
	}
	if (On_Plane)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Press \' W \' and \' S \' to Start Ship", Color(1, 1, 0), 1.5, 7, 22);
		modelStack.PopMatrix();
	}

	//Show player if he can interact with item
	if (doorinteract)
	{
		if (npc.robot1.canInteract || npc.door.canInteract || npc.robot2.canInteract || npc.robot3.canInteract)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], npc.interactDia, Color(1, 1, 0), 1.5, 7, 20);
			if (npc.robot1.robot == "robot1")
			{
				int j = 25;
				for (int i = npc.dialogue; i < my_arr.size() - 7; ++i)
				{
					j--;
					RenderTextOnScreen(meshList[GEO_TEXT], my_arr[i], Color(1, 1, 0), 1.5, 4, j);
				}
			}
			if (npc.robot1.robot == "robot1.1")
			{
				npc.dialogue = 1;
				RenderTextOnScreen(meshList[GEO_TEXT], my_arr[3], Color(1, 1, 0), 1.5, 4, 25);
			}
			if (npc.robot1.robot == "robot1.2")
			{
				npc.dialogue = 2;
				RenderTextOnScreen(meshList[GEO_TEXT], my_arr[4], Color(1, 1, 0), 1.5, 4, 25);
			}
			if (npc.robot2.robot == "robot2")
			{
				RenderTextOnScreen(meshList[GEO_TEXT], my_arr[5], Color(1, 1, 0), 1.5, 4, 25);
			}
			if (npc.robot3.robot == "robot3")
			{

				RenderTextOnScreen(meshList[GEO_TEXT], my_arr[npc.dialoguePlus], Color(1, 1, 0), 1.5, 4, 25);
			}
		}
	}
	RenderTextOnScreen(meshList[GEO_TEXT], shop, Color(0.4, 0.6, 1), 1.5, 7, 7);

	int x = 38.5;
	int y = 14;
	//All element for player inventory
	RenderQuadOnScreen(meshList[GEO_AMMOICON], 2, x, y, 90, 1, 0, 0, 0);
	RenderQuadOnScreen(meshList[GEO_GOLDICON], 2, x, y - 3, 90, 1, 0, 0, 0);
	RenderQuadOnScreen(meshList[GEO_EGGICON], 2, x, y - 6, 90, 1, 0, 0, 0);
	RenderQuadOnScreen(meshList[GEO_OREICON], 2, x, y - 9, 90, 1, 0, 0, 0);
	RenderQuadOnScreen(meshList[GEO_BOMBICON], 2, x, y - 12, 90, 1, 0, 0, 0);

	RenderTextOnScreen(meshList[GEO_TEXT], ammo, Color(0, 0, 1), 1.5, x + 11.5, y + 3.5);
	RenderTextOnScreen(meshList[GEO_TEXT], s_gold, Color(0, 0, 1), 1.5, x + 11.5, y - 0.5);
	RenderTextOnScreen(meshList[GEO_TEXT], egg, Color(0, 0, 1), 1.5, x + 11.5, y - 4.5);
	RenderTextOnScreen(meshList[GEO_TEXT], ore, Color(0, 0, 1), 1.5, x + 11.5, y - 8.5);
	RenderTextOnScreen(meshList[GEO_TEXT], bomb, Color(0, 0, 1), 1.5, x + 11.5, y - 12.5);

	/*RenderTextOnScreen(meshList[GEO_TEXT], var, Color(1, 1, 0), 1.5, 1, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], var1, Color(1, 1, 0), 1.5, 1, 2);*/
	RenderTextOnScreen(meshList[GEO_TEXT], Fps, Color(1, 1, 0), 1.5, 1, 39);

	glBlendFunc(1, 1);
	RenderQuadOnScreen(meshList[GEO_STORY1], 10, 4, storyPosition, 90, 1, 0, 0, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBlendFunc(1, gun);
	RenderQuadOnScreen(meshList[GEO_GUNICON], 2, 1.6, 2, 90, 1, 0, 0, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBlendFunc(1, pickaxe);
	RenderQuadOnScreen(meshList[GEO_PICKAXEICON], 2, 1.6, 5, 90, 1, 0, 0, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBlendFunc(1, sword);
	RenderQuadOnScreen(meshList[GEO_SWORDICON], 2, 1.6, 8, 90, 1, 0, 0, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (storyDismiss && !npc.robot1.canInteract && !npc.robot2.canInteract && !npc.robot3.canInteract)
	{
		RenderQuadOnScreen(meshList[GEO_CROSSHAIR], 1, 40, 30, 90, 1, 0, 0, 1);
	}
}

void Scene3::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
void Scene3::Enemy_Updating(float dt)
{
	Position P = { camera.position.x, camera.position.y, camera.position.z };
	for (int i = 0; i < 5; i++)
	{
		enemy[i].Enemy_movement(P, 30 * dt, Size, Map, enemy, i, Z_Displacement, X_Displacement);
	}
	camera = enemy[0].enemy_attack(enemy, VtoP(camera.position), camera);
}
void Scene3::Enemy_Rendering()
{
	for (int i = 0; i < 5; i++)
	{
		Position A = enemy[i].Return_Position();
		modelStack.PushMatrix();
		modelStack.Translate(A.x, -20, A.z);
		modelStack.Scale(2, 2, 2);
		RenderMesh(meshList[GEO_COKE], true);
		modelStack.PopMatrix();
	}
}
void Scene3::Map_Reading()
{
	string line;
	ifstream myfile("Map//Map3.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < 20; i++)
		{
			getline(myfile, line);
			for (int j = 0; j < 20; j++)
			{
				Map[i][j] = line.at(j);
			}
		}
		myfile.close();
	}
	else cout << "Unable to read Map!!" << endl;
}
void Scene3::Map_Rendering()
{
	modelStack.PushMatrix();

	modelStack.Translate(X_Displacement, -22.5, Z_Displacement);

	modelStack.PushMatrix();
	modelStack.Scale(2.5 * Size, 2.5 * Size, 2.5 * Size);
	RenderMesh(meshList[GEO_PYRAMIDNEW], true);
	modelStack.PushMatrix();
	modelStack.Scale(Size, (2 / (2.5*Size)), Size);
	RenderMesh(meshList[GEO_PYRAMIDWALL], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Start Point
	modelStack.Translate(-Size * 10, 10, -Size * 10);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(Size*i, 0, Size*j);
			modelStack.Scale(Size, Size, Size);
			if (Map[i][j] == char('0'))
			{
				RenderMesh(meshList[GEO_PYRAMIDPILLAR], true);
			}
			else if (Map[i][j] == char('1'))
			{
				RenderMesh(meshList[GEO_PYRAMIDWALL], true);
			}
			modelStack.PopMatrix();
		}
	}
	modelStack.PopMatrix();
	camera.position.y = -10;
}
void Scene3::Character_Movement(float dt)
{
	if (Application::IsKeyPressed('Q') && light[3].power == 0)
	{
		light[3].position = VtoP(camera.position);
		light[3].power = 10000 * dt;
	}
	if (light[3].power > 0)
	{
		light[3].power -= 100 * dt;
	}
	else if (light[3].power < 0)
	{
		light[3].power = 0;
	}
	
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	if (Application::IsKeyPressed('R'))
	{
		camera.Reset();
	}

	//Changing view (target)
	if (Application::IsKeyPressed(VK_LEFT))
	{
		camera.cameraRotate.y += (float)(120 * dt);
		followy += (float)(120 * dt);
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		camera.cameraRotate.y -= (float)(120 * dt);
		followy -= (float)(120 * dt);
	}
	if (Application::IsKeyPressed(VK_UP))
	{
		camera.cameraRotate.x -= (float)(120 * dt);
		followx += (float)(120 * dt);
	}
	if (Application::IsKeyPressed(VK_DOWN))
	{
		camera.cameraRotate.x += (float)(120 * dt);
		followx -= (float)(120 * dt);

	}


	if (followx > camera.maxCameraX)
	{
		followx = 49.99;

	}
	if (followx < -camera.maxCameraX)
	{
		followx = -49.99;
	}

	//Bounds checking based on maximum and minimum
	if (camera.position.x > camera.maxX)
	{
		camera.position.x = camera.maxX;
	}
	if (camera.position.x < camera.minX)
	{
		camera.position.x = camera.minX;
	}
	if (camera.position.z > camera.maxZ)
	{
		camera.position.z = camera.maxZ;
	}
	if (camera.position.z < camera.minZ)
	{
		camera.position.z = camera.minZ;
	}
	if (checkNear(camera, npc.door.Nposition) <= 15)
	{
		if (npc.door.Collision)
		{
			if (camera.position.x < npc.door.Nposition.x)
			{
				camera.position.x = npc.door.Nposition.x - 10;
			}

			if (camera.position.x > npc.door.Nposition.x)
			{
				camera.position.x = npc.door.Nposition.x + 10;
			}
		}
	}
	float distance = sqrt(((camera.position.x - Plane.x)*(camera.position.x - Plane.x))+((camera.position.z - Plane.z)*(camera.position.z - Plane.z)));
	if (distance <= 100 && Plane.y < 0)
	{
		if (!On_Plane && Application::IsKeyPressed('E') && plantbomb == false)
		{
			doorinteract = false;
			On_Plane = true;
		}
		if (On_Plane && Application::IsKeyPressed('Q') && plantbomb == false)
		{
			doorinteract = true;
			On_Plane = false;
			camera.Reset();
		}
	}
	if (On_Plane)
	{
		camera.position.Set(Plane.x, 40 + Plane.y, Plane.z);

		if (Application::IsKeyPressed('W'))
		{
			if (Plane.y < 200)
			{
				Speed += (1 + Speed)*dt;
				Plane.y += Speed*dt;
			}
			else if (Plane.x > 15)
			{
				Plane.y = 200;
				Speed -= (0.65*Speed)*dt;
				Plane.x -= Speed*dt;
			}
			else
			{
				Speed = 0;
				Plane.y = 200;
				Plane.x = 15;
			}
		}
		if (Application::IsKeyPressed('S'))
		{
			if (Plane.x < 350)
			{
				Speed += (1 + Speed)*dt;
				Plane.x += Speed*dt;
			}
			else if (Plane.y > -20)
			{
				Plane.x = 350;
				Speed -= (0.65*Speed)*dt;
				Plane.y -= Speed*dt;
			}
			else
			{
				Speed = 0;
				Plane.y = -20;
				Plane.x = 350;
			}
		}
	}
	else if (!On_Plane)
	{
		//Moving the camera
		Vector3 Test = camera.position;
		if (Application::IsKeyPressed('W'))
		{
			Test.x += sin(DegreeToRadian(camera.cameraRotate.y)) * camera.cameraSpeed*dt;
			if (enemy[0].Collision_Detection(VtoP(Test), Size, Map, enemy, -1, Z_Displacement, X_Displacement))
			{
				camera.position = Test;
			}
			else
			{
				Test = camera.position;
			}
			Test.z += cos(DegreeToRadian(camera.cameraRotate.y)) * camera.cameraSpeed *dt;
			if (enemy[0].Collision_Detection(VtoP(Test), Size, Map, enemy, -1, Z_Displacement, X_Displacement))
			{
				camera.position = Test;
			}
		}

		if (Application::IsKeyPressed('S'))
		{
			Test.x += sin(DegreeToRadian(camera.cameraRotate.y + 180)) * camera.cameraSpeed *dt;
			if (enemy[0].Collision_Detection(VtoP(Test), Size, Map, enemy, -1, Z_Displacement, X_Displacement))
			{
				camera.position = Test;
			}
			else
			{
				Test = camera.position;
			}
			Test.z += cos(DegreeToRadian(camera.cameraRotate.y + 180)) * camera.cameraSpeed *dt;
			if (enemy[0].Collision_Detection(VtoP(Test), Size, Map, enemy, -1, Z_Displacement, X_Displacement))
			{
				camera.position = Test;
			}
		}

		if (Application::IsKeyPressed('A'))
		{
			Test.x += sin(DegreeToRadian(camera.cameraRotate.y + 90)) * camera.cameraSpeed *dt;
			if (enemy[0].Collision_Detection(VtoP(Test), Size, Map, enemy, -1, Z_Displacement, X_Displacement))
			{
				camera.position = Test;
			}
			else
			{
				Test = camera.position;
			}
			Test.z += cos(DegreeToRadian(camera.cameraRotate.y + 90)) * camera.cameraSpeed *dt;
			if (enemy[0].Collision_Detection(VtoP(Test), Size, Map, enemy, -1, Z_Displacement, X_Displacement))
			{
				camera.position = Test;
			}
		}

		if (Application::IsKeyPressed('D'))
		{
			Test.x += sin(DegreeToRadian(camera.cameraRotate.y + 270)) * camera.cameraSpeed *dt;
			if (enemy[0].Collision_Detection(VtoP(Test), Size, Map, enemy, -1, Z_Displacement, X_Displacement))
			{
				camera.position = Test;
			}
			else
			{
				Test = camera.position;
			}
			Test.z += cos(DegreeToRadian(camera.cameraRotate.y + 270)) * camera.cameraSpeed *dt;
			if (enemy[0].Collision_Detection(VtoP(Test), Size, Map, enemy, -1, Z_Displacement, X_Displacement))
			{
				camera.position = Test;
			}
		}
	}
	//Only allow rotating to look 90 degrees up and 90 degrees down
	if (camera.cameraRotate.x > camera.maxCameraX)
	{
		camera.cameraRotate.x = camera.maxCameraX;
	}

	else if (camera.cameraRotate.x < -camera.maxCameraX)
	{
		camera.cameraRotate.x = -camera.maxCameraX;
	}

	//Changing target
	camera.target = Vector3(sin(DegreeToRadian(camera.cameraRotate.y))*cos(DegreeToRadian(camera.cameraRotate.x)) + camera.position.x, -sin(DegreeToRadian(camera.cameraRotate.x)) + camera.position.y,
		cos(DegreeToRadian(camera.cameraRotate.y))*cos(DegreeToRadian(camera.cameraRotate.x)) + camera.position.z);
	camera.view = (camera.target - camera.position).Normalized();
	Vector3 right = camera.view.Cross(camera.defaultUp);
	right.y = 0;
	camera.up = right.Cross(camera.view);
}


void Scene3::RenderObjects(Mesh*mesh, float size, float x, float y, float z)
{

	modelStack.PushMatrix();
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, z);
	RenderMesh(mesh, true);


	modelStack.PopMatrix();
}


void Scene3::ObjectsHolding(Mesh*mesh, float size)
{

	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Rotate(followy, 0, 1, 0);
	modelStack.Rotate(followx, 0, 0, 1);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0.9, -0.12, -0.3);
	modelStack.Scale(size, size, size);
	RenderMesh(mesh, true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}


void Scene3::EquipmentHolding(Mesh*mesh, float size)
{

	modelStack.PushMatrix();

	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Rotate(followy, 0, 1, 0);
	modelStack.Rotate(followx, 0, 0, 1);


	modelStack.PushMatrix();
	modelStack.Translate(0.9, -0.12, 0.3);
	modelStack.Scale(size, size, size);
	RenderMesh(mesh, true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void Scene3::Plane_Rendering()
{
	modelStack.PushMatrix();
	modelStack.Translate(Plane.x, Plane.y, Plane.z);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(5, 5, 5);
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_PLANEBODY], true);
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_PLANEROCKET], true);
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_PLANEWING], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}