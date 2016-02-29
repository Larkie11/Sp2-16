#include "GL\glew.h"
#include "Shop.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "SharedData.h"
#include <sstream>

//This class is to rendeer the shop scene
Shop::Shop()
{
}
Shop::~Shop()
{
}
void Shop::Init()
{
	npc.spaceDoor.Nposition = Vector3(-90, -20, 0);
	npc.seller.Nposition = Vector3(20, -20, 0);

	icon = 31.6;
	icon2 = 19;
	Dialogue("Text//Shop.txt");
	PressTime = 0;
	sound.playMusic("Music//Shop.mp3");
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

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

	//Initialize camera settings
	camera.Init(Vector3(-30, -10, 0), Vector3(0, 0, 0), Vector3(0, 1, 0));
	camera.cameraRotate.y = -270;
	meshList[GEO_REF_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	//meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1, 0));
	meshList[GEO_QUAD] = MeshBuilder::GenerateRepeatQuad("quad", Color(1, 1, 0), 1, 1, 10);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//Shop_Floor.tga");
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_CEILING] = MeshBuilder::GenerateRepeatQuad("floor", Color(1, 1, 1), 1, 1, 10);
	meshList[GEO_CEILING]->textureID = LoadTGA("Image//Shop_Floor.tga");
	meshList[GEO_CEILING]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CEILING]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_CEILING]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_CEILING]->material.kShininess = 1.f;

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
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//_Font.tga");

	meshList[GEO_SHOPICON] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 5, 1);
	meshList[GEO_SHOPICON]->textureID = LoadTGA("Image//Shop_Speech.tga");

	meshList[GEO_SHOPKEEPER] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 4, 7);
	meshList[GEO_SHOPKEEPER]->textureID = LoadTGA("Image//Shop_Cp30.tga");

	meshList[GEO_SHOPKEEPER3D] = MeshBuilder::GenerateOBJ("bottom", "OBJ//ShopKeeper.obj");
	meshList[GEO_SHOPKEEPER3D]->textureID = LoadTGA("Image//Shop_Keeper.tga");

	meshList[GEO_SPACEDOOR] = MeshBuilder::GenerateOBJ("bottom", "OBJ//Spacedoor.obj");
	meshList[GEO_SPACEDOOR]->textureID = LoadTGA("Image//Shop_Spacedoor.tga");

	meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("bottom", "OBJ//Table.obj");
	meshList[GEO_TABLE]->textureID = LoadTGA("Image//Shop_Table.tga");

	meshList[GEO_SHOPWALL] = MeshBuilder::GenerateOBJ("shop", "OBJ//Shop1.obj");
	meshList[GEO_SHOPWALL]->textureID = LoadTGA("Image//Shop_SpaceWall.tga");

	GLuint plane = LoadTGA("Image//Scene_Plane.tga");
	meshList[GEO_PLANEBODY] = MeshBuilder::GenerateOBJ("Star", "OBJ//planebody.obj");
	meshList[GEO_PLANEBODY]->textureID = plane;

	meshList[GEO_PLANEWING] = MeshBuilder::GenerateOBJ("Star", "OBJ//planewing.obj");
	meshList[GEO_PLANEWING]->textureID = plane;

	meshList[GEO_PLANEROCKET] = MeshBuilder::GenerateOBJ("Star", "OBJ//planerocket.obj");
	meshList[GEO_PLANEROCKET]->textureID = plane;

	meshList[GEO_AMMOICON] = MeshBuilder::GenerateQuad("ammoicon", Color(1, 1, 1), 3, 3);
	meshList[GEO_AMMOICON]->textureID = LoadTGA("Image//I_Ammo.tga");

	meshList[GEO_GOLDICON] = MeshBuilder::GenerateQuad("goldicon", Color(1, 1, 1), 3, 3);
	meshList[GEO_GOLDICON]->textureID = LoadTGA("Image//I_Gold.tga");

	meshList[GEO_EGGICON] = MeshBuilder::GenerateQuad("eggicon", Color(1, 1, 1), 3, 3);
	meshList[GEO_EGGICON]->textureID = LoadTGA("Image//I_Egg.tga");

	meshList[GEO_OREICON] = MeshBuilder::GenerateQuad("Ore", Color(1, 1, 1), 3, 3);
	meshList[GEO_OREICON]->textureID = LoadTGA("Image//I_Ore.tga");

	meshList[GEO_BOMBICON] = MeshBuilder::GenerateQuad("Bomb", Color(1, 1, 1), 3, 3);
	meshList[GEO_BOMBICON]->textureID = LoadTGA("Image//I_Bomb.tga");

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 16.0f / 9.0f, 0.1f, 10000.0f);
	projectionStack.LoadMatrix(projection);
}
static bool Lighting9 = true;
void Shop::ShopOptions()
{
	if (shopInput == "Shop")
	{
		switch (shop)
		{
		case MenuShop::S_BUY:
			if (Application::IsKeyPressed(VK_RETURN) && PressTime == 0)
			{
				icon = 31.6;
				icon2 = 19;
				PressTime = deltaTime / 5;
				shopInput = "Buy";
				buy = MenuShop::SB_AMMO;
			}
			break;
		case MenuShop::S_SELL:
			if (Application::IsKeyPressed(VK_RETURN) && PressTime == 0)
			{
				PressTime = deltaTime / 5;
				icon = 31.6;
				icon2 = 19;
				shopInput = "Sell";
				sell = MenuShop::SS_AMMO;
			}
			break;
		case MenuShop::S_BACK:
			if (Application::IsKeyPressed(VK_RETURN) && PressTime == 0)
			{
				sound.playSE("Music//Robot.mp3");
				shopInput = "";
				icon = 31.6;
				icon2 = 19;
				PressTime = deltaTime;
				shop = MenuShop::S_BUY;
				cout << "Byebye" << endl;
			}
			break;
		}
	}
	if (shopInput == "Buy")
	{
		switch (buy)
		{
		case MenuShop::SB_AMMO:
			description = "To shoot at your enemies!";
			if (Application::IsKeyPressed(VK_RETURN) && PressTime == 0)
			{
				PressTime = deltaTime / 5;
				if (SharedData::GetInstance()->gold.quantity > 19)
				{
					SharedData::GetInstance()->gold.quantity -= 20;
					SharedData::GetInstance()->bullet.quantity++;
					coolDown = deltaTime;
					b_gold = true;
					nomore = "gained ammo";
				}
				else
				{
					coolDown = deltaTime;
					b_gold = true;
					nomore = "no gold to buy";
				}
			}
			break;
		case MenuShop::SB_BOMB:
			if (SharedData::GetInstance()->bomb.quantity < 1)
			{
				description = "Oh... This is a MUST to get!";
			}
			else
			{
				description = "Sold out!";
			}
			if (Application::IsKeyPressed(VK_RETURN) && PressTime == 0)
			{
				PressTime = deltaTime / 5;
				if (SharedData::GetInstance()->gold.quantity >= 999 && SharedData::GetInstance()->bomb.quantity < 1)
				{
					SharedData::GetInstance()->gold.quantity -= 999;
					SharedData::GetInstance()->bomb.quantity=1;
					coolDown = deltaTime;
					b_gold = true;
					nomore = "gained bomb";
				}
				else if (SharedData::GetInstance()->gold.quantity < 999)
				{
					coolDown = deltaTime;
					b_gold = true;
					nomore = "no gold to buy";
				}
			}
			break;
		case MenuShop::SB_BACK:
			description = "";
			if (Application::IsKeyPressed(VK_RETURN) && PressTime == 0)
			{
				PressTime = deltaTime;
				shopInput = "Shop";
				shop = MenuShop::S_BUY;
				icon = 31.6;
				icon2 = 19;
			}
			break;
		}
	}
	if (shopInput == "Sell")
	{
		switch (sell)
		{
		case MenuShop::SS_AMMO:
			if (Application::IsKeyPressed(VK_RETURN) && PressTime == 0)
			{
				PressTime = deltaTime / 5;
				coolDown = deltaTime;
				gold = 10;
				if (SharedData::GetInstance()->bullet.quantity > 0)
				{
					none = true;
					nomore = "gained gold";
					SharedData::GetInstance()->gold.quantity += gold;
					SharedData::GetInstance()->bullet.quantity--;
				}
				else
				{
					none = true;
					nomore = "no ammo";
				}
			}
			break;
		case MenuShop::SS_BOMB:
			if (Application::IsKeyPressed(VK_RETURN) && PressTime == 0)
			{
				PressTime = deltaTime / 5;
				coolDown = deltaTime;
				gold = 5;
				if (SharedData::GetInstance()->mineral.quantity > 0)
				{
					SharedData::GetInstance()->gold.quantity += gold;
					SharedData::GetInstance()->mineral.quantity--;
					none = true;
					nomore = "Gained gold";
				}
				else
				{
					none = true;
					nomore = "no ore";
				}
			}
			break;
		case MenuShop::SS_EGG:
			if (Application::IsKeyPressed(VK_RETURN) && PressTime == 0)
			{
				PressTime = deltaTime / 5;
				coolDown = deltaTime;
				gold = 200;
				if (SharedData::GetInstance()->egg.quantity > 0)
				{
					SharedData::GetInstance()->gold.quantity += gold;
					SharedData::GetInstance()->egg.quantity--;
					none = true;
					nomore = "Gained gold";
				}
				else
				{
					none = true;
					nomore = "no egg";
				}
			}
			break;
		case MenuShop::SS_BACK:
			if (Application::IsKeyPressed(VK_RETURN) && PressTime == 0)
			{
				PressTime = deltaTime;
				shopInput = "Shop";
				shop = MenuShop::S_BUY;
				icon = 31.6;
				icon2 = 19;
			}
			break;
		}
	}
}
void Shop::userInput()
{
	if (shopInput == "Shop")
	{
		if (shop > MenuShop::S_BUY)
		{
			if (Application::IsKeyPressed(VK_UP) && PressTime == 0)
			{
				sound.playSE("Music//Menu.mp3");
				PressTime = deltaTime / 7;
				shop = static_cast<MenuShop::SHOP_OPTION>(shop - 1);
				cout << shop;
				icon += 1.6;
				icon2 += 1;
			}
		}
		if (shop < MenuShop::S_MAX - 1)
		{
			if (Application::IsKeyPressed(VK_DOWN) && PressTime == 0)
			{
				sound.playSE("Music//Menu.mp3");
				PressTime = deltaTime / 7;
				shop = static_cast<MenuShop::SHOP_OPTION>(shop + 1);
				cout << shop;
				icon -= 1.6;
				icon2 -= 1;
			}
		}
	}
	if (shopInput == "Sell")
	{
		if (sell > MenuShop::SS_AMMO)
		{
			if (Application::IsKeyPressed(VK_UP) && PressTime == 0)
			{
				sound.playSE("Music//Menu.mp3");
				PressTime = deltaTime / 7;
				sell = static_cast<MenuShop::SHOP_SELL>(sell - 1);
				cout << sell;
				icon += 1.6;
				icon2 += 1;
			}
		}
		if (sell < MenuShop::SS_MAX - 1)
		{
			if (Application::IsKeyPressed(VK_DOWN) && PressTime == 0)
			{
				sound.playSE("Music//Menu.mp3");
				PressTime = deltaTime / 7;
				sell = static_cast<MenuShop::SHOP_SELL>(sell + 1);
				cout << sell;
				icon -= 1.6;
				icon2 -= 1;
			}
		}
	}

	if (shopInput == "Buy")
	{
		if (buy > MenuShop::SB_AMMO)
		{
			if (Application::IsKeyPressed(VK_UP) && PressTime == 0)
			{
				sound.playSE("Music//Menu.mp3");
				PressTime = deltaTime / 7;
				buy = static_cast<MenuShop::SHOP_BUY>(buy - 1);
				cout << buy;
				icon += 1.6;
				icon2 += 1;
			}
		}
		if (buy < MenuShop::SB_MAX - 1)
		{
			if (Application::IsKeyPressed(VK_DOWN) && PressTime == 0)
			{
				sound.playSE("Music//Menu.mp3");
				PressTime = deltaTime / 7;
				buy = static_cast<MenuShop::SHOP_BUY>(buy + 1);
				cout << buy;
				icon -= 1.6;
				icon2 -= 1;
			}
		}
	}
}
void Shop::Update(double dt)
{
	npc.Shop(camera, dt);
	if (PressTime > 0)
	{
		PressTime -= 1;
	}
	else
	{
		PressTime = 0;
	}

	if (coolDown > 0)
	{
		coolDown -= 1;
	}
	else
	{
		coolDown = 0;
	}
	if (shopInput != "Shop" && shopInput != "Buy" && shopInput != "Sell")
	{
		camera.Update(dt);
		mouse.MouseUpdate(dt, camera);
	}
	if (detectCollision.collideByDist(camera.position, npc.seller.Nposition) <= 35)
	{
		if (Application::IsKeyPressed('E') && PressTime == 0)
		{
			sound.playSE("Music//Hello.mp3");
			PressTime = deltaTime / 5;
			shopInput = "Shop";
		}
	}
	if (npc.stopMusic)
	{
		sound.stopMusic("Music//Shop.mp3");
	}
	ShopOptions();
	userInput();
	
	deltaTime = (1.0 / dt);
}
void Shop::Dialogue(string filename)
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
void Shop::RenderMesh(Mesh * mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
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
void Shop::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
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
void Shop::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
void Shop::RenderQuadOnScreen(Mesh* mesh, float size, float x, float y, float rotate, float rx, float ry, float rz, float z)
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
void Shop::RenderSkybox()
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
static float SSCALE1 = 500.f;
void Shop::Render()
{
	std::ostringstream oss;
	oss << "Camera X: " << camera.position.x;
	string var = oss.str();

	std::ostringstream oss1;
	oss1 << "Camera Z: " << camera.position.z;
	string var1 = oss1.str();

	std::ostringstream ammoOSS;
	std::ostringstream goldOSS;
	std::ostringstream bombOSS;
	std::ostringstream oreOSS;
	std::ostringstream eggOSS;
	std::ostringstream fpsOSS;
	std::ostringstream nomoreOSS;
	std::ostringstream gainOSS;

	ammoOSS << SharedData::GetInstance()->bullet.quantity;
	goldOSS << SharedData::GetInstance()->gold.quantity;
	bombOSS << SharedData::GetInstance()->bomb.quantity;
	oreOSS << SharedData::GetInstance()->mineral.quantity;
	eggOSS << SharedData::GetInstance()->egg.quantity;
	fpsOSS << "FPS : " << deltaTime;

	nomoreOSS << "You have " << nomore;
	string Fps = fpsOSS.str();
	string ammo = ammoOSS.str();
	string egg = eggOSS.str();
	string ore = oreOSS.str();
	string s_gold = goldOSS.str();
	string nmOSS = nomoreOSS.str();
	string gain = gainOSS.str();
	string bomb = bombOSS.str();

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

	modelStack.PushMatrix();
	modelStack.Translate(-135, -40, -5);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_PLANEBODY], false);
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_PLANEROCKET], false);
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_PLANEWING], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Move skybox
	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 0, -90 + camera.position.z + 50);
	modelStack.Scale(3, 3, 3);
	RenderSkybox();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -20, 0);
	modelStack.Scale(7, 7, 7);
	RenderMesh(meshList[GEO_SHOPWALL], false);
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_TABLE], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(npc.spaceDoor.Nposition.x, npc.spaceDoor.Nposition.y, npc.spaceDoor.Nposition.z);
	modelStack.Scale(7, 7, 7);
	RenderMesh(meshList[GEO_SPACEDOOR], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(npc.seller.Nposition.x, npc.seller.Nposition.y, npc.seller.Nposition.z);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_SHOPKEEPER3D], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(110, -20, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(400, 1, 400);
	RenderMesh(meshList[GEO_QUAD], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(50, 20, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(400, 1, 400);
	RenderMesh(meshList[GEO_QUAD], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	if (npc.seller.canInteract && shopInput != "Shop" && shopInput != "Buy" && shopInput != "Sell"||npc.spaceDoor.canInteract)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], npc.interactDia, Color(1, 1, 0), 1.5, 7, 20);
	}

	if (shopInput == "Shop" || shopInput == "Buy" || shopInput == "Sell")
	{
		RenderQuadOnScreen(meshList[GEO_SHOPKEEPER], 8, 2, 3.5, 90, 1, 0, 0, 1);
		RenderQuadOnScreen(meshList[GEO_SHOPICON], 10, 4.7, 3, 90, 1, 0, 0, 1);
	}

	if (shopInput == "Shop")
	{

		int j = 21;
		RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(0, 0, 1), 1.7, 16, icon2);
		for (int arr = 0; arr < my_arr.size() - 9; ++arr)
		{
			--j;
			RenderTextOnScreen(meshList[GEO_TEXT], my_arr[arr], Color(0, 0, 0), 1.7, 17, j);
		}
	}
	if (shopInput == "Buy")
	{
		int j = 21;
		RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(0, 0, 1), 1.7, 16, icon2);

		for (int arr = 4; arr < my_arr.size() - 5; ++arr)
		{
			--j;
			RenderTextOnScreen(meshList[GEO_TEXT], my_arr[arr], Color(0, 0, 0), 1.7, 17, j);
		}
		if (b_gold)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], nmOSS, Color(1, 0, 0), 1.7, 18, 21);
			if (coolDown == 0)
			{
				b_gold = false;
			}
		}

		RenderTextOnScreen(meshList[GEO_TEXT], description, Color(1, 0, 0), 1.7, 17, 16);
	}
	if (shopInput == "Sell")
	{
		int j = 21;
		RenderTextOnScreen(meshList[GEO_TEXT], ">", Color(0, 0, 1), 1.7, 16, icon2);

		for (int arr = 8; arr < my_arr.size(); ++arr)
		{
			--j;
			RenderTextOnScreen(meshList[GEO_TEXT], my_arr[arr], Color(0, 0, 0), 1.7, 17, j);
		}

		if (none)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], nmOSS, Color(1, 0, 0), 1.7, 18, 21);
			if (coolDown == 0)
			{
				none = false;
			}
		}
	}
	var.resize(16);
	var1.resize(16);
	Fps.resize(11);
	RenderTextOnScreen(meshList[GEO_TEXT], var, Color(1, 1, 0), 1.5, 1, 38);
	RenderTextOnScreen(meshList[GEO_TEXT], var1, Color(1, 1, 0), 1.5, 1, 37);
	RenderTextOnScreen(meshList[GEO_TEXT], Fps, Color(1, 1, 0), 1.5, 1, 39);
	int x = 38.5;
	int y = 14;
	//All element for player inventory
	RenderQuadOnScreen(meshList[GEO_AMMOICON], 2, x, y, 90, 1, 0, 0, 1);
	RenderQuadOnScreen(meshList[GEO_GOLDICON], 2, x, y - 3, 90, 1, 0, 0, 1);
	RenderQuadOnScreen(meshList[GEO_EGGICON], 2, x, y - 6, 90, 1, 0, 0, 1);
	RenderQuadOnScreen(meshList[GEO_OREICON], 2, x, y - 9, 90, 1, 0, 0, 1);
	RenderQuadOnScreen(meshList[GEO_BOMBICON], 2, x, y - 12, 90, 1, 0, 0, 1);

	RenderTextOnScreen(meshList[GEO_TEXT], ammo, Color(0, 0, 1), 1.5, x + 11.5, y + 3.5);
	RenderTextOnScreen(meshList[GEO_TEXT], s_gold, Color(0, 0, 1), 1.5, x + 11.5, y - 0.5);
	RenderTextOnScreen(meshList[GEO_TEXT], egg, Color(0, 0, 1), 1.5, x + 11.5, y - 4.5);
	RenderTextOnScreen(meshList[GEO_TEXT], ore, Color(0, 0, 1), 1.5, x + 11.5, y - 8.5);
	RenderTextOnScreen(meshList[GEO_TEXT], bomb, Color(0, 0, 1), 1.5, x + 11.5, y - 12.5);
}
void Shop::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}