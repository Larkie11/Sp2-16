#include "GL\glew.h"
#include "StartCutScene.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "LoadTGA.h"
#include "SharedData.h"

//This class is to render the first scenario where player has to fix his own spaceship
StartCutScene::StartCutScene()
{
}
StartCutScene::~StartCutScene()
{
}
void StartCutScene::Init()
{
	srand(time(NULL));
	camera.cameraRotate = Vector3(0, 380, 0);
	sound.playSE("Music//SE1.mp3");
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
	camera.Init(Vector3(52, 0, -701), Vector3(0, 0, 0), Vector3(0, 1, 0));
	
	GLuint floor = LoadTGA("Image//Scene_Floor.tga");
	//meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1, 0));
	meshList[GEO_QUAD] = MeshBuilder::GenerateRepeatQuad("quad", Color(1, 1, 0), 1, 1, 10);
	meshList[GEO_QUAD]->textureID = floor;
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

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

	GLuint pyramid = LoadTGA("Image//Scene_Pyramid.tga");
	meshList[GEO_PYRAMIDNEW] = MeshBuilder::GenerateOBJ("pyramid", "OBJ//PyramidNew.obj");
	meshList[GEO_PYRAMIDNEW]->textureID = pyramid;

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
void StartCutScene::Update(double dt)
{
	if (planePos2 > 450)
	{
		planePos2 -= (float)(300 * dt);
	}
	
	else
	{
		blowUp = true;
		if (explosionScale < 10)
		{
			explosionScale += (float)(10 * dt);
		}
	}
	
	if (explosionScale >= 10)
	{
		SharedData::GetInstance()->stateCheck = true;
		SharedData::GetInstance()->gameState = SharedData::GAME;
	}
	if (planePos > -9)
	{
		planePos -= (float)(60 * dt);
	}
	
	Character_Movement(dt);
}
static bool Lighting9 = true;
void StartCutScene::RenderMesh(Mesh * mesh, bool enableLight)
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
void StartCutScene::RenderText(Mesh* mesh, std::string text, Color color)
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
void StartCutScene::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
//Rendering current skybox
static float SBSCALE1 = 1000.f;
void StartCutScene::RenderSkybox()
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
void StartCutScene::Render()
{
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
	Map_Rendering();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-100, 0, 0);
	modelStack.Scale(30, 30, 30);

	RenderMesh(meshList[GEO_MOONBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(planePos2, planePos, 0);
	modelStack.Rotate(10, 0, 0, 1);
	modelStack.Rotate(270, 0, 1, 0);
	modelStack.Scale(5, 5, 5);
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_PLANEBODY], false);
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_PLANEROCKET], false);
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_PLANEWING], false);
	if (blowUp)
	{
		modelStack.PushMatrix();
		modelStack.Scale(explosionScale, explosionScale, explosionScale);
		RenderMesh(meshList[GEO_EXPLOSION], false);
		modelStack.PopMatrix();
	}
	modelStack.Translate(0, 3.6, -3);
	modelStack.Scale(thrusterScale, thrusterScale, thrusterScale);
	RenderMesh(meshList[GEO_THRUSTER], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(2, 2, 2);
	RenderSkybox();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(0, -20, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(2000, 1, 2000);
	RenderMesh(meshList[GEO_QUAD], false);
	modelStack.PopMatrix();

	RenderTextOnScreen(meshList[GEO_TEXT], "Loading...", Color(1, 1, 0), 1.5, 1, 1);
}
void StartCutScene::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
void StartCutScene::Map_Rendering()
{
	modelStack.PushMatrix();

	modelStack.Translate(X_Displacement, -22.5, Z_Displacement);

	modelStack.PushMatrix();
	modelStack.Scale(2.5 * Size, 2.5 * Size, 2.5 * Size);
	RenderMesh(meshList[GEO_PYRAMIDNEW], false);
	modelStack.PopMatrix();
	camera.position.y = -10;
}
void StartCutScene::Character_Movement(float dt)
{
	//Changing view (target)
	if (randNum == 1)
	{
		camera.cameraRotate.y += (float)(100 * dt);
	}
	if (randNum == 2)
	{
		camera.cameraRotate.y -= (float)(100 * dt);
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