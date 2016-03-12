#pragma once
#include "loadgen/gl_core_4_4.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "ShaderProgram.h"
#include "Camera.h"
#include <physx/PxPhysicsAPI.h>
#include <physx/PxScene.h>
#include <physx/pvd/PxVisualDebugger.h>
#include "ImguiImpl.h"

using namespace physx;

using glm::mat4;
using glm::vec4;

class Application
{
public:
	Application();
	~Application();

	// Starts all systems required for the engine to run
	 bool Initialize();
	 // Shuts down all currently running engine systems
	 void Terminate();
	 // Runs the engine after initialization
	 void Run();
	 // Nvidia PhysX
	 void InitializePhysx();
	 void InitializePhysxDebugger();
	 void UpdatePhysX(float deltaTime);
	 void TestPhysx();

	 // Temp functions
	 //void GenerateGrid(unsigned int rows, unsigned int cols);
	 //void DrawGrid(Camera* camera, ShaderProgram* shaderProgram, int rows, int cols);

	 // pure virtual Loop functions.
	 virtual void Load() = 0;
	 virtual void Update(float deltaTime) = 0;
	 virtual void Draw(float deltaTime) = 0;
	 virtual void Unload() = 0;

	 // Sets clear color
	 void SetClearColor(vec4 newColor);

private:
	// GLFW data pointers
	static GLFWwindow* window;
	static GLFWmonitor* monitor;
	static const GLFWvidmode* videoMode;

	// Callback for screen size changes
	static void OnScreenSizeChange(GLFWwindow* w,  int width, int height);
	
	double beginTime;
	double endTime;
	float deltaTime;
	vec3 clearColor;

	// TEMP
	bool wireFrame;
	bool show_test_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImColor(114, 144, 154);

	// TEMP PHYSICS
	PxFoundation* g_PhysicsFoundation;
	PxPhysics* g_Physics;
	PxScene* g_PhysicsScene; 
	PxDefaultErrorCallback gDefaultErrorCallback; 
	PxDefaultAllocator gDefaultAllocatorCallback;
	PxSimulationFilterShader gDefaultFilterShader = PxDefaultSimulationFilterShader; 
	PxMaterial* g_PhysicsMaterial; 
	PxMaterial* g_boxMaterial;
	PxCooking* g_PhysicsCooker;
};

