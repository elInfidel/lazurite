#include "Engine.h"
#include "Game.h"

int main()
{
	Engine* app = new Game();
	if (app->Initialize())
		app->Run();
	app->Terminate();
	return 0;
}