#version 420 core

layout(location=0) in vec4 position;
layout(location=2) in vec3 normal;

// MVP Matrices
uniform mat4 mMat;
uniform mat4 vMat;
uniform mat4 pMat;
uniform mat4 mvMat;
uniform mat4 mvpMat;

void main()
{
	vec4 pos = mvpMat * position;
	gl_Position = pos;
}
