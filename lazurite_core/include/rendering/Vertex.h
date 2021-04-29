#pragma once
#include "glm/glm.hpp"

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
	glm::vec4 position;
	glm::vec3 normal;
	glm::vec2 texCoord1;
};