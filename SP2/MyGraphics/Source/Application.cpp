
#include "Application.h"

//Include GLEW
#include <GL/glew.h>
#include "SharedData.h"
//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "Cutscene.h"
#include "SceneMenu.h"
#include "Shop.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Cutscene.h"

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{
}

Application::~Application()
{
}


void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h); // update opengl the new window size
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);
	
	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	SharedData::GetInstance()->width = mode->width + 1;
	SharedData::GetInstance()->height = mode->height + 1;

	//Change glfwGetPrimaryMonitor to null for windowed version, change width and height to your own liking (Example 1080, 768, null, null)
	//m_window = glfwCreateWindow(SharedData::GetInstance()->width, SharedData::GetInstance()->height, "SPACE", glfwGetPrimaryMonitor(), nullptr);
	m_window = glfwCreateWindow(1080, 768, "SPACE", NULL, nullptr);
	glfwSetCursorPos(m_window, SharedData::GetInstance()->width / 2, SharedData::GetInstance()->height / 2);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	
	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
}

void Application::Run()
{
	//Main Loop
	Scene *scene = new Cutscene;	
	scene->Init();

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && SharedData::GetInstance()->gameState!= SharedData::QUIT && !IsKeyPressed(VK_ESCAPE))
	{
		scene->Update(m_timer.getElapsedTime());
		scene->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
		m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

		//To change scene, have to first make stateCheck true
		//And the set the gameState
		if (SharedData::GetInstance()->stateCheck)
		{
			delete scene;
			SharedData::GetInstance()->stateCheck = false;

			switch (SharedData::GetInstance()->gameState)
			{
			case SharedData::MENU:
				scene = new SceneMenu();
				break;
			case SharedData::GAME:
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				scene = new Cutscene();
				break;
			case SharedData::SCENE2:
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				scene = new Scene2();
				break;
			case SharedData::SCENE3:
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				scene = new Scene3();
				break;
			case SharedData::CUTSCENE:
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				scene = new Cutscene();
				break;
			case SharedData::SHOP:
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				scene = new Shop();
				break;
			}
			scene->Init();
		}
	} //Check if the ESC key had been pressed or if the window had been closed
	
	scene->Exit();
	delete scene;
	
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
