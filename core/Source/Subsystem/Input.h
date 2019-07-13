#pragma once
#include "glfw/glfw3.h"
#include "glm/vec2.hpp"

using glm::vec2;

class Input
{
public:
	static Input* GetInstance();   // Returns singleton
								   
	bool GetKey(int key);          // Returns true if key is down
	bool GetKeyPressed(int key);   // Returns true if key is pressed for the first time
	bool GetKeyDown(int key);      // Returns true if key is repeating
	bool GetKeyReleased(int key);  // Returns true if key has been released
	
	vec2 GetMousePos();                      // Returns a vec2 containing current mouse coordinates
	void GetMousePos(float &x, float &y);    // Sets variable references to current mouse coordinates
	vec2 GetMouseDelta();                    // Returns a vec2 containing current mouse delta
	void GetMouseDelta(float &x, float &y);  // Sets variable references to current mouse delta

	void EndFrame(float deltaTime);

private:
	Input();
	~Input();

	static Input* singleton;
	static const int MAX_KEYS = 512;

	vec2  mousePosition;         // The current position of the mouse in screen space
	vec2  mouseDelta;            // Changes in mouse position represented as a delta value
	signed char keys[MAX_KEYS];  // Stores GLFW key definitions from events

	// GLFW Callbacks
	static void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods); // Called on key state change
	static void OnChar(GLFWwindow* window, unsigned int character);                     // Called on character state change
	static void OnMousePos(GLFWwindow* window, double x, double y);                     // Called on mouse position change
	static void OnMouseButton(GLFWwindow* window, int button, int action, int mods);    // Called on mouse button state change
	static void OnMouseScroll(GLFWwindow* window, double x, double y);                  // Called on mouse scroll state change
};

