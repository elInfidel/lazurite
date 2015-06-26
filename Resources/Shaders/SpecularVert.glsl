#version 410

layout(location=0) in vec4 position;
layout(location=2) in vec4 normal;
out vec4 vPosition;
out vec4 vNormal;

uniform mat4 model = mat4(1.0f);
uniform mat4 viewProjection;

void main()
{ 
	vPosition = position;
	vNormal = normal;
	gl_Position = viewProjection * model * position;
}