#include "Engine.h"
#include <iostream>

#include "Core/Input.h"
#include "Core/MemoryAllocator.h"

#include "Camera.h"
#include "ShaderProgram.h"

Engine::Engine() : clearColor(vec3(30.0f / 255.0f, 30.0f / 255.0f, 30.0f / 255.0f)) { }
Engine::~Engine() { }

bool Engine::Initialize()
{
	// Attempt to initialize GLFW
	if (!glfwInit())
		return false;

	monitor = glfwGetPrimaryMonitor();
	videoMode = glfwGetVideoMode(monitor);

	// Window hints for window creation
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a new OpenGL window
	window = glfwCreateWindow((int)(videoMode->width / 1.2f), (int)(videoMode->height / 1.2f), "Lazurite Framework", nullptr, nullptr);

	// Terminate if glfw fails to create a window
	if (!window)
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

	// Instantiating time variables
	beginTime = glfwGetTime();
	endTime = 0.0;
	deltaTime = 1.0f / 60.0f;

	// Initializing engine subsystems
	ImGui_ImplGlfwGL3_Init(window, true);

	// Set viewport dimensions and callback for future window size changes.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, OnScreenSizeChange);

	// Print program information
	printf("***Lazurite Framework***\n\n");
	int major = 0, minor = 0, rev = 0;

	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	printf(" OpenGL Version: %i.%i\n", major, minor);

	glfwGetVersion(&major, &minor, &rev);
	printf(" GLFW Version:   %i.%i.%i\n", major, minor, rev);

	printf(" IMGUI Version:  %s", IMGUI_VERSION);


	return true;
}

void Engine::Terminate()
{
	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();
}

void Engine::Run()
{
	Load();

	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		SetClearColor(vec4(clearColor, 1));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();

		// Calling functions of Game class
		Update(deltaTime);
		Draw(deltaTime);

		ImGui::Render();
		glfwSwapBuffers(window);
		Input::GetInstance()->Update(deltaTime);

		// Calculating deltaTime
		endTime = glfwGetTime();
		deltaTime = (float)(endTime - beginTime);
		beginTime = endTime;
		// If the deltaTime is too large we can assume we continued execution from a breakpoint
		// and reset the deltaTime back to an optimal scenario of 16ms
		if (deltaTime > 1.0f)
			deltaTime = 1.0f / 60.0f;
	}

	Unload();
}

void Engine::SetClearColor(vec4 color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Engine::OnScreenSizeChange(GLFWwindow* w, int width, int height)
{
	glViewport(0, 0, width, height);
}