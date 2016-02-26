#include "GL\glew.h"
#include "Cutscene.h"

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
Cutscene::Cutscene()
{
}
Cutscene::~Cutscene()
{
}
void Cutscene::Init()
{
	srand(time(NULL));
	Map_Reading();

	JumpTime = 0;


	PressTime = 0;

	camera.cameraRotate = Vector3(0, 140, 0);

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
	light[3].color.Set(1, 0, 0);
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
	if (planePos2 < 1200)
	{
		camera.Init(Vector3(220, 0, 195), Vector3(0, 0, 0), Vector3(0, 1, 0));
	}
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

	GLuint pyramid = LoadTGA("Image//Scene_Pyramid.tga");
	meshList[GEO_PYRAMIDNEW] = MeshBuilder::GenerateOBJ("pyramid", "OBJ//PyramidNew.obj");
	meshList[GEO_PYRAMIDNEW]->textureID = pyramid;
	meshList[GEO_PYRAMIDDOOR] = MeshBuilder::GenerateOBJ("pyramid", "OBJ//PyramidDoor.obj");
	meshList[GEO_PYRAMIDDOOR]->textureID = LoadTGA("Image//Scene_slabs.tga");
	meshList[GEO_PYRAMIDWALL] = MeshBuilder::GenerateOBJ("Walls", "OBJ/Wall.obj");
	meshList[GEO_PYRAMIDWALL]->textureID = pyramid;

	GLuint plane = LoadTGA("Image//Scene_Plane.tga");
	meshList[GEO_PLANEBODY] = MeshBuilder::GenerateOBJ("Star", "OBJ//planebody.obj");
	meshList[GEO_PLANEBODY]->textureID = plane;

	meshList[GEO_PLANEWING] = MeshBuilder::GenerateOBJ("Star", "OBJ//planewing.obj");
	meshList[GEO_PLANEWING]->textureID = plane;

	meshList[GEO_PLANEROCKET] = MeshBuilder::GenerateOBJ("Star", "OBJ//planerocket.obj");
	meshList[GEO_PLANEROCKET]->textureID = plane;

	meshList[GEO_MOONBALL] = MeshBuilder::GenerateOBJ("moonball", "OBJ//moon.obj");
	meshList[GEO_MOONBALL]->textureID = LoadTGA("Image//Scene_moon.tga");

	meshList[GEO_EXPLOSION] = MeshBuilder::GenerateOBJ("moonball", "OBJ//Explode.obj");
	meshList[GEO_EXPLOSION]->textureID = LoadTGA("Image//Scene_Explosion.tga");

	meshList[GEO_THRUSTER] = MeshBuilder::GenerateOBJ("moonball", "OBJ//thruster.obj");
	meshList[GEO_THRUSTER]->textureID = LoadTGA("Image//Scene_Thruster.tga");

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 16.0f / 9.0f, 0.1f, 10000.0f);
	projectionStack.LoadMatrix(projection);
}
void Cutscene::Update(double dt)
{
	/*if (planePos2 < 1200)
	{
		camera.Init(Vector3(220, 0, 195), Vector3(0, 0, 0), Vector3(0, 1, 0));
	}*/
	if (planePos2 >= 1200)
	{
		camera.Init(Vector3(400, 20, 2), Vector3(0, 0, 0), Vector3(0, 1, 0));
		camera.cameraRotate= Vector3(-10, 270, 0);
		randNum = (rand() % 4) + 1;
	}
	if (planePos2 >= 1100)
	{
		blowUp = true;
		if (explosionScale < 200)
		{
			explosionScale += (float)(50 * dt);
		}
	}
	if (planePos < 10)
	{
		planePos += (float)(10 * dt);
	}

	if (planePos >= 10 && planePos2 < 1200)
	{
		planePos2 += (float)(1000 * dt);
		if (thrusterScale < 1)
		{
			thrusterScale += (float)(10 * dt);
		}
	}
	Character_Movement(dt);
	//Debugging purpose
	if (Application::IsKeyPressed('P'))
	{
		SharedData::GetInstance()->stateCheck = true;
		SharedData::GetInstance()->gameState = SharedData::SCENE2;
	}
}
//Reading from text file
void Cutscene::Dialogue(string filename)
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
bool Lighting9 = true;
void Cutscene::RenderMesh(Mesh * mesh, bool enableLight)
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
void Cutscene::RenderText(Mesh* mesh, std::string text, Color color)
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
void Cutscene::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
void Cutscene::RenderQuadOnScreen(Mesh* mesh, float size, float x, float y, float rotate, float rx, float ry, float rz, float z)
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
void Cutscene::RenderSkybox()
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
void Cutscene::Render()
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
	std::ostringstream partscountOSS;

	ammoOSS << SharedData::GetInstance()->bullet.quantity;
	goldOSS << SharedData::GetInstance()->gold.quantity;
	bombOSS << SharedData::GetInstance()->bomb.quantity;
	oreOSS << SharedData::GetInstance()->mineral.quantity;
	eggOSS << SharedData::GetInstance()->egg.quantity;

	partscountOSS << "SpaceShip Parts: " << parts << "/2";
	fpsOSS << "FPS : " << deltaTime;
	string Fps = fpsOSS.str();
	string ammo = ammoOSS.str();
	string bomb = bombOSS.str();
	string egg = eggOSS.str();
	string ore = oreOSS.str();
	string s_gold = goldOSS.str();
	string partscount = partscountOSS.str();

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
	modelStack.PushMatrix();
	Map_Rendering();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, 0);
	modelStack.Scale(30, 30, 30);

	RenderMesh(meshList[GEO_MOONBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(planePos2, planePos, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(5, 5, 5);
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_PLANEBODY], true);
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_PLANEROCKET], true);
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_PLANEWING], true);
	modelStack.PushMatrix();
	modelStack.Translate(0, 3.6, -3);
	modelStack.Scale(thrusterScale, thrusterScale, thrusterScale);
	RenderMesh(meshList[GEO_THRUSTER], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	if (blowUp)
	{
		modelStack.PushMatrix();
		modelStack.Scale(explosionScale, explosionScale, explosionScale);
		RenderMesh(meshList[GEO_EXPLOSION], false);
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
	RenderMesh(meshList[GEO_PYRAMIDDOOR], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(0, -20, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(2000, 1, 2000);
	RenderMesh(meshList[GEO_QUAD], false);
	modelStack.PopMatrix();

	var.resize(16);
	var1.resize(16);
	Fps.resize(11);
	RenderTextOnScreen(meshList[GEO_TEXT], shop, Color(0.4, 0.6, 1), 1.5, 7, 7);

	RenderTextOnScreen(meshList[GEO_TEXT], var, Color(1, 1, 0), 1.5, 1, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], var1, Color(1, 1, 0), 1.5, 1, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], Fps, Color(1, 1, 0), 1.5, 1, 39);

	if (storyDismiss && npc.interactDia != "You have fixed the ship. Loading...")
	{
		RenderQuadOnScreen(meshList[GEO_CROSSHAIR], 1, 40, 30, 90, 1, 0, 0, 1);
	}
}

void Cutscene::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
void Cutscene::Enemy_Updating(float dt)
{
	Position P = { camera.position.x, camera.position.y, camera.position.z };
	for (int i = 0; i < 5; i++)
	{
		enemy[i] = enemy[i].Enemy_movement(enemy[i], P, 30 * dt, Size, Map, enemy, i, Z_Displacement, X_Displacement);
	}
	camera = enemy[0].enemy_attack(enemy,VtoP(camera.position),camera);
}
void Cutscene::Enemy_Rendering()
{
	for (int i = 0; i < 5; i++)
	{
		Position A = enemy[i].Return_Position(enemy[i]);
		modelStack.PushMatrix();
		modelStack.Translate(A.x, -20, A.z);
		modelStack.Scale(2, 2, 2);
		RenderMesh(meshList[GEO_COKE], true);
		modelStack.PopMatrix();
	}
}
void Cutscene::Map_Reading()
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
void Cutscene::Map_Rendering()
{
	modelStack.PushMatrix();

	modelStack.Translate(X_Displacement, -22.5, Z_Displacement);

	modelStack.PushMatrix();
	modelStack.Scale(2.5 * Size, 2.5 * Size, 2.5 * Size);
	RenderMesh(meshList[GEO_PYRAMIDNEW], false);
	modelStack.PushMatrix();
	modelStack.Scale(Size, (2 / (2.5*Size)), Size);
	RenderMesh(meshList[GEO_PYRAMIDWALL], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	camera.position.y = -10;
}
void Cutscene::Character_Movement(float dt)
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
	if (randNum == 1)
	{
		camera.cameraRotate.y += (float)(100 * dt);
	}
	if (randNum == 2)
	{
		camera.cameraRotate.y -= (float)(100 * dt);
		followy -= (float)(100 * dt);
	}
	if (randNum == 3)
	{
		camera.cameraRotate.x -= (float)(100 * dt);
	}
	if (randNum == 4)
	{
		camera.cameraRotate.x += (float)(100 * dt);
	}

	//Moving the camera
	Vector3 Test = camera.position;
	//Changing target
	camera.target = Vector3(sin(DegreeToRadian(camera.cameraRotate.y))*cos(DegreeToRadian(camera.cameraRotate.x)) + camera.position.x, -sin(DegreeToRadian(camera.cameraRotate.x)) + camera.position.y,
		cos(DegreeToRadian(camera.cameraRotate.y))*cos(DegreeToRadian(camera.cameraRotate.x)) + camera.position.z);
	camera.view = (camera.target - camera.position).Normalized();
	Vector3 right = camera.view.Cross(camera.defaultUp);
	right.y = 0;
	camera.up = right.Cross(camera.view);
}