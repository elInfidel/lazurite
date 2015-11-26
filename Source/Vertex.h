#pragma once
#include "glm/glm.hpp"

using glm::vec2;
using glm::vec3;
using glm::vec4;

namespace VertexOffset
{
	enum Offsets
	{
		PositionOffset = 0,
		ColorOffset = PositionOffset + sizeof(glm::vec4),
		NormalOffset = ColorOffset + sizeof(glm::vec3),
		TangentOffset = NormalOffset + sizeof(glm::vec3),
		BiTangentOffset = TangentOffset + sizeof(glm::vec3),
		IndicesOffset = BiTangentOffset + sizeof(glm::vec3),
		WeightsOffset = IndicesOffset + sizeof(glm::vec3),
		TexCoord1Offset = WeightsOffset + sizeof(glm::vec3),
		TexCoord2Offset = TexCoord1Offset + sizeof(glm::vec2),
	};
}

struct Vertex
{
	vec4 position = vec4(1.0);
	vec3 color;
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
	vec3 indices;
	vec3 weights;
	vec2 texCoord1;
	vec2 texCoord2;
};

struct CPUParticleVertex
{
	vec4 position;
	vec4 color;
};