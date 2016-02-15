#include "Scene3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"
#include "Vertex.h"

Scene3::Scene3()
{
}

Scene3::~Scene3()
{
}


void Scene3::Init()
{
	// Init VBO here
	//Set background color to dark blue
	//            R     G     B
	glClearColor(0.f, 0.f, 0.f, 0.0f);
	//Enable depth test
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	camera.Init(Vector3(80, 80, 80), Vector3(0, 0, 0), Vector3(0, 1, 0));
	Color colour_red(1, 0, 0);
	Color colour_blue(0, 0, 1);
	Color colour_green(0, 1, 0);
	Color colour_yellow(1, 1, 0);
	Color colour_orange(1, 0.5, 0);
	Color colour_bl(0, 0, 0.5);
	Color colour_salmon(0.7, 0.2, 0.2);
	Color colour_tur(0.6, 0.9, 0.9);

	meshList[GEO_REF_AXES] = MeshBuilder::GenerateAxes("Reference", 1000, 1000, 1000);
	meshList[GEO_REF_QUAD] = MeshBuilder::GenerateQuad("Quad", colour_red, 1, 1);
	meshList[GEO_REF_CUBE] = MeshBuilder::GenerateCube("Cube", colour_blue, 1, 1, 1);
	meshList[GEO_REF_CIRCLE] = MeshBuilder::GenerateCircle("Circle", colour_green, 1, 1);
	meshList[GEO_REF_CIRCLE1] = MeshBuilder::GenerateCircles("Circles", colour_blue,36);
	meshList[GEO_REF_HEM] = MeshBuilder::GenerateHemisphere("Hem", colour_blue, 1, 1, 1, 1);
	meshList[GEO_REF_SPHERE] = MeshBuilder::GenerateSphere("Sph", colour_green, 1, 2, 3);
	meshList[GEO_REF_SPHERE1] = MeshBuilder::GenerateSpheres("Sph", colour_green, 18, 36);
	meshList[GEO_REF_PLANET] = MeshBuilder::GenerateSpheres("Sph", colour_green, 18, 36);
	meshList[GEO_REF_PLANET1] = MeshBuilder::GenerateSpheres("Sph", colour_bl, 18, 36);
	meshList[GEO_REF_PLANET2] = MeshBuilder::GenerateSpheres("Sph", colour_salmon, 18, 36);
	meshList[GEO_REF_PLANET3] = MeshBuilder::GenerateSpheres("Sph", colour_bl, 18, 36);
	meshList[GEO_REF_PLANET4] = MeshBuilder::GenerateSpheres("Sph", colour_tur, 18, 36);
	meshList[GEO_REF_MOON] = MeshBuilder::GenerateSpheres("Sph", colour_yellow, 18, 36);
	meshList[GEO_REF_SUN] = MeshBuilder::GenerateSpheres("Sph", colour_orange, 18, 36);
	meshList[GEO_REF_RING] = MeshBuilder::GenerateRing("Ring", colour_red, 0.5f, 1);
	meshList[GEO_REF_RING1] = MeshBuilder::GenerateRing("Ring", colour_red, 4.5, 6);
	meshList[GEO_REF_RING2] = MeshBuilder::GenerateRing("Ring", colour_orange, 6, 9);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);

	srand(time(NULL));

	//Generate a default VAO for now 
	//Generate and bind once
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Generate buffers into GPU through library
	 //generate index buffer
	//Different color
	
	//Load vertex and fragment shaders 
	//Colors
	m_programID = LoadShaders(
		//Vertex shader for position
		//"Shader//SimpleVertexShader.vertexshader",
		//Fragment shader for color
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader"
		);

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	//Use our shader
	glUseProgram(m_programID);
}

void Scene3::Update(double dt)
{
	camera.Update(dt);

	if (Application::IsKeyPressed('1'))
	{
		glEnable(GL_CULL_FACE);
	}

	if (Application::IsKeyPressed('2'))
	{
		glDisable(GL_CULL_FACE);
	}

	if (Application::IsKeyPressed('3'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (Application::IsKeyPressed('4'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	rotateAngle += (float)(10 * dt);
	rotateSun += (float)(10 * dt);
	rotatePlanet += (float)(20 * dt);
	rotatePlanet1 += (float)(15 * dt);
	rotatePlanet2 -= (float)(7 * dt);
	rotatePlanet3 -= (float)(30 * dt);
	rotateMoon += (float)(30 * dt);
}

//Every frame
void Scene3::Render()
{
	//Mtx44 translate, rotate, scale;
	//Mtx44 model;
	//Mtx44 view;
	//Mtx44 projection;
	//Mtx44 MVP;

	//translate.SetToIdentity();
	//rotate.SetToIdentity();
	//scale.SetToIdentity();
	//model.SetToIdentity();
	//view.SetToIdentity(); //no need camera for now, set it at World's origin
	// //FOV, Aspect ratio, Near plane, Far plane
	////projection.SetToOrtho(-40, +40, -30, +30, -10, +10); //Our world is a cube defined by these boundaries

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	/*view.SetToLookAt(camera.position.x, camera.position.y, camera.position.z, 
					 camera.target.x, camera.target.y, camera.target.z, 
					 camera.up.x, camera.up.y, camera.up.z);

	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);*/

	// Render VBO here
	//Clear color buffer every frame
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	Mtx44 MVP;
	

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelStack.PushMatrix();
	//meshList[GEO_REF_AXES]->Render();
	modelStack.PopMatrix();
	//meshList[GEO_REF_QUAD]->Render();
	//meshList[GEO_REF_RING]->Render();
	

	modelStack.PushMatrix();
	modelStack.Rotate(rotateSun, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_SUN]->Render();
	modelStack.PopMatrix(); //go back to origin

	modelStack.PushMatrix(); //Planet 1 system
	modelStack.Rotate(rotateAngle, 0, 1, 0); //revolution about centre
	modelStack.Translate(48, 0, 0);

	modelStack.PushMatrix(); //Moon
	modelStack.Rotate(rotateMoon, 90, 1, 90); //Revolution about planet
	modelStack.Translate(0, 7, 0); //Offset
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_MOON]->Render();
	modelStack.PopMatrix(); //go back to origin

	modelStack.PushMatrix(); //Moon
	modelStack.Rotate(rotateMoon, 0, 1, rotateMoon); //Revolution about planet
	modelStack.Translate(0, 7, 0); //Offset
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_MOON]->Render();
	modelStack.PopMatrix(); //go back to origin

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	//modelStack.Rotate(20 * rotateAngle, 0, 1, 0);
	modelStack.Rotate(0, 20 * rotateAngle, 1, 0);
	modelStack.Rotate(rotateAngle, 90, 1, 0); //revolution about centre
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_RING1]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(4, 4, 4);
	modelStack.Rotate(40* rotateAngle, 0, 1, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_PLANET]->Render();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Planet1
	modelStack.PushMatrix(); //Planet1 system
	modelStack.Rotate(rotateAngle, 0, 1, 0); //revolution about centre
	modelStack.Translate(18, 0, 0);

	modelStack.PushMatrix();
	modelStack.Rotate(rotateMoon, 0, 1, 0);
	modelStack.Translate(8, 0, 0);
	modelStack.Rotate(rotateMoon, 0, 1, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_MOON]->Render();
	modelStack.PopMatrix(); //go back to origin

	modelStack.PushMatrix();
	modelStack.Scale(7, 7, 7);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_PLANET1]->Render();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(4, 4, 4);
	modelStack.Rotate(rotatePlanet2, 0, 1, 0);
	modelStack.Translate(9.5, 0, 0);
	modelStack.Rotate(rotatePlanet2, 0, 1, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_PLANET2]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	
	modelStack.Rotate(rotatePlanet3, 0, 1, 0);
	modelStack.Translate(65, 0, 0);
	modelStack.Rotate(rotatePlanet3, 0, 1, 0);

	modelStack.PushMatrix();
	modelStack.Scale(3, 3, 3);
	modelStack.Rotate(0, 20 * rotateAngle, 1, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_PLANET4]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//modelStack.Rotate(20 * rotateAngle, 0, 1, 0);
	modelStack.Rotate(0, 20 * rotateAngle, 1, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_RING2]->Render();
	modelStack.PopMatrix();
	modelStack.PopMatrix();


	/*translate.SetToTranslation(0, -2, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;*/
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//meshList[GEO_REF_CIRCLE]->Render();

	/*translate.SetToTranslation(-3, 0, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;*/
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//meshList[GEO_REF_SPHERE]->Render();

	/*translate.SetToTranslation(3, 0, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;*/
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//meshList[GEO_REF_HEM]->Render();

	/*translate.SetToTranslation(0, -1, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;*/
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	//meshList[GEO_REF_CIRCLE1]->Render();

	/*translate.SetToTranslation(0, 0, 2);
	model = translate * rotate * scale;
	MVP = projection * view * model;*/
	
	
}

void Scene3::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	//Delete to prevent memory leak
	glDeleteProgram(m_programID);
}
