#include "Lab5b.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"
#include "Vertex.h"

Lab5b::Lab5b()
{
}

Lab5b::~Lab5b()
{
}


void Lab5b::Init()
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
	meshList[GEO_REF_QUAD] = MeshBuilder::GenerateQuad("Quad", Color(1,1,1), 1, 1);
	meshList[GEO_REF_CUBE] = MeshBuilder::GenerateCube("Cube", colour_blue, 1, 1, 1);
	meshList[GEO_REF_BODY] = MeshBuilder::GenerateCube("Cube", colour_blue, 30, 25, 10);
	meshList[GEO_REF_ARM] = MeshBuilder::GenerateCube("Cube", colour_green, 10, 20, 10);
	meshList[GEO_REF_CIRCLE] = MeshBuilder::GenerateCircle("Circle", colour_green, 1, 1);
	meshList[GEO_REF_CIRCLE1] = MeshBuilder::GenerateCircles("Circles", colour_blue, 36);
	meshList[GEO_REF_HEM] = MeshBuilder::GenerateHemisphere("Hem", colour_blue, 1, 1, 1, 1);
	meshList[GEO_REF_SPHERE] = MeshBuilder::GenerateSpheres("Sph", colour_green, 18,36);
	meshList[GEO_REF_SPHERE1] = MeshBuilder::GenerateSpheres("Sph", colour_green, 18, 36);
	
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

void Lab5b::RenderHead()
{
	Mtx44 MVP;

	modelStack.PushMatrix();
	modelStack.Scale(5, 5, 5);
	modelStack.Translate(0, 3.5, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_SPHERE]->Render();
	modelStack.PopMatrix();
}

void Lab5b::RenderBody()
{
	Mtx44 MVP;

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_BODY]->Render();
	modelStack.PopMatrix();
}

void Lab5b::RenderLimb()
{
	Mtx44 MVP;

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_ARM]->Render();
	modelStack.PopMatrix();
}

void Lab5b::RenderRobot()
{

	Mtx44 MVP;
	modelStack.PushMatrix();
	RenderHead();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderBody();
	modelStack.PushMatrix();
	modelStack.Translate(20, 0, 0);
	modelStack.Rotate(rotateAngle, 1, 0, 0);
	RenderLimb();
	modelStack.PushMatrix();
	modelStack.Translate(0, -20, 0);
	modelStack.Rotate(-30, 1, 0, 0);
	RenderLimb();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-20, 0, 0);
	modelStack.Rotate(rotateAngle1, 1, 0, 0);
	RenderLimb();
	modelStack.PushMatrix();
	modelStack.Translate(0, -20, 0);
	modelStack.Rotate(-30, 1, 0, 0);
	RenderLimb();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-8, -22.5, 0);
	modelStack.Rotate(rotateAngle2 - 10, 1, 0, 0);
	RenderLimb();
	modelStack.PushMatrix();
	modelStack.Translate(0, -17, -4);
	modelStack.Rotate(30, 1, 0, 0);
	RenderLimb();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(8, -22.5, 0);
	modelStack.Rotate(rotateAngle3 - 30, 1, 0, 0);
	RenderLimb();
	modelStack.PushMatrix();
	modelStack.Translate(0, -17, -4);
	modelStack.Rotate(10, 1, 0, 0);
	RenderLimb();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

}

void Lab5b::Update(double dt)
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
	
	

	
	
	if (Rotate == true)
	{
		rotateAngle += (float)(30 * dt);

		if (rotateAngle > 30)
		{
			Rotate = false;
		}
	}

	if (Rotate == false)
	{
		rotateAngle -= (float)(30 * dt);

		if (rotateAngle <= -30)
		{
			Rotate = true;
		}
	}

	if (Rotate1 == true)
	{
		rotateAngle1 += (float)(30 * dt);

		if (rotateAngle1 > 30)
		{
			Rotate1 = false;
		}
	}

	if (Rotate1 == false)
	{
		rotateAngle1 -= (float)(30 * dt);

		if (rotateAngle1 <= -30)
		{
			Rotate1 = true;
		}
	}

	if (Rotate2 == true)
	{
		rotateAngle2 += (float)(30 * dt);

		if (rotateAngle2 > 30)
		{
			Rotate2 = false;
		}
	}

	if (Rotate2 == false)
	{
		rotateAngle2 -= (float)(30 * dt);

		if (rotateAngle2 <= -30)
		{
			Rotate2 = true;
		}
	}

	if (Rotate3 == true)
	{
		rotateAngle3 += (float)(30 * dt);

		if (rotateAngle3 > 30)
		{
			Rotate3 = false;
		}
	}

	if (Rotate3 == false)
	{
		rotateAngle3 -= (float)(30 * dt);

		if (rotateAngle3 <= -30)
		{
			Rotate3 = true;
		}
	}





	/*if (Rotate == false)
	{
		rotateAngle += 1;
		if (rotateAngle = 30)
		{
			Rotate = true;
		}
	}*/
	
}

//Every frame
void Lab5b::Render()
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
	
	modelStack.PushMatrix();
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_AXES]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(0, -0.1, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_QUAD]->Render();
	modelStack.PopMatrix();

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	RenderRobot();
	
	
	

	/*modelStack.PushMatrix();
	modelStack.Scale(10, 10, 10);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_SPHERE]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(10, 10, 10);
	modelStack.Translate(1, 0, 0);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_REF_CUBE]->Render();
	modelStack.PopMatrix();*/
	//meshList[GEO_REF_RING]->Render();

}

void Lab5b::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	//Delete to prevent memory leak
	glDeleteProgram(m_programID);
}
