// ---------------------------------------------------------------------------
// Application.cpp
// Main framework for an application
//
// Original author: <Liam Parker>
// Date created: 14/10/2014
// ---------------------------------------------------------------------------
#include "Engine/Application.h"
#include "Engine/Time.h"
#include "GL/glew.h"
#include "GL/glfw3.h"
#include <iostream>

namespace lazurite
{
	Application::Application()
	{

	}
	
	Application::~Application()
	{
	
	}
	
	bool Application::LazuriteInit(int width, int height, const char* name, bool fullScreen = false)
	{
		if(!InitGLFW())
			return false;
		
		if(fullScreen)
			window = glfwCreateWindow(width, height, name, glfwGetPrimaryMonitor(), NULL);
		else
			window = glfwCreateWindow(width, height, name, NULL, NULL);
	
		if(window == nullptr)
			return false;
	
		glfwMakeContextCurrent(window);

		if(!InitGLEW())
			return false;

		glEnable(GL_DEPTH_TEST);
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

		return true;
	}

	void Application::Run()
	{
		//Main game loop
		do
		{
			glClearColor( 0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			time.Update();

			if(glfwGetKey(window, GLFW_KEY_ESCAPE ) == GLFW_PRESS)
				break;

			//Wireframe mode
			if(glfwGetKey(window, GLFW_KEY_F1 ) == GLFW_PRESS)
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			else if(glfwGetKey(window, GLFW_KEY_F2 ) == GLFW_PRESS)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			Update();
			Render();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		while(!glfwWindowShouldClose(window));
	}
	
	void Application::LazuriteTerminate()
	{
		glfwTerminate();
	}
	
	bool Application::InitGLFW()
	{
		if(glfwInit() != GL_TRUE)
		{
			fprintf(stderr, "ERROR: GLFW failed to initialize!");
			return false;
		}
		
		glfwWindowHint(GLFW_SAMPLES, 8);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Targeting OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS compatibility
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

		// DISABLED - SOIL DOESN'T SUPPORT LATEST CONTEXTS
		// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		return true;
	}

	bool Application::InitGLEW()
	{
		glewExperimental = GL_TRUE;

		if(glewInit() != GLEW_OK)
		{
			fprintf(stderr, "ERROR: GLEW failed to initialize!");
			return false;
		}
		else
			return true;
	}
}
