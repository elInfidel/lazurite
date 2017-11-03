#version 420 core

layout(location=0) in vec4 position;
layout(location=2) in vec3 normal;

// MVP Matrices
uniform mat4 mMat;
uniform mat4 vMat;
uniform mat4 pMat;
uniform mat4 mvMat;
uniform mat4 mvpMat;

// Light
uniform vec3 lightPos = vec3(0.0f, 10.0f, 0.0f);

out struct vData
{
  vec3 normal;
  vec3 lightDir;
  vec3 viewDir;
} vertexData;

void main()
{
	vec4 p = mvMat * position;

	vertexData.normal = mat3(mvMat) * normal;
	vertexData.lightDir = lightPos - p.xyz;
	vertexData.viewDir = -p.xyz;

	gl_Position = pMat * p;
}
