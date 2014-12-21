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
	Application::Application()
	{
		time = new Time();
	}
	
	Application::~Application()
	{
	
	}

	bool Application::LazuriteInit(int width, int height)
	{
		if(!InitGLFW())
			return false;
	
		window = glfwCreateWindow(width, height, "Lazurite Engine", NULL, NULL);
	
		if(window == nullptr)
			return false;
	
		glfwMakeContextCurrent(window);
	
		if(!InitGLEW())
			return false;
	
		return true;
	}
	
	bool Application::LazuriteInit(int width, int height, const char* name)
	{
		if(!InitGLFW())
			return false;

		window = glfwCreateWindow(width, height, name, NULL, NULL);
	
		if(window == nullptr)
			return false;
	
		glfwMakeContextCurrent(window);
	
		if(!InitGLEW())
			return false;

		return true;
	}
	
	bool Application::LazuriteInit(int width, int height, const char* name, bool fullScreen)
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

		return true;
	}
	
	void Application::Run()
	{
		//Testing sprite functionality
	Sprite sprite;
	int width, height, bpp;
	sprite.loadTexture("Content/test_texture.png", width, height, bpp);

	float rotation = 0.0f;

		//Main game loop
		do
		{
			time->Update();
			glfwPollEvents();

			if(glfwGetKey(window, GLFW_KEY_ESCAPE ) == GLFW_PRESS)
				break;

			if(glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS)
				sprite.transform.Translate(Vector3(0.0f, 5.0f, 0.0f));
			if(glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS)
				sprite.transform.Translate(Vector3(-5.0f, 0.0f, 0.0f));
			if(glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS)
				sprite.transform.Translate(Vector3(0.0f, -5.0f, 0.0f));
			if(glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS)
				sprite.transform.Translate(Vector3(5.0f, 0.0f, 0.0f));

			if(glfwGetKey(window, GLFW_KEY_Q ) == GLFW_PRESS)
				rotation += 0.1f * Time::GetDeltaTime();
			if(glfwGetKey(window, GLFW_KEY_E ) == GLFW_PRESS)
				rotation -= 0.1f * Time::GetDeltaTime();

			sprite.transform.Rotate(Vector3(0,0,rotation));

			ClearScreen();
	
			Update();
			Draw();
			sprite.Draw();

			glfwSwapBuffers(window);
		}
		while(!glfwWindowShouldClose(window));
	}
	
	void Application::LazuriteTerminate()
	{
		glfwTerminate();
		delete time;
	}

	void Application::ClearScreen()
	{
		glClearColor(0.4f, 0.4f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	bool Application::InitGLFW()
	{
		if(!glfwInit())
		{
			fprintf(stderr, "ERROR: GLFW failed to initialize!");
			return false;
		}
	
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Targeting OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS compatibility
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

		// SOIL DOESN'T SUPPORT LATEST CONTEXTS
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		return true;
	}

	bool Application::InitGLEW()
	{
		glewExperimental = true;

		if(glewInit() != GLEW_OK)
		{
			fprintf(stderr, "ERROR: GLEW failed to initialize!");
			return false;
		}
		else
			return true;
	}
}
