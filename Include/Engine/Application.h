// ---------------------------------------------------------------------------
// Application.h
// Main framework for an application
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//Forward Declarations
struct GLFWwindow;
class Time;

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

	bool Initialize(int width, int height);
	bool Initialize(int width, int height, const char* name);
	bool Initialize(int width, int height, const char* name, bool fullScreen);

	void ClearScreen();
	void LazuriteTerminate();

private:
	GLFWwindow *window;
	Time *time;
};

#endif // _APPLICATION_H_