#pragma once
#include <vector>
#include "Camera.h"
#include "GameObject.h"
#include "Model.h"

class RenderSystem
{
protected:
	RenderSystem();
	~RenderSystem();

	void QueueRenderCommand();

private:

};

