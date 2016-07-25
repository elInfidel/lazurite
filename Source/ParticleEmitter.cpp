#include "ParticleEmitter.h"
#include "loadgen/gl_core_4_4.h"
#include "glfw/glfw3.h"
#include <iostream>

ParticleEmitter::ParticleEmitter() : particles(nullptr), firstDead(0), maxParticles(0), vao(0), vbo(0), ibo(0), vertexData(nullptr)
{

}

ParticleEmitter::~ParticleEmitter()
{
	delete[] particles;
	delete[] vertexData;

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void ParticleEmitter::Initialize(unsigned int maxParticles, float emitRate, float lifetimeMin, float lifetimeMax,
									float velocityMin, float velocityMax, float startSize, 
									float endSize, const vec4& startColor, const vec4& endColor)
{
	// Set up timer
	emitTimer = 0.0f;
	emitRate = 1.0f / emitRate;

	// Set up emitter variables
	this->maxParticles = maxParticles;
	this->emitRate = emitRate;
	this->lifespanMin = lifetimeMin;
	this->lifespanMax = lifetimeMax;
	this->velocityMin = velocityMin;
	this->velocityMax = velocityMax;
	this->startSize = startSize;
	this->endSize = endSize;
	this->startColor = startColor;
	this->endColor = endColor;

	// Create particle arrays
	particles = new CPUParticle::Particle[maxParticles];
	firstDead = 0;
	vertexData = new CPUParticleVertex[maxParticles * 4];

	// Creating index buffers
	unsigned int* indexData = new unsigned int[maxParticles * 6];

	for (unsigned int i = 0; i < maxParticles; ++i)
	{
		indexData[i * 6 + 0] = i * 4 + 0;
		indexData[i * 6 + 1] = i * 4 + 1;
		indexData[i * 6 + 2] = i * 4 + 2;

		indexData[i * 6 + 3] = i * 4 + 0;
		indexData[i * 6 + 4] = i * 4 + 2;
		indexData[i * 6 + 5] = i * 4 + 3;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(CPUParticleVertex), vertexData, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxParticles * 6 * sizeof(unsigned int), indexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // Pos
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(CPUParticleVertex), 0);
	glEnableVertexAttribArray(1); // Color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(CPUParticleVertex), ((char*)0) + 16);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] indexData;
}

void ParticleEmitter::Update(float deltaTime, Camera* camera)
{
	emitTimer += deltaTime;
	while (emitTimer > emitRate)
	{
		Emit();
		emitTimer -= emitRate;
	}

	unsigned int quad = 0;

	for (unsigned int i = 0; i < firstDead; i++)
	{
		CPUParticle::Particle* particle = &particles[i];

		particle->lifetime += deltaTime;
		if (particle->lifetime >= particle->lifespan)
		{
			*particle = particles[firstDead - 1];
			firstDead--;
		}
		else
		{
			// Move the particle
			particle->position += particle->velocity * deltaTime;

			// Size the particle
			particle->size = glm::mix(startSize, endSize, particle->lifetime / particle->lifespan);

			// Resize quad and color it
			particle->color = glm::mix(startColor, endColor, particle->lifetime / particle->lifespan);

			float halfSize = particle->size * 0.5f;

			vertexData[quad * 4 + 0].position = vec4(halfSize, halfSize, 0, 1);
			vertexData[quad * 4 + 0].color = particle->color;

			vertexData[quad * 4 + 1].position = vec4(-halfSize, halfSize, 0, 1);
			vertexData[quad * 4 + 1].color = particle->color;

			vertexData[quad * 4 + 2].position = vec4(-halfSize, -halfSize, 0, 1);
			vertexData[quad * 4 + 2].color = particle->color;

			vertexData[quad * 4 + 3].position = vec4(halfSize, -halfSize, 0, 1);
			vertexData[quad * 4 + 3].color = particle->color;

			// Billboard the particle
			vec3 zAxis = glm::normalize(vec3(camera->transform.GetPosition()) - particle->position);
			vec3 xAxis = glm::cross(vec3(camera->transform.GetUp()), zAxis);
			vec3 yAxis = glm::cross(zAxis, xAxis);

			glm::mat4 billboard(vec4(xAxis, 0), vec4(yAxis, 0), vec4(zAxis, 0), vec4(0, 0, 0, 1));

			vertexData[quad * 4 + 0].position = billboard * vertexData[quad * 4 + 0].position + vec4(particle->position, 0);

			vertexData[quad * 4 + 1].position = billboard * vertexData[quad * 4 + 1].position + vec4(particle->position, 0);

			vertexData[quad * 4 + 2].position = billboard * vertexData[quad * 4 + 2].position + vec4(particle->position, 0);

			vertexData[quad * 4 + 3].position = billboard * vertexData[quad * 4 + 3].position + vec4(particle->position, 0);

			++quad;
		}
	}
}

void ParticleEmitter::Draw(ShaderProgram* shaderProgram, Camera* camera)
{
	shaderProgram->Use();
	shaderProgram->SetUniform("viewProjection", camera->GetProjectionMatrix() * camera->GetViewMatrix());

	// Sync living particles with vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, firstDead * 4 * sizeof(CPUParticleVertex), vertexData);

	// Draw particles
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, firstDead * 6, GL_UNSIGNED_INT, 0); 
}

void ParticleEmitter::Emit()
{
	if (firstDead >= maxParticles)
		return;

	CPUParticle::Particle& particle = particles[firstDead++];

	particle.position = transform.GetPosition();

	particle.lifetime = 0;
	particle.lifespan = (rand() / (float)RAND_MAX) * (lifespanMax - lifespanMin) + lifespanMin;

	particle.color = startColor;
	particle.size = startSize;

	float velocity = (rand() / (float)RAND_MAX) * (velocityMax - velocityMin) + velocityMin;

	particle.velocity.x = (rand() / (float)RAND_MAX) * 2 - 1;
	particle.velocity.y = (rand() / (float)RAND_MAX) * 2 - 1;
	particle.velocity.z = (rand() / (float)RAND_MAX) * 2 - 1;
	particle.velocity = glm::normalize(particle.velocity) * velocity;

}