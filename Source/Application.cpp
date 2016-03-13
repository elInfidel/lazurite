#include "Application.h"
#include <iostream>
#include "Core/Input.h"
#include "Core/MemoryAllocator.h"

GLFWwindow* Application::window;
GLFWmonitor* Application::monitor;
const GLFWvidmode* Application::videoMode;

Application::Application() : wireFrame(false), clearColor(vec3(30.0f / 255.0f, 30.0f / 255.0f, 30.0f / 255.0f)) { }
Application::~Application() { }

bool Application::Initialize()
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

	// Setting up some OpenGL functionality
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Enable backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Enable color blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable anti-aliasing
	glEnable(GL_MULTISAMPLE);

	// Enable gamma correction
	glEnable(GL_FRAMEBUFFER_SRGB);

	// Instantiating time variables
	beginTime = glfwGetTime(); // Priming beginTime with value of high resolution system clock
	endTime = 0.0;
	deltaTime = 1.0f / 60.0f; // Assuming a starting deltaTime of 60fps (16.667ms)

	// Initializing engine subsystems
	InitializePhysx();
	InitializePhysxDebugger();
	TestPhysx();

	ImGui_ImplGlfwGL3_Init(window, true);

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
	ImGui_ImplGlfwGL3_Shutdown();
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
		Update(deltaTime);
		UpdatePhysX(deltaTime);

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

	g_PhysicsScene->release();
	g_Physics->release();
	g_PhysicsFoundation->release();

	Unload();
}

void Application::InitializePhysx()
{
	PxAllocatorCallback* myCallback = new MemoryAllocator();
	g_PhysicsFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, *myCallback, gDefaultErrorCallback);
	g_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *g_PhysicsFoundation, PxTolerancesScale());
	PxInitExtensions(*g_Physics); 
	g_PhysicsMaterial = g_Physics->createMaterial(0.5f, 0.5f, .5f); 
	PxSceneDesc sceneDesc(g_Physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0, -10.0f, 0);
	sceneDesc.filterShader = &physx::PxDefaultSimulationFilterShader;
	sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
	g_PhysicsScene = g_Physics->createScene(sceneDesc);
}

void Application::InitializePhysxDebugger()
{
	// check if PvdConnection manager is available on this platform 
	if (g_Physics->getPvdConnectionManager() == NULL) return;
	// setup connection parameters 
	const char* pvd_host_ip = "127.0.0.1"; 
	// IP of the PC which is running PVD 
	int port = 5425;
	// TCP port to connect to, where PVD is listening 
	unsigned int timeout = 100;
	// timeout in milliseconds to wait for PVD to respond, //consoles and remote PCs need a higher timeout. 
	PxVisualDebuggerConnectionFlags connectionFlags = PxVisualDebuggerExt::getAllConnectionFlags(); 
	// and now try to connectPxVisualDebuggerExt 
	auto connection = PxVisualDebuggerExt::createConnection( g_Physics-> getPvdConnectionManager(),pvd_host_ip, port, timeout, connectionFlags);
}

void Application::UpdatePhysX(float deltaTime) 
{
	if (deltaTime <= 0) { return; }
	
	g_PhysicsScene->simulate(deltaTime);
	while (g_PhysicsScene->fetchResults() == false) 
	{
		// don’t need to do anything here yet but we have to fetch results
	}
}

void Application::TestPhysx()
{
	//add a plane 
	PxTransform pose = PxTransform(PxVec3(0.0f, 0, 0.0f), PxQuat(PxHalfPi*1.0f, PxVec3(0.0f, 0.0f, 1.0f))); 
	PxRigidStatic* plane = PxCreateStatic(*g_Physics, pose, PxPlaneGeometry(), *g_PhysicsMaterial);
	//add it to the physX scene 
	g_PhysicsScene->addActor(*plane);
	//add a box 
	float density = 10; PxBoxGeometry box(2, 2, 2);
	PxTransform transform(PxVec3(0, 5, 0)); 
	PxRigidDynamic* dynamicActor = PxCreateDynamic(*g_Physics, transform, box, *g_PhysicsMaterial, density); 
	//add it to the physX scene 
	g_PhysicsScene->addActor(*dynamicActor);
}

void Application::SetClearColor(vec4 color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Application::OnScreenSizeChange(GLFWwindow* w, int width, int height)
{
	glViewport(0, 0, width, height);
}