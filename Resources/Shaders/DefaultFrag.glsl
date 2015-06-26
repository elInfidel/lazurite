#version 410

in vec4 vNormal;
in vec4 vPosition;
out vec4 fragColor;

void main()
{
	fragColor = vNormal;
}