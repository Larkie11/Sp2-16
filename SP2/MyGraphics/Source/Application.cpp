/******************************************************************************/
/*!
\file	Application.cpp
\author Tang Wen Sheng, edited by Mok Wei Min
\par
\brief
Runs the game, with the correct scenes
*/
/******************************************************************************/
#include "Application.h"
//Include GLEW
#include <GL/glew.h>
#include "SharedData.h"
//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "StartCutScene.h"
#include "Sp2.h"
#include "SceneMenu.h"
#include "Shop.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Cutscene.h"
#include "SceneWin.h"

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

/******************************************************************************/
/*!
\brief
Defines an error callback

\exception None
\return None
*/
/******************************************************************************/
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

/******************************************************************************/
/*!
\brief
Defines key input callback

\exception None
\return None
*/
/******************************************************************************/
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

/******************************************************************************/
/*!
\brief
Check which key is presses

\exception None
\return None
*/
/******************************************************************************/
bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}
/******************************************************************************/
/*!
\brief
Default constructor

\exception None
\return None
*/
/******************************************************************************/
Application::Application()
{
}
/******************************************************************************/
/*!
\brief
Default destructor

\exception None
\return None
*/
/******************************************************************************/
Application::~Application()
{
}

/******************************************************************************/
/*!
\brief
Updates opengl new window size

\exception None
\return None
*/
/******************************************************************************/
void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}
/******************************************************************************/
/*!
\brief
Initializes

\exception None
\return None
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief
Main loop to run the game

\exception None
\return None
*/
/******************************************************************************/
void Application::Run()
{
	//Main Loop
	Scene *scene = new SceneMenu;
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

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
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				scene = new SceneMenu();
				break;
			case SharedData::G_CUTSCENE:
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				scene = new StartCutScene();
				break;
			case SharedData::GAME:
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				scene = new SP2();
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
			case SharedData::WIN:
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				scene = new SceneWin();
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
/******************************************************************************/
/*!
\brief
Exit game, terminate and clean up GLFW

\exception None
\return None
*/
/******************************************************************************/
void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
