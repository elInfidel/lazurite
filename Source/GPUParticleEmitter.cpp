#include "GPUParticleEmitter.h"
#include <iostream>

GPUParticleEmitter::GPUParticleEmitter() : particles(nullptr), maxParticles(0), drawProgram(0), updateProgram(0), lastDrawTime(0)
{
	vao[0] = 0;
	vao[1] = 0;
	vbo[0] = 0;
	vbo[1] = 0;
}


GPUParticleEmitter::~GPUParticleEmitter()
{
	delete[] particles;

	glDeleteVertexArrays(2, vao);
	glDeleteBuffers(2, vbo);

	delete drawProgram;
	delete updateProgram;
}

void GPUParticleEmitter::Initialize(unsigned int maxParticles, float lifespanMin,
									float lifespanMax, float velocityMin, float velocityMax, float startSize,
									float endSize, const vec4& startColor, const vec4& endColor)
{
	this->maxParticles = maxParticles;
	this->lifespanMin = lifespanMin;
	this->lifespanMax = lifespanMax;
	this->velocityMin = velocityMin;
	this->velocityMax = velocityMax;
	this->startSize = startSize;
	this->endSize = endSize;
	this->startColor = startColor;
	this->endColor = endColor;

	particles = new GPUParticle::Particle[maxParticles];

	activeBuffer = 0;

	CreateBuffers();
	CreateUpdateProgram();
	CreateDrawProgram();
}

void GPUParticleEmitter::CreateBuffers()
{
	// Generate buffers
	glGenVertexArrays(2, vao);
	glGenBuffers(2, vbo);

	// Setup update program
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, maxParticles * sizeof(GPUParticle::Particle), particles, GL_STREAM_DRAW);

	glEnableVertexAttribArray(0); // Position
	glEnableVertexAttribArray(1); // Velocity
	glEnableVertexAttribArray(2); // Lifetime
	glEnableVertexAttribArray(3); // Lifespan

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GPUParticle::Particle), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GPUParticle::Particle), ((char*)0) + 12);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(GPUParticle::Particle), ((char*)0) + 24);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(GPUParticle::Particle), ((char*)0) + 28);

	// Setup draw program
	glBindVertexArray(vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, maxParticles * sizeof(GPUParticle::Particle), 0, GL_STREAM_DRAW);

	glEnableVertexAttribArray(0); // Position
	glEnableVertexAttribArray(1); // Velocity
	glEnableVertexAttribArray(2); // Lifetime
	glEnableVertexAttribArray(3); // Lifespan

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GPUParticle::Particle), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GPUParticle::Particle), ((char*)0) + 12);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(GPUParticle::Particle), ((char*)0) + 24);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(GPUParticle::Particle), ((char*)0) + 28);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GPUParticleEmitter::CreateUpdateProgram()
{
	const char* varyings[] = { "position", "velocity", "lifetime", "lifespan" };

	updateProgram = new ShaderProgram();
	updateProgram->CompileShader("Resources/Shaders/Particle/GPUPartUpdate.glsl", OpenGLShader::VERTEX);
	updateProgram->SetTransformFeedbackVaryings(4, varyings, GL_INTERLEAVED_ATTRIBS);
	updateProgram->Link();
	updateProgram->Validate();

	glUseProgram(updateProgram->GetHandle());

	updateProgram->SetUniform("lifeMin", lifespanMin);
	updateProgram->SetUniform("lifeMin", lifespanMax);
}

void GPUParticleEmitter::CreateDrawProgram()
{
	drawProgram = new ShaderProgram();
	drawProgram->CompileShader("Resources/Shaders/Particle/GPUPartVert.glsl", OpenGLShader::VERTEX);
	drawProgram->CompileShader("Resources/Shaders/Particle/GPUPartFrag.glsl", OpenGLShader::FRAGMENT);
	drawProgram->CompileShader("Resources/Shaders/Particle/GPUPartGeom.glsl", OpenGLShader::GEOMETRY);
	drawProgram->Link();
	drawProgram->Validate();

	glUseProgram(drawProgram->GetHandle());

	drawProgram->SetUniform("sizeStart", startSize);
	drawProgram->SetUniform("sizeEnd", endSize);

	drawProgram->SetUniform("colorStart", startColor);
	drawProgram->SetUniform("colorEnd", endColor);
}

void GPUParticleEmitter::Draw(float time, Camera& camera)
{
	// Updating Particles
	glUseProgram(updateProgram->GetHandle());

	float delta = time - lastDrawTime;
	lastDrawTime = time;

	updateProgram->SetUniform("time", time);
	updateProgram->SetUniform("deltaTime", delta);
	updateProgram->SetUniform("emitterPosition", transform.GetPosition());

	glEnable(GL_RASTERIZER_DISCARD);

	glBindVertexArray(vao[activeBuffer]);

	unsigned int otherBuffer = (activeBuffer + 1) % 2;

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo[otherBuffer]);

	glBeginTransformFeedback(GL_POINTS);
	glDrawArrays(GL_POINTS, 0, maxParticles);
	glEndTransformFeedback();

	glDisable(GL_RASTERIZER_DISCARD);

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);

	// Drawing particles
	glUseProgram(drawProgram->GetHandle());

	drawProgram->SetUniform("projectionView", camera.GetProjectionView());
	drawProgram->SetUniform("cameraTransform", camera.transform->GetModelMatrix());

	glBindVertexArray(vao[otherBuffer]);
	glDrawArrays(GL_POINTS, 0, maxParticles);

	activeBuffer = otherBuffer;
}