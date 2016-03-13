#include "Renderer.h"

Renderer::Renderer()
{
	std::thread(RenderLoop);
}


Renderer::~Renderer()
{
	commandQueue.clear();
}

void Renderer::SubmitRenderCommand(RenderCommand command)
{
	commandQueue.push_back(command);
}

void Renderer::RenderLoop()
{
	while (!shutdownRequested)
	{
		if (renderRequested)
		{
			IterateRenderCommands();
			renderRequested = false;
		}
	}
}

void Renderer::IterateRenderCommands()
{
	for (auto command : commandQueue)
	{

	}
}

void Renderer::RenderScene(const Camera & camera)
{
	//renderInfo.camera = camera;
	renderRequested = true;
}