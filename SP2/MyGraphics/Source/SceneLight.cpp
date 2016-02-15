#include "SceneLight.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"

SceneLight::SceneLight()
{
}

SceneLight::~SceneLight()
{
}

void SceneLight::Init()
{
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

	m_programID = LoadShaders("Shader//Shading.vertexshader","Shader//Shading.fragmentshader");
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
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled"); 
	glUseProgram(m_programID);

	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1,&light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);


	//Initialize camera settings
	camera.Init(Vector3(80, 70, 70), Vector3(0, 0, 0), Vector3(0, 1, 0));

	meshList[GEO_REF_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	//meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1, 0));
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 0),1,1);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_REF_SPHERE] = MeshBuilder::GenerateSpheres("Sph", Color(1, 0, 1), 18, 36);
	meshList[GEO_REF_SPHERE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_SPHERE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_REF_SPHERE]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_SPHERE]->material.kShininess = 10.f;

	meshList[GEO_REF_SPHERE1] = MeshBuilder::GenerateSpheres("Sph", Color(0, 0, 1), 18, 36);
	meshList[GEO_REF_SPHERE1]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_REF_SPHERE1]->material.kDiffuse.Set(0.4f, 0.4f, 0.4f);
	meshList[GEO_REF_SPHERE1]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_SPHERE1]->material.kShininess = 100.f;

	meshList[GEO_REF_SPHERE2] = MeshBuilder::GenerateSpheres("Sph", Color(0, 0.5, 1), 18, 36);
	meshList[GEO_REF_SPHERE2]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_REF_SPHERE2]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_SPHERE2]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_SPHERE2]->material.kShininess = 1.f;

	meshList[GEO_REF_CONE] = MeshBuilder::GenerateConeHem("Sph", Color(0, 0.5, 1), 1, 36);
	meshList[GEO_REF_CONE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_REF_CONE]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_CONE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_CONE]->material.kShininess = 1.f;

	meshList[GEO_REF_SPHERE3] = MeshBuilder::GenerateSpheres("Sph", Color(0.3, 0.2, 0.6), 18, 36);
	meshList[GEO_REF_SPHERE3]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_REF_SPHERE3]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_SPHERE3]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_SPHERE3]->material.kShininess = 1.6f;

	meshList[GEO_REF_SPHERE4] = MeshBuilder::GenerateSpheres("Sph", Color(0.8, 0.2, 0.6), 18, 36);
	meshList[GEO_REF_SPHERE4]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_SPHERE4]->material.kDiffuse.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_REF_SPHERE4]->material.kSpecular.Set(0.4f, 0.4f, 0.4f);
	meshList[GEO_REF_SPHERE4]->material.kShininess = 20.f;

	meshList[GEO_REF_SPHERE5] = MeshBuilder::GenerateSpheres("Sph", Color(0.2, 0.6, 0.5), 18, 36);
	meshList[GEO_REF_SPHERE5]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_REF_SPHERE5]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_SPHERE5]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_REF_SPHERE5]->material.kShininess = 50.f;

	meshList[GEO_REF_SPHERE6] = MeshBuilder::GenerateSpheres("Sph", Color(0.3, 0.1, 0.3), 18, 36);
	meshList[GEO_REF_SPHERE6]->material.kAmbient.Set(0.4f, 0.4f, 0.4f);
	meshList[GEO_REF_SPHERE6]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_SPHERE6]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_REF_SPHERE6]->material.kShininess = 0.5f;

	meshList[GEO_REF_SPHERE7] = MeshBuilder::GenerateSpheres("Sph", Color(0.5, 0.f, 0.f), 18, 36);
	meshList[GEO_REF_SPHERE7]->material.kAmbient.Set(0.7f, 0.4f, 0.5f);
	meshList[GEO_REF_SPHERE7]->material.kDiffuse.Set(0.4f, 0.2f, 0.3f);
	meshList[GEO_REF_SPHERE7]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_REF_SPHERE7]->material.kShininess = 15.f;

	meshList[GEO_REF_SPHERE8] = MeshBuilder::GenerateSpheres("Sph", Color(0.2, 0.5f, 0.f), 18, 36);
	meshList[GEO_REF_SPHERE8]->material.kAmbient.Set(0.2f, 0.5f, 0.7f);
	meshList[GEO_REF_SPHERE8]->material.kDiffuse.Set(0.4f, 0.2f, 0.3f);
	meshList[GEO_REF_SPHERE8]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_REF_SPHERE8]->material.kShininess = 15.f;

	meshList[GEO_REF_CYL] = MeshBuilder::GenerateCone("Sph", Color(0.2, 0.5f, 0.f),36);
	

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSpheres("Sph", Color(1, 1, 1), 18, 36);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);
}

static float LSPEED = 10.f;
bool Lighting = true;

void SceneLight::Update(double dt)
{
	camera.Update(dt);

	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);

	if (Application::IsKeyPressed('Z'))
		Lighting = false;

	if (Application::IsKeyPressed('X'))
		Lighting = true;

}
void SceneLight::RenderMesh(Mesh * mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight && Lighting)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose =modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1,GL_FALSE, &modelView_inverse_transpose.a[0]);
			//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1,&mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1,&mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1,&mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS],mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	mesh->Render();

}


void SceneLight::Render()
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

	//new code
	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

	RenderMesh(meshList[GEO_REF_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Scale(100, 100, 100);
	modelStack.Translate(0, -0.1f, 0);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_REF_SPHERE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Scale(10, 10, 10);
	modelStack.Translate(-2, 0, 2);
	RenderMesh(meshList[GEO_REF_SPHERE1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Scale(10, 10, 10);
	modelStack.Translate(2, 0, -2);
	RenderMesh(meshList[GEO_REF_SPHERE2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Scale(10, 10, 10);
	modelStack.Translate(0, 0, 2);
	RenderMesh(meshList[GEO_REF_SPHERE3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Scale(10, 10, 10);
	modelStack.Translate(2, 0, 0);
	RenderMesh(meshList[GEO_REF_SPHERE4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Scale(10, 10, 10);
	modelStack.Translate(2, 0, 2);
	RenderMesh(meshList[GEO_REF_SPHERE5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Scale(10, 10, 10);
	modelStack.Translate(-2, 0, 0);
	RenderMesh(meshList[GEO_REF_SPHERE6], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Scale(10, 10, 10);
	modelStack.Translate(-2, 0, -2);
	RenderMesh(meshList[GEO_REF_CYL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Scale(10, 10, 10);
	modelStack.Translate(0, 0, -2);
	RenderMesh(meshList[GEO_REF_SPHERE8], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//to do: transformation code here
	modelStack.Scale(10, 10, 10);
	modelStack.Translate(0, 3, 0);
	RenderMesh(meshList[GEO_REF_CONE], true);
	modelStack.PopMatrix();
}

void SceneLight::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}