#include "Assignment2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"

Assignment2::Assignment2()
{
}

Assignment2::~Assignment2()
{
}

void Assignment2::Init()
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

	//Initialize values
	eyes = true;
	showsphere = true;
	baymaxA = true;
	eyeSize = 1;
	wing = 45;
	wingx = -1;
	fly = 7;
	flyScale = 0.1;

	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//LightSource.fragmentshader");

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

	glUseProgram(m_programID);

	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(0, 70, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.00f;
	light[0].kQ = 0.00f;
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

	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	//Initialize camera settings
	camera.Init(Vector3(10, 40, 120), Vector3(-10, 10, 0), Vector3(0, 10, 0));

	meshList[GEO_REF_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(0, 0.9, 0.2), 1, 1);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_REF_CUBE] = MeshBuilder::GenerateCubes2("Cube", Color(0.6, 0.1, 0.1), 0.5, 2, 0.5);
	meshList[GEO_REF_CUBE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_CUBE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_REF_CUBE]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_CUBE]->material.kShininess = 1.f;

	meshList[GEO_REF_SPHERE] = MeshBuilder::GenerateSpheres("Sph", Color(0, 1, 0), 18, 36, 0.5f, 0.5f, 0.5f);
	meshList[GEO_REF_SPHERE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_SPHERE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_REF_SPHERE]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_SPHERE]->material.kShininess = 10.f;

	meshList[GEO_REF_BSPHERE] = MeshBuilder::GenerateSpheres("Sph", Color(1, 1, 1), 18, 36, 0.5f, 0.5f, 0.5f);
	meshList[GEO_REF_BSPHERE]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_REF_BSPHERE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_REF_BSPHERE]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_REF_BSPHERE]->material.kShininess = 1.f;

	meshList[GEO_REF_SPHERE1] = MeshBuilder::GenerateSpheres("Sph", Color(1, 1, 1), 18, 36, 1, 1, 1);
	meshList[GEO_REF_SPHERE1]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_SPHERE1]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_REF_SPHERE1]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_SPHERE1]->material.kShininess = 10.f;

	meshList[GEO_REF_ASPHERE] = MeshBuilder::GenerateSpheres("Sph", Color(1, 1, 1), 18, 36, 8, 10, 8);
	meshList[GEO_REF_ASPHERE]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_REF_ASPHERE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_REF_ASPHERE]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_REF_ASPHERE]->material.kShininess = 1.f;

	meshList[GEO_REF_AARM] = MeshBuilder::GenerateSpheres("Sph", Color(1, 1, 1), 18, 36, 3, 6, 1);
	meshList[GEO_REF_AARM]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_REF_AARM]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_REF_AARM]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_REF_AARM]->material.kShininess = 1.f;

	meshList[GEO_REF_ALEG] = MeshBuilder::GenerateSpheres("Sph", Color(1, 1, 1), 18, 36, 2.5, 6, 3);
	meshList[GEO_REF_ALEG]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_REF_ALEG]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_REF_ALEG]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_REF_ALEG]->material.kShininess = 5.f;

	meshList[GEO_REF_EYES] = MeshBuilder::GenerateSpheres("Sph", Color(0, 0, 0), 18, 36, 0.5f, 0.5f, 0.5f);
	meshList[GEO_REF_EYES]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_REF_EYES]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_REF_EYES]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_REF_EYES]->material.kShininess = 5.f;

	meshList[GEO_REF_MOUTH] = MeshBuilder::GenerateCylinder2("Cyl", Color(0, 0, 0), 0.4, 0.4, 0.6, 6, 0.2, 1.8);
	meshList[GEO_REF_MOUTH]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_REF_MOUTH]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_MOUTH]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_MOUTH]->material.kShininess = 1.6f;

	meshList[GEO_REF_CONE] = MeshBuilder::GenerateCone2("Cone", Color(1, 0.25, 0), 1, 36, 1.5, 2, 1.45);
	meshList[GEO_REF_CONE]->material.kAmbient.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_CONE]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_CONE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_CONE]->material.kShininess = 1.f;

	meshList[GEO_REF_BCONE] = MeshBuilder::GenerateCone2("Cone", Color(1, 0.25, 0), 1, 36, 0.9, 0.5, 0.55);
	meshList[GEO_REF_BCONE]->material.kAmbient.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_BCONE]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_BCONE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_BCONE]->material.kShininess = 1.f;

	meshList[GEO_REF_CYL] = MeshBuilder::GenerateCylinder2("Cyl", Color(0.3, 0.2, 0.6), 3, 3, 0.6, 3, 1, 1.8);
	meshList[GEO_REF_CYL]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_REF_CYL]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_CYL]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_CYL]->material.kShininess = 1.6f;

	meshList[GEO_REF_ACYL] = MeshBuilder::GenerateCylinder2("Cyl", Color(1.0, 0.25, 0), 4, 4, 0.6, 2, 1, 2);
	meshList[GEO_REF_ACYL]->material.kAmbient.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_ACYL]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_ACYL]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_ACYL]->material.kShininess = 1.6f;

	meshList[GEO_REF_JSPHERE] = MeshBuilder::GenerateSpheres("Sph", Color(0, 0, 0), 18, 36, 1.2f, 1.2f, 1.2f);
	meshList[GEO_REF_JSPHERE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_JSPHERE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_REF_JSPHERE]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_JSPHERE]->material.kShininess = 10.f;

	meshList[GEO_REF_WCIRCLE] = MeshBuilder::GenerateHemispheres2("Circles", Color(1.0, 0.25, 0), 18, 36, 0.5, 0.2, 2);
	meshList[GEO_REF_WCIRCLE]->material.kAmbient.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_WCIRCLE]->material.kDiffuse.Set(0.4f, 0.2f, 0.3f);
	meshList[GEO_REF_WCIRCLE]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_REF_WCIRCLE]->material.kShininess = 15.f;

	meshList[GEO_REF_GUARD] = MeshBuilder::GenerateSpheres("Sph", Color(1.0, 0.25, 0), 18, 16, 2, 2, 2.5);
	meshList[GEO_REF_GUARD]->material.kAmbient.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_GUARD]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_GUARD]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_GUARD]->material.kShininess = 1.6f;

	meshList[GEO_REF_ACYL2] = MeshBuilder::GenerateCylinder2("Cyl", Color(0, 0, 0), 1, 1, 0.6, 2.1, 1, 2.1);
	meshList[GEO_REF_ACYL2]->material.kAmbient.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_ACYL2]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_ACYL2]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_ACYL2]->material.kShininess = 1.6f;

	meshList[GEO_REF_LSPHERE] = MeshBuilder::GenerateSpheres("Sph", Color(1.0, 0.25, 0), 18, 16, 2.5, 3, 2);
	meshList[GEO_REF_LSPHERE]->material.kAmbient.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_LSPHERE]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_LSPHERE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_LSPHERE]->material.kShininess = 1.6f;

	meshList[GEO_REF_LCYL] = MeshBuilder::GenerateCylinder2("Cyl", Color(1.0, 0.25, 0), 4, 4, 0.6, 1.5, 1, 2.5);
	meshList[GEO_REF_LCYL]->material.kAmbient.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_LCYL]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_LCYL]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_LCYL]->material.kShininess = 1.6f;

	meshList[GEO_REF_LCYL1] = MeshBuilder::GenerateCylinder2("Cyl", Color(1.0, 0.25, 0), 4, 4, 0.6, 2.5, 1, 3);
	meshList[GEO_REF_LCYL1]->material.kAmbient.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_LCYL1]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_LCYL1]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_LCYL1]->material.kShininess = 1.6f;

	meshList[GEO_REF_LCYL2] = MeshBuilder::GenerateCylinder2("Cyl", Color(1.0, 0.25, 0), 4, 4, 0.6, 2.4, 1, 2.4);
	meshList[GEO_REF_LCYL2]->material.kAmbient.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_LCYL2]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_LCYL2]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_LCYL2]->material.kShininess = 1.6f;

	meshList[GEO_REF_LCONE] = MeshBuilder::GenerateCones2("Cone", Color(1, 0.25, 0), 36, 1.4, 2, 1.4);
	meshList[GEO_REF_LCONE]->material.kAmbient.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_LCONE]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_LCONE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_LCONE]->material.kShininess = 1.f;

	meshList[GEO_REF_HEM] = MeshBuilder::GenerateHemispheres2("Hem", Color(0, 0, 0), 18, 36, 1, 1, 1);
	meshList[GEO_REF_HEM]->material.kAmbient.Set(0.2f, 0.5f, 0.7f);
	meshList[GEO_REF_HEM]->material.kDiffuse.Set(0.4f, 0.2f, 0.3f);
	meshList[GEO_REF_HEM]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_REF_HEM]->material.kShininess = 15.f;

	meshList[GEO_REF_TOP] = MeshBuilder::GenerateCubes2("Cube", Color(0, 0.7, 0.8), 1, 0.5, 2);
	meshList[GEO_REF_TOP]->material.kAmbient.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_REF_TOP]->material.kDiffuse.Set(0.4f, 0.2f, 0.3f);
	meshList[GEO_REF_TOP]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_REF_TOP]->material.kShininess = 15.f;

	meshList[GEO_REF_BOTTOM] = MeshBuilder::GenerateCubes2("Cube", Color(0, 0.5, 0.7), 0.9, 1, 1.9);
	meshList[GEO_REF_BOTTOM]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_BOTTOM]->material.kDiffuse.Set(0.4f, 0.2f, 0.3f);
	meshList[GEO_REF_BOTTOM]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_REF_BOTTOM]->material.kShininess = 15.f;

	meshList[GEO_REF_FSPHERE] = MeshBuilder::GenerateSpheres("Sph", Color(1, 1, 0), 18, 36, 1, 1, 1);
	meshList[GEO_REF_FSPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_REF_FSPHERE]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_FSPHERE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_FSPHERE]->material.kShininess = 1.6f;

	meshList[GEO_REF_FCONE] = MeshBuilder::GenerateCone2("Cone", Color(1, 1, 0), 1, 36, 1, 2, 1);
	meshList[GEO_REF_FCONE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_REF_FCONE]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_FCONE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_FCONE]->material.kShininess = 1.f;

	meshList[GEO_REF_TCONE] = MeshBuilder::GenerateCones2("Cone", Color(0, 0.3, 0), 36, 1.5, 5, 1.5);
	meshList[GEO_REF_TCONE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_REF_TCONE]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_REF_TCONE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REF_TCONE]->material.kShininess = 10.f;

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSpheres("Sph", Color(1, 1, 1), 18, 36);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);
}

static float LSPEED = 10.f;
bool Lighting1 = true;

void Assignment2::Update(double dt)
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

	//Changijng lights
	if (Application::IsKeyPressed('5'))
	{
		light[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	if (Application::IsKeyPressed('6'))
	{
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	if (Application::IsKeyPressed('7'))
	{
		light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}

	//Off and on lighting
	if (Application::IsKeyPressed('Z'))
		Lighting1 = false;

	if (Application::IsKeyPressed('X'))
		Lighting1 = true;

	//Move baymax
	if (Application::IsKeyPressed('W'))
	{
		position.x += (float)(30 * dt);
	}

	if (Application::IsKeyPressed('S'))
	{
		position.x -= (float)(30 * dt);
	}

	//Rotate baymax
	if (Application::IsKeyPressed('A'))
	{
		angle -= (float)(30 * dt);
	}
	if (Application::IsKeyPressed('D'))
	{
		angle += (float)(30 * dt);
	}

	//Only baymax with armor flies
	if (baymaxA == true)
	{
		if (Application::IsKeyPressed('E'))
		{
			if (wing < 80)
			{
				wing += (float)(30 * dt);
				wingx += (float)(0.5*dt);
			}

			if (wing >= 80)
			{
				fly += (float)(20 * dt);
			}

			if (fly > 10)
			{
				if (flyScale <1)
					flyScale += (float)(10 * dt);
			}
		}
	}

	//Make sure baymax without armor appears on the ground, reset baymax with armor wings
	if (Application::IsKeyPressed('R'))
	{
		fly = 8;
		sphere = 2;
		flyScale = 0.1;
		position.x = 0;
		rotateArm = 0;
		rotateLeg = 0;
		rotateArmB = 0;
		if (baymaxA == true)
		{
			wing = 45;
			wingx = -1;
		}
	}

	//Make baymax fly
	if (Application::IsKeyPressed('C'))
	{
		if (showsphere == true)
		{
			sphere += (float)(30 * dt);
			if (sphere >= 25)
			{
				showsphere = false;
				if (baymaxA == true)
				{
					baymaxA = false;
					baymaxB = true;
				}

				else if (baymaxB == true)
				{
					baymaxB = false;
					baymaxA = true;
				}
			}
		}

		if (showsphere == false)
		{
			sphere -= (float)(30 * dt);
			if (sphere <= 2)
			{
				showsphere = true;
			}
		}
	}

	//Moving baymax with animation
	if (Application::IsKeyPressed('W') || Application::IsKeyPressed('A') || Application::IsKeyPressed('S') || Application::IsKeyPressed('D'))
	{
		if (fly < 9)
		{
			if (rotate == true)
			{
				rotateArm += (float)(30 * dt);
				rotateArmB += (float)(30 * dt);
				rotateLeg += (float)(30 * dt);

				if (rotateArm > 30 || rotateArmB > 15)
				{
					rotate = false;
				}
			}
			if (rotate == false)
			{
				rotateArm -= (float)(30 * dt);
				rotateArmB -= (float)(30 * dt);
				rotateLeg -= (float)(30 * dt);

				if (rotateArm <= -30 || rotateArmB <= -15)
				{
					rotate = true;
				}
			}
		}
	}

	//Blinking eyes
	if (eyes == true)
	{
		eyeSize -= (float)(0.5 * dt);

		if (eyeSize <= 0.2)
		{
			eyes = false;
		}
	}

	if (eyes == false)
	{
		eyeSize += (float)(0.5 * dt);
		if (eyeSize >= 1)
		{
			eyes = true;
		}
	}
}
void Assignment2::RenderMesh(Mesh * mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight && Lighting1)
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
	mesh->Render();
}
void Assignment2::RenderFloor()
{
	modelStack.PushMatrix();
	modelStack.Scale(500, 500, 500);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Translate(0, 0, 0);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();
}
//Render tree relative to tree trunk
void Assignment2::RenderTrees()
{
	modelStack.PushMatrix();
	modelStack.Scale(10, 10, 10);
	modelStack.Translate(0, 1.01, -2);
	RenderMesh(meshList[GEO_REF_CUBE], true);

	modelStack.PushMatrix();
	modelStack.Translate(0, 2.5, 0);
	RenderMesh(meshList[GEO_REF_TCONE], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}
//Render cone relative to sphere 
void Assignment2::RenderFlyEffect()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 1, 0);
	modelStack.Scale(flyScale, flyScale, flyScale);
	RenderMesh(meshList[GEO_REF_FSPHERE], true);

	modelStack.PushMatrix();
	modelStack.Scale(1, -1.5, 1);
	RenderMesh(meshList[GEO_REF_FCONE], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}
//Render bottom relative to top box
void Assignment2::ItemBox()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, -5.2, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_REF_TOP], true);

	modelStack.PushMatrix();
	modelStack.Translate(0, -0.5, 0);
	RenderMesh(meshList[GEO_REF_BOTTOM], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}
//Baymax body
void Assignment2::RenderBody()
{
	if (baymaxA == true)
	{
		modelStack.PushMatrix();
		////to do: transformation code here
		modelStack.Scale(5, 5, 5);

		modelStack.PushMatrix();
		modelStack.Translate(0, 4, 0);
		RenderMesh(meshList[GEO_REF_CONE], true);

		modelStack.PushMatrix();
		////to do: transformation code here
		modelStack.Translate(1.5, wingx, -1.4);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Rotate(wing, 0, 1, 0);
		RenderMesh(meshList[GEO_REF_WCIRCLE], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-1.5, wingx, -1.4);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Rotate(-wing, 0, 1, 0);
		RenderMesh(meshList[GEO_REF_WCIRCLE], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Scale(0.5, 0.5, 0.5);

		modelStack.PushMatrix();
		modelStack.Translate(0, -3, 0);
		RenderMesh(meshList[GEO_REF_CYL], true);

		modelStack.PushMatrix();
		modelStack.Scale(2, 2, 2);
		modelStack.Translate(0, -0.7, 0);
		RenderMesh(meshList[GEO_REF_BCONE], true);
		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
	}
	else
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, 10, 0);
		RenderMesh(meshList[GEO_REF_ASPHERE], true);
	}
}
void Assignment2::RenderArm()
{
	if (baymaxA == true)
	{
		modelStack.PushMatrix();
		//modelStack.Translate(-9, 15, 0);
		//modelStack.Rotate(0, 0, 0, 1);
		RenderMesh(meshList[GEO_REF_ACYL], true);

		modelStack.PushMatrix();
		modelStack.Translate(0, -2, 0);
		RenderMesh(meshList[GEO_REF_JSPHERE], true);
	}
	else
	{
		modelStack.PushMatrix();
		RenderMesh(meshList[GEO_REF_AARM], true);
		modelStack.PopMatrix();
	}
}
//Render bottom arm relative to top arm
void Assignment2::RenderLowerArm()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, -2.2, 0);
	RenderMesh(meshList[GEO_REF_ACYL], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}
void Assignment2::RenderLeg()
{
	if (baymaxA == true)
	{
		modelStack.PushMatrix();
		RenderMesh(meshList[GEO_REF_LSPHERE], true);

		modelStack.PushMatrix();
		modelStack.Translate(1.5, -2.2, 0);
		RenderMesh(meshList[GEO_REF_LCYL], true);

		modelStack.PushMatrix();
		modelStack.Rotate(10, 0, 0, 1);
		modelStack.Translate(-2.5, 0.2, 0);
		RenderMesh(meshList[GEO_REF_LCYL], true);

		modelStack.PushMatrix();
		modelStack.Translate(1.3, 0, 0);
		RenderMesh(meshList[GEO_REF_LCYL1], true);

		modelStack.PushMatrix();
		modelStack.Translate(0, -2.3, 0);
		modelStack.Scale(1.4, 1.4, 1.4);
		RenderMesh(meshList[GEO_REF_JSPHERE], true);
		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
	}
	else
	{
		modelStack.PushMatrix();
		RenderMesh(meshList[GEO_REF_ALEG], true);
		modelStack.PopMatrix();
	}
}
void Assignment2::RenderLowerLeg()
{
	modelStack.PushMatrix();
	modelStack.Translate(1, -5, 0);
	modelStack.Scale(1.4, 1.4, 1.4);
	RenderMesh(meshList[GEO_REF_LCONE], true);

	modelStack.PushMatrix();
	modelStack.Translate(0, -3, 0);
	RenderMesh(meshList[GEO_REF_LCYL2], true);

}
void Assignment2::RenderFace()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 22.5, 0);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_REF_BSPHERE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1, 22.5, 2.25);
	modelStack.Scale(1, eyeSize, 1);
	RenderMesh(meshList[GEO_REF_EYES], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1, 22.5, 2.25);
	modelStack.Scale(1, eyeSize, 1);
	RenderMesh(meshList[GEO_REF_EYES], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 22.35, 2.3);
	modelStack.Scale(0.2, 0.2, 0.2);
	RenderMesh(meshList[GEO_REF_MOUTH], true);
	modelStack.PopMatrix();
}
void Assignment2::RenderABaymax()
{
	if (baymaxA == true)
	{
		//Render head
		modelStack.PushMatrix();
		RenderFace();

		modelStack.PushMatrix();
		RenderBody();

		modelStack.PushMatrix();
		modelStack.Translate(-9, 19, 0);
		RenderMesh(meshList[GEO_REF_GUARD], true);

		//Left arm
		modelStack.PushMatrix();
		modelStack.Translate(0, -2, 0);
		modelStack.Rotate(-rotateArm, 1, 0, 0);
		RenderArm();

		modelStack.PushMatrix();
		modelStack.Rotate(-rotateArm, 1, 0, 0);
		RenderLowerArm();
		ItemBox();

		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(9, 19, 0);
		RenderMesh(meshList[GEO_REF_GUARD], true);

		modelStack.PushMatrix();
		modelStack.Translate(0, -2, 0);
		modelStack.Rotate(rotateArm, 1, 0, 0);
		RenderArm();

		modelStack.PushMatrix();
		modelStack.Rotate(rotateArm, 1, 0, 0);
		RenderLowerArm();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();

		//Right leg
		modelStack.PushMatrix();
		modelStack.Translate(3, 5.5, 0);
		modelStack.Rotate(-rotateLeg, 1, 0, 0);
		RenderLeg();

		RenderLowerLeg();
		modelStack.PushMatrix();
		modelStack.Translate(0, -2, 1);
		modelStack.Scale(1.2, -1.2, 1.2);
		RenderMesh(meshList[GEO_REF_HEM], true);
		RenderFlyEffect();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();

		//Left leg
		modelStack.PushMatrix();
		modelStack.Translate(-3, 5.5, 0);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Rotate(-rotateLeg, 1, 0, 0);
		RenderLeg();
		RenderLowerLeg();

		modelStack.PushMatrix();
		modelStack.Translate(0, -2, -1);
		modelStack.Scale(1.2, -1.2, 1.2);
		RenderMesh(meshList[GEO_REF_HEM], true);

		RenderFlyEffect();

		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
	}
	else
	{
		//Render head
		modelStack.PushMatrix();
		RenderFace();
		modelStack.PushMatrix();
		RenderBody();

		modelStack.PushMatrix();
		modelStack.Translate(6.5, 3.3, 0);
		modelStack.Rotate(-150, 0, 0, 1);
		modelStack.Rotate(-rotateArmB, 1, 0, 0);
		RenderArm();
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-6.5, 3.3, 0);
		modelStack.Rotate(150, 0, 0, 1);
		modelStack.Rotate(rotateArmB, 1, 0, 0);
		RenderArm();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-3, -2, 0);
		modelStack.Rotate(rotateLeg, 1, 0, 0);
		RenderLeg();
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(3, -2, 0);
		modelStack.Rotate(-rotateLeg, 1, 0, 0);
		RenderLeg();
		modelStack.PopMatrix();
	}
}
void Assignment2::Render()
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
	//RenderMesh(meshList[GEO_REF_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderFloor();

	modelStack.PushMatrix();
	modelStack.Translate(25, 0, 0);
	RenderTrees();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-25, 0, 0);
	RenderTrees();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-60, 0, 30);
	RenderTrees();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(60, 0, 30);
	RenderTrees();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Render baymax with armor start
	modelStack.PushMatrix();
	modelStack.Rotate(angle, 0, 1, 0);
	modelStack.Translate(0, fly, position.x);
	RenderABaymax();
	modelStack.PopMatrix(); //<--renderbaymax pop 

	//Relevant to baymax position
	modelStack.PushMatrix();
	modelStack.Translate(0, 15, 0);
	modelStack.Scale(sphere, sphere, sphere);
	RenderMesh(meshList[GEO_REF_SPHERE1], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}
void Assignment2::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}