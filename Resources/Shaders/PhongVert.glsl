#version 410

layout(location=0) in vec4 Position;
layout(location=2) in vec4 Normal;
layout(location=3) in vec4 Tangent;
layout(location=4) in vec4 BiTangent;
layout(location=7) in vec2 TexCoord;

out vec4 vPosition;
out vec2 vTexCoord;
out vec4 vNormal;
out vec4 vTangent;
out vec4 vBiTangent;

uniform mat4 model;
uniform mat4 viewProjection;

void main() 
{
	vPosition = Position;
	vNormal = Normal;
	vTexCoord = TexCoord;
	vTangent = Tangent;
	vBiTangent = BiTangent;
	
	gl_Position = viewProjection * model * Position;
}