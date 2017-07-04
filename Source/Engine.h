#pragma once
#include "loadgen/gl_core_4_4.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "ImguiImpl.h"
#include "Core/Input.h"

using glm::mat4;
using glm::vec4;

class Engine
{
public:
	Engine();
	~Engine();

	// Starts all systems required for the engine to run
	 bool Initialize();
	 // Shuts down all currently running engine systems
	 void Terminate();
	 // Runs the engine after initialization
	 void Run();

	 // pure virtual Loop functions.
	 virtual void Load() = 0;
	 virtual void Update(float deltaTime) = 0;
	 virtual void Draw(float deltaTime) = 0;
	 virtual void Unload() = 0;

	 // Sets clear color
	 void SetClearColor(vec4 newColor);

private:
	// GLFW data pointers
	GLFWwindow* window;
	GLFWmonitor* monitor;
	const GLFWvidmode* videoMode;

	// Callback for screen size changes
	static void OnScreenSizeChange(GLFWwindow* w,  int width, int height);
	
	double beginTime;
	double endTime;
	float deltaTime;
	glm::vec3 clearColor;

	// TEMP
	bool wireFrame;
};

