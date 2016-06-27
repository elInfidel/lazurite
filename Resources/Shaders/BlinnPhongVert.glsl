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
uniform vec3 lightDir = vec3(0.0f, -1.0f, 0.0f);

out struct vData
{
  vec3 n;
  vec3 l;
  vec3 v;
} vertexData;

void main()
{
	vec4 p = mvMat * position;

	vertexData.n = mat3(mvMat) * normal;
	vertexData.l = lightDir;
	vertexData.v = -p.xyz;

	gl_Position = pMat * p;
}
