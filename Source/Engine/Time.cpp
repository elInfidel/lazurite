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
	double Time::currentTime = 0.0f;
	double Time::previousTime = 0.0f;
	double Time::deltaTime = 0.0f;

	Time::Time()
	{

	}

	Time::~Time()
	{
	
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
}