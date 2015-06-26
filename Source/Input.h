#pragma once
#include "glfw/glfw3.h"
#include "glm/vec2.hpp"
#include <map>

using std::map;
using glm::vec2;


class Input
{
public:
	static void Initialize();
	static void ShutDown();

	static bool GetKey(int key);          // Returns true if key is down
	static bool GetKeyPressed(int key);   // Returns true if key is pressed for the first time
	static bool GetKeyDown(int key);      // Returns true if key is repeating
	static bool GetKeyReleased(int key);  // Returns true if key has been released
	 
	static vec2 GetMousePos();
	static void GetMousePos(float &x, float &y);
	static vec2 GetMouseDelta();
	static void GetMouseDelta(float &x, float &y);


	// TEMP
	static bool mouseLocked;

private:
	Input();
	~Input();

	// Input state data
	static vec2 mousePosition;
	static vec2 mouseDelta;
	static map<int, int> keys;

	// GLFW Callbacks
	static void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods); // Called on key state change
	static void OnChar(GLFWwindow* window, unsigned int character);                     // Called on character state change
	static void OnMousePos(GLFWwindow* window, double x, double y);                     // Called on mouse position change
	static void OnMouseButton(GLFWwindow* window, int button, int action, int mods);    // Called on mouse button state change
	static void OnMouseScroll(GLFWwindow* window, double x, double y);                  // Called on mouse scroll state change
};

