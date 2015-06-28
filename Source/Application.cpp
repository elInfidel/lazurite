#include "Application.h"
#include <iostream>
#include "Input.h"
#include "glm/gtc/type_ptr.hpp"

Application::Application() : wireFrame(false), clearColor(vec3(192.0f / 255.0f, 192.0f / 255.0f, 192.0f / 255.0f))
{

}

Application::~Application()
{
	
}

bool Application::Initialize()
{
	// Attempt to initialize GLFW
	if (!glfwInit())
		return false;

	monitor = glfwGetPrimaryMonitor();
	videoMode = glfwGetVideoMode(monitor);

	// Window hints for window creation
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a new OpenGL window
	window = glfwCreateWindow((int)(videoMode->width / 1.2f), (int)(videoMode->height / 1.2f), "Lazurite Framework", nullptr, nullptr);

	// Terminate if glfw fails to create a window
	if (window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	// Set the newly created window to the current openGL context
	glfwMakeContextCurrent(window);

	// Attempt to load openGL functions through loadgen
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwTerminate();
		return false;
	}

	// Setting up some OpenGL functionality
	SetClearColor(vec4(0.3f, 0.3f, 0.3f, 1.0f));
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Disable backface culling temp
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	// Instantiating time variables
	beginTime = glfwGetTime(); // Priming beginTime with value of high resolution system clock
	endTime = 0.0;
	deltaTime = 1.0f / 60.0f; // Assuming a starting deltaTime of 60fps (16.667ms)

	// Initializing engine subsystems
	Input::Initialize();

	// TEMP INIT TW
	TwInit(TW_OPENGL_CORE, nullptr);
	TwWindowSize((int)(videoMode->width / 1.2f), (int)(videoMode->height / 1.2f));
	glfwSetFramebufferSizeCallback(window, OnScreenSizeChange);

	// Print system data
	printf("***Lazurite Framework***\n");
	int major = ogl_GetMajorVersion();
	int minor = ogl_GetMinorVersion();
	int rev = 0;
	printf(" OpenGL Version: %i.%i\n", major, minor);
	glfwGetVersion(&major, &minor, &rev);
	printf(" GLFW Version:   %i.%i\n", major, minor);

	return true;
}

void Application::Terminate()
{
	TwDeleteAllBars();
	TwTerminate();
	glfwTerminate();
}

void Application::Run()
{
	Load();

	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		SetClearColor(vec4(clearColor, 1));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();

		// TODO: TEMP
		if (Input::GetKeyPressed(GLFW_KEY_F9))
		{
			glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			Input::mouseLocked = true;
		}
		else if (Input::GetKeyPressed(GLFW_KEY_F10))
		{
			glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			Input::mouseLocked = false;
		}

		// TODO: TEMP
		if (Input::GetKeyPressed(GLFW_KEY_F1))
			wireFrame = (!wireFrame); // BUG - Toggle flickers, input class needs loads of work

		// Calling functions of Game class
		Update(deltaTime);

		if (wireFrame)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		Draw(deltaTime);

		// Temp TW DRAW
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		TwDraw();

		glfwSwapBuffers(window);

		// Calculating deltaTime
		endTime = glfwGetTime();
		deltaTime = (float)(endTime - beginTime);
		beginTime = endTime;
		// If the deltaTime is too large we can assume we continued execution from a breakpoint
		// and reset the deltaTime back to a optimal scenario of 16ms
		if (deltaTime > 1.0f)
			deltaTime = 1.0f / 60.0f;
	}

	Unload();
}

void Application::SetClearColor(vec4 color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Application::OnScreenSizeChange(GLFWwindow* w, int width, int height)
{
	glViewport(0, 0, width, height);
	TwWindowSize(width, height);
}