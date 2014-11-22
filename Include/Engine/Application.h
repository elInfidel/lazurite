// ---------------------------------------------------------------------------
// Application.h
// Main framework for an application
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include "Time.h"

//Forward Declarations
struct GLFWwindow;

namespace lazurite
{
	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	
	protected:
		virtual bool Load() = 0;
		virtual void Unload() = 0;
	
		virtual void Update() = 0;
		virtual void Draw() = 0;
	
		bool LazuriteInit(int width, int height);
		bool LazuriteInit(int width, int height, const char* name);
		bool LazuriteInit(int width, int height, const char* name, bool fullScreen);

		void LazuriteTerminate();
	
	private:
		void ClearScreen();
		GLFWwindow *window;
		Time *time;
	};
}

#endif // _APPLICATION_H_