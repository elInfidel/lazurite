// ---------------------------------------------------------------------------
// Application.h
// Main framework for an application
//
// Original author: <Liam Parker>
// Date created: 14/10/2014
// ---------------------------------------------------------------------------
#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include "Time.h"
#include "Input/Input.h"

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
		virtual void Update() = 0;
		virtual void Render() = 0;
		
		bool LazuriteInit(int width, int height, const char* name);
		bool LazuriteInit(int width, int height, const char* name, bool fullScreen);

		void LazuriteTerminate();

	private:
		// Handle to application window
		GLFWwindow *window;

		bool InitGLFW();
		bool InitGLEW();
	};
}

#endif // _APPLICATION_H_