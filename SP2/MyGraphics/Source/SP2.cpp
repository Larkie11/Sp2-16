#include "GL\glew.h"
#include "SP2.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

Position VtoP(Vector3 V)
{
	Position P = { V.x, V.y, V.z };
	return P;
}
Vector3 PtoV(Position V)
{
	Vector3 P = { V.x, V.y, V.z };
	return P;
}
SP2::SP2()
{
}
SP2::~SP2()
{
}
void SP2::Init()
{
	srand(time(NULL));
	Map_Reading();
	Object_Reading();
	JumpTime = 0;
	choose = STARTGAME;
	c_option = O_SETTING;
	Input = "Menu";
	Dialogue("Text//Dialogue1.txt");
	// Init VBO here

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
	light[0].position.Set(250, 55, -90);
	light[0].color.Set(1, 1, 1);
	light[0].power = 4;
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
	light[1].position.Set(-300, 37, 185);
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

	light[2].type = Light::LIGHT_SPOT;
	light[2].position.Set(0, 37, 135);
	light[2].color.Set(1, 1, 1);
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

	light[3].type = Light::LIGHT_SPOT;
	light[3].position.Set(300, 37, 185);
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
	light[5].position.Set(40, 37, -70);
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
	camera.Init(Vector3(-300, -10, 0), Vector3(0, 0, 0), Vector3(0, 1, 0));
	meshList[GEO_REF_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	//meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1, 0));
	meshList[GEO_QUAD] = MeshBuilder::GenerateRepeatQuad("quad", Color(1, 1, 0), 1, 1, 10);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//Tile.tga");
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_FLOOR] = MeshBuilder::GenerateRepeatQuad("floor", Color(1, 1, 1), 1.015, 1, 10);
	meshList[GEO_FLOOR]->textureID = LoadTGA("Image//Tile2.tga");
	meshList[GEO_FLOOR]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_FLOOR]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_FLOOR]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_FLOOR]->material.kShininess = 1.f;

	meshList[GEO_BROAD] = MeshBuilder::GenerateRepeatQuad("floor", Color(1, 1, 1), 30, 7, 10);
	meshList[GEO_BROAD]->textureID = LoadTGA("Image//tile3.tga");
	meshList[GEO_BROAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BROAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_BROAD]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_BROAD]->material.kShininess = 1.f;

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

	meshList[GEO_MLAND] = MeshBuilder::GenerateOBJ("land", "OBJ//Land.obj");
	meshList[GEO_MLAND]->textureID = LoadTGA("Image//Land.tga");

	meshList[GEO_MFLY] = MeshBuilder::GenerateOBJ("fly", "OBJ//Fly.obj");
	meshList[GEO_MFLY]->textureID = LoadTGA("Image//Fly.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Text2.tga");

	GLuint wood = LoadTGA("Image//book.tga");
	GLuint textID = LoadTGA("Image//Chair.tga");
	meshList[GEO_BENCH] = MeshBuilder::GenerateOBJ("bench", "OBJ//Bench.obj");
	meshList[GEO_BENCH]->textureID = wood;

	meshList[GEO_OUTER] = MeshBuilder::GenerateOBJ("Wall", "OBJ//WallOuter.obj");
	meshList[GEO_OUTER]->textureID = LoadTGA("Image//Outside.tga");

	GLuint santa = LoadTGA("Image//Santa.tga");
	meshList[GEO_SANTA] = MeshBuilder::GenerateOBJ("Wall", "OBJ//Char.obj");
	meshList[GEO_SANTA]->textureID = santa;

	meshList[GEO_SANTAR] = MeshBuilder::GenerateOBJ("Wall", "OBJ//CharR.obj");
	meshList[GEO_SANTAR]->textureID = santa;

	meshList[GEO_SANTAL] = MeshBuilder::GenerateOBJ("Wall", "OBJ//CharL.obj");
	meshList[GEO_SANTAL]->textureID = santa;

	meshList[GEO_SANTALEG] = MeshBuilder::GenerateOBJ("Wall", "OBJ//CharLeg.obj");
	meshList[GEO_SANTALEG]->textureID = santa;

	GLuint steve = LoadTGA("Image//Steve.tga");
	meshList[GEO_STEVE] = MeshBuilder::GenerateOBJ("Wall", "OBJ//Char.obj");
	meshList[GEO_STEVE]->textureID = steve;

	meshList[GEO_STEVER] = MeshBuilder::GenerateOBJ("Wall", "OBJ//CharR.obj");
	meshList[GEO_STEVER]->textureID = steve;

	meshList[GEO_STEVEL] = MeshBuilder::GenerateOBJ("Wall", "OBJ//CharL.obj");
	meshList[GEO_STEVEL]->textureID = steve;

	meshList[GEO_STEVELEG] = MeshBuilder::GenerateOBJ("Wall", "OBJ//CharLeg.obj");
	meshList[GEO_STEVELEG]->textureID = steve;

	meshList[GEO_DOOR] = MeshBuilder::GenerateOBJ("Wall", "OBJ//Door.obj");
	meshList[GEO_DOOR]->textureID = LoadTGA("Image//Door.tga");

	meshList[GEO_LAMP] = MeshBuilder::GenerateOBJ("Lamp", "OBJ//Lamp.obj");
	meshList[GEO_LAMP]->textureID = textID;

	meshList[GEO_SHELVES] = MeshBuilder::GenerateOBJ("Shelves", "OBJ//shelves.obj");
	meshList[GEO_SHELVES]->textureID = wood;

	meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("Shelves", "OBJ//table.obj");
	meshList[GEO_TABLE]->textureID = wood;

	meshList[GEO_VENDING] = MeshBuilder::GenerateOBJ("VM", "OBJ//shelves.obj");
	meshList[GEO_VENDING]->textureID = LoadTGA("Image//vending.tga");

	meshList[GEO_TREE] = MeshBuilder::GenerateOBJ("Tree", "OBJ//Tree.obj");
	meshList[GEO_TREE]->textureID = wood;

	meshList[GEO_BUILDING] = MeshBuilder::GenerateOBJ("Building", "OBJ//building.obj");
	meshList[GEO_BUILDING]->textureID = LoadTGA("Image//b1.tga");

	meshList[GEO_BUILDING1] = MeshBuilder::GenerateOBJ("Building", "OBJ//building.obj");
	meshList[GEO_BUILDING1]->textureID = LoadTGA("Image//b2.tga");

	meshList[GEO_COKE] = MeshBuilder::GenerateOBJ("coke", "OBJ//coke.obj");
	meshList[GEO_COKE]->textureID = LoadTGA("Image//coke.tga");

	meshList[GEO_PYRAMID] = MeshBuilder::GenerateOBJ("pyramid", "OBJ//pryramidobj.obj");
	meshList[GEO_PYRAMID]->textureID = LoadTGA("Image//sand_2.tga");

	meshList[GEO_MOONBALL] = MeshBuilder::GenerateOBJ("moonball", "OBJ//moon.obj");
	meshList[GEO_MOONBALL]->textureID = LoadTGA("Image//m_front.tga");

	meshList[GEO_BULLET] = MeshBuilder::GenerateOBJ("model1", "OBJ//Missile.obj");
	meshList[GEO_BULLET]->textureID = LoadTGA("Image//coke.tga");

	meshList[GEO_BULLET2] = MeshBuilder::GenerateOBJ("bullet2", "OBJ//Missile.obj");
	meshList[GEO_BULLET2]->textureID = LoadTGA("Image//sand_2.tga");


	meshList[GEO_PYRAMIDNEW] = MeshBuilder::GenerateOBJ("pyramid", "OBJ//PyramidNew.obj");
	meshList[GEO_PYRAMIDNEW]->textureID = LoadTGA("Image//sand_2.tga");
	meshList[GEO_PYRAMIDWALL] = MeshBuilder::GenerateOBJ("Walls", "OBJ/Wall.obj");
	meshList[GEO_PYRAMIDWALL]->textureID = LoadTGA("Image//sand_2.tga");
	meshList[GEO_PYRAMIDPILLAR] = MeshBuilder::GenerateOBJ("Pillars", "OBJ//Pillar.obj");
	meshList[GEO_PYRAMIDPILLAR]->textureID = LoadTGA("Image//sand_2.tga");



	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSpheres("Sph", Color(1, 1, 1), 18, 36);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 16.0f / 9.0f, 0.1f, 10000.0f);
	projectionStack.LoadMatrix(projection);
}
static float LSPEED = 10.f;
static bool Lighting9 = true;
static int dialogue = 0;
void SP2::UpdateMenu()
{
	if (Input == "Menu")
	{
		switch (choose)
		{
		case STARTGAME:
			color = "Red1";
			if (Application::IsKeyPressed(VK_RETURN))
			{
				Input = "Game";
			}
			userInput(0);
			break;
		case OPTIONS:
			color = "Red2";
			if (Application::IsKeyPressed(VK_RETURN))
			{
				Input = "Options";
				c_option = O_SETTING;
				while (Application::IsKeyPressed(VK_RETURN))
				{
					Input = "Options";
					c_option = O_SETTING;
				}
			}
			userInput(0);
			break;
		case QUIT:
			color = "Red3";
			if (Application::IsKeyPressed(VK_RETURN))
			{
				Exit();
			}
			userInput(0);
			break;
		}
	}
	else if (Input == "Options")
	{
		switch (c_option)
		{
		case O_SETTING:
			color = "Red4";
			userInput(1);
			break;
		case O_QUIT:
			color = "Red5";
			if (Application::IsKeyPressed(VK_RETURN))
			{
				Input = "Menu";
				choose = STARTGAME;
				while (Application::IsKeyPressed(VK_RETURN))
				{
					Input = "Menu";
					choose = STARTGAME;
				}
			}
			userInput(1);
			break;
		}
	}
}
void SP2::userInput(int user)
{
	if (user == 0)
	{
		if (choose < MAX - 1)
		{
			if (Application::IsKeyPressed(VK_DOWN))
			{
				choose = static_cast<MENU>(choose + 1);
				cout << choose << endl;
			}
		}
		if (choose > STARTGAME)
		{
			if (Application::IsKeyPressed(VK_UP))
			{
				choose = static_cast<MENU>(choose - 1);
				cout << choose << endl;
			}
		}
		while (Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed(VK_DOWN))
		{
			choose = choose;
		}
	}
	if (user == 1)
	{
		if (c_option < O_MAX - 1)
		{
			if (Application::IsKeyPressed(VK_DOWN))
			{
				c_option = static_cast<OPTION>(c_option + 1);
				cout << c_option << endl;
			}
		}
		if (c_option > O_SETTING)
		{
			if (Application::IsKeyPressed(VK_UP))
			{
				c_option = static_cast<OPTION>(c_option - 1);
				cout << c_option << endl;
			}
		}
		while (Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed(VK_UP))
		{
			c_option = c_option;
		}
	}
}
void SP2::Update(double dt)
{
	if (Input == "Game")
	{
		Enemy_Updating(dt);
		Object_Updating(dt);
		Character_Movement(dt);
		//camera.Update(dt);
	}
	
	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
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


	//Shooting button
	if (Application::IsKeyPressed('H'))
		bullet.b_Count = 10;

	if (Application::IsKeyPressed('G'))
		bullet.Shoot(dt, camera);

	//Bullet movement
	if (bullet.shotFired)
	{
		bullet.b1_position += bullet.velocity * dt;
		bullet.b2_position += bullet.velocity * dt;
	}
	deltaTime = (1.0 / dt);

	UpdateMenu();
}
void SP2::Dialogue(string filename)
{
	ifstream myfile(filename.c_str());
	string line;
	string new_line;

	while (std::getline(myfile, line))
	{
		new_line = line + "\n";
		cout << new_line;
		my_arr.push_back(new_line);
	}
}
void SP2::RenderMesh(Mesh * mesh, bool enableLight)
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
void SP2::RenderText(Mesh* mesh, std::string text, Color color)
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
void SP2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
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
void SP2::RenderQuadOnScreen(Mesh* mesh, float size, float x, float y, float rotate)
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
	modelStack.Translate(x, y, 0);
	modelStack.Rotate(rotate, 1, 0, 0);
	RenderMesh(mesh, false);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}
static float SBSCALE1 = 1000.f;
void SP2::RenderSkybox()
{
		//modelStack.PushMatrix();
		////to do: transformation code here
		//modelStack.Translate(0, -20, -398);
		//modelStack.Rotate(90, 1, 0, 0);
		//modelStack.Rotate(180, 0, 0, 1);
		//modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
		//RenderMesh(meshList[GEO_FRONT], false);
		//modelStack.PopMatrix();

		//modelStack.PushMatrix();
		////to do: transformation code here
		//modelStack.Translate(0, 0, -0.9);
		//modelStack.Translate(0, -20, 600);
		//modelStack.Rotate(90, 1, 0, 0);
		//modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
		//RenderMesh(meshList[GEO_BACK], false);
		//modelStack.PopMatrix();

		//modelStack.PushMatrix();
		////to do: transformation code here
		//modelStack.Translate(5, 0, 0);
		//modelStack.Translate(-500, -20, 100);
		//modelStack.Rotate(-90, 0, 0, 1);
		//modelStack.Rotate(-180, 1, 0, 0);
		//modelStack.Rotate(90, 0, 1, 0);
		//modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
		//RenderMesh(meshList[GEO_LEFT], false);
		//modelStack.PopMatrix();

		//modelStack.PushMatrix();
		////to do: transformation code here	
		//modelStack.Translate(-5, 0, 0);
		//modelStack.Translate(500, -20, 100);
		//modelStack.Rotate(-90, 0, 0, 1);
		//modelStack.Rotate(90, 0, 1, 0);
		//modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
		//RenderMesh(meshList[GEO_RIGHT], false);
		//modelStack.PopMatrix();

		//modelStack.PushMatrix();
		////to do: transformation code here
		//modelStack.Translate(0, -500, 100);
		//modelStack.Rotate(180, 1, 0, 0);
		//modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
		//RenderMesh(meshList[GEO_BOTTOM], false);
		//modelStack.PopMatrix();

		//modelStack.PushMatrix();
		////to do: transformation code here
		//modelStack.Translate(0, -11, 0);
		//modelStack.Translate(0, 490, 100);
		//modelStack.Rotate(90, 0, 1, 0);
		//modelStack.Rotate(360, 0, 0, 1);
		//modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
		//RenderMesh(meshList[GEO_TOP], false);
		//modelStack.PopMatrix();
	
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
void SP2::Render()
{
	std::ostringstream oss;
	oss << "Camera X: " << camera.position.x;
	string var = oss.str();

	std::ostringstream oss1;
	oss1 << "Camera Z: " << camera.position.z;
	string var1 = oss1.str();

	/*std::ostringstream dia;
	dia << data[dialogue];
	string dialoguedata = dia.str();

	std::ostringstream diaV;
	diaV << data[dialogueVending];
	string dialogueV = diaV.str();

	std::ostringstream diaD;
	diaD << data[dialogueDoor];
	string dialogueD = diaD.str();

	std::ostringstream diaC;
	diaC << data[dialogueCoke];
	string dialogueC = diaC.str();

	std::ostringstream diaS;
	diaS << data[dialogueSteve];
	string dialogueS = diaS.str();*/
	std::ostringstream ammoOSS;
	std::ostringstream fpsOSS;
	if (Input == "Game")
	{
		fpsOSS << "FPS : " << deltaTime;
	
	
		ammoOSS << "AMMO : " << bullet.b_Count;
	}
	string Fps = fpsOSS.str();
	string ammo = ammoOSS.str();


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
//new code
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

	if (Input == "Game")
	{

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
		modelStack.Scale(30, 30, 30);
		modelStack.Translate(0, -1, 0);
		RenderMesh(meshList[GEO_MOONBALL], true);
		modelStack.PopMatrix();
	}

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
	modelStack.Scale(3, 3, 3);
	RenderSkybox();
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
	if (Input != "Game")
	{
		RenderQuadOnScreen(meshList[GEO_PATH], 6, 6.7, 5, 90);
	}
	RenderQuadOnScreen(meshList[GEO_COKE], 2, 5, 5, 0);


	
	if (Input == "Menu")
	{
		if (color == "Red1")
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Start", Color(1, 0, 0), 1.7, 5, 21);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Start", Color(0, 1, 0), 1.7, 5, 21);

		}
		if (color == "Red2")
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Options", Color(1, 0, 0), 1.7, 5, 20);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Options", Color(0, 1, 0), 1.7, 5, 20);

		}
		if (color == "Red3")
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Quit", Color(1, 0, 0), 1.7, 5, 19);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Quit", Color(0, 1, 0), 1.7, 5, 19);

		}
	}
	if (Input == "Options")
	{
		if (color == "Red4")
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Settings", Color(1, 0, 0), 1.7, 5, 19);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Settings", Color(0, 1, 0), 1.7, 5, 19);
		}
		if (color == "Red5")
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Quit", Color(1, 0, 0), 1.7, 5, 18);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Quit", Color(0, 1, 0), 1.7, 5, 18);
		}
	}

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

	modelStack.PushMatrix();
	modelStack.Translate(bullet.b1_position.x, bullet.b1_position.y, bullet.b1_position.z);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(bullet.b_Angel, 0, 1, 0);

	modelStack.Scale(0.3, 0.3, 0.3);
	RenderMesh(meshList[GEO_BULLET], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(bullet.b2_position.x, bullet.b2_position.y, bullet.b2_position.z);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(bullet.b_Angel, 0, 1, 0);


	modelStack.Scale(0.3, 0.3, 0.3);
	RenderMesh(meshList[GEO_BULLET2], true);
	modelStack.PopMatrix();

	var.resize(16);
	var1.resize(16);
	Fps.resize(11);
	//RenderTextOnScreen(meshList[GEO_TEXT], "Hold V for instructions", Color(1, 1, 0), 2, 1, 4);
	RenderTextOnScreen(meshList[GEO_TEXT], ammo, Color(1, 1, 0), 1.5, 1, 39);
	RenderTextOnScreen(meshList[GEO_TEXT], var, Color(1, 1, 0), 1.5, 1, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], var1, Color(1, 1, 0), 1.5, 1, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], Fps, Color(1, 1, 0), 1.5, 1, 1);
//	RenderTextOnScreen(meshList[GEO_TEXT], Key, Color(1, 1, 0),2,1,1);
	//RenderTextOnScreen(meshList[GEO_TEXT], Coke, Color(1, 1, 0), 2, 8, 1);

	modelStack.PopMatrix();




}
void SP2::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
void SP2::Enemy_Updating(float dt)
{
	Position P = { camera.position.x, camera.position.y, camera.position.z };
	for (int i = 0; i < 10; i++)
	{
		enemy[i] = enemy[i].Enemy_movement(enemy[i], P, 30 * dt);
	}
}
void SP2::Enemy_Rendering()
{
	for (int i = 0; i < 10; i++)
	{
		Position A = enemy[i].Return_Position(enemy[i]);
		modelStack.PushMatrix();
		modelStack.Translate(A.x, -20, A.z);
		modelStack.Scale(30, 30, 30);
		RenderMesh(meshList[GEO_COKE], true);
		modelStack.PopMatrix();
	}
	Enemy_Shooting();
}
void SP2::Enemy_Shooting()
{
	if (bullet.b1_position.y > 0)
	{
		for (int i = 0; i < 10; i++)
		{
			Position A = enemy[i].Return_Position(enemy[i]);
			float range = sqrt(((bullet.b1_position.x - A.x)*(bullet.b1_position.x - A.x)) + ((bullet.b1_position.z - A.z)*(bullet.b1_position.z - A.z)));
			if (range < 50)
			{
				enemy[i] = enemy[i].DamageReceived(enemy[i], 20);
				cout << "You hitted Enemy " << i << endl;
			}
		}
	}
	if (bullet.b2_position.y > 0)
	{
		for (int i = 0; i < 10; i++)
		{
			Position A = enemy[i].Return_Position(enemy[i]);
			float range = sqrt(((bullet.b1_position.x - A.x)*(bullet.b1_position.x - A.x)) + ((bullet.b1_position.z - A.z)*(bullet.b1_position.z - A.z)));
			if (range < 50)
			{
				enemy[i] = enemy[i].DamageReceived(enemy[i], 20);
				cout << "You hitted Enemy " << i << endl;
			}
		}
	}
}

void SP2::Map_Reading()
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

float Size = 10;
void SP2::Map_Rendering()
{
	modelStack.PushMatrix();

	modelStack.Translate(0, -20, 0);

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

bool SP2::Collision_Detection(Position Character)
{
	bool check = true;
	int X = 10 + (Character.x / Size);
	int Z = 10 + (Character.z / Size);
	if (X < 24 && X > 19)
	{
		X = 19;
	}
	if (Z < 24 && Z > 19)
	{
		Z = 19;
	}
	if (X > -4 && X < 0)
	{
		X = 0;
	}
	if (Z > -4 && Z < 0)
	{
		Z = 0;
	}
	cout << X << " / " <<Z<< endl;
	if (X > -1 && X < 20 && Z > -1 && Z < 20)
	{
		if (Map[X][Z] != char(' '))
		{
			check = false;
		}

	}
	return check;
}

void SP2::Character_Movement(float dt)
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
		if (Collision_Detection(VtoP(Test)))
		{
			camera.position = Test;
		}
		else
		{
			Test = camera.position;
		}
		Test.z += cos(DegreeToRadian(camera.cameraRotate.y)) * camera.cameraSpeed *dt;
		if (Collision_Detection(VtoP(Test)))
		{
			camera.position = Test;
		}
	}

	if (Application::IsKeyPressed('S'))
	{
		Test.x += sin(DegreeToRadian(camera.cameraRotate.y + 180)) * camera.cameraSpeed *dt;
		if (Collision_Detection(VtoP(Test)))
		{
			camera.position = Test;
		}
		else
		{
			Test = camera.position;
		}
		Test.z += cos(DegreeToRadian(camera.cameraRotate.y + 180)) * camera.cameraSpeed *dt;
		if (Collision_Detection(VtoP(Test)))
		{
			camera.position = Test;
		}
	}

	if (Application::IsKeyPressed('A'))
	{
		Test.x += sin(DegreeToRadian(camera.cameraRotate.y + 90)) * camera.cameraSpeed *dt;
		if (Collision_Detection(VtoP(Test)))
		{
			camera.position = Test;
		}
		else
		{
			Test = camera.position;
		}
		Test.z += cos(DegreeToRadian(camera.cameraRotate.y + 90)) * camera.cameraSpeed *dt;
		if (Collision_Detection(VtoP(Test)))
		{
			camera.position = Test;
		}
	}

	if (Application::IsKeyPressed('D'))
	{
		Test.x += sin(DegreeToRadian(camera.cameraRotate.y + 270)) * camera.cameraSpeed *dt;
		if (Collision_Detection(VtoP(Test)))
		{
			camera.position = Test;
		}
		else
		{
			Test = camera.position;
		}
		Test.z += cos(DegreeToRadian(camera.cameraRotate.y + 270)) * camera.cameraSpeed *dt;
		if (Collision_Detection(VtoP(Test)))
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


void SP2::RenderObjects(Mesh*mesh, float size, float x, float y, float z)
{

	modelStack.PushMatrix();
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, z);
	RenderMesh(mesh, true);


	modelStack.PopMatrix();
}


void SP2::Object_Reading()
{
	for (int i = 0; i < Num_Object; i++)
	{
		object[i].ItemType = Items::VENDINGMACHINE;
		object[i].position.Set(i * 10, 0, i * 10);
	}
	object_on_hand.ItemType = Items::None;
	object_on_hand.position.Set(camera.target.x * 1, -10, camera.target.z * 1);
	T_object_Num = -1;
}

void SP2::Object_Rendering()
{
	modelStack.PushMatrix();
	modelStack.Scale(10, 10, 10);
	for (int i = 0; i < Num_Object; i++)
	{
		if (object[i].ItemType == Items::VENDINGMACHINE)
		{
			modelStack.PushMatrix();
			modelStack.Translate(object[i].position.x, object[i].position.y, object[i].position.z);
			RenderMesh(meshList[GEO_COKE], true);
			modelStack.PopMatrix();
		}
	}
	if (object_on_hand.ItemType == Items::VENDINGMACHINE)
	{
		modelStack.PushMatrix();
		modelStack.Scale(10, 10, 10);
		modelStack.Translate(object_on_hand.position.x, object_on_hand.position.y, object_on_hand.position.z);
		RenderMesh(meshList[GEO_COKE], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();
}

void SP2::Object_Updating(float dt)
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
	object_on_hand.position.Set(camera.target.x * 1, -10, camera.target.z * 1);
}
