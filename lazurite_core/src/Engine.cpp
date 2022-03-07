#include "Engine.h"
#include "subsystem/Input.h"
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <chrono>
#include <numeric>

Engine::Engine() : clearColor(glm::vec4(30.0f / 255.0f, 30.0f / 255.0f, 30.0f / 255.0f, 1.0f)) { }
Engine::~Engine() { }

bool Engine::Initialize()
{
	// Attempt to initialize GLFW
	if (!glfwInit())
		return false;

	auto monitor = glfwGetPrimaryMonitor();
	auto videoMode = glfwGetVideoMode(monitor);
	
	// Window hints for window creation
	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a new OpenGL window
	window = glfwCreateWindow(
		videoMode->width,
		videoMode->height,
		"Lazurite Framework",
		nullptr,
		nullptr);

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
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

	// TODO Move this into a render subsystem
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_MULTISAMPLE);

	// IMGUI Init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 420");

	// Instantiating time variables
	beginTime = glfwGetTime();
	endTime = 0.0;
	deltaTime = 1.0f / 60.0f;

	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, OnScreenSizeChange);

	// Print system data
	printf("***Lazurite Framework***\n");
	int major, minor, rev = 0;
	glfwGetVersion(&major, &minor, &rev);
	printf(" GLFW Version:   %i.%i\n", major, minor);

	return true;
}

void Engine::Terminate()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

void Engine::Run()
{
	Load();

	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		beginTime = glfwGetTime();

		glfwPollEvents();
		// Calling functions of Game class
		auto tickTimeStart = std::chrono::steady_clock::now();
		Tick(deltaTime);
		auto tickTimeEnd = std::chrono::steady_clock::now();
		DrawInternal(deltaTime);
		Input::GetInstance()->EndFrame(deltaTime);

		// Calculating deltaTime
		// If the deltaTime is too large we can assume we continued execution from a breakpoint
		// and reset the deltaTime back to a optimal scenario of 16ms
		endTime = glfwGetTime();
		deltaTime = (float)(endTime - beginTime);
		beginTime = endTime;

		auto monitor = glfwGetPrimaryMonitor();

		if (deltaTime > 1.0f)
			deltaTime = 1.0f / 60.0f;
	}

	Unload();
}

void Engine::DrawInternal(float deltaTime)
{
	// Clear the back buffer in preperation for drawing a new frame.s
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Imgui start frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Call user implementation of draw
	auto drawTimeStart = std::chrono::steady_clock::now();
	Draw(deltaTime);
	auto drawTimeEnd = std::chrono::steady_clock::now();

	// Render debugging overlay.
	// TODO: pull this into something else.
	ImGui::Begin("Scene Statistics");
	this->previousFpsValues.push_back(1.0f / deltaTime);
	if (this->previousFpsValues.size() > 75) this->previousFpsValues.erase(this->previousFpsValues.begin());
	char overlay[32];
	auto const count = static_cast<float>(this->previousFpsValues.size());
	auto average = std::accumulate(
		this->previousFpsValues.begin(),
		this->previousFpsValues.end(), 0.0
	) / this->previousFpsValues.size();
	sprintf(overlay, "%d", (int)average);
	ImGui::PlotLines(
		"Frame Rate",
		this->previousFpsValues.data(),
		this->previousFpsValues.size(),
		0, overlay, 0.0f, 150.0f, ImVec2(0, 40.0f)
	);
	int millis = (int)std::chrono::duration_cast<std::chrono::milliseconds>(drawTimeEnd - drawTimeStart).count();
	ImGui::Text("Tick: %5d ms", millis);
	millis = (int)std::chrono::duration_cast<std::chrono::milliseconds>(drawTimeEnd - drawTimeStart).count();
	ImGui::Text("Draw: %5d ms", millis);
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Swap the freshly prepared back buffer with the front
	glfwSwapBuffers(window);
}

void Engine::OnScreenSizeChange(GLFWwindow* w, int width, int height)
{
	glViewport(0, 0, width, height);
	auto engine = (Engine*)glfwGetWindowUserPointer(w);
	engine->DrawInternal(engine->deltaTime);
}