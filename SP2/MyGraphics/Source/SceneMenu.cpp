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
	menuIcon = 118;
	colorBlue = (0.4, 0.8, 0.8);
	colorNormal = (0.1, 0.2, 0);

	//Sets the enum for option menu and menu scren
	choose = menushop.STARTGAME;
	c_option = menushop.O_SETTING;
	Input = "Menu";

	//Read the menu texts from text file
	Dialogue("Text//Menu.txt");

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
	camera.Init(Vector3(-300, -10, 0), Vector3(0, 0, 0), Vector3(0, 1, 0));

	meshList[GEO_PATH] = MeshBuilder::GenerateQuad("land", Color(1, 1, 1), 14, 13);
	meshList[GEO_PATH]->textureID = LoadTGA("Image//Menu.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Text2.tga");

	meshList[GEO_STAR] = MeshBuilder::GenerateOBJ("Star", "OBJ//Star.obj");
	meshList[GEO_STAR]->textureID = LoadTGA("Image//sand_2.tga");

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 16.0f / 9.0f, 0.1f, 10000.0f);
	projectionStack.LoadMatrix(projection);
}
//Sets color for the words
void SceneMenu::setColor(int which, string color)
{
	if (color == "colorBlue")
	{
		colorA[which].Set(colorBlue.r, colorBlue.g, colorBlue.b);
	}
	if (color == "colorNormal")
	{
		colorA[which].Set(colorNormal.r, colorNormal.g, colorNormal.b);
	}
	if (color == "colorSpecial")
	{
		colorA[which].Set(0.3, 0.8, 0.4);
	}
}
//Handles all switch cases
void SceneMenu::UpdateMenu()
{
	if (Input == "Menu")
	{
		switch (choose)
		{
		case MenuShop::STARTGAME:
			setColor(0, "colorBlue");
			setColor(1, "colorNormal");
			setColor(2, "colorNormal");
			setColor(3, "colorNormal");
			menuIcon = 117;

			if (Application::IsKeyPressed(VK_RETURN) && menushop.PressTime == 0)
			{
				menushop.PressTime = deltaTime / 2;
				my_arr[0] = "Loading Game";
				SharedData::GetInstance()->stateCheck = true;
				SharedData::GetInstance()->gameState = SharedData::GAME;
			}
			userInput();
			break;
		case MenuShop::OPTIONS:
			setColor(0, "colorNormal");
			setColor(1, "colorBlue");
			setColor(2, "colorNormal");
			setColor(3, "colorNormal");
			if (Application::IsKeyPressed(VK_RETURN))
			{
				menuIcon = 104;
				Input = "Options";
				c_option = MenuShop::O_SETTING;
			}
			userInput();
			break;
		case MenuShop::CREDITS:
			setColor(1, "colorNormal");
			setColor(2, "colorBlue");
			setColor(3, "colorNormal");
			
			setColor(6, "colorSpecial");
			setColor(7, "colorNormal");
			setColor(8, "colorNormal");
			setColor(9, "colorNormal");
			setColor(10, "colorNormal");
			setColor(11, "colorBlue");
			if (Application::IsKeyPressed(VK_RETURN) && menushop.PressTime == 0)
			{
				menuIcon = 90;
				menushop.PressTime = deltaTime / 5;
				Input = "Credits";
				c_option = MenuShop::O_CREDIT;
			}
			userInput();
			break;
		case MenuShop::QUIT:
			setColor(0, "colorNormal");
			setColor(1, "colorNormal");
			setColor(2, "colorNormal");
			setColor(3, "colorBlue");
			if (Application::IsKeyPressed(VK_RETURN))
			{
				SharedData::GetInstance()->gameState = SharedData::QUIT;
			}
			userInput();
			break;
		}
	}
	if (Input == "Options")
	{
		switch (c_option)
		{
		case MenuShop::O_SETTING:
			setColor(4, "colorBlue");
			setColor(5, "colorNormal");
			if (Application::IsKeyPressed(VK_RETURN) && menushop.PressTime == 0)
			{

			}
			userInput();
			break;
		case MenuShop::O_QUIT:
			setColor(4, "colorNormal");
			setColor(5, "colorBlue");
			if (Application::IsKeyPressed(VK_RETURN) && menushop.PressTime == 0)
			{
				menushop.PressTime = deltaTime / 5;
				choose = MenuShop::STARTGAME;
				Input = "Menu";
			}
			userInput();
			break;
		}
	}
	if (Input == "Credits")
	{
		switch (c_option)
		{
		case MenuShop::O_CREDIT:
			setColor(4, "colorBlue");
			setColor(5, "colorNormal");
			if (Application::IsKeyPressed(VK_RETURN) && menushop.PressTime == 0)
			{
				menushop.PressTime = deltaTime;
				Input = "Menu";
				choose = MenuShop::STARTGAME;
			}
			break;
		}
	}
}
//Handles user up and down input
void SceneMenu::userInput()
{
	
	if (Input == "Menu")
	{
		if (px < 210 || px > 540)
		{
			if (choose < MenuShop::MAX - 1)
			{
				if (Application::IsKeyPressed(VK_DOWN) && menushop.PressTime == 0)
				{
					menuIcon -= 6.5;
					menushop.PressTime = deltaTime / 10;
					choose = static_cast<MenuShop::MENU>(choose + 1);
				}
			}
			if (choose > MenuShop::STARTGAME)
			{
				if (Application::IsKeyPressed(VK_UP) && menushop.PressTime == 0)
				{
					menuIcon += 6.5;
					menushop.PressTime = deltaTime / 10;
					choose = static_cast<MenuShop::MENU>(choose - 1);
				}
			}
		}
	}
	if (Input == "Options")
	{
		if (c_option < MenuShop::O_MAX - 2)
		{
			if (Application::IsKeyPressed(VK_DOWN) && menushop.PressTime == 0)
			{
				menuIcon -= 6.5;
				menushop.PressTime = deltaTime / 10;
				c_option = static_cast<MenuShop::OPTION>(c_option + 1);
			}
		}
		if (c_option > MenuShop::O_SETTING)
		{
			if (Application::IsKeyPressed(VK_UP) && menushop.PressTime == 0)
			{
				menuIcon += 6.5;
				menushop.PressTime = deltaTime / 10;
				c_option = static_cast<MenuShop::OPTION>(c_option - 1);
			}
		}
	}
}
//Handles user mouse input
void SceneMenu::mouseControl()
{
	POINT p;
	if (GetCursorPos(&p))
	{
		px = p.x;
		py = p.y;
	}
	if (Input == "Menu")
	{
		if (px > 210 && px < 540)
		{
			if (py >412 && py < 449)
			{
				choose = MenuShop::STARTGAME;
				menuIcon = 117;
				if (Application::IsKeyPressed(VK_LBUTTON))
				{
					my_arr[0] = "Loading Game";
					SharedData::GetInstance()->stateCheck = true;
					SharedData::GetInstance()->gameState = SharedData::GAME;
				}
			}

			if (py > 450 && py < 485)
			{
				menuIcon = 111.5;
				choose = MenuShop::OPTIONS;
				if (Application::IsKeyPressed(VK_LBUTTON))
				{
					menuIcon = 104;
					Input = "Options";
					c_option = MenuShop::O_SETTING;
				}
			}
			if (py > 487 && py < 522)
			{
				menuIcon = 105;
				choose = MenuShop::CREDITS;
				if (Application::IsKeyPressed(VK_LBUTTON))
				{
					menuIcon = 90;
					Input = "Credits";
					c_option = MenuShop::O_CREDIT;

				}
			}
			if (py > 523 && py < 556)
			{
				menuIcon = 98.5;
				choose = MenuShop::QUIT;
				if (Application::IsKeyPressed(VK_LBUTTON) && menushop.PressTime == 0)
				{
					SharedData::GetInstance()->gameState = SharedData::QUIT;
				}
			}
		}
	}

	if (Input == "Credits")
	{
		if (px > 210 && px < 339 && py > 559 && py < 591)
		{
			if (Application::IsKeyPressed(VK_LBUTTON))
			{
				Input = "Menu";
				choose = MenuShop::STARTGAME;
			}
		}
	}


	if (Input == "Options")
	{
		if (px > 210 && px < 582)
		{
			if (py > 488 && py < 519)
			{
				menuIcon = 104;
				c_option = MenuShop::O_SETTING;
			}

			if (py > 520 && py < 555)
			{
				menuIcon = 97.5;
				c_option = MenuShop::O_QUIT;
				if (Application::IsKeyPressed(VK_LBUTTON))
				{
					menushop.PressTime = deltaTime / 5;
					Input = "Menu";
				}
			}
		}
	}
}
void SceneMenu::Update(double dt)
{
	POINT p;
	if (GetCursorPos(&p))
	{
		px = p.x;
		py = p.y;
	}
	if (menushop.PressTime > 0)
	{
		menushop.PressTime -= (float)(50 * dt);
	}
	else
	{
		menushop.PressTime = 0;
	}

	rotateCoke += (float)(100 * dt);

	deltaTime = (1.0 / dt);

	UpdateMenu();
	mouseControl();
}
//Read from text file
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
void SceneMenu::Render()
{
	std::ostringstream fpsOSS;
	fpsOSS << "FPS : " << deltaTime;
	string Fps = fpsOSS.str();

	std::ostringstream mouseXOSS;
	mouseXOSS << "X : " << px;
	string mouseX = mouseXOSS.str();
	std::ostringstream mouseYOSS;
	mouseYOSS << "Y : " << py;
	string mouseY = mouseYOSS.str();
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
	RenderQuadOnScreen(meshList[GEO_STAR], 0.3, 18, menuIcon, rotateCoke, 0, 1, 0, 2);

	RenderQuadOnScreen(meshList[GEO_PATH], 6, 6.5, 6, 90, 1, 0, 0, 0);

	if (Input == "Menu")
	{
		int j = 19;
		for (int i = 0; i < my_arr.size() - 8; ++i)
		{
			j--;
			RenderTextOnScreen(meshList[GEO_TEXT], my_arr[i], colorA[i], 2, 5, j);
		}
	}
	if (Input == "Options")
	{
		int j = 17.9;
		for (int i = 4; i < my_arr.size() - 6; ++i)
		{
			j--;
			RenderTextOnScreen(meshList[GEO_TEXT], my_arr[i], colorA[i], 2, 5, j);
		}
	}
	if (Input == "Credits")
	{
		int j = 20;
		for (int i = 6; i < my_arr.size(); ++i)
		{
			j--;
			RenderTextOnScreen(meshList[GEO_TEXT], my_arr[i], colorA[i], 2, 5, j);
		}
	}

	Fps.resize(11);
	RenderTextOnScreen(meshList[GEO_TEXT], Fps, Color(1, 1, 0), 1.5, 1, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], mouseX, Color(1, 1, 0), 1.5, 1, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], mouseY, Color(1, 1, 0), 1.5, 1, 3);
}
void SceneMenu::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}