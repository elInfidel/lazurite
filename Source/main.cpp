#include "Engine.h"
#include "Editor.h"

int main()
{
	Engine* app = new Editor();
	if (app->Initialize())
		app->Run();
	app->Terminate();
	return 0;
}