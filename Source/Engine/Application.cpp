// ---------------------------------------------------------------------------
// Application.cpp
// Main framework for an application
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------

#include "Engine/Application.h"
#include "Engine/Sprite.h"
#include "Engine/Time.h"
#include "GL/glew.h"
#include "GL/glfw3.h"
#include <iostream>

namespace lazurite
{

	//////////////////////////////////////////
	//
	// CONSTRUCTORS
	//
	/////////////////////////////////////////
	Application::Application()
	{
		time = new Time();
	}
	
	/////////////////////////////////////////
	//
	// MEMBER FUNCTIONS
	//
	/////////////////////////////////////////
	bool Application::LazuriteInit(int width, int height)
	{
		if(!glfwInit())
		{
			fprintf(stderr, "ERROR: GLFW failed to start up!");
			return false;
		}
	
		window = glfwCreateWindow(width, height, "Lazurite Engine", NULL, NULL);
	
		if(window == nullptr)
		{
			return false;
		}
	
		glfwMakeContextCurrent(window);
	
		if(glewInit() != GLEW_OK)
		{
			return false;
		}
	
		return true;
	}
	
	bool Application::LazuriteInit(int width, int height, const char* name)
	{
		if(!glfwInit())
		{
			fprintf(stderr, "ERROR: GLFW failed to start up!");
			return false;
		}
	
		window = glfwCreateWindow(width, height, name, NULL, NULL);
	
		if(window == nullptr)
		{
			return false;
		}
	
		glfwMakeContextCurrent(window);
	
		if(glewInit() != GLEW_OK)
		{
			return false;
		}
	
		return true;
	}
	
	bool Application::LazuriteInit(int width, int height, const char* name, bool fullScreen)
	{
		if(!glfwInit())
		{
			fprintf(stderr, "ERROR: GLFW failed to start up!");
			return false;
		}
	
		if(fullScreen)
			window = glfwCreateWindow(width, height, name, glfwGetPrimaryMonitor(), NULL);
		else
			window = glfwCreateWindow(width, height, name, NULL, NULL);
	
		if(window == nullptr)
		{
			return false;
		}
	
		glfwMakeContextCurrent(window);
	
		if(glewInit() != GLEW_OK)
		{
			return false;
		}
	
		return true;
	}
	
	void Application::Run()
	{
		//Testing sprite functionality
		Sprite sprite;
		int width, height, bpp;
		sprite.loadTexture("Content/test_texture.png", width, height, bpp);

		//Main game loop
		do
		{
			time->Update();
			glfwPollEvents();
	
			ClearScreen();
	
			sprite.Draw();
			Update();
			Draw();
	
			glfwSwapBuffers(window);
		}
		while(!glfwWindowShouldClose(window));
	}
	
	void Application::ClearScreen()
	{
		glClearColor(0.4f, 0.4f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void Application::LazuriteTerminate()
	{
		glfwTerminate();
		delete time;
	}
	
	/////////////////////////////////////////
	//
	// DESTRUCTORS
	//
	/////////////////////////////////////////
	Application::~Application()
	{
	
	}
}
