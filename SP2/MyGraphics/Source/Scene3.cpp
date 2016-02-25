#include "GL\glew.h"
#include "Scene3.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "SharedData.h"
#include <sstream>

//This class is to render the first scenario where player has to fix his own spaceship
Position VtoP3(Vector3 V)
{
	Position P = { V.x, V.y, V.z };
	return P;
}
Vector3 PtoV3(Position V)
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
	Object_Reading();
	JumpTime = 0;
	storyShow = true;
	negativeDotProduct = true;
	SharedData::GetInstance()->gameScene = "Scene3";
	Dialogue("Text//RobotScene1.txt");
	PressTime = 0;
	// Init VBO here
	b_coolDown = b_coolDownLimit = 0.08;
	startCoolDdown = false;
	storyPosition = 3;

	//Position of door
	door.Nposition = Vector3(127, -21, 0);
	robot1.Nposition = Vector3(245, -21, -150);
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

	m_parameters[U_LIGHT4_POSITION] = glGetUniformLocation(m_programID, "lights[4].position_cameraspace");
	m_parameters[U_LIGHT4_COLOR] = glGetUniformLocation(m_programID, "lights[4].color");
	m_parameters[U_LIGHT4_POWER] = glGetUniformLocation(m_programID, "lights[4].power");
	m_parameters[U_LIGHT4_KC] = glGetUniformLocation(m_programID, "lights[4].kC");
	m_parameters[U_LIGHT4_KL] = glGetUniformLocation(m_programID, "lights[4].kL");
	m_parameters[U_LIGHT4_KQ] = glGetUniformLocation(m_programID, "lights[4].kQ");
	m_parameters[U_LIGHT4_TYPE] = glGetUniformLocation(m_programID, "lights[4].type");
	m_parameters[U_LIGHT4_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[4].spotDirection");
	m_parameters[U_LIGHT4_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[4].cosCutoff");
	m_parameters[U_LIGHT4_COSINNER] = glGetUniformLocation(m_programID, "lights[4].cosInner");
	m_parameters[U_LIGHT4_EXPONENT] = glGetUniformLocation(m_programID, "lights[4].exponent");

	m_parameters[U_LIGHT5_POSITION] = glGetUniformLocation(m_programID, "lights[5].position_cameraspace");
	m_parameters[U_LIGHT5_COLOR] = glGetUniformLocation(m_programID, "lights[5].color");
	m_parameters[U_LIGHT5_POWER] = glGetUniformLocation(m_programID, "lights[5].power");
	m_parameters[U_LIGHT5_KC] = glGetUniformLocation(m_programID, "lights[5].kC");
	m_parameters[U_LIGHT5_KL] = glGetUniformLocation(m_programID, "lights[5].kL");
	m_parameters[U_LIGHT5_KQ] = glGetUniformLocation(m_programID, "lights[5].kQ");
	m_parameters[U_LIGHT5_TYPE] = glGetUniformLocation(m_programID, "lights[5].type");
	m_parameters[U_LIGHT5_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[5].spotDirection");
	m_parameters[U_LIGHT5_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[5].cosCutoff");
	m_parameters[U_LIGHT5_COSINNER] = glGetUniformLocation(m_programID, "lights[5].cosInner");
	m_parameters[U_LIGHT5_EXPONENT] = glGetUniformLocation(m_programID, "lights[5].exponent");

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

	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(0, 0, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 2;
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
	light[1].position.Set(-300, 37, 0);
	light[1].color.Set(1, 1, 1);
	light[1].power = 3;
	light[1].kC = 5.f;
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
	light[2].position.Set(-60, 100, -300);
	light[2].color.Set(1, 1, 1);
	light[2].power = 5;
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

	light[3].type = Light::LIGHT_SPOT;
	light[3].position.Set(350, 37,0);
	light[3].color.Set(1, 1, 1);
	light[3].power = 3;
	light[3].kC = 1.f;
	light[3].kL = 0.1f;
	light[3].kQ = 0.001f;
	light[3].cosCutOff = cos(Math::DegreeToRadian(45));
	light[3].cosInner = cos(Math::DegreeToRadian(30));
	light[3].exponent = 3.f;
	light[3].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT3_TYPE], light[3].type);
	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &light[3].color.r);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], light[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], light[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], light[3].kQ);
	glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], light[3].cosCutOff);
	glUniform1f(m_parameters[U_LIGHT3_COSINNER], light[3].cosInner);
	glUniform1f(m_parameters[U_LIGHT3_EXPONENT], light[3].exponent);

	light[4].type = Light::LIGHT_POINT;
	light[4].position.Set(0, 200, 300);
	light[4].color.Set(1, 1, 1);
	light[4].power = 40;
	light[4].kC = 1.f;
	light[4].kL = 0.1f;
	light[4].kQ = 0.001f;
	light[4].cosCutOff = cos(Math::DegreeToRadian(45));
	light[4].cosInner = cos(Math::DegreeToRadian(30));
	light[4].exponent = 3.f;
	light[4].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT4_TYPE], light[4].type);
	glUniform3fv(m_parameters[U_LIGHT4_COLOR], 1, &light[4].color.r);
	glUniform1f(m_parameters[U_LIGHT4_POWER], light[4].power);
	glUniform1f(m_parameters[U_LIGHT4_KC], light[4].kC);
	glUniform1f(m_parameters[U_LIGHT4_KL], light[4].kL);
	glUniform1f(m_parameters[U_LIGHT4_KQ], light[4].kQ);
	glUniform1f(m_parameters[U_LIGHT4_COSCUTOFF], light[4].cosCutOff);
	glUniform1f(m_parameters[U_LIGHT4_COSINNER], light[4].cosInner);
	glUniform1f(m_parameters[U_LIGHT4_EXPONENT], light[4].exponent);

	light[5].type = Light::LIGHT_SPOT;
	light[5].position.Set(0, 0, 0);
	light[5].color.Set(1, 1, 1);
	light[5].power = 3;
	light[5].kC = 1.f;
	light[5].kL = 0.1f;
	light[5].kQ = 0.001f;
	light[5].cosCutOff = cos(Math::DegreeToRadian(45));
	light[5].cosInner = cos(Math::DegreeToRadian(30));
	light[5].exponent = 3.f;
	light[5].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT5_TYPE], light[5].type);
	glUniform3fv(m_parameters[U_LIGHT5_COLOR], 1, &light[5].color.r);
	glUniform1f(m_parameters[U_LIGHT5_POWER], light[5].power);
	glUniform1f(m_parameters[U_LIGHT5_KC], light[5].kC);
	glUniform1f(m_parameters[U_LIGHT5_KL], light[5].kL);
	glUniform1f(m_parameters[U_LIGHT5_KQ], light[5].kQ);
	glUniform1f(m_parameters[U_LIGHT5_COSCUTOFF], light[5].cosCutOff);
	glUniform1f(m_parameters[U_LIGHT5_COSINNER], light[5].cosInner);
	glUniform1f(m_parameters[U_LIGHT5_EXPONENT], light[5].exponent);

	glUniform1i(m_parameters[U_NUMLIGHTS], 6);

	//Initialize camera settings
	camera.Init(Vector3(300, -10, 0), Vector3(0, 0, 0), Vector3(0, 1, 0));
	meshList[GEO_REF_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	//meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1, 0));
	meshList[GEO_QUAD] = MeshBuilder::GenerateRepeatQuad("quad", Color(1, 1, 0), 1, 1, 10);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//Tile.tga");
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_PATH] = MeshBuilder::GenerateQuad("land", Color(1, 1, 1), 14, 13);
	meshList[GEO_PATH]->textureID = LoadTGA("Image//Menu.tga");

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1, 1);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//m_front.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1, 1);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//m_back.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1, 1);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//m_left.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1, 1);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//m_right.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1, 1);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//m_top.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1, 1);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//m_bottom.tga");

	meshList[GEO_FRONT1] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1, 1);
	meshList[GEO_FRONT1]->textureID = LoadTGA("Image//d_front.tga");

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
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Text2.tga");

	GLuint wood = LoadTGA("Image//book.tga");
	GLuint textID = LoadTGA("Image//Chair.tga");

	GLuint santa = LoadTGA("Image//Santa.tga");
	
	meshList[GEO_BAG] = MeshBuilder::GenerateQuad("Bag", Color(1, 1, 1), 5, 5);
	meshList[GEO_BAG]->textureID = LoadTGA("Image//Bag.tga");

	meshList[GEO_VENDING] = MeshBuilder::GenerateOBJ("VM", "OBJ//shelves.obj");
	meshList[GEO_VENDING]->textureID = LoadTGA("Image//vending.tga");

	meshList[GEO_ROBOT] = MeshBuilder::GenerateOBJ("Robot1", "OBJ//R2D2.obj");
	meshList[GEO_ROBOT]->textureID = LoadTGA("Image//R2D2_D.tga");

	meshList[GEO_BUILDING] = MeshBuilder::GenerateOBJ("Building", "OBJ//building.obj");
	meshList[GEO_BUILDING]->textureID = LoadTGA("Image//b1.tga");

	meshList[GEO_COKE] = MeshBuilder::GenerateOBJ("coke", "OBJ//coke.obj");
	meshList[GEO_COKE]->textureID = LoadTGA("Image//coke.tga");

	meshList[GEO_STORY1] = MeshBuilder::GenerateQuad("Story2", Color(1, 1, 1), 4, 5);
	meshList[GEO_STORY1]->textureID = LoadTGA("Image//story2.tga");

	meshList[GEO_PYRAMID] = MeshBuilder::GenerateOBJ("pyramid", "OBJ//pryramidobj.obj");
	meshList[GEO_PYRAMID]->textureID = LoadTGA("Image//sand_2.tga");

	meshList[GEO_MOONBALL] = MeshBuilder::GenerateOBJ("moonball", "OBJ//moon.obj");
	meshList[GEO_MOONBALL]->textureID = LoadTGA("Image//moon.tga");

	meshList[GEO_BULLET] = MeshBuilder::GenerateOBJ("model1", "OBJ//Missile.obj");
	meshList[GEO_BULLET]->textureID = LoadTGA("Image//coke.tga");

	meshList[GEO_PYRAMIDNEW] = MeshBuilder::GenerateOBJ("pyramid", "OBJ//PyramidNew.obj");
	meshList[GEO_PYRAMIDNEW]->textureID = LoadTGA("Image//sand_2.tga");
	meshList[GEO_PYRAMIDDOOR] = MeshBuilder::GenerateOBJ("pyramid", "OBJ//PyramidDoor.obj");
	meshList[GEO_PYRAMIDDOOR]->textureID = LoadTGA("Image//slabs.tga");
	meshList[GEO_PYRAMIDWALL] = MeshBuilder::GenerateOBJ("Walls", "OBJ/Wall.obj");
	meshList[GEO_PYRAMIDWALL]->textureID = LoadTGA("Image//sand_2.tga");
	meshList[GEO_PYRAMIDPILLAR] = MeshBuilder::GenerateOBJ("Pillars", "OBJ//Pillar.obj");
	meshList[GEO_PYRAMIDPILLAR]->textureID = LoadTGA("Image//sand_2.tga");

	meshList[GEO_STAR] = MeshBuilder::GenerateOBJ("Star", "OBJ//Star.obj");
	meshList[GEO_STAR]->textureID = LoadTGA("Image//sand_2.tga");

	meshList[GEO_SPACESHIP] = MeshBuilder::GenerateOBJ("Star", "OBJ//SPACESHIP.obj");
	meshList[GEO_SPACESHIP]->textureID = LoadTGA("Image//SPACESHIP.tga");

	meshList[GEO_PLANEBODY] = MeshBuilder::GenerateOBJ("Star", "OBJ//planebody.obj");
	meshList[GEO_PLANEBODY]->textureID = LoadTGA("Image//PLANE.tga");

	meshList[GEO_PLANEWING] = MeshBuilder::GenerateOBJ("Star", "OBJ//planewing.obj");
	meshList[GEO_PLANEWING]->textureID = LoadTGA("Image//PLANE.tga");

	meshList[GEO_PLANEROCKET] = MeshBuilder::GenerateOBJ("Star", "OBJ//planerocket.obj");
	meshList[GEO_PLANEROCKET]->textureID = LoadTGA("Image//PLANE.tga");

	meshList[GEO_STAR] = MeshBuilder::GenerateOBJ("Star", "OBJ//Star.obj");
	meshList[GEO_STAR]->textureID = LoadTGA("Image//sand_2.tga");

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSpheres("Sph", Color(1, 1, 1), 18, 36);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 16.0f / 9.0f, 0.1f, 10000.0f);
	projectionStack.LoadMatrix(projection);
}
static float LSPEED = 10.f;
static bool Lighting9 = true;
//Check for player and object distance
//Takes in camera and object vector3
bool Scene3::checkNear(Camera3 camera, Vector3 rhs)
{
	if (sqrt(((camera.position.x - rhs.x)*(camera.position.x - rhs.x)) + ((camera.position.z - rhs.z)*(camera.position.z - rhs.z))) <= 25)
	{
		return true;
	}
	return false;
}
bool Scene3::checkFaceNorth(Camera3 camera, Vector3 rhs, bool north)
{
	return false;
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
	Object_Updating(dt);
	Character_Movement(dt);
	mouse.MouseUpdate(dt, camera);
	//cout << camera.view.Dot(Nposition) << endl;
	//cout << camera.cameraRotate.y << endl;

	//cout << camera.view.Dot(robot1.Nposition) << endl;
	//If player is on the outside of the pyramid
	if (camera.position.x > door.Nposition.x)
	{
		door.negativeDotProduct = true;
	}
	//If player is on the inside of the pyramid
	if (camera.position.x < door.Nposition.x)
	{
		door.negativeDotProduct = false;
	}
	//This is to check if player is near to the door and facing the door using dot product
	//Since a door has 2 side, the character view dot product door will have both negative and positive, so we have to handle both cases
	if (checkNear(camera, door.Nposition))
	{
		//Check if the player is outside the temple and facing door to the inside
		if (door.negativeDotProduct == true && camera.view.Dot(door.Nposition) < 0)
		{
			//Show player press e to interact
			door.canInteract = true;
			if (Application::IsKeyPressed('E'))
			{
				if (door.Nposition.y > -50)
				{
					door.Nposition.y -= (float)(100 * dt);
				}
			}
		}
		//Update player if player turns away
		else if (door.negativeDotProduct == true && camera.view.Dot(door.Nposition) > 0)
		{
			door.canInteract = false;
		}
		//Check if player is inside the temple and facing door to the outside
		if (door.negativeDotProduct == false && camera.view.Dot(door.Nposition) > 0)
		{
			door.canInteract = true;
			if (Application::IsKeyPressed('E'))
			{
				if (door.Nposition.y > -50)
				{
					door.Nposition.y -= (float)(100 * dt);
				}
			}
		}
		//Update player if player turns away
		else if (door.negativeDotProduct == false && camera.view.Dot(door.Nposition) < 0)
		{
			door.canInteract = false;
		}
	}
	else
	{
		//Dont show the press e to interact
		door.canInteract = false;
		//Everytime a player is far, the door will auto close up
		if (door.Nposition.y < -22)
		{
			door.Nposition.y += (float)(100 * dt);
		}
	}

	if (checkNear(camera, robot1.Nposition))
	{
		if (camera.view.Dot(robot1.Nposition) > 0)
		{
			//Show player press e to interact
			robot1.canInteract = true;
			if (Application::IsKeyPressed('E') && coolDownTime == 0)
			{
				dialogue = 0;
				coolDownTime = deltaTime / 5;
				whichRobot = "robot1";
			}
			if (Application::IsKeyPressed('1'))
			{
				whichRobot = "robot1.1";
			}
			if (Application::IsKeyPressed('2'))
			{
				whichRobot = "robot1.2";
			}
		}
		else
		{
			robot1.canInteract = false;
		}
	}
	else
	{
		robot1.canInteract = false;
		whichRobot = "";
	}
	//To open the shop for now
	if (Application::IsKeyPressed('O'))
	{
		shop = "Loading Shop";
		SharedData::GetInstance()->stateCheck = true;
		SharedData::GetInstance()->gameState = SharedData::SHOP;
	}

	//Check if player presses tab and start to move the story upwards
	if (storyShow == true && Application::IsKeyPressed(VK_TAB)&&coolDownTime == 0)
	{
		coolDownTime = deltaTime/10;
		if (storyPosition >= 3)
		{
			storyDismiss = true;
			storyShow = false;
		}
	}
	//Check if player presses tab and start to move story downwards
	if (storyDismiss == true && Application::IsKeyPressed(VK_TAB) && coolDownTime == 0)
	{
		coolDownTime = deltaTime/10;
		if (storyPosition <= -3)
		{
			storyDismiss = false;
			storyShow = true;
		}
	}
	if (storyDismiss && storyPosition > -3)
	{
		storyPosition -= (float)(3 * dt);
		
	}
	if (storyShow && storyPosition < 3)
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
	if (Application::IsKeyPressed(VK_LBUTTON))
	{
		if (SharedData::GetInstance()->bullet.quantity > 0)
		{
			startCoolDdown = true;
			if (b_coolDown == b_coolDownLimit)
			{
				SharedData::GetInstance()->bullet.quantity--;
				bullet_arr.push_back(new Bullet(camera));
			}
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

	for (vector<Bullet*>::iterator iter = bullet_arr.begin(); iter != bullet_arr.end();)
	{

		//if destory bullet = true 
		if ((*iter)->Update(dt))
		{
			iter = bullet_arr.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	deltaTime = (1.0 / dt);
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
	std::ostringstream goldOSS;
	std::ostringstream fpsOSS;
	
	ammoOSS << "AMMO : " << SharedData::GetInstance()->bullet.quantity;
	goldOSS << "Gold: " << SharedData::GetInstance()->gold.quantity;
	fpsOSS << "FPS : " << deltaTime;
	string Fps = fpsOSS.str();
	string ammo = ammoOSS.str();
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
		Object_Rendering();
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, -50, 0);
		modelStack.Scale(30, 30, 30);

		RenderMesh(meshList[GEO_MOONBALL], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 200, 0);
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[GEO_SPACESHIP], true);
		modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(350, -20, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(5, 5, 5);
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_PLANEWING], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_PLANEROCKET], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_PLANEBODY], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[2].position.x, light[2].position.y, light[2].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[3].position.x, light[3].position.y, light[3].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[4].position.x, light[4].position.y, light[4].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[5].position.x, light[5].position.y, light[5].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	//Move skybox
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 0, -90 + camera.position.z + 50);
	modelStack.Scale(2, 2, 2);
	RenderSkybox();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(door.Nposition.x, door.Nposition.y, door.Nposition.z);
	modelStack.Scale(25, 25, 25);
	RenderMesh(meshList[GEO_PYRAMIDDOOR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(robot1.Nposition.x, robot1.Nposition.y, robot1.Nposition.z);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_ROBOT], false);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(0, -20, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(1000, 1, 1000);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	RenderTextOnScreen(meshList[GEO_TEXT], shop, Color(0.4, 0.6, 1), 1.7, 5, 20);
	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(-10, 3, -60);
	RenderText(meshList[GEO_TEXT], "", Color(0, 1, 0));
	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(25, 0, 0);
	RenderText(meshList[GEO_TEXT], "", Color(0, 1, 0));
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	for (vector<Bullet*>::iterator iter = bullet_arr.begin(); iter != bullet_arr.end(); ++iter)
	{
		modelStack.PushMatrix();
		modelStack.Translate((*iter)->position.x,(*iter)->position.y,(*iter)->position.z);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Rotate((*iter)->b_Angle, 0, 1, 0);

		modelStack.Scale(0.3, 0.3, 0.3);
		RenderMesh(meshList[GEO_BULLET], true);
		modelStack.PopMatrix();
	}
	var.resize(16);
	var1.resize(16);
	Fps.resize(11);

	//All element for player inventory
	RenderTextOnScreen(meshList[GEO_TEXT], ammo, Color(1, 1, 0), 1.5, 1, 39);
	RenderTextOnScreen(meshList[GEO_TEXT], s_gold, Color(1, 1, 0), 1.5, 45, 39);
	RenderTextOnScreen(meshList[GEO_TEXT], var, Color(1, 1, 0), 1.5, 1, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], var1, Color(1, 1, 0), 1.5, 1, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], Fps, Color(1, 1, 0), 1.5, 1, 1);

	//Show player if he can interact with item
	if (robot1.canInteract||door.canInteract)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press E" , Color(1, 1, 0), 1.5, 5, 5);
		if (whichRobot == "robot1")
		{
			int j = 25;
			for (int i = dialogue; i < my_arr.size()-3; ++i)
			{
				j--;
				RenderTextOnScreen(meshList[GEO_TEXT], my_arr[i], Color(1, 1, 0), 1.5, 5, j);
			}
		}
		if (whichRobot == "robot1.1")
		{
			dialogue = 1;
			RenderTextOnScreen(meshList[GEO_TEXT], my_arr[4], Color(1, 1, 0), 1.5, 5, 25);
		}
		if (whichRobot == "robot1.2")
		{
			dialogue = 2;
			RenderTextOnScreen(meshList[GEO_TEXT], my_arr[5], Color(1, 1, 0), 1.5, 5, 25);
		}
	}

	

	RenderQuadOnScreen(meshList[GEO_STORY1], 10, 4, storyPosition, 90, 1, 0, 0, 0);

	RenderQuadOnScreen(meshList[GEO_BAG], 1, 50, 3, 90, 1, 0, 0, 0);
}
void Scene3::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
void Scene3::Enemy_Updating(float dt)
{
	Position P = { camera.position.x, camera.position.y, camera.position.z };
	for (int i = 0; i < 10; i++)
	{
		enemy[i] = enemy[i].Enemy_movement(enemy[i], P, 30 * dt, Size, Map, enemy, i, Z_Displacement, X_Displacement, emeny_size);
	}

	camera = enemy[0].enemy_attack(enemy, VtoP3(camera.position), camera, emeny_size);
}
void Scene3::Enemy_Rendering()
{
	for (int i = 0; i < emeny_size; i++)
	{
		Position A = enemy[i].Return_Position(enemy[i]);
		modelStack.PushMatrix();
		modelStack.Translate(A.x, -20, A.z);
		modelStack.Scale(30, 30, 30);
		RenderMesh(meshList[GEO_COKE], true);
		modelStack.PopMatrix();
	}
}
void Scene3::Map_Reading()
{
	string line;
	ifstream myfile("Map//Map1.txt");
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

	modelStack.Translate(0, -21, 0);

	modelStack.PushMatrix();
	modelStack.Scale(2.5 * Size, 2.5 * Size, 2.5 * Size);
	RenderMesh(meshList[GEO_PYRAMIDNEW], true);
	modelStack.PushMatrix();
	modelStack.Scale(Size, (2 / (2.5*Size)), Size);
	RenderMesh(meshList[GEO_PYRAMIDWALL], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Start Point
	modelStack.Translate(-Size * 10, Size*1.3, -Size * 10);
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

	if (Application::IsKeyPressed('R'))
	{
		camera.Reset();
	}

	//Changing view (target)
	if (Application::IsKeyPressed(VK_LEFT))
	{
		camera.cameraRotate.y += (float)(100 * dt);
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		camera.cameraRotate.y -= (float)(100 * dt);
	}
	if (Application::IsKeyPressed(VK_UP))
	{
		camera.cameraRotate.x -= (float)(100 * dt);
	}
	if (Application::IsKeyPressed(VK_DOWN))
	{
		camera.cameraRotate.x += (float)(100 * dt);
	}
	if (Application::IsKeyPressed('N'))
	{
		camera.position.y -= 1;
	}
	if (Application::IsKeyPressed('M'))
	{
		camera.position.y += 1;
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

	//Moving the camera
	Vector3 Test = camera.position;
	if (Application::IsKeyPressed('W'))
	{
		Test.x += sin(DegreeToRadian(camera.cameraRotate.y)) * camera.cameraSpeed*dt;
		if (enemy[0].Collision_Detection(VtoP3(Test), Size, Map, enemy, -1, Z_Displacement, X_Displacement, emeny_size))
		{
			camera.position = Test;
		}
		else
		{
			Test = camera.position;
		}
		Test.z += cos(DegreeToRadian(camera.cameraRotate.y)) * camera.cameraSpeed *dt;
		if (enemy[0].Collision_Detection(VtoP3(Test), Size, Map, enemy, -1, Z_Displacement, X_Displacement, emeny_size))
		{
			camera.position = Test;
		}
	}

	if (Application::IsKeyPressed('S'))
	{
		Test.x += sin(DegreeToRadian(camera.cameraRotate.y + 180)) * camera.cameraSpeed *dt;
		if (enemy[0].Collision_Detection(VtoP3(Test), Size, Map, enemy, -1, Z_Displacement, X_Displacement, emeny_size))
		{
			camera.position = Test;
		}
		else
		{
			Test = camera.position;
		}
		Test.z += cos(DegreeToRadian(camera.cameraRotate.y + 180)) * camera.cameraSpeed *dt;
		if (enemy[0].Collision_Detection(VtoP3(Test), Size, Map, enemy, -1, Z_Displacement, X_Displacement, emeny_size))
		{
			camera.position = Test;
		}

	}

	if (Application::IsKeyPressed('A'))
	{
		Test.x += sin(DegreeToRadian(camera.cameraRotate.y + 90)) * camera.cameraSpeed *dt;
		if (enemy[0].Collision_Detection(VtoP3(Test), Size, Map, enemy, -1, Z_Displacement, X_Displacement, emeny_size))
		{
			camera.position = Test;
		}
		else
		{
			Test = camera.position;
		}
		Test.z += cos(DegreeToRadian(camera.cameraRotate.y + 90)) * camera.cameraSpeed *dt;
		if (enemy[0].Collision_Detection(VtoP3(Test), Size, Map, enemy, -1, Z_Displacement, X_Displacement, emeny_size))
		{
			camera.position = Test;
		}
	}

	if (Application::IsKeyPressed('D'))
	{
		Test.x += sin(DegreeToRadian(camera.cameraRotate.y + 270)) * camera.cameraSpeed *dt;
		if (enemy[0].Collision_Detection(VtoP3(Test), Size, Map, enemy, -1, Z_Displacement, X_Displacement, emeny_size))
		{
			camera.position = Test;
		}
		else
		{
			Test = camera.position;
		}
		Test.z += cos(DegreeToRadian(camera.cameraRotate.y + 270)) * camera.cameraSpeed *dt;
		if (enemy[0].Collision_Detection(VtoP3(Test), Size, Map, enemy, -1, Z_Displacement, X_Displacement, emeny_size))
		{
			camera.position = Test;
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


void Scene3::Object_Reading()
{
	for (int i = 0; i < Num_Object; i++)
	{/// this + item below =render out 
		/*	object[i].ItemType = Items::SPACEBODY;
		object[i].position.Set(i * 10, 0, i * 10);

		object[i].ItemType = Items::SPACEWING;
		object[i].position.Set(i * 10, 0, i * 10);*/

		object[i].ItemType = Items::SPACEROCKET;
		object[i].position.Set(i * 10, 0, i * 10);

		/*	object[i].ItemType = Items::SWORD;
		object[i].position.Set(i * 10, 0, i * 10);

		object[i].ItemType = Items::GUN;
		object[i].position.Set(i * 10, 0, i * 10);

		object[i].ItemType = Items::CAMERA;
		object[i].position.Set(i * 10, 0, i * 10);*/
	}
	object_on_hand.ItemType = Items::None;
	object_on_hand.position.Set(camera.view.x, camera.view.y, camera.view.z);
	T_object_Num = -1;
}

void Scene3::Object_Rendering()
{
	modelStack.PushMatrix();
	//modelStack.Scale(10, 10, 10);
	for (int i = 0; i < Num_Object; i++) // 5 num object so its run 5 sets 
	{
		if (object[i].ItemType == Items::SPACEROCKET)
		{
			modelStack.PushMatrix();
			modelStack.Translate(object[i].position.x, object[i].position.y, object[i].position.z);   // original location
			modelStack.Scale(1, 1, 1);
			RenderMesh(meshList[GEO_PLANEROCKET], true);
			modelStack.PopMatrix();
		}
	}
	if (object_on_hand.ItemType == Items::SPACEROCKET)
	{
		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);//change to hand
		modelStack.Translate(-object_on_hand.position.x * 5, -object_on_hand.position.y, -object_on_hand.position.z * 5);//change to hand
		modelStack.Scale(1, 1, 1);

		RenderMesh(meshList[GEO_PLANEROCKET], true);
		modelStack.PopMatrix();
	}

	if (object_on_hand.ItemType == Items::SPACEWING)
	{
		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);//change to hand
		modelStack.Translate(-object_on_hand.position.x * 5, -object_on_hand.position.y, -object_on_hand.position.z * 5);//change to hand
		modelStack.Scale(1, 1, 1);

		RenderMesh(meshList[GEO_PLANEWING], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();
}

void Scene3::Object_Updating(float dt)
{
	if (Application::IsKeyPressed('E') && object_on_hand.ItemType != Items::None)
	{
		object[T_object_Num].ItemType = object_on_hand.ItemType;
		object[T_object_Num].position = object_on_hand.position;
		object_on_hand.ItemType = Items::None;
		T_object_Num = -1;

	}
	else if (Application::IsKeyPressed('E'))
	{
		int Pointer = 0;
		float Range = sqrt(((camera.position.x - object[0].position.x)*(camera.position.x - object[0].position.x)) + ((camera.position.x - object[0].position.z)*(camera.position.x - object[0].position.z)));
		for (int i = 1; i < Num_Object; i++)
		{
			float T_Range = sqrt(((camera.position.x - object[i].position.x)*(camera.position.x - object[i].position.x)) + ((camera.position.x - object[i].position.z)*(camera.position.x - object[i].position.z)));
			if (T_Range < Range)
			{
				Range = T_Range;
				Pointer = i;
			}
		}
		if (Range <= 20)
		{
			object_on_hand.ItemType = object[Pointer].ItemType;
			T_object_Num = Pointer;
			object[Pointer].ItemType = Items::None;
			object[Pointer].position.Set(-1000, -1000, -1000);
		}
	}
	object_on_hand.position.Set(camera.position.x - camera.target.x, camera.position.y - camera.target.y, camera.position.z - camera.target.z);
	if (object_on_hand.position.x < float(0.0000001) && object_on_hand.position.x> 0)
	{
		object_on_hand.position.x = 0;
	}
	if (object_on_hand.position.x > -float(0.0000001) && object_on_hand.position.x< 0)
	{
		object_on_hand.position.x = 0;
	}
	if (object_on_hand.position.y < float(0.0000001) && object_on_hand.position.y> 0)
	{
		object_on_hand.position.y = 0;
	}
	if (object_on_hand.position.y > -float(0.0000001) && object_on_hand.position.y< 0)
	{
		object_on_hand.position.y = 0;
	}
	if (object_on_hand.position.z < float(0.0000001) && object_on_hand.position.z> 0)
	{
		object_on_hand.position.z = 0;
	}
	if (object_on_hand.position.z > -float(0.0000001) && object_on_hand.position.z< 0)
	{
		object_on_hand.position.z = 0;
	}
}
