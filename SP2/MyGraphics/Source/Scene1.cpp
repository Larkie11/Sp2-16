#include "Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"


Scene1::Scene1()
{
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
	// Init VBO here
	//Set background color to dark blue
	//            R     G     B
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	//Enable depth test
	glEnable(GL_DEPTH_TEST);

	//Generate a default VAO for now 
	//Generate and bind once
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Generate buffers into GPU through library
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	
	//If you transform things in an array, every vertex will transform as well
	//An array of 3 vectors which represents 3 verticles
	static const GLfloat vertex_buffer_data[] = {
		-0.3f, 0.1f, 0.0f, //vertex 0 of triangle
		0.3f, 0.1f, 0.0f, //vertex 1 of triangle
		0.0f, -0.1f, 0.0f, //vertex 2 of triangle
		
		0.0f, 0.35f, 0.0f, //vertex 0 of triangle
		-0.2f, -0.3f, 0.0f, //vertex 1 of triangle
		0.0f, -0.1f, 0.0f, //vertex 2 of triangle
		
		0.0f, 0.35f, 0.0f, //vertex 0 of triangle
		0.2f, -0.3f, 0.0f, //vertex 1 of triangle
		0.0f, -0.1f, 0.0f, //vertex 2 of triangle
	};

	//No neg colors
	//An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data[] = {
		0.5f, 0.0f, 0.0f, //color of vertex 0
		0.5f, 0.0f, 0.0f, //color of vertex 1
		0.5f, 0.0f, 0.0f, //color of vertex 2
		0.5f, 0.0f, 0.0f, //color of vertex 0
		0.5f, 0.0f, 0.0f, //color of vertex 1
		0.5f, 0.0f, 0.0f, //color of vertex 2
		0.5f, 0.0f, 0.0f, //color of vertex 0
		0.5f, 0.0f, 0.0f, //color of vertex 1
		0.5f, 0.0f, 0.0f, //color of vertex 2
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	//Pass the vertex/color data to the GPU at load time (not run time)
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
	//Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	//Transfer vertices to openGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);


	//2nd shape
	static const GLfloat vertex_buffer_data1[] = {
		-0.7f, 0.7f, 0.0f, //vertex 0 of triangle
		0.0f, 1.0f, 0.0f, //vertex 1 of triangle
		0.0f, 0.0f, 0.0f, //vertex 2 of triangle

		0.7f, 0.7f, 0.0f, //vertex 0 of triangle
		0.0f, 1.0f, 0.0f, //vertex 1 of triangle
		0.0f, 0.0f, 0.0f, //vertex 2 of triangle

		-1.0f, 0.0f, 0.0f, //vertex 0 of triangle
		-0.7f, 0.7f, 0.0f, //vertex 1 of triangle
		0.0f, 0.0f, 0.0f, //vertex 2 of triangle

		1.0f, 0.0f, 0.0f, //vertex 0 of triangle
		0.7f, 0.7f, 0.0f, //vertex 1 of triangle
		0.0f, 0.0f, 0.0f, //vertex 2 of triangle

		-1.0f, 0.0f, 0.0f, //vertex 0 of triangle
		-0.7f, -0.7f, 0.0f, //vertex 1 of triangle
		0.0f, 0.0f, 0.0f, //vertex 2 of triangle

		-0.7f, -0.7f, 0.0f, //vertex 0 of triangle
		0.0f, -1.0f, 0.0f, //vertex 1 of triangle
		0.0f, 0.0f, 0.0f, //vertex 2 of triangle

		0.7f, -0.7f, 0.0f, //vertex 0 of triangle
		0.0f, -1.0f, 0.0f, //vertex 1 of triangle
		0.0f, 0.0f, 0.0f, //vertex 2 of triangle

		1.0f, 0.0f, 0.0f, //vertex 0 of triangle
		0.7f, -0.7f, 0.0f, //vertex 1 of triangle
		0.0f, 0.0f, 0.0f, //vertex 2 of triangle
	};

	static const GLfloat color_buffer_data1[] = {
		1.0f, 0.0f, 0.0f, //color of vertex 0
		1.0f, 0.0f, 0.0f, //color of vertex 1
		1.0f, 0.0f, 0.0f, //color of vertex 2
		1.0f, 0.0f, 0.0f, //color of vertex 0
		1.0f, 0.0f, 0.0f, //color of vertex 1
		1.0f, 0.0f, 0.0f, //color of vertex 2
		1.0f, 0.0f, 0.0f, //color of vertex 0
		1.0f, 0.0f, 0.0f, //color of vertex 1
		1.0f, 0.0f, 0.0f, //color of vertex 2
		1.0f, 0.0f, 0.0f, //color of vertex 0
		1.0f, 0.0f, 0.0f, //color of vertex 1
		1.0f, 0.0f, 0.0f, //color of vertex 2
		1.0f, 0.0f, 0.0f, //color of vertex 0
		1.0f, 0.0f, 0.0f, //color of vertex 1
		1.0f, 0.0f, 0.0f, //color of vertex 2
		1.0f, 0.0f, 0.0f, //color of vertex 0
		1.0f, 0.0f, 0.0f, //color of vertex 1
		1.0f, 0.0f, 0.0f, //color of vertex 2
		1.0f, 0.0f, 0.0f, //color of vertex 2
		1.0f, 0.0f, 0.0f, //color of vertex 0
		1.0f, 0.0f, 0.0f, //color of vertex 1
		1.0f, 0.0f, 0.0f, //color of vertex 2
		1.0f, 0.0f, 0.0f, //color of vertex 2
		1.0f, 0.0f, 0.0f, //color of vertex 0
		1.0f, 0.0f, 0.0f, //color of vertex 1
		1.0f, 0.0f, 0.0f, //color of vertex 2
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	//Pass vertex/color data to the GPU at load time (not run time)
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data1), color_buffer_data1, GL_STATIC_DRAW);
	//Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data1), vertex_buffer_data1, GL_STATIC_DRAW);

	//Load vertex and fragment shaders 
	//Colors
	m_programID = LoadShaders(
		//Vertex shader for position
		"Shader//SimpleVertexShader.vertexshader",
		//Fragment shader for color
		"Shader//SimpleFragmentShader.fragmentshader");
	//Use our shader
	glUseProgram(m_programID);
}

void Scene1::Update(double dt)
{
}

//Every frame
void Scene1::Render()
{
	// Render VBO here
	//Clear color buffer every frame
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//Telling gpu which vertex data to use
	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glEnableVertexAttribArray(1); //2nd attribute buffer: colors

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	//Attribute pointer for vertex
	glVertexAttribPointer(
		0,            //attribute 0. Must match the layout in the
					  //shader. Usually 0 is for vertex
		3,            //size
		GL_FLOAT,     //type
		GL_FALSE,     //normalized?
		0,            //stride
		0             //array buffer offset
	);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	//Attribute pointer for color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	

	//Draw triangle 1
	//Starting from vertex 0; 3 verticles = 1 triangle
	glDrawArrays(GL_TRIANGLES, 0, 9);

	//After use disable
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glEnableVertexAttribArray(1); //2nd attribute buffer: colors

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(0,  3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	//Draw triangle 2 (24 refers to how much in the array)
	//GL_TRIANGLESTRIP for saving vertices (Can draw rectangle too)
	//GL LINE, POINTS, TRIANGLES, TRIANGLE STRIP 
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);

	//After use, disable
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Scene1::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	//Delete to prevent memory leak
	glDeleteProgram(m_programID);
}
