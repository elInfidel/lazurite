// ---------------------------------------------------------------------------
// Time.cpp
// A class for keeping track of time.
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#include "Engine/Time.h"
#include "GL/glfw3.h"

double Time::currentTime = 0;
double Time::previousTime = 0;
double Time::deltaTime = 0;

/////////////////////////////////////////
//
// CONSTRUCTORS
//
/////////////////////////////////////////
Time::Time()
{

}

/////////////////////////////////////////
//
// STATIC FUNCTIONS
//
/////////////////////////////////////////
void Time::Update()
{
	currentTime = glfwGetTime();
	deltaTime = currentTime - previousTime;

	previousTime = currentTime;
}

/////////////////////////////////////////
//
// STATIC FUNCTIONS
//
/////////////////////////////////////////
double Time::GetDeltaTime()
{
	return deltaTime;
}

double Time::GetCurrentTime()
{
	return currentTime;
}

/////////////////////////////////////////
//
// DESTRUCTORS
//
/////////////////////////////////////////
Time::~Time()
{

}
