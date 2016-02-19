#include "GL\glew.h"
#include "SceneMenu.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "MeshBuilder.h"
#include "Utility.h"
#include "SharedData.h"
#include "LoadTGA.h"
#include <sstream>


SceneMenu::SceneMenu()
{
}
SceneMenu::~SceneMenu()
{
}
void SceneMenu::Init()
{
	srand(time(NULL));
	icon = 31.6;
	icon2 = 19;
	menuIcon = 116;

	choose = menushop.STARTGAME;
	c_option = menushop.O_SETTING;
	Input = "Menu";
	Dialogue("Text//Dialogue1.txt");

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

	meshList[GEO_PATH] = MeshBuilder::GenerateQuad("land", Color(1, 1, 1), 14, 13);
	meshList[GEO_PATH]->textureID = LoadTGA("Image//Menu.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Text2.tga");

	GLuint wood = LoadTGA("Image//book.tga");
	GLuint textID = LoadTGA("Image//Chair.tga");
	meshList[GEO_BENCH] = MeshBuilder::GenerateOBJ("bench", "OBJ//Bench.obj");
	meshList[GEO_BENCH]->textureID = wood;

	GLuint santa = LoadTGA("Image//Santa.tga");
	

	meshList[GEO_VENDING] = MeshBuilder::GenerateOBJ("VM", "OBJ//shelves.obj");
	meshList[GEO_VENDING]->textureID = LoadTGA("Image//vending.tga");

	meshList[GEO_BUILDING] = MeshBuilder::GenerateOBJ("Building", "OBJ//building.obj");
	meshList[GEO_BUILDING]->textureID = LoadTGA("Image//b1.tga");

	meshList[GEO_COKE] = MeshBuilder::GenerateOBJ("coke", "OBJ//coke.obj");
	meshList[GEO_COKE]->textureID = LoadTGA("Image//coke.tga");

	meshList[GEO_STAR] = MeshBuilder::GenerateOBJ("Star", "OBJ//Star.obj");
	meshList[GEO_STAR]->textureID = LoadTGA("Image//sand_2.tga");

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSpheres("Sph", Color(1, 1, 1), 18, 36);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 16.0f / 9.0f, 0.1f, 10000.0f);
	projectionStack.LoadMatrix(projection);
}
static float LSPEED = 10.f;
static bool Lighting9 = true;
void SceneMenu::UpdateMenu()
{
	if (Input == "Menu")
	{
		switch (choose)
		{
		case MenuShop::STARTGAME:
			color = "Red1";
			menuIcon = 116;
			if (Application::IsKeyPressed(VK_RETURN))
			{
				SharedData::GetInstance()->stateCheck = true;
				SharedData::GetInstance()->gameState = SharedData::GAME;
			}
			userInput(0);
			break;
		case MenuShop::OPTIONS:
			color = "Red2";
			if (Application::IsKeyPressed(VK_RETURN))
			{
				menuIcon = 105;
				Input = "Options";
				c_option = MenuShop::O_SETTING;
			}
			userInput(0);
			break;
		case MenuShop::QUIT:
			color = "Red3";
			if (Application::IsKeyPressed(VK_RETURN))
			{
				SharedData::GetInstance()->gameState = SharedData::QUIT;
			}
			userInput(0);
			break;
		}
	}
		if (Input == "Options")
		{
			switch (c_option)
			{
			case MenuShop::O_SETTING:
				color = "Red4";
				userInput(1);
				break;
			case MenuShop::O_QUIT:
				color = "Red5";
				if (Application::IsKeyPressed(VK_RETURN))
				{
					Input = "Menu";
					choose = MenuShop::STARTGAME;
					while (Application::IsKeyPressed(VK_RETURN))
					{
						Input = "Menu";
						choose = menushop.STARTGAME;
					}
				}
				userInput(1);
				break;
			}
		}
}
void SceneMenu::userInput(int user)
{
	if (user == 0)
	{
		if (choose < MenuShop::MAX - 1)
		{
			if (Application::IsKeyPressed(VK_DOWN) && menushop.PressTime == 0)
			{
				menuIcon -= 6;
				menushop.PressTime = deltaTime / 10;
				choose = static_cast<MenuShop::MENU>(choose + 1);
				cout << choose << endl;
			}
		}
		if (choose > MenuShop::STARTGAME)
		{
			if (Application::IsKeyPressed(VK_UP) && menushop.PressTime == 0)
			{
				menuIcon += 6;
				menushop.PressTime = deltaTime / 10;
				choose = static_cast<MenuShop::MENU>(choose - 1);
				cout << choose << endl;
			}
		}

	}
	if (user == 1)
	{
		if (c_option < MenuShop::O_MAX - 1)
		{
			if (Application::IsKeyPressed(VK_DOWN) && menushop.PressTime == 0)
			{
				menuIcon -= 6;
				menushop.PressTime = deltaTime / 10;
				c_option = static_cast<MenuShop::OPTION>(c_option + 1);
				cout << c_option << endl;
			}
		}
		if (c_option > MenuShop::O_SETTING)
		{
			if (Application::IsKeyPressed(VK_UP) && menushop.PressTime == 0)
			{
				menuIcon += 6;
				menushop.PressTime = deltaTime / 10;
				c_option = static_cast<MenuShop::OPTION>(c_option - 1);
				cout << c_option << endl;
			}
		}
	}
}
void SceneMenu::Update(double dt)
{
	if (menushop.PressTime > 0)
	{
		menushop.PressTime -= 1;
	}
	else
	{
		menushop.PressTime = 0;
	}

	rotateCoke += (float)(100 * dt);

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

	/*if (Application::IsKeyPressed('H'))
	{
		b_Ammo = 30;
		if (menushop.shopInput != "Buy" && Input == "Game")
		{
			menushop.shopInput = "Shop";
		}
	}

	if (Application::IsKeyPressed('G'))
	{
		if (b_Ammo > 0)
		{
			startCoolDdown = true;
			if (b_coolDown == b_coolDownLimit)
			{
				b_Ammo--;
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
	}*/

	//for (vector<Bullet*>::iterator iter = bullet_arr.begin(); iter != bullet_arr.end();)
	//{

	//	//if destory bullet = true 
	//	if ((*iter)->Update(dt))
	//	{
	//		iter = bullet_arr.erase(iter);
	//	}
	//	else
	//	{
	//		iter++;
	//	}

	//}

	deltaTime = (1.0 / dt);

	UpdateMenu();
}
void SceneMenu::Dialogue(string filename)
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
void SceneMenu::RenderMesh(Mesh * mesh, bool enableLight)
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
void SceneMenu::RenderText(Mesh* mesh, std::string text, Color color)
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
void SceneMenu::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
void SceneMenu::RenderQuadOnScreen(Mesh* mesh, float size, float x, float y, float rotate, float rx, float ry, float rz, float z)
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
static float SBSCALE1 = 1000.f;

void SceneMenu::Render()
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
	/*if (Input == "Game")
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
	}*/

	////Move skybox
	//modelStack.PushMatrix();
	//modelStack.Translate(0 + camera.position.x, 0, -90 + camera.position.z + 50);
	//modelStack.Scale(3, 3, 3);
	//RenderSkybox();
	//modelStack.PopMatrix();
	
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
	
	RenderQuadOnScreen(meshList[GEO_STAR], 0.3, 20, menuIcon, rotateCoke, 0, 1, 0,2);

	RenderQuadOnScreen(meshList[GEO_PATH], 6, 6.7, menu_pos, 90, 1, 0, 0,0);
	
	/*if (menushop.shopInput == "Shop")
	{
		int j = 21;
		RenderQuadOnScreen(meshList[GEO_COKE], 1, 6, icon, rotateCoke,0,1,0,0);
		RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(0, 1, 0), 1.7, 4, icon2);
		for (int arr = 0; arr < my_arr.size() - 3; ++arr)
		{
			--j;
			RenderTextOnScreen(meshList[GEO_TEXT], my_arr[arr], Color(1, 1, 1), 1.7, 5, j);
		}
	}
	if (menushop.shopInput == "Buy")
	{
		int j = 18;
		RenderQuadOnScreen(meshList[GEO_COKE], 1, 6, icon, rotateCoke, 0, 1, 0, 0);
		for (int arr = 6; arr < my_arr.size(); ++arr)
		{
			--j;
			RenderTextOnScreen(meshList[GEO_TEXT], my_arr[arr], Color(1, 1, 1), 1.7, 5, j);
		}
		if (b_gold)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "No more gold!", Color(1, 1, 1), 1.7, 10, 20);
		}
	}*/
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
	var.resize(16);
	var1.resize(16);
	Fps.resize(11);
	RenderTextOnScreen(meshList[GEO_TEXT], ammo, Color(1, 1, 0), 1.5, 1, 39);
	RenderTextOnScreen(meshList[GEO_TEXT], s_gold, Color(1, 1, 0), 1.5, 45, 39);
	RenderTextOnScreen(meshList[GEO_TEXT], var, Color(1, 1, 0), 1.5, 1, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], var1, Color(1, 1, 0), 1.5, 1, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], Fps, Color(1, 1, 0), 1.5, 1, 1);
	modelStack.PopMatrix();
}
void SceneMenu::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}