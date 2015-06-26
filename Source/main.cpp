#include "Application.h"
#include "Game.h"

int main()
{
	Application* app = new Game();
	if (app->Initialize())
		app->Run();
	app->Terminate();
	return 0;
}