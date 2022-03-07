#pragma once
#include "gl_core_4_4.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "subsystem/Input.h"
#include <vector>

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

	// pure virtual loop functions. We call down into implemention once for each of these events during a cycle of the loop.
	virtual void Load() = 0;
	virtual void Tick(float deltaTime) = 0;
	virtual void Draw(float deltaTime) = 0;
	virtual void Unload() = 0;

	// Certain functionality for rendering is handled at the engine level.
	void DrawInternal(float deltaTime);

private:
	// GLFW data pointers
	GLFWwindow* window;

	// Callback for screen size changes
	static void OnScreenSizeChange(GLFWwindow* w,  int width, int height);
	
	std::vector<float> previousFpsValues;

	double beginTime;
	double endTime;
	float deltaTime;
	glm::vec4 clearColor;
};

