#include "Engine.h"
#include <iostream>

#include "Core/Input.h"
#include "Core/MemoryAllocator.h"
#include "Core/Physics.h"

#include "Camera.h"
#include "ShaderProgram.h"

Engine::Engine() : wireFrame(false), clearColor(vec3(30.0f / 255.0f, 30.0f / 255.0f, 30.0f / 255.0f)) { }
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

	// Instantiating time variables
	beginTime = glfwGetTime();
	endTime = 0.0;
	deltaTime = 1.0f / 60.0f;

	// Initializing engine subsystems
	physics = new Physics();
	physics->Initialize();

	scene = new Scene();

	ImGui_ImplGlfwGL3_Init(window, true);

	glfwSetFramebufferSizeCallback(window, OnScreenSizeChange);

	// Print system data
	printf("***Lazurite Framework***\n");
	int major, minor, rev;
	printf(" OpenGL Version: %i.%i\n", major, minor);
	glfwGetVersion(&major, &minor, &rev);
	printf(" GLFW Version:   %i.%i\n", major, minor);

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

		// TODO: TEMP
		if (Input::GetInstance()->GetKeyPressed(GLFW_KEY_F9))
		{
			glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			Input::GetInstance()->mouseLocked = true;
		}
		else if (Input::GetInstance()->GetKeyPressed(GLFW_KEY_F10))
		{
			glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			Input::GetInstance()->mouseLocked = false;
		}

		// TODO: TEMP
		if (Input::GetInstance()->GetKeyPressed(GLFW_KEY_F1))
			wireFrame = (!wireFrame);

		// Calling functions of Game class
		Update(*scene, deltaTime);
		physics->Update(deltaTime);

		if (wireFrame)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		Draw(deltaTime);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		ImGui::Render();
		glfwSwapBuffers(window);
		Input::GetInstance()->Update(deltaTime);

		// Calculating deltaTime
		endTime = glfwGetTime();
		deltaTime = (float)(endTime - beginTime);
		beginTime = endTime;
		// If the deltaTime is too large we can assume we continued execution from a breakpoint
		// and reset the deltaTime back to a optimal scenario of 16ms
		if (deltaTime > 1.0f)
			deltaTime = 1.0f / 60.0f;
	}

	ImGui_ImplGlfwGL3_Shutdown();
	physics->Shutdown();

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