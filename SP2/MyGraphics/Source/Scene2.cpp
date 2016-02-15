#include "Scene2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Application.h"

Scene2::Scene2()
{
}

Scene2::~Scene2()
{
}


void Scene2::Init()
{
	// Init VBO here
	//Set background color to dark blue
	//            R     G     B
	glClearColor(0.5f, 0.4f, 0.8f, 0.0f);
	//Enable depth test
	glEnable(GL_DEPTH_TEST);

	//Initiate
	rotateAngle = 180;
	rotateFull = 0;
	translateX = 35;
	translateY = 40;
	translateY1 = 40;
	scaleAll = 0.5;

	scale = false;
	rotate = false;

	srand(time(NULL));

	//Generate a default VAO for now 
	//Generate and bind once
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Generate buffers into GPU through library
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	//If you transform things in an array, every vertex will transform as well
	static const GLfloat vertex_buffer_data[] = {
		-3.0f, 2.0f, 0.0f,
		3.0f, 2.0f, 0.0f,
		0.0f, -0.5f, 0.0f,

		0.0f, 4.0f, 0.0f, //vertex 0 of triangle
		-2.0f, -2.0f, 0.0f, //vertex 1 of triangle
		0.0f, -0.5f, 0.0f, //vertex 2 of triangle

		0.0f, 4.0f, 0.0f, //vertex 0 of triangle
		2.0f, -2.0f, 0.0f, //vertex 1 of triangle
		0.0f, -0.5f, 0.0f, //vertex 2 of triangle
	};

	//No neg colors
	//An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data[] = {
		0.7f, 0.2f, 0.4f, //color of vertex 0
		0.7f, 0.2f, 0.4f, //color of vertex 1
		0.7f, 0.2f, 0.4f, //color of vertex 2
		0.7f, 0.2f, 0.4f, //color of vertex 0
		0.7f, 0.2f, 0.4f, //color of vertex 1
		0.7f, 0.2f, 0.4f, //color of vertex 2
		0.7f, 0.2f, 0.4f, //color of vertex 0
		0.7f, 0.2f, 0.4f, //color of vertex 1
		0.7f, 0.2f, 0.4f, //color of vertex 2
	};

	static const GLfloat color_buffer_data1[] = {
		0.5f, 0.0f, 1.0f, //color of vertex 0
		0.5f, 0.0f, 1.0f, //color of vertex 1
		0.5f, 0.0f, 1.0f, //color of vertex 2
		0.5f, 0.0f, 1.0f, //color of vertex 0
		0.5f, 0.0f, 1.0f, //color of vertex 1
		0.5f, 0.0f, 1.0f, //color of vertex 2
		0.5f, 0.0f, 1.0f, //color of vertex 0
		0.5f, 0.0f, 1.0f, //color of vertex 1
		0.5f, 0.0f, 1.0f, //color of vertex 2
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	//Pass the vertex/color data to the GPU at load time (not run time)
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
	//Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	//Transfer vertices to openGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	//Different color
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data1, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

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

void Scene2::Update(double dt)
{
	//Play when press space
	if (Application::IsKeyPressed(VK_SPACE))
	{
		//Rotate and rotate back
		if (rotateAngle >= 100 & rotate == false)
		{
			rotateAngle -= (float)(30 * dt);

			if (rotateAngle <= 100)
			{
				rotate = true;
			}
		}

		if (rotateAngle <= 260 & rotate == true)
		{
			rotateAngle += (float)(30 * dt);

			if (rotateAngle >= 260)
			{
				rotate = false;
			}
		}

		//Move until out of screen and reset
		if (translateX > -45)
		{
			translateX -= (float)(10 * dt);
		}

		else
		{
			translateX = 45;
		}

		//Continue scaling till 2
		if (scaleAll < 2 & scale == false)
		{
			scaleAll += (float)(1 * dt);
			if (scaleAll > 2)
			{
				scale = true;
			}
		}
		//Translate back
		else if (scale == true)
		{
			scaleAll -= (float)(1 * dt);
			if (scaleAll < 0.5)
			{
				scale = false;
			}
		}
	}

	//BONUS - DROP AND ROTATE
	if (translateY >= -40)
	{
		translateY -= (float)(speed * dt);
	}
	else if (translateY <= -40)
	{
		translateY = 40;
	}
	if (translateY > 39)
	{
		//Half of the screen
		dropping = rand() % 30 + (-30);

		//Randomise speed everytime when its at the top
		speed = rand() % 30 + (3);
	}

	if (translateY1 >= -35)
	{
		translateY1 -= (float)(speed1 *dt);
	}
	else if (translateY1 <= -35)
	{
		translateY1 = 40;
	}
	if (translateY1 > 39)
	{
		//Half of the screen
		dropping1 = rand() % 30 + (-30);

		//Randomise speed everytime when its at the top
		speed1 = rand() % 50 + (3);
	}

	rotateFull += (float)(50 * dt);
}

//Every frame
void Scene2::Render()
{
	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity(); //no need camera for now, set it at World's origin
	projection.SetToOrtho(-40, +40, -30, +30, -10, +10); //Our world is a cube defined by these boundaries

	// Render VBO here
	//Clear color buffer every frame
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//Object  1 - rotation (no translation)
	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glEnableVertexAttribArray(1); //2nd attribute buffer: colors

	scale.SetToScale(2, 2, 2);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	//translate.SetToTranslation(0, 0, 0);
	model = rotate * scale; //scale,followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //Update the shader the new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	//Attribute pointer for vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	//Attribute pointer for color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	//Object 2 - translation (no scaling)
	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glEnableVertexAttribArray(1); //2nd attribute buffer: colors

	//scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(20, 0, 0, 1);
	translate.SetToTranslation(translateX, 5, 1);
	model = translate * rotate; //scale,followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //Update the shader the new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	//Attribute pointer for color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	//Object 3 - scaling (no rotation)
	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glEnableVertexAttribArray(1); //2nd attribute buffer: colors

	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	//rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(20, 10, 1);
	model = translate * scale; //scale,followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //Update the shader the new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	//Attribute pointer for color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	//BONUS - DROP AND ROTATE (2 GEOMETRIES - STAR & TRIANGLE)
	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glEnableVertexAttribArray(1); //2nd attribute buffer: colors

	scale.SetToScale(2, 2, 2);
	rotate.SetToRotation(rotateFull, 0, 0, 1);
	translate.SetToTranslation(dropping, translateY, 1);
	model = translate * rotate * scale; //scale,followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //Update the shader the new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	//Attribute pointer for color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 9);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	//TRIANGLE
	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glEnableVertexAttribArray(1); //2nd attribute buffer: colors

	scale.SetToScale(2, 2, 2);
	rotate.SetToRotation(rotateFull, 0, 0, 1);
	translate.SetToTranslation(dropping1, translateY1, 1);
	model = translate * rotate * scale; //scale,followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //Update the shader the new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	//Attribute pointer for color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Scene2::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	//Delete to prevent memory leak
	glDeleteProgram(m_programID);
}
