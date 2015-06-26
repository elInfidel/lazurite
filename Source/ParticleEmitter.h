#pragma once
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "Vertex.h"
#include "Transform.h"
#include "ShaderProgram.h"
#include "Camera.h"

using glm::vec3;
using glm::vec4;

namespace CPUParticle
{
	struct Particle
	{
		vec3 position;
		vec3 velocity;
		vec4 color;
		float size;
		float lifetime;
		float lifespan;
	};
}

class ParticleEmitter
{
public:
	ParticleEmitter();
	virtual ~ParticleEmitter();

	void Initialize(unsigned int maxParticles, float emitRate, float lifespanMin,
		float lifespanMax, float velocityMin, float velocityMax, float startSize,
		float endSize, const vec4& startColor, const vec4& endColor);

	void Update(float deltaTime, Camera* camera);
	void Draw(ShaderProgram* shaderProgram, Camera* camera);

	Transform transform;

protected:
	void Emit();

	// Emitter data
	CPUParticle::Particle* particles;
	unsigned int firstDead;
	unsigned int maxParticles;

	// Emitter settings
	float emitTimer;
	float emitRate;

	float lifespanMin;
	float lifespanMax;

	float velocityMin;
	float velocityMax;

	float startSize;
	float endSize;

	vec4 startColor;
	vec4 endColor;

	// OpenGL Data
	unsigned int vao, vbo, ibo;
	CPUParticleVertex* vertexData;
};

