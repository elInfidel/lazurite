#pragma once
#include "CoreSystem.h"
#include "loadgen/gl_core_4_4.h"
#include "../Camera.h"
#include "../Material.h"
#include "../ShaderProgram.h"
#include "../Component/Transform.h"
#include <vector>
#include <thread>

struct RenderCommand
{
	Transform& transform;
	Material& material;
	ShaderProgram& shaderProgram;
	GLuint vao, vbo, ebo;
};

struct RenderInfo
{
	Camera& camera;
};

class Renderer : public CoreSystem
{
	friend class Application;
public:
	Renderer();
	~Renderer();

	void RenderScene(const Camera& camera);
	void SubmitRenderCommand(RenderCommand command);

private:
	//RenderInfo renderInfo;

	bool renderRequested = false;
	bool shutdownRequested = false;

	std::vector<RenderCommand> commandQueue;

	void RenderLoop();
	void IterateRenderCommands();
};

