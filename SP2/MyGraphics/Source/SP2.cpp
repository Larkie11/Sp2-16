#include "GL\glew.h"
#include "SP2.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>
#include <iostream>
using std::cout;
using std::endl;

SP2::SP2()
{
}
SP2::~SP2()
{
}
void SP2::Init()
{
	choose = STARTGAME;
	c_option = O_SETTING;
	Input = "Menu";
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

	m_parameters[U_MVP] = glGetUniformLocation(m_programID,"MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID,"MV");
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

	glUniform1i(m_parameters[U_NUMLIGHTS],6);

	//Initialize camera settings
	camera.Init(Vector3(-3, 0, 70), Vector3(0, 0, 0), Vector3(0, 1, 0));
	meshList[GEO_REF_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	//meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1, 0));
	meshList[GEO_QUAD] = MeshBuilder::GenerateRepeatQuad("quad", Color(1, 1, 0), 1, 1,10);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//Tile.tga");
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_FLOOR] = MeshBuilder::GenerateRepeatQuad("floor", Color(1, 1, 1),1.015,1,10);
	meshList[GEO_FLOOR]->textureID = LoadTGA("Image//Tile2.tga");
	meshList[GEO_FLOOR]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_FLOOR]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_FLOOR]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_FLOOR]->material.kShininess = 1.f;

	meshList[GEO_BROAD] = MeshBuilder::GenerateRepeatQuad("floor", Color(1, 1, 1), 30, 7,10);
	meshList[GEO_BROAD]->textureID = LoadTGA("Image//tile3.tga");
	meshList[GEO_BROAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BROAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_BROAD]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_BROAD]->material.kShininess = 1.f;

	meshList[GEO_PATH] = MeshBuilder::GenerateRepeatQuad("floor", Color(1, 1, 1), 10, 0.5,10);
	meshList[GEO_PATH]->textureID = LoadTGA("Image//path.tga");
	meshList[GEO_PATH]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_PATH]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_PATH]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_PATH]->material.kShininess = 1.f;

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
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//GungsuhChe.tga");

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

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSpheres("Sph", Color(1, 1, 1), 18, 36);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 16.0f / 9.0f, 0.1f, 10000.0f);
	projectionStack.LoadMatrix(projection);

	door = false;
	string no1 = "I found a key, do you want it? Y/N"; //0
	string no2 = "Here you go!";	                   //1
	string no3 = "Oh, ok then..";                      //2
	string no4 = "I gave you the key already";         //3

	string no5 = "Pick the can of coke up? Y/N";       //4
	string no6 = "Picked up can of coke";              //5
	string no7 = "You did not pick up the coke";       //6

	string no8 = "Out of drinks";                      //7
	string no9 = "Return can of coke? Y/N";            //8
	string no10 = "Returned can of coke";              //9
	string no11 = "You did not return the coke";       //10
	
	string no12 = "You need a key first, hint: Santa"; //11
	string no13 = "Press E";                           //12

	string no14 = "Hi! I'm here to help! Press Y!";    //13
	string no15 = "Keep pressing Y to continue!";       //14
	string no16 = "W,A,S,D to move!";                 //15
	string no17 = "Up,down,left,right to change view!";//16
	string no18 = "Hold V to see all the instructions!";//17

	data.push_back(no1);
	data.push_back(no2);
	data.push_back(no3);
	data.push_back(no4);
	data.push_back(no5);
	data.push_back(no6);
	data.push_back(no7);
	data.push_back(no8);
	data.push_back(no9);
	data.push_back(no10);
	data.push_back(no11);
	data.push_back(no12);
	data.push_back(no13);
	data.push_back(no14);
	data.push_back(no15);
	data.push_back(no16);
	data.push_back(no17);	
	data.push_back(no18);
	night = true;
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
			break;
		case QUIT:
			color = "Red3";
			if (Application::IsKeyPressed(VK_RETURN))
			{
				Exit();
			}
			break;
		}
		if (choose < MAX - 1)
		{
			if (Application::IsKeyPressed(VK_DOWN))
			{
				choose = static_cast<MENU>(choose + 1);
				cout << choose << endl;
				while (Application::IsKeyPressed(VK_DOWN))
				{
					choose = choose;
				}
			}
		}
		if (choose > STARTGAME)
		{
			if (Application::IsKeyPressed(VK_UP))
			{
				choose = static_cast<MENU>(choose - 1);
				cout << choose << endl;
				while (Application::IsKeyPressed(VK_UP))
				{
					choose = choose;
				}
			}
		}
	}
	else if (Input == "Options")
	{
		switch (c_option)
		{
		case O_SETTING:
			Red4 = true;
			Red5 = false;
			break;
		case O_QUIT:
			Red4 = false;
			Red5 = true;
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
			break;
		}
		if (c_option < O_MAX - 1)
		{
			if (Application::IsKeyPressed(VK_DOWN))
			{
				c_option = static_cast<OPTION>(c_option + 1);
				cout << c_option << endl;
				while (Application::IsKeyPressed(VK_DOWN))
				{
					c_option = c_option;
				}
			}
		}
		if (c_option > O_SETTING)
		{
			if (Application::IsKeyPressed(VK_UP))
			{
				c_option = static_cast<OPTION>(c_option - 1);
				cout << c_option << endl;
				while (Application::IsKeyPressed(VK_UP))
				{
					c_option = c_option;
				}
			}
		}
	}
}

void SP2::Update(double dt)
{
	if (Input == "Game")
	{
		camera.Update(dt);
	}
	
	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	if (Application::IsKeyPressed('5'))
	{
		light[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);

		light[1].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	}
	if (Application::IsKeyPressed('6'))
	{
		//light[0].type = Light::LIGHT_SPOT;
		//glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);

		light[1].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	}
	if (Application::IsKeyPressed('7'))
	{
		//light[0].type =Light::LIGHT_DIRECTIONAL;
		//glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);

		light[1].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	}
		
	if (Application::IsKeyPressed('I'))
		light[4].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[4].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[4].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[4].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[4].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[4].position.y += (float)(LSPEED * dt);

	if (Application::IsKeyPressed('Z'))
	{
		Lighting9 = false;
	}

	else if (Application::IsKeyPressed('X'))
	{
		Lighting9 = true;
		
	}

	


	deltaTime = (1.0 / dt);

	UpdateMenu();

	if (camera.position.x > 10 && camera.position.x < 40 && camera.position.z > -42 && camera.position.z < -20)
	{
		showS = true;
		if (showS)
		{
			if (Application::IsKeyPressed('Y'))
			{
				if (dialogueSteve < data.size()-1)
				{
					++dialogueSteve;
				}
				while (Application::IsKeyPressed('Y'))
				{
					dialogueSteve = dialogueSteve;
				}
			}
		}
	}

	else
	{
		showS = false;
		dialogueSteve = 13;
	}

	if (Application::IsKeyPressed('R'))
	{
		key1 = 0;
		night = 1;
		coca = 0;
		returned = false;
		cokeY = 2.5;
		Lighting9 = true;
	}

	if (camera.position.z > -30 && camera.position.z <0 && camera.position.x > 150 && camera.position.x < 190)
	{
		showV = true;
		if (coca == 1)
		{
			if (Application::IsKeyPressed('Y'))
			{
				dialogueVending = 9;
				coca = 0;
				returned = true;
				cokeY = -30;
			}
			if (Application::IsKeyPressed('N'))
			{
				dialogueVending = 10;
			}
		}
	}
	
	else
	{
		showV = false;
		//didnt return can of coke
		if (coca == 1)
		{
			dialogueVending = 8;
		}

		else if (coca == 0 && returned == false)
		{
			dialogueVending = 7;
		}
		else if (returned)
		{
			dialogueVending = 9;
		}
	}

	if (coca == 1)
	{
		cokeX = camera.position.x;
		cokeY = camera.position.y;
		if (Application::IsKeyPressed(VK_LEFT))
		{
			rotateCokeY +=(float)(100*dt);
		}
		if (Application::IsKeyPressed(VK_RIGHT))
		{
			rotateCokeY -= (float)(100 * dt);
		}
	}

	//table
	if (camera.position.z < -100 && camera.position.z >-180 && camera.position.x > 290 && camera.position.x < 340)
	{
		showC = true;
			if (Application::IsKeyPressed('Y'))
			{
				dialogueCoke = 5;
				coca = 1;
				cokeFollow = true;
			}

			if (Application::IsKeyPressed('N'))
			{
				dialogueCoke = 6;
			}
	}
	else
	{
		showC = false;
		if (cokeY == -7)
		{
			dialogueCoke = 4;
		}
	}
	if (Application::IsKeyPressed('V'))
	{
		showInstructions = true;
	}
	else
	{
		showInstructions = false;
	}
	cokeX += camera.position.x + 0.1;
	cokeZ += camera.position.z + 0.1;
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

static float SBSCALE1 = 1000.f;
void SP2::RenderSkybox()
{
	if (night == 0)
	{
		modelStack.PushMatrix();
		//to do: transformation code here
		modelStack.Translate(0, -20, -398);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Rotate(180, 0, 0, 1);
		modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
		RenderMesh(meshList[GEO_FRONT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		//to do: transformation code here
		modelStack.Translate(0, 0, -0.9);
		modelStack.Translate(0, -20, 600);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
		RenderMesh(meshList[GEO_BACK], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		//to do: transformation code here
		modelStack.Translate(5, 0, 0);
		modelStack.Translate(-500, -20, 100);
		modelStack.Rotate(-90, 0, 0, 1);
		modelStack.Rotate(-180, 1, 0, 0);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
		RenderMesh(meshList[GEO_LEFT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		//to do: transformation code here	
		modelStack.Translate(-5, 0, 0);
		modelStack.Translate(500, -20, 100);
		modelStack.Rotate(-90, 0, 0, 1);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
		RenderMesh(meshList[GEO_RIGHT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		//to do: transformation code here
		modelStack.Translate(0, -500, 100);
		modelStack.Rotate(180, 1, 0, 0);
		modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
		RenderMesh(meshList[GEO_BOTTOM], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		//to do: transformation code here
		modelStack.Translate(0, -11, 0);
		modelStack.Translate(0, 490, 100);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Rotate(360, 0, 0, 1);
		modelStack.Scale(SBSCALE1, SBSCALE1, SBSCALE1);
		RenderMesh(meshList[GEO_TOP], false);
		modelStack.PopMatrix();
	}
	if (night == 1)
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
}

void SP2::RenderMuseum()
{
	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Translate(0, -20, -398);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(700, 700, 700);
	RenderMesh(meshList[GEO_FRONT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Translate(0, 0, -0.9);
	modelStack.Translate(0, -20, 600);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(700, 700, 700);
	RenderMesh(meshList[GEO_BACK], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Translate(5, 0, 0);
	modelStack.Translate(-500, -20, 100);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(-180, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(700, 700, 700);
	RenderMesh(meshList[GEO_LEFT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here	
	modelStack.Translate(-5, 0, 0);
	modelStack.Translate(500, -20, 100);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(700, 700, 700);
	RenderMesh(meshList[GEO_RIGHT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Translate(0, -500, 100);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(700, 700, 700);
	RenderMesh(meshList[GEO_BOTTOM], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Translate(0, -11, 0);
	modelStack.Translate(0, 490, 100);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(360, 0, 0, 1);
	modelStack.Scale(700, 700, 700);
	RenderMesh(meshList[GEO_TOP], true);
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

	std::ostringstream dia;
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
	string dialogueS = diaS.str();

	std::ostringstream fpsOSS;
	if (Input == "Game")
	{
		fpsOSS << "FPS: " << deltaTime;
	}
	string Fps = fpsOSS.str();

	std::ostringstream keyOSS;
	keyOSS << "Key: " << key1;
	string Key = keyOSS.str();

	std::ostringstream cokeOSS;
	cokeOSS << "Coke: " << coca;
	string Coke = cokeOSS.str();


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

	modelStack.PushMatrix();
	modelStack.Translate(0, 1, 0);

	
	//Move skybox
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 0, -90 + camera.position.z + 50);
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

	if (door)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], dialogueD, Color(1, 1, 0), 2, 6, 10);
	}

	if (showV)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], dialogueV, Color(1, 1, 0), 2, 6, 10);
	}

	if (showC)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], dialogueC, Color(1, 1, 0), 2, 6, 10);
	}

	if (showS)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], dialogueS, Color(1, 1, 0), 2, 6, 10);
	}


	if (showInstructions)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Up,down,left,right to shift character view" , Color(1, 0, 0), 1.7, 2, 21);
		RenderTextOnScreen(meshList[GEO_TEXT], "W, A, S, D to move", Color(1, 0, 0), 1.7, 2, 20);
		RenderTextOnScreen(meshList[GEO_TEXT], "Z/X to on/off light", Color(1, 0, 0), 1.7, 2, 19);

		RenderTextOnScreen(meshList[GEO_TEXT], "Move near to objects to see interaction", Color(1, 0, 1), 1.7, 2, 17);
		RenderTextOnScreen(meshList[GEO_TEXT], "Interactions: Door,NPC,Vending machine,Coke", Color(1, 0, 1), 1.7, 2, 16);
		RenderTextOnScreen(meshList[GEO_TEXT], "Different things happens based on your choice", Color(1, 0, 1), 1.7, 2, 14);
	}

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
		if (Red4)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Settings", Color(1, 0, 0), 1.7, 5, 19);
		}
		if (Red4==false)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Settings", Color(0, 1, 0), 1.7, 5, 19);
		}
		if (Red5)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Quit", Color(1, 0, 0), 1.7, 5, 18);
		}
		if (Red5==false)
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

	RenderTextOnScreen(meshList[GEO_TEXT], "Hold V for instructions", Color(1, 1, 0), 2, 1, 4);
	RenderTextOnScreen(meshList[GEO_TEXT], Fps, Color(1, 1, 0), 2, 1, 29);
	RenderTextOnScreen(meshList[GEO_TEXT], var, Color(1, 1, 0), 2, 1, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], var1, Color(1, 1, 0), 2, 1, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], Key, Color(1, 1, 0),2,1,1);
	RenderTextOnScreen(meshList[GEO_TEXT], Coke, Color(1, 1, 0), 2, 8, 1);

	modelStack.PopMatrix();
}
void SP2::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}