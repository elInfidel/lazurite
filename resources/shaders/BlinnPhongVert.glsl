#version 420 core

layout(location=0) in vec4 position;
layout(location=2) in vec3 normal;

// MVP Matrices
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

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
	vec4 p = view * model * position;

	vertexData.normal = mat3(view * model) * normal;
	vertexData.lightDir = lightPos - p.xyz;
	vertexData.viewDir = -p.xyz;

	gl_Position = projection * p;
}
