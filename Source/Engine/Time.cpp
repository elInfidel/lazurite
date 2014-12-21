// ---------------------------------------------------------------------------
// Time.cpp
// A class for keeping track of time.
//
// Original author: <Liam Parker>
// Date created: 3/11/2014
// ---------------------------------------------------------------------------
#include "Engine/Time.h"
#include "GL/glfw3.h"

namespace lazurite
{
	double Time::currentTime = 0;
	double Time::previousTime = 0;
	double Time::deltaTime = 0;
	
	Time::Time()
	{
		currentTime = 0.0f;
		previousTime = 0.0f;
		deltaTime = 0.0f;
	}

	void Time::Update()
	{
		currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
	
		previousTime = currentTime;
	}

	double Time::GetDeltaTime()
	{
		return deltaTime;
	}
	
	double Time::GetCurrentTime()
	{
		return currentTime;
	}

	Time::~Time()
	{
	
	}
}